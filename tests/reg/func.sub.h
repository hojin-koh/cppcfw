#pragma once
// Include the header part
#include <cppcfwv0/reg.h>

namespace test_reg {

  struct RegFunc : public ::cppcfwv0::Reg<RegFunc, int(*)(int)> {
    using Reg::Reg;
  };

}
