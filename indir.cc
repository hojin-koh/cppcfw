// Simple pimpl object with two constructor parameters
#include "indir.sub.h"
#include <catch2/catch_test_macros.hpp>

#include <vector>

namespace test_hiter {

SCENARIO("Indirect iterator", "[hiter]") {

  GIVEN("Reading from iterators for second half of vector<{long,int}>") {
    const std::vector<std::pair<long,int>> v {{1,9},{2,3},{3,7},{4,199},{5,-375}};

    THEN("It simply works forward") {
      auto itr = v.begin(), itrEnd = v.end();
      IterVecIndir b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; ++itr, ++b) {
        REQUIRE(*b == itr->second);
        REQUIRE(b != e);
      }
      REQUIRE(b == e);
    }

    THEN("It simply works backward") {
      auto itr = v.begin(), itrEnd = v.end();
      IterVecIndir b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; ++itr, ++b) {}
      --itr; --b;
      REQUIRE(*b == itr->second);
      REQUIRE(b != e);
    }

  } // reading from vector


  GIVEN("Writing to iterators for vector<int>") {
    std::vector<std::pair<long,int>> v {{91,99}, {92,99}, {93,99}};

    THEN("It simply works") {
      auto itr = v.begin(), itrEnd = v.end();
      IterVecIndir b {&itr}, e {&itrEnd};
      int content = 1;
      for (; itr != itrEnd; ++itr, ++b, ++content) {
        *b = content;
      }
      //*b = content;

      REQUIRE(v.size() == 3);
      REQUIRE(v.at(0).first == 91);
      REQUIRE(v.at(1).first == 92);
      REQUIRE(v.at(2).first == 93);
      REQUIRE(v.at(0).second == 1);
      REQUIRE(v.at(1).second == 2);
      REQUIRE(v.at(2).second == 3);
    }

  } // writing to vector

} // end 2-dir iterator

}
