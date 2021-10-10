// Simple pimpl object with no parameters
#include "0.sub.h"
#include "2.sub.h"
#include "cpmv.sub.h"
#include <doctest/doctest.h>

#include <utility> // std::move

TEST_CASE("PImpl object without parameters") {
  test_pimpl::Test0 obj;
  CHECK(obj.run() == 500);

  SUBCASE("Mutable") {
    obj.change(900);
    CHECK(obj.run() == 900);
  }
} // end 0 parameter case

TEST_CASE("PImpl const object without parameters") {
  const test_pimpl::Test0 obj;
  CHECK(obj.run() == 500);
} // end 0 parameter const case

TEST_CASE("PImpl object with two parameters") {
  test_pimpl::Test2 obj {100, 300};
  CHECK(obj.run() == 400);
} // end 0 parameter const case


TEST_CASE("Copyable object") {
  test_pimpl::TestCpMv obj {300};

  SUBCASE("Copy constructor") {
    test_pimpl::TestCpMv objCopied(obj);
    CHECK(*objCopied.getPtr() == *obj.getPtr());
    CHECK(objCopied.getPtr() != obj.getPtr());
  }

  SUBCASE("Copy assignment") {
    test_pimpl::TestCpMv objCopied {999};
    objCopied = obj;
    CHECK(*objCopied.getPtr() == *obj.getPtr());
    CHECK(objCopied.getPtr() != obj.getPtr());
  }
}


TEST_CASE("Movable object") {
  const int ans {300};
  test_pimpl::TestCpMv obj {ans};
  const int* pAns = obj.getPtr();

  SUBCASE("Move constructor") {
    test_pimpl::TestCpMv objMoved(std::move(obj));
    CHECK(*objMoved.getPtr() == ans);
    CHECK(objMoved.getPtr() == pAns);
  }

  SUBCASE("Move assignment") {
    test_pimpl::TestCpMv objMoved {999};
    objMoved = std::move(obj);
    CHECK(*objMoved.getPtr() == ans);
    CHECK(objMoved.getPtr() == pAns);
  }

  SUBCASE("Swap") {
    const int ans2 {600};
    test_pimpl::TestCpMv obj2 {ans2};
    const int* pAns2 = obj2.getPtr();
    std::swap(obj, obj2);
    CHECK(*obj.getPtr() == ans2);
    CHECK(*obj2.getPtr() == ans);
    CHECK(obj.getPtr() == pAns2);
    CHECK(obj2.getPtr() == pAns);
  }
}
