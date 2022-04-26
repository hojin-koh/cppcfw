#include "iters.sub.h"
// Include the implementation part
#include <cppcfwv0/hiter-inl.h>

#include <vector>
#include <forward_list>
#include <string>

CPPCFWV0_HITER_IMPL(test_hiter::IterVecInt, std::vector<int>::iterator);

CPPCFWV0_HITER_IMPL_STR(test_hiter::IterSListStr, std::forward_list<std::string>::iterator);
