// Simple pimpl object with no parameters
#include "0.sub.h"
#include <catch2/catch_test_macros.hpp>

SCENARIO("PImpl object without parameters", "[pimpl]") {

  GIVEN("A class with zero-param pimpl") {
    Test0 obj;
    THEN("It simply works") {
      REQUIRE(obj.run() == 179);
    }
  }
} // end 0 parameter scenario
