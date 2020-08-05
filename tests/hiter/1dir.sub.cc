#include "1dir.sub.h"
// Include the implementation part
#include <cppcfwv0/hiter-inl.h>

#include <forward_list>

using test_hiter::IterSListInt;

template class ::cppcfwv0::HIter<IterSListInt, int>;
template <>
struct cppcfwv0::HIter<IterSListInt, int>::Impl : public ::cppcfwv0::HIterImpl<IterSListInt, cppcfwv0::HIter<IterSListInt, int>::Impl, std::forward_list<int>::iterator> {
  using HIterImpl::HIterImpl;
};
