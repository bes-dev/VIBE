#include "gtest/gtest.h"
#include "random_buffer.hpp"

TEST(RandomBuffer, init)
{
    utils::RandomBuffer rng;
    ASSERT_TRUE(rng.init(65535));
}
