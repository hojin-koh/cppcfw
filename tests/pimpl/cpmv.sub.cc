#include "cpmv.sub.h"
// Include the implementation part
#include <cppcfwv0/pimpl-inl.h>

#include <vector>

namespace test_pimpl {

  class TestCpMv::Impl {
  private:
    std::vector<int> m_vec;
  public:
    // No destructor/copy/move, copy and move can be automatically generated here
    Impl(int a) {
      m_vec.push_back(a);
    }

    int* getPtr() {
      return &m_vec[0];
    }
  };

  TestCpMv::TestCpMv(int a) : pimpl(a) {}

  TestCpMv::~TestCpMv() = default;
  TestCpMv::TestCpMv(TestCpMv&& rhs) noexcept = default;
  TestCpMv& TestCpMv::operator=(TestCpMv&& rhs) noexcept = default;
  TestCpMv::TestCpMv(const TestCpMv& rhs) = default;
  TestCpMv& TestCpMv::operator=(const TestCpMv& rhs) = default;

  int* TestCpMv::getPtr() {
    return pimpl->getPtr();
  }

}

// instantiate the template PImpl class who wraps around our implementation class
template class ::cppcfwv0::PImpl<::test_pimpl::TestCpMv::Impl>;
