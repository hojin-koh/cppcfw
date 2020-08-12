// Simple pimpl object with two constructor parameters
#include "1dir.sub.h"
#include <catch2/catch_test_macros.hpp>

#include <stdexcept>
#include <forward_list>

namespace test_hiter {

SCENARIO("1-direction iterator", "[hiter]") {

  THEN("It should be default-constructable and copyable/movable") {
    IterSListInt empty;
    IterSListInt empty2 {empty};
    IterSListInt empty3 {std::move(empty2)};
    empty2 = empty;
    empty3 = std::move(empty);
  }

  GIVEN("Reading from iterators for forward_list<int>") {
    const std::forward_list<int> s {6, 4, 2};

    THEN("It simply works forward") {
      auto itr = s.begin(), itrEnd = s.end();
      IterSListInt b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; ++itr, ++b) {
        REQUIRE(*b == *itr);
        REQUIRE(b != e);
      }
      REQUIRE(b == e);
    }

    THEN("Postfix increment also works") {
      auto itr = s.begin(), itrEnd = s.end();
      IterSListInt b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; itr++, b++) {
        REQUIRE(*b == *itr);
        REQUIRE(b != e);
      }
      REQUIRE(b == e);
    }

    THEN("It should throw if attempted to decrement the iterator") {
      auto itr = s.begin();
      IterSListInt b {&itr};
      REQUIRE_THROWS_AS(--b, std::domain_error);
    }

    THEN("It should have correct postfix and prefix increment behaviour") {
      auto itr = s.begin();
      IterSListInt b {&itr}, b0 {&itr};
      REQUIRE(b++ == b0);
      auto b1 {b};
      REQUIRE(++b != b1);
    }

  } // reading from forward_list

} // end 1-dir iterator

}
