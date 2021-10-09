#include "pod.sub.h"
// Include the implementation part
#include <cppcfwv0/reg-inl.h>

//CPPCFWV0_REG_IMPL(test_reg::RegLong, long);

  using RegParent = cppcfwv0::Reg<test_reg::RegLong, long>;
  using ContainerInner = std::map<std::string, std::pair<long, std::string>>;
  template <>
  struct RegParent::Impl : public ::cppcfwv0::RegImpl<test_reg::RegLong, RegParent::Impl, long> {};
  //CPPCFWV0_HITER_IMPL(RegParent::Iter, ContainerInner::iterator::value_type, ContainerInner::iterator);
  template struct cppcfwv0::Reg<test_reg::RegLong, long>;
