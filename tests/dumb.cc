// A dumb test file
#include <catch2/catch_test_macros.hpp>

SCENARIO("123", "[123]") {

  GIVEN("A test") {
    THEN("It should pass!") {
      REQUIRE(1 == 1);
    }
  }

} // end straightforward test


