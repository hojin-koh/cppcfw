// Simple pimpl object with two constructor parameters
#include "cached.sub.h"
#include <catch2/catch_test_macros.hpp>

#include <vector>

namespace test_hiter {

SCENARIO("Cached indirect iterator", "[hiter]") {

  GIVEN("Reading from iterators for second half of vector<{long,int}>") {
    const std::vector<std::pair<long,int>> v {{1,9},{2,3},{3,7},{4,199},{5,-375}};

    THEN("It simply works forward") {
      auto itr = v.begin(), itrEnd = v.end();
      IterVecCached b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; ++itr, ++b) {
        REQUIRE(*b == itr->second);
        REQUIRE(b != e);
      }
      REQUIRE(b == e);
    }

    THEN("It simply works backward") {
      auto itr = v.begin(), itrEnd = v.end();
      IterVecCached b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; ++itr, ++b) {}
      --itr; --b;
      REQUIRE(*b == itr->second);
      REQUIRE(b != e);
    }

    THEN("It works for copied iterators") {
      auto itr = v.begin(), itrEnd = v.end();
      IterVecCached b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; ++itr, ++b) {
        auto b2 = b;
        REQUIRE(*b2 == itr->second);
        REQUIRE(b2 != e);
      }
    }

  } // reading from vector

} // end 2-dir iterator

}
