#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

#include "tbb/tbb.h"

void SerialApplySqrt(std::vector<int>& a) {
  for (size_t i = 0; i < a.size(); ++i) {
    a[i] = std::sqrt(a[i]);
  }
}

class ApplySqrt {
  std::vector<int> *const my_a;
  std::vector<float> *const my_b;

public:

  void operator()(const tbb::blocked_range<size_t>& r) const {
    for (size_t i = r.begin(); i < r.end(); ++i) {
      (*my_b)[i] = std::sqrt((*my_a)[i]);
    }
  }

  ApplySqrt(std::vector<int> *const a,
      std::vector<float> *const b) : my_a(a), my_b(b) {};
};


int main(int argc, char** argv) {

  // Explicit number of threads
  tbb::task_scheduler_init init(tbb::task_scheduler_init::default_num_threads());

  std::cout << "Initializing numbers..." << std::endl;
  const int kMax = 1000000000;
  std::vector<int> nums;
  std::vector<float> roots;
  std::vector<int>* p_a = &nums;
  std::vector<float>* p_b = &roots;
  nums.reserve(kMax);
  roots.reserve(kMax);
  for(int i = 0; i < kMax; ++i) {
    nums.push_back(i);
  }

  std::cout << "done" << std::endl;

  tbb::parallel_for(
      tbb::blocked_range<size_t>(0, nums.size()),
      ApplySqrt(p_a, p_b));


  // for(int i = 0; i < kMax; ++i) {
  //   std::cout << "Sqrt of " << nums[i] << " is " << roots[i] << std::endl;
  // }

  return 0;
}
