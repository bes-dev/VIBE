#ifndef __VIBE_HPP__
#define __VIBE_HPP__

#include <opencv2/core/core.hpp>
#include <memory>

#define RANDOM_BUFFER_SIZE 65535

namespace vibe
{

class VIBE
{
public:

    VIBE();
    ~VIBE();
    void init(const cv::Mat& img);
    void update(const cv::Mat& img);
    cv::Mat& getMask();

private:
    cv::Size size_;

    int pixel_neighbor_;
    int distance_threshold_;
    int matching_threshold_;
    int update_factor_;

    int samples_;
    int chanels_;
    int pixels_;

    unsigned char *model_;

    cv::Mat mask_;

    unsigned int rng_[RANDOM_BUFFER_SIZE];
    int rng_idx_;

    cv::Vec2i getRndNeighbor(int i, int j);
};

}

#endif /*__VIBE_HPP__*/
