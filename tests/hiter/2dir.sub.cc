#include "2dir.sub.h"
// Include the implementation part
#include <cppcfwv0/hiter-inl.h>

#include <vector>

using test_hiter::IterVecInt;

template class ::cppcfwv0::HIter<IterVecInt, int>;
template <>
struct cppcfwv0::HIter<IterVecInt, int>::Impl : public ::cppcfwv0::HIterImpl<IterVecInt, cppcfwv0::HIter<IterVecInt, int>::Impl, std::vector<int>::iterator> {
  using HIterImpl::HIterImpl;
};
