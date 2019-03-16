#include "random.h"

std::random_device Random::rd;
std::mt19937 Random::rng(Random::rd());
std::uniform_real_distribution<double> Random::dist_zero_to_one(0, 1);
std::uniform_real_distribution<double> Random::dist_neg_one_to_one(-1, 1);
