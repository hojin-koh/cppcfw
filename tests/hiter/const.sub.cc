#include "const.sub.h"
// Include the implementation part
#include <cppcfwv0/hiter-inl.h>

#include <vector>

using test_hiter::IterVecIntConst;

template class ::cppcfwv0::HIter<IterVecIntConst, const int>;
template <>
struct cppcfwv0::HIter<IterVecIntConst, const int>::Impl : public ::cppcfwv0::HIterImpl<IterVecIntConst, cppcfwv0::HIter<IterVecIntConst, const int>::Impl, std::vector<int>::const_iterator> {
  using HIterImpl::HIterImpl;
};
