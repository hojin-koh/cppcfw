// Simple pimpl object with no parameters
#include "iters.sub.h"
#include <doctest/doctest.h>
#include <rapidcheck.h>

using namespace std::string_literals;

TEST_CASE("Default-constructable and copyable/movable") {
  test_hiter::IterMapFloat empty;
  test_hiter::IterMapFloat empty2 {empty};
  test_hiter::IterMapFloat empty3 {std::move(empty2)};
  empty2 = empty;
  empty3 = std::move(empty);
}

template <typename T1, typename T2>
auto getIteratorChecker(void (*pFunc)(T2&, typename T1::iterator&)) {
  return [pFunc](T1 data) {
    { // Prefix operator
      auto itrAns = data.begin(), itrAnsEnd = data.end();
      T2 itr {&itrAns}, itrEnd {&itrAnsEnd};
      for (; itrAns != itrAnsEnd; ++itrAns, ++itr) {
        pFunc(itr, itrAns);
        RC_ASSERT(itr != itrEnd);
      }
      RC_ASSERT(itr == itrEnd);
    }
    { // Postfix operator
      auto itrAns = data.begin(), itrAnsEnd = data.end();
      T2 itr {&itrAns}, itrEnd {&itrAnsEnd};
      for (; itrAns != itrAnsEnd; itrAns++, itr++) {
        pFunc(itr, itrAns);
        RC_ASSERT(itr != itrEnd);
      }
      RC_ASSERT(itr == itrEnd);
    }
  };
}


TEST_CASE("HIter with indirect access") {
  using T1 = std::map<float, float>;
  using T2 = test_hiter::IterMapFloat;
  CHECK(rc::check("<"s + typeid(T2).name() + "> Forward iteration",
        getIteratorChecker<T1, T2>([](T2& itr, T1::iterator& itrAns) {
          RC_ASSERT((*itr).first == int((*itrAns).first));
          RC_ASSERT((*itr).second == int((*itrAns).second));
          RC_ASSERT(itr->first == int(itrAns->first));
          RC_ASSERT(itr->second == int(itrAns->second));
        })
      ));
}

template <typename TContainer, typename TIterator>
struct TypePair {
  using T1 = TContainer;
  using T2 = TIterator;
};

#define TYPEPAIR_DIRECT \
  TypePair<std::vector<int>, test_hiter::IterVecInt>, \
  TypePair<std::forward_list<std::string>, test_hiter::IterSListStr>

TEST_CASE_TEMPLATE("HIter with direct access", T, TYPEPAIR_DIRECT) {
  using T1 = typename T::T1;
  using T2 = typename T::T2;
  CHECK(rc::check("<"s + typeid(T2).name() + "> Forward iteration",
        getIteratorChecker<T1, T2>([](T2& itr, typename T1::iterator& itrAns) {
          RC_ASSERT(*itr == *itrAns);
        })
      ));
}

TEST_CASE("HIter with direct access for string key") {
  using T1 = std::map<std::string, int>;
  using T2 = test_hiter::IterMapStrInt;
  CHECK(rc::check("<"s + typeid(T2).name() + "> Forward iteration",
        getIteratorChecker<T1, T2>([](T2& itr, T1::iterator& itrAns) {
          RC_ASSERT(*itr == itrAns->first);
        })
      ));
}
