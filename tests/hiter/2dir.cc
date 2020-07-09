// Simple pimpl object with two constructor parameters
#include "2dir.sub.h"
#include <catch2/catch_test_macros.hpp>

#include <vector>

namespace test_hiter {

SCENARIO("2-direction iterator", "[hiter]") {

  GIVEN("Reading from iterators for vector<int>") {
    const std::vector<int> v {9,3,7,199,-375};

    THEN("It simply works forward") {
      auto itr = v.begin(), itrEnd = v.end();
      IterVecInt b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; ++itr, ++b) {
        REQUIRE(*b == *itr);
        REQUIRE(b != e);
      }
      REQUIRE(b == e);
    }

    THEN("It simply works backward") {
      auto itr = v.begin(), itrEnd = v.end();
      IterVecInt b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; ++itr, ++b) {}
      --itr; --b;
      REQUIRE(*b == *itr);
      REQUIRE(b != e);
    }

  } // reading from vector


  GIVEN("Writing to iterators for vector<int>") {
    std::vector<int> v {99, 99, 99};

    THEN("It simply works") {
      auto itr = v.begin(), itrEnd = v.end();
      IterVecInt b {&itr}, e {&itrEnd};
      int content = 1;
      for (; itr != itrEnd; ++itr, ++b, ++content) {
        *b = content;
      }

      REQUIRE(v.size() == 3);
      REQUIRE(v.at(0) == 1);
      REQUIRE(v.at(1) == 2);
      REQUIRE(v.at(2) == 3);
    }

  } // writing to vector

} // end 2-dir iterator

}
