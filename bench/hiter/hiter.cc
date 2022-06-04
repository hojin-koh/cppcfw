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
  std::map<std::string, std::string> mValueStr;

  virtual std::vector<celero::TestFixture::ExperimentValue> getExperimentValues() const override {
    std::vector<celero::TestFixture::ExperimentValue> problemSpace;
    problemSpace.push_back(524288);
    return problemSpace;
  }

  void setUp(const celero::TestFixture::ExperimentValue& experimentValue) override {
    this->aValue.reserve(experimentValue.Value);
    std::generate_n(std::back_inserter(this->aValue), experimentValue.Value, getInt);
    std::generate_n(std::back_inserter(this->aValueStr), experimentValue.Value/2, getStr);
    for (const auto& s : this->aValueStr) {
      mValueStr.insert(std::pair(s, s));
    }
  }

  void tearDown() override {
    std::vector<long>().swap(this->aValue); // force reallocation
    std::vector<std::string>().swap(this->aValueStr); // force reallocation
  }

};

namespace {
  const int nSample = 128;
  const int nIteration = 8;
}

BASELINE_F(HIter, Direct, FixtureHIter, nSample, nIteration) {
  auto itrOrigB {this->aValue.begin()}, itrOrigE {this->aValue.end()};
  for (; itrOrigB != itrOrigE; itrOrigB++) {
    celero::DoNotOptimizeAway(static_cast<long>(*itrOrigB));
  }
}

BENCHMARK_F(HIter, HIterPre, FixtureHIter, nSample, nIteration) {
  auto itrOrigB = this->aValue.begin(), itrOrigE = this->aValue.end();
  bench_hiter::IterVecLong itrB{&itrOrigB}, itrE{&itrOrigE};
  for (; itrB != itrE; ++itrB) {
    celero::DoNotOptimizeAway(static_cast<long>(*itrB));
  }
}

BENCHMARK_F(HIter, HIterPost, FixtureHIter, nSample, nIteration) {
  auto itrOrigB = this->aValue.begin(), itrOrigE = this->aValue.end();
  bench_hiter::IterVecLong itrB{&itrOrigB}, itrE{&itrOrigE};
  for (; itrB != itrE; itrB++) {
    celero::DoNotOptimizeAway(static_cast<long>(*itrB));
  }
}


// String

BASELINE_F(HIterStr, Direct, FixtureHIter, nSample, nIteration) {
  auto itrOrigB {this->aValueStr.begin()}, itrOrigE {this->aValueStr.end()};
  for (; itrOrigB != itrOrigE; itrOrigB++) {
    celero::DoNotOptimizeAway(static_cast<const char*>(itrOrigB->c_str()));
  }
}

BENCHMARK_F(HIterStr, HIterPre, FixtureHIter, nSample, nIteration) {
  auto itrOrigB = this->aValueStr.begin(), itrOrigE = this->aValueStr.end();
  bench_hiter::IterVecStr itrB{&itrOrigB}, itrE{&itrOrigE};
  for (; itrB != itrE; ++itrB) {
    celero::DoNotOptimizeAway(static_cast<const char*>(*itrB));
  }
}

BENCHMARK_F(HIterStr, HIterPost, FixtureHIter, nSample, nIteration) {
  auto itrOrigB = this->aValueStr.begin(), itrOrigE = this->aValueStr.end();
  bench_hiter::IterVecStr itrB{&itrOrigB}, itrE{&itrOrigE};
  for (; itrB != itrE; itrB++) {
    celero::DoNotOptimizeAway(static_cast<const char*>(*itrB));
  }
}


// String pair (key only)

BASELINE_F(HIterStrKey, Direct, FixtureHIter, nSample, nIteration) {
  auto itrOrigB {this->mValueStr.begin()}, itrOrigE {this->mValueStr.end()};
  for (; itrOrigB != itrOrigE; itrOrigB++) {
    celero::DoNotOptimizeAway(static_cast<const char*>(itrOrigB->first.c_str()));
  }
}

BENCHMARK_F(HIterStrKey, HIterPre, FixtureHIter, nSample, nIteration) {
  auto itrOrigB = this->mValueStr.begin(), itrOrigE = this->mValueStr.end();
  bench_hiter::IterMapStr itrB{&itrOrigB}, itrE{&itrOrigE};
  for (; itrB != itrE; ++itrB) {
    celero::DoNotOptimizeAway(static_cast<const char*>(*itrB));
  }
}

BENCHMARK_F(HIterStrKey, HIterPost, FixtureHIter, nSample, nIteration) {
  auto itrOrigB = this->mValueStr.begin(), itrOrigE = this->mValueStr.end();
  bench_hiter::IterMapStr itrB{&itrOrigB}, itrE{&itrOrigE};
  for (; itrB != itrE; itrB++) {
    celero::DoNotOptimizeAway(static_cast<const char*>(*itrB));
  }
}
