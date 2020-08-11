// Simple pimpl object with two constructor parameters
#include "const.sub.h"
#include <catch2/catch_test_macros.hpp>

#include <vector>

namespace test_hiter {

SCENARIO("const iterator", "[hiter]") {

  GIVEN("Reading from iterators for vector<int>") {
    const std::vector<int> v {2, 5, 9};

    THEN("It simply works forward") {
      auto itr = v.begin(), itrEnd = v.end();
      IterVecIntConst b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; ++itr, ++b) {
        REQUIRE(*b == *itr);
        REQUIRE(b != e);
      }
      REQUIRE(b == e);
    }

  } // reading from vector


} // end 2-dir iterator

}
