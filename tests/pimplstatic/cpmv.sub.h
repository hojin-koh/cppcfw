#pragma once
// Include the header part
#include <cppcfwv0/pimpl-static.h>

#include "config.h"

namespace test_pimpl_static {

  class TestCpMv {
  private:
    // This is the intended usage in the header file
    class Impl; cppcfwv0::PImplS<Impl, ::test_pimpl_static::config::sizeVectorInt> pimpl;
  public:
    TestCpMv(int a);

    ~TestCpMv();
    TestCpMv(TestCpMv&& rhs) noexcept;
    TestCpMv& operator=(TestCpMv&& rhs) noexcept;
    TestCpMv(const TestCpMv& rhs);
    TestCpMv& operator=(const TestCpMv& rhs);

    int* getPtr();
  };

}
