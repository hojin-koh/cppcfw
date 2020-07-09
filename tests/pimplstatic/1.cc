// Simple pimpl object with two constructor parameters
#include "1.sub.h"
#include <catch2/catch_test_macros.hpp>

namespace test_pimpl_static {

SCENARIO("Static PImpl object with parameters", "[pimpl-static]") {

  GIVEN("An object with two-param static pimpl") {
    Test1 obj {100};
    THEN("It simply works") {
      REQUIRE(obj.run() == 101);
    }
  }

} // end static scenario

}
