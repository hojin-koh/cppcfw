#pragma once
// Include the header part
#include <cppcfwv0/hiter.h>

#include <cppcfwv0/strfwd.h>
#include <utility>

namespace test_hiter {

  struct IterVecInt : public ::cppcfwv0::HIter<IterVecInt, int> {
    using HIter::HIter;
  };

  struct IterSListStr : public ::cppcfwv0::HIter<IterSListStr, std::string> {
    using HIter::HIter;
  };

  struct IterMapStrInt : public ::cppcfwv0::HIter<IterMapStrInt, std::pair<const std::string, int>> {
    using HIter::HIter;
  };

}
