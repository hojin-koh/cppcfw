#pragma once
// Include the header part
#include <cppcfwv0/hiter.h>

namespace test_hiter {

  struct IterVecIndir : public ::cppcfwv0::HIter<IterVecIndir, int> {
    using HIter::HIter;
  };

}
