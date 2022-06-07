// Simple pimpl object with no parameters
#include "reg.sub.h"
#include <doctest/doctest.h>
#include <rapidcheck.h>

using namespace std::string_literals;

TEST_CASE("Default-constructable and copyable/movable") {
  test_reg::RegPod empty;
  CHECK(empty.size() == 0);
  test_reg::RegPod empty2 {empty};
  test_reg::RegPod empty3 {std::move(empty2)};
  empty2 = empty;
  empty3 = std::move(empty);
}

template <typename TEquiv, typename TReg>
struct TypePair {
  using T1 = TEquiv;
  using T2 = TReg;
};


#define TYPEPAIR_TEST \
  TypePair<std::map<std::string, std::pair<long, std::string>>, test_reg::RegPod>

TEST_CASE_TEMPLATE("Reg content test", T, TYPEPAIR_TEST) {

  using T1 = typename T::T1;
  using T2 = typename T::T2;
  CHECK(rc::check("<"s + typeid(T2).name() + "> Registry test",
    [](T1 data) {
      T2 reg;
      for (const auto& d : data) {
        reg.add(d.first.c_str(), d.second.first, d.second.second.c_str());
      }
      auto itr = data.begin(), itrEnd = data.end();
      auto b {reg.begin()}, e{reg.end()};
      for (; itr != itrEnd; ++itr, ++b) {
        RC_ASSERT(b->first == itr->first);
        RC_ASSERT(*b->second.first == itr->second.first);
        RC_ASSERT(b->second.second == itr->second.second);
        RC_ASSERT(b != e);
      }
      RC_ASSERT(b == e);
  }));

}
