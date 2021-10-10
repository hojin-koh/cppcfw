#pragma once
// Include the header part
#include "config.h"
#include <cppcfwv0/pimpl-static.h>

namespace test_pimpl_static {

  class Test0 {
  private:
    // This is the intended usage in the header file
    class Impl; cppcfwv0::PImplS<Impl, sizeof(int)> pimpl;
  public:
    Test0();
    ~Test0();
    int run();
    int run() const;
    void change(int value);
  };

}
