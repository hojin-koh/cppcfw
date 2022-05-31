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

// Automatic testing of iterator behaviour

template <typename TContainer, typename TIterator>
struct TypePair {
  using T1 = TContainer;
  using T2 = TIterator;
};

#define TYPEPAIR_FORWARD \
  TypePair<std::vector<int>, test_hiter::IterVecInt>, \
  TypePair<std::forward_list<std::string>, test_hiter::IterSListStr>


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

TEST_CASE("HIter with pair key specialization") {
  using T1 = std::map<std::string, int>;
  using T2 = test_hiter::IterMapStrInt;
  CHECK(rc::check("<"s + typeid(T2).name() + "> Forward prefix iteration",
    [](T1 data) {
      auto itr = data.begin(), itrEnd = data.end();
      T2 b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; ++itr, ++b) { // Prefix operator
        RC_ASSERT(*b == itr->first);
        RC_ASSERT(b != e);
      }
      RC_ASSERT(b == e);
  }));
}
