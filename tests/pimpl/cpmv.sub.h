#pragma once
// Include the header part
#include <cppcfwv0/pimpl.h>

namespace test_pimpl {

  class TestCpMv {
  private:
    // This is the intended usage in the header file
    class Impl; cppcfwv0::PImpl<Impl> pimpl;
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
