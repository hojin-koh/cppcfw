#pragma once
// Include the header part
#include <cppcfwv0/hiter.h>

namespace test_hiter {

  struct IterVecIntConst : public ::cppcfwv0::HIter<IterVecIntConst, const int> {};

}
