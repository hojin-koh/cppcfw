#pragma once
// Include the header part
#include <cppcfwv0/hiter.h>

namespace test_hiter {

  struct IterVecInt : public ::cppcfwv0::HIter<IterVecInt, int> {
    using HIter::HIter;
  };

}
