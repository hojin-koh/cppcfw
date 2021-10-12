#pragma once
// Include the header part
#include <cppcfwv0/reg.h>

#include <utility>

namespace test_reg {

  struct RegPod : public ::cppcfwv0::Reg<RegPod, long> {
    using Reg::Reg;
  };

}
