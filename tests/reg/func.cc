// Simple registry with function pointers
#include "func.sub.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <stdexcept>
#include <vector>
#include <iostream>

using Catch::Matchers::Equals;

namespace test_reg {

int func1(int a) { return a+15; }
int func2(int a) { return a+30; }

SCENARIO("Registry accepting function pointers", "[reg]") {

  THEN("It should be default-constructable and movable") {
    RegFunc reg;
    RegFunc reg2;
    RegFunc regMove {std::move(reg)};
    regMove = std::move(reg2);
  }

  GIVEN("Some function pointers inside") {
    RegFunc reg;
    REQUIRE(reg.size() == 0);
    reg.add("f1", &func1, "Description1");
    reg.add("f2", &func2);

    THEN("We can retrieve and use the function pointer") {
      REQUIRE(reg.get("f1")(50) == 65);
      REQUIRE(reg.get("f2")(70) == 100);
    }

  } // end function pointer

} // end simple registry

}
