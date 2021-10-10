#pragma once
// Include the header part
#include <cppcfwv0/pimpl-static.h>

namespace test_pimpl_static {

  class Test2 {
  private:
    // This is the intended usage in the header file
    class Impl; cppcfwv0::PImplS<Impl, sizeof(int)*2> pimpl;
  public:
    Test2(int a, int b);
    ~Test2();
    int run();
  };

}
