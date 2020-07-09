#pragma once
// Include the header part
#include <cppcfwv0/hiter.h>

namespace test_hiter {

  struct IterVecCached : public ::cppcfwv0::HIter<IterVecCached, int> {
    using HIter::HIter;
  };

}
