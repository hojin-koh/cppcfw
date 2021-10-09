// Simple pimpl object with two constructor parameters
#include "str.sub.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <vector>
#include <string>
#include <map>

using Catch::Matchers::Equals;

namespace test_hiter {

SCENARIO("string iterator", "[hiter]") {

  GIVEN("From iterators for vector<string>") {
    std::vector<std::string> v {"ABC","DEF","QQQ","III"};

    THEN("It can read") {
      auto itr = v.begin(), itrEnd = v.end();
      IterVecStr b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; ++itr, ++b) {
        REQUIRE(*b == *itr);
        REQUIRE(b != e);
      }
      REQUIRE(b == e);
    }

    THEN("It can write") {
      auto itr = v.begin(), itrEnd = v.end();
      IterVecStr b {&itr}, e {&itrEnd};
      for (; itr != itrEnd; ++itr, ++b) {
        *b += "QQ";
        REQUIRE(b != e);
      }
      REQUIRE(b == e);

      REQUIRE(v.at(0) == "ABCQQ");
      REQUIRE(v.at(3) == "IIIQQ");
    }

  } // reading from vector

} // end string iterator

}
