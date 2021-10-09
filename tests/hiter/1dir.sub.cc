#include "1dir.sub.h"
// Include the implementation part
#include <cppcfwv0/hiter-inl.h>

#include <forward_list>

CPPCFWV0_HITER_IMPL(test_hiter::IterSListInt, int, std::forward_list<int>::iterator);
