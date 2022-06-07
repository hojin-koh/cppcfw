#pragma once
// Include the header part
#include <cppcfwv0/hiter.h>

#include <utility>

namespace test_hiter {

  struct IterMapFloat : public ::cppcfwv0::HIterBase<IterMapFloat, std::pair<const int, int>> {
    std::pair<const int, int> const getValue() const;
  };

  struct IterVecInt : public ::cppcfwv0::HIter<IterVecInt, int> {};

  struct IterSListStr : public ::cppcfwv0::HIter<IterSListStr, const char*> {};

  struct IterMapStrInt : public ::cppcfwv0::HIter<IterMapStrInt, const char*> {};

}
