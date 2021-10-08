#include "str.sub.h"
// Include the implementation part
#include <cppcfwv0/hiter-inl.h>

#include <vector>
#include <string>
#include <map>

CPPCFWV0_HITER_IMPL(test_hiter::IterVecStr, std::string, std::vector<std::string>::iterator) {
  using HIterImpl::HIterImpl;
};

using typeMapStrInt = std::map<std::string, int>;
CPPCFWV0_HITER_IMPL(test_hiter::IterMapStr, std::string, typeMapStrInt::const_iterator) {
  using HIterImpl::HIterImpl;
};
