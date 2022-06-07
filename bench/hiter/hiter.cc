#include "hiter.sub.h"
//#include "hiter-indir.sub.h"
//#include "hiter-cached.sub.h"

#include <celero/Celero.h>
#include "../benchutils.h"

#include <vector>
#include <string>
#include <map>

struct FixtureHIter : public celero::TestFixture {
  using TestFixture::TestFixture;

  std::vector<long> aValue;
  std::vector<std::string> aValueStr;

  virtual std::vector<celero::TestFixture::ExperimentValue> getExperimentValues() const override {
    std::vector<celero::TestFixture::ExperimentValue> problemSpace;
    problemSpace.push_back(131072);
    return problemSpace;
  }

  void setUp(const celero::TestFixture::ExperimentValue& experimentValue) override {
    this->aValue.reserve(experimentValue.Value);
    std::generate_n(std::back_inserter(this->aValue), experimentValue.Value, getInt);
    std::generate_n(std::back_inserter(this->aValueStr), experimentValue.Value, getStr);
  }

  void tearDown() override {
    std::vector<long>().swap(this->aValue); // force reallocation
    std::vector<std::string>().swap(this->aValueStr); // force reallocation
  }

};


BASELINE_F(HIter, Direct, FixtureHIter, 0, 0) {
  auto itrOrigB {this->aValue.begin()}, itrOrigE {this->aValue.end()};
  for (; itrOrigB != itrOrigE; ++itrOrigB) {
    celero::DoNotOptimizeAway(static_cast<long>(*itrOrigB));
  }
}

BENCHMARK_F(HIter, HIter, FixtureHIter, 0, 0) {
  auto itrOrigB = this->aValue.begin(), itrOrigE = this->aValue.end();
  bench_hiter::IterVecLong itrB{&itrOrigB}, itrE{&itrOrigE};
  for (; itrB != itrE; ++itrB) {
    celero::DoNotOptimizeAway(static_cast<long>(*itrB));
  }
}

BENCHMARK_F(HIter, Indirect, FixtureHIter, 0, 0) {
  auto itrOrigB = this->aValue.begin(), itrOrigE = this->aValue.end();
  bench_hiter::IterVecLongIndir itrB{&itrOrigB}, itrE{&itrOrigE};
  for (; itrB != itrE; ++itrB) {
    celero::DoNotOptimizeAway(static_cast<long>(*itrB));
  }
}


// String

BASELINE_F(HIterStr, Direct, FixtureHIter, 0, 0) {
  auto itrOrigB {this->aValueStr.begin()}, itrOrigE {this->aValueStr.end()};
  for (; itrOrigB != itrOrigE; ++itrOrigB) {
    celero::DoNotOptimizeAway(static_cast<const char*>(itrOrigB->c_str()));
  }
}

BENCHMARK_F(HIterStr, HIter, FixtureHIter, 0, 0) {
  auto itrOrigB = this->aValueStr.begin(), itrOrigE = this->aValueStr.end();
  bench_hiter::IterVecStr itrB{&itrOrigB}, itrE{&itrOrigE};
  for (; itrB != itrE; ++itrB) {
    celero::DoNotOptimizeAway(static_cast<const char*>(*itrB));
  }
}

BENCHMARK_F(HIterStr, Indirect, FixtureHIter, 0, 0) {
  auto itrOrigB = this->aValueStr.begin(), itrOrigE = this->aValueStr.end();
  bench_hiter::IterVecStrIndir itrB{&itrOrigB}, itrE{&itrOrigE};
  for (; itrB != itrE; ++itrB) {
    celero::DoNotOptimizeAway(static_cast<const char*>(*itrB));
  }
}
