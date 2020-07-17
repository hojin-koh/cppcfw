#include "0.sub.h"
// Include the implementation part
#include <cppcfwv0/pimpl-inl.h>

namespace test_pimpl {

  // Implement the inner class here
  class Test0::Impl {
  public:
    int a {500};
    int run() const {
      return a;
    }
  };

  // Be sure to declare ctor/dtors
  Test0::~Test0() = default;
  Test0::Test0() = default;

  int Test0::run() {
    return pimpl->run();
  }

  int Test0::run() const {
    return pimpl->run();
  }

}

// instantiate the template PImpl class who wraps around our implementation class
template class ::cppcfwv0::PImpl<::test_pimpl::Test0::Impl>;
