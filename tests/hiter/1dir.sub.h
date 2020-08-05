#pragma once
// Include the header part
#include <cppcfwv0/hiter.h>

namespace test_hiter {

  struct IterSListInt : public ::cppcfwv0::HIter<IterSListInt, int> {
    using HIter::HIter;
  };

}
