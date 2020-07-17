// Simple pimpl object with no parameters
#include "0.sub.h"
#include <catch2/catch_test_macros.hpp>

namespace test_pimpl {

SCENARIO("PImpl object without parameters", "[pimpl]") {

  GIVEN("An object with zero-param pimpl") {
    Test0 obj;
    THEN("It simply works") {
      REQUIRE(obj.run() == 500);
    }
  }

  GIVEN("An const object") {
    const Test0 obj;
    THEN("The qualifier isn't discarded") {
      REQUIRE(obj.run() == 500);
    }
  }

} // end 0 parameter scenario

}
