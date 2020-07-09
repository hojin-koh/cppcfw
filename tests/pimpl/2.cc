// Simple pimpl object with two constructor parameters
#include "2.sub.h"
#include <catch2/catch_test_macros.hpp>

namespace test_pimpl {

SCENARIO("PImpl object with parameters", "[pimpl]") {

  GIVEN("An object with two-param pimpl") {
    Test2 obj {100, 300};
    THEN("It simply works") {
      REQUIRE(obj.run() == 400);
    }
  }

} // end 2 parameter scenario

}
