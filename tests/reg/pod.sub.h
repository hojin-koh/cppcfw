#pragma once
// Include the header part
#include <cppcfwv0/reg.h>

namespace test_reg {

  struct RegLong : public ::cppcfwv0::Reg<RegLong, long> {
    using Reg::Reg;
  };

}
