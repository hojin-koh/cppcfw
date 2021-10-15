// Simple pimpl object with no parameters
#include "reg.sub.h"
#include <doctest/doctest.h>
#include <rapidcheck.h>

using namespace std::string_literals;

TEST_CASE("Default-constructable and copyable/movable") {
  test_reg::RegPod empty;
  CHECK(empty.size() == 0);
  test_reg::RegPod empty2 {empty};
  test_reg::RegPod empty3 {std::move(empty2)};
  empty2 = empty;
  empty3 = std::move(empty);
}

template <typename TEquiv, typename TReg>
struct TypePair {
  using T1 = TEquiv;
  using T2 = TReg;
};


#define TYPEPAIR_TEST \
  TypePair<std::map<std::string, std::pair<long, std::string>>, test_reg::RegPod>

//TEST_CASE_TEMPLATE("Reg content test", T, TYPEPAIR_FORWARD) {
//
//  CHECK(rc::check("<"s + typeid(typename T::T2).name() + "> Forward prefix iteration",
//    [](typename T::T1 data) {
//      auto itr = data.begin(), itrEnd = data.end();
//      typename T::T2 b {&itr}, e {&itrEnd};
//      for (; itr != itrEnd; ++itr, ++b) { // Prefix operator
//        RC_ASSERT(*b == *itr);
//        RC_ASSERT(b != e);
//      }
//      RC_ASSERT(b == e);
//  }));
//
//}
