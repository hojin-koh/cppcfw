#pragma once
// Include the header part
#include <cppcfwv0/pimpl-static.h>

namespace test_pimpl_static {

  class Test1 {
  private:
    // This is the intended usage in the header file
    class Impl; cppcfwv0::PImplS<Impl, sizeof(int)> pimpl;
  public:
    Test1(int a);
    ~Test1();
    int run();
  };

}
