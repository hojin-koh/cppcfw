#include "0.sub.h"
// Include the implementation part
#include <cppcfwv0/pimpl-inl.h>

// Implement the inner class here
class Test0::Impl {
public:
  int a {179};
  int run() {
    return a;
  }
};

// Be sure to declare ctor/dtors
Test0::~Test0() = default;
Test0::Test0() = default;

int Test0::run() {
  return pimpl->run();
}

// instantiate the template PImpl class who wraps around our implementation class
template class ::cppcfwv0::PImpl<Test0::Impl>;
