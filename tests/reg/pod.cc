// Simple registry with plain old types
#include "pod.sub.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <stdexcept>
#include <vector>
#include <iostream>

using Catch::Matchers::Equals;

namespace test_reg {

SCENARIO("Simple registry", "[reg]") {

  THEN("It should be default-constructable and movable") {
    RegLong reg;
    RegLong reg2;
    RegLong regMove {std::move(reg)};
    regMove = std::move(reg2);
  }

  GIVEN("Some simple data inside") {
    RegLong reg;
    REQUIRE(reg.size() == 0);
    reg.add("a40", 40, "Description40");
    reg.add("a15", 15);

    THEN("The size and existence check should be correct") {
      REQUIRE(reg.size() == 2);
      REQUIRE(reg.has("a15"));
      REQUIRE(reg.has("a40"));
      REQUIRE(!reg.has("a99"));
      REQUIRE(!reg.has(""));
    }

    THEN("It should throw if we attempt to add the same name again") {
      REQUIRE_THROWS_AS(reg.add("a15", 999), std::out_of_range);
    }

    THEN("We can retrieve that data") {
      REQUIRE(reg.get("a15") == 15);
      REQUIRE(reg.get("a40") == 40);
      REQUIRE_THAT(reg.getDesc("a15"), Equals(""));
      REQUIRE_THAT(reg.getDesc("a40"), Equals("Description40"));
    }

    THEN("We can iterate over registered name") {
      auto itr = reg.begin();
    //  const std::vector<std::string> aAnswer {"a15", "a40"};
    //  int i=0;
    //  for (const auto& name : reg) {
    //    REQUIRE_THAT(name, Equals(aAnswer[i]));
    //    ++i;
    //  }
    }

  } // end simple data

} // end simple registry

}
