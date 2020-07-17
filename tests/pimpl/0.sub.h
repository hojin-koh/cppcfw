#pragma once
// Include the header part
#include <cppcfwv0/pimpl.h>

namespace test_pimpl {

  class Test0 {
  private:
    // This is the intended usage in the header file
    class Impl; cppcfwv0::PImpl<Impl> pimpl;
  public:
    Test0();
    ~Test0();
    int run();
    int run() const;
  };

}
