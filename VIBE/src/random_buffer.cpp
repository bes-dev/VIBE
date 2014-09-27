#include "random_buffer.hpp"
#include <opencv2/core/core.hpp>

namespace utils {

RandomBuffer::RandomBuffer(int size, int seed)
{
    init(size, seed);
}

bool RandomBuffer::init(int size, int seed)
{
    size_ = size;
    idx_ = 0;
    buffer_ = std::unique_ptr<int[]>(new int[size_]);
    if(buffer_ != nullptr)
    {
        cv::RNG rng(seed);
        for (int i = 0; i < size_; i++)
        {
            buffer_[i] = rng.uniform(0, std::numeric_limits<int>::max());
        }
        return true;
    }
    return false;
}

}
