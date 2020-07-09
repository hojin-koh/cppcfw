#include "hiter.sub.h"
#include <cppcfwv0/hiter-inl.h>

#include <vector>

CPPCFWV0_HITER_IMPL(bench_hiter::IterVecLong, long, std::vector<long>::iterator) {
  using HIterImpl::HIterImpl;
};
