#pragma once
// Include the header part
#include <cppcfwv0/pimpl.h>

namespace test_pimpl {

  class Test2 {
  private:
    // This is the intended usage in the header file
    class Impl; cppcfwv0::PImpl<Impl> pimpl;
  public:
    Test2(int a, int b);
    ~Test2();
    int run();
  };

}
