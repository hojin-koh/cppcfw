// Simple pimpl object with no parameters
#include "iters.sub.h"
#include <doctest/doctest.h>
#include <rapidcheck.h>

using namespace std::string_literals;

TEST_CASE("Default-constructable and copyable/movable") {
  test_hiter::IterVecInt empty;
  test_hiter::IterVecInt empty2 {empty};
  test_hiter::IterVecInt empty3 {std::move(empty2)};
  empty2 = empty;
  empty3 = std::move(empty);
}

template <typename TContainer, typename TIterator>
struct TypePair {
  using T1 = TContainer;
  using T2 = TIterator;
};


#define TYPEPAIR_FORWARD \
  TypePair<std::vector<int>, test_hiter::IterVecInt>, \
  TypePair<std::forward_list<std::string>, test_hiter::IterSListStr>, \
  TypePair<std::map<std::string, int>, test_hiter::IterMapStrInt>

TEST_CASE_TEMPLATE("HIter forward iteration", T, TYPEPAIR_FORWARD) {

  CHECK(rc::check("<"s + typeid(typename T::T2).name() + "> Forward prefix iteration",
    [](typename T::T1 data) {
      auto itr = data.begin(), itrEnd = data.end();
      typename T::T2 b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; ++itr, ++b) { // Prefix operator
        RC_ASSERT(*b == *itr);
        RC_ASSERT(b != e);
      }
      RC_ASSERT(b == e);
  }));

  CHECK(rc::check("<"s + typeid(typename T::T2).name() + "> Forward postfix iteration",
    [](typename T::T1 data) {
      auto itr = data.begin(), itrEnd = data.end();
      typename T::T2 b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; itr++, b++) { // Postfix operator
        RC_ASSERT(*b == *itr);
        RC_ASSERT(b != e);
      }
      RC_ASSERT(b == e);
  }));
}


#define TYPEPAIR_WRITE \
  TypePair<std::vector<int>, test_hiter::IterVecInt>, \
  TypePair<std::forward_list<std::string>, test_hiter::IterSListStr>


TEST_CASE_TEMPLATE("HIter write", T, TYPEPAIR_WRITE) {

  CHECK(rc::check("<"s + typeid(typename T::T2).name() + "> Write",
    [](typename T::T1 data) {
      auto itr = data.begin(), itrEnd = data.end();
      typename T::T2 b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; ++itr, ++b) {
        const auto valNew = *rc::gen::arbitrary<typename T::T1::iterator::value_type>();
        *b = valNew;
        RC_ASSERT(*itr == valNew);
      }
  }));

}
