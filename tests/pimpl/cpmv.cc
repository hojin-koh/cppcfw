// Simple pimpl object which can be copied or moved
#include "cpmv.sub.h"
#include <catch2/catch_test_macros.hpp>

namespace test_pimpl {

SCENARIO("PImpl object which can be copied or moved", "[pimpl]") {

  GIVEN("A class that should be copyable") {
    TestCpMv obj {300};
    THEN("The pimpl object can be copied with copy constructor") {
      TestCpMv objCopyCtor(obj);
      REQUIRE(*objCopyCtor.getPtr() == *obj.getPtr());
      REQUIRE(objCopyCtor.getPtr() != obj.getPtr());
    }
    THEN("The pimpl object can be copied with copy assign") {
      TestCpMv objCopyAssign {999};
      objCopyAssign = obj;
      REQUIRE(*objCopyAssign.getPtr() == *obj.getPtr());
      REQUIRE(objCopyAssign.getPtr() != obj.getPtr());
    }
  } // end copy test

  GIVEN("A class that should be moveable") {
    const int ans = 300;
    TestCpMv obj {ans};
    const int* pAns = obj.getPtr();
    THEN("The pimpl object can be moved with move constructor") {
      TestCpMv objMoveCtor(std::move(obj));
      REQUIRE(*objMoveCtor.getPtr() == ans);
      REQUIRE(objMoveCtor.getPtr() == pAns);
    }
    THEN("The pimpl object can be moved with move assign") {
      TestCpMv objMoveAssign {999};
      objMoveAssign = std::move(obj);
      REQUIRE(*objMoveAssign.getPtr() == ans);
      REQUIRE(objMoveAssign.getPtr() == pAns);
    }
  } // end move test

  GIVEN("Two objects that should be movable") {
    TestCpMv obj1 {150}, obj2 {900};
    THEN("std::swap works on them") {
      std::swap(obj1, obj2);
      REQUIRE(*obj1.getPtr() == 900);
      REQUIRE(*obj2.getPtr() == 150);
    }
  } // end swap test

} // end copy/move

}
