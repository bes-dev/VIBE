#include "vibe.hpp"

#include <random>

#include <opencv2/core/core.hpp>

namespace vibe
{

VIBE::VIBE()
{
    samples_ = 20;
    pixel_neighbor_ = 1;
    distance_threshold_ = 20;
    matching_threshold_ = 2;
    update_factor_ = 16;
    model_ = nullptr;

    rng_idx_ = 0;
    srand(0);
    for (int i = 0; i < RANDOM_BUFFER_SIZE; i ++)
    {
        rng_[i] = rand();
    }
}

VIBE::~VIBE()
{
    if (model_ != nullptr)
    {
        delete[] model_;
    }
}

cv::Vec2i VIBE::getRndNeighbor(int i, int j)
{
    int rnd = rng_[rng_idx_ = ( rng_idx_ + 1 ) % RANDOM_BUFFER_SIZE] % 8;
    int start_i = i - pixel_neighbor_;
    int start_j = j - pixel_neighbor_;
    int area = pixel_neighbor_ * 2 + 1;
    int position_i = rnd / area;
    int position_j = rnd % area;
    int cur_i = std::max(std::min(start_i + position_i, size_.height - 1), 0);
    int cur_j = std::max(std::min(start_j + position_j, size_.width - 1), 0);
    return cv::Vec2i(cur_i, cur_j);
}

void VIBE::init(const cv::Mat &img)
{
    size_ = img.size();
    chanels_ = img.channels();
    pixels_ = size_.width * size_.height;
    model_ = new unsigned char[chanels_ * samples_ * pixels_];
    mask_ = cv::Mat(size_, CV_8UC1, cv::Scalar::all(0));

    unsigned char* image = img.data;
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            for (int c = 0; c < chanels_; c++)
            {
                model_[chanels_ * samples_ * size_.width * i + chanels_ * samples_ * j + c] = image[size_.width * i + chanels_ * j + c];
            }
            for (int s = 1; s < samples_; s++)
            {
                cv::Vec2i rnd_pos = getRndNeighbor(i, j);
                int img_idx = size_.width * rnd_pos[0] + chanels_ * rnd_pos[1];
                int model_idx = chanels_ * samples_ * size_.width * i + chanels_ * samples_ * j + chanels_ * s;
                for (int c = 0; c < chanels_; c ++)
                {
                    model_[model_idx + c] = image[img_idx + c];
                }
            }
        }
    }
}

void VIBE::update(const cv::Mat& img)
{
    unsigned char *img_ptr = img.data;
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            bool flag = false;
            int matching_counter = 0;
            int img_idx = size_.width * i + chanels_ * j;
            for (int s = 0; s < samples_; s ++)
            {
                int model_idx = chanels_ * samples_ * size_.width * i + chanels_ * samples_ * j + chanels_ * s;
                for (int c = 0; c < chanels_; c ++)
                {
                    if (std::abs(img_ptr[img_idx + c] - model_[model_idx + c]) < distance_threshold_)
                    {
                        matching_counter++;
                    }
                }
                if ( matching_counter > matching_threshold_)
                {
                    flag = true;
                    break;
                }
            }

            if (flag)
            {
                mask_.data[size_.width * i + j] = 0;
                if(rng_[ rng_idx_ = ( rng_idx_ + 1 ) % RANDOM_BUFFER_SIZE] % update_factor_)
                {
                    int sample = rng_[ rng_idx_ = ( rng_idx_ + 1 ) % RANDOM_BUFFER_SIZE] % samples_;
                            int model_idx = chanels_ * samples_ * size_.width * i + chanels_ * samples_ * j + chanels_ * sample;
                            for (int c = 0; c < chanels_; c ++)
                    {
                        model_[model_idx + c] = img_ptr[img_idx + c];
                    }

                    cv::Vec2i rnd_pos = getRndNeighbor(i, j);
                    sample = rng_[rng_idx_ = ( rng_idx_ + 1) % RANDOM_BUFFER_SIZE] % samples_;
                            model_idx = chanels_ * samples_ * size_.width * rnd_pos[0] + chanels_ * samples_ * rnd_pos[1] + chanels_ * sample;
                            for (int c = 0; c < chanels_; c ++)
                    {
                        model_[model_idx + c] = img_ptr[img_idx + c];
                    }

                }
            }
            else
            {
                mask_.data[size_.width * i + j] = 255;
            }
        }
    }
}

cv::Mat& VIBE::getMask()
{
    return mask_;
}


}
