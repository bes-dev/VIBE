#ifndef __RANDOM_BUFFER_HPP__
#define __RANDOM_BUFFER_HPP__

#include <memory>
#include <algorithm>
#include <iostream>

namespace utils
{

class RandomBuffer
{
public:

    RandomBuffer(int size = 65535, int seed = 0);
    bool init(int size, int seed = 0);

    inline int next()
    {
        return buffer_[ idx_ = (idx_ + 1) % size_];
    }

    inline int uniform(int min, int max)
    {
        return min + static_cast<float>(buffer_[ idx_ = (idx_ + 1) % size_]) / std::numeric_limits<int>::max() * (max - min);
    }

private:

    std::unique_ptr<int[]> buffer_;
    int size_;
    int idx_;
};

}

#endif /*__RANDOM_BUFFER_HPP__*/
