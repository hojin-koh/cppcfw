#pragma once
// Include the header part
#include <cppcfwv0/hiter.h>

#include <utility>

namespace test_hiter {

  struct IterVecInt : public ::cppcfwv0::HIter<IterVecInt, int> {
  };

  struct IterSListStr : public ::cppcfwv0::HIter<IterSListStr, const char*> {
  };

}
