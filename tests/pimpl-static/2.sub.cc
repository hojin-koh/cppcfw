#include "2.sub.h"
// Include the implementation part
#include <cppcfwv0/pimpl-static-inl.h>

namespace test_pimpl_static {

  // Implement the inner class here
  class Test2::Impl {
  public:
    int a, b;
    Impl(int a, int b) : a(a), b(b) {}
    int run() const {
      return a+b;
    }
  };

  // Be sure to declare ctor/dtors
  Test2::~Test2() = default;
  Test2::Test2(int a, int b) : pimpl(a, b) {}

  int Test2::run() {
    return pimpl->run();
  }

}

// instantiate the template PImplS class who wraps around our implementation class
template class ::cppcfwv0::PImplS<::test_pimpl_static::Test2::Impl, sizeof(int)*2>;
