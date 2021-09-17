#include "1.sub.h"
// Include the implementation part
#include <cppcfwv0/pimpl-static-inl.h>

namespace test_pimpl_static {

  // Implement the inner class here
  class Test1::Impl {
  public:
    int a;
    Impl(int a) : a(a) {}
    int run() const {
      return a+1;
    }
  };

  // Be sure to declare ctor/dtors
  Test1::~Test1() = default;
  Test1::Test1(int a) : pimpl(a) {}

  int Test1::run() {
    return pimpl->run();
  }

}

// instantiate the template PImpl class who wraps around our implementation class
template class ::cppcfwv0::PImplS<::test_pimpl_static::Test1::Impl, sizeof(int)>;
