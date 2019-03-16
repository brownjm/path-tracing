#ifndef RANDOM_H_
#define RANDOM_H_

#include <random>

class Random {
public:
  static double zero_to_one() {    // [0, 1)
    return dist_zero_to_one(rng);
  }

  static double neg_one_to_one() { // [-1, 1)
    return dist_neg_one_to_one(rng);
  }

private:
  static std::random_device rd;
  static std::mt19937 rng;
  static std::uniform_real_distribution<double> dist_zero_to_one;
  static std::uniform_real_distribution<double> dist_neg_one_to_one;

};


#endif // RANDOM_H_
