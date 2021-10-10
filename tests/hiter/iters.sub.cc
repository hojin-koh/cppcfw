#include "iters.sub.h"
// Include the implementation part
#include <cppcfwv0/hiter-inl.h>

#include <vector>
#include <forward_list>
#include <string>
#include <map>

CPPCFWV0_HITER_IMPL(test_hiter::IterVecInt, std::vector<int>::iterator);

CPPCFWV0_HITER_IMPL(test_hiter::IterSListStr, std::forward_list<std::string>::iterator);

using MapStrInt = std::map<std::string, int>;
CPPCFWV0_HITER_IMPL(test_hiter::IterMapStrInt, MapStrInt::iterator);
