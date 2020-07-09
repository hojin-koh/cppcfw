#include "hiter.sub.h"
#include "hiter-indir.sub.h"
#include "hiter-cached.sub.h"

#include <celero/Celero.h>
#include "../benchutils.h"

#include <vector>

struct FixtureHIter : public celero::TestFixture {
  using TestFixture::TestFixture;

  std::vector<long> aValue;
  std::vector<std::pair<int, long>> aValuePair;

  virtual std::vector<celero::TestFixture::ExperimentValue> getExperimentValues() const override {
    std::vector<celero::TestFixture::ExperimentValue> problemSpace;
    problemSpace.push_back(524288);
    return problemSpace;
  }

  void setUp(const celero::TestFixture::ExperimentValue& experimentValue) override {
    this->aValue.reserve(experimentValue.Value);
    std::generate_n(std::back_inserter(this->aValue), experimentValue.Value, getInt);
    for (const auto& n : this->aValue) {
      aValuePair.push_back({n, n});
    }
  }

  void tearDown() override {
    std::vector<long>().swap(this->aValue); // force reallocation
    std::vector<std::pair<int, long>>().swap(this->aValuePair);
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

BENCHMARK_F(HIter, HIterIndirPre, FixtureHIter, nSample, nIteration) {
  auto itrOrigB = this->aValuePair.begin(), itrOrigE = this->aValuePair.end();
  bench_hiter::IterVecLongIndir itrB{&itrOrigB}, itrE{&itrOrigE};
  for (; itrB != itrE; ++itrB) {
    celero::DoNotOptimizeAway(static_cast<long>(*itrB));
  }
}

BENCHMARK_F(HIter, HIterIndirPost, FixtureHIter, nSample, nIteration) {
  auto itrOrigB = this->aValuePair.begin(), itrOrigE = this->aValuePair.end();
  bench_hiter::IterVecLongIndir itrB{&itrOrigB}, itrE{&itrOrigE};
  for (; itrB != itrE; itrB++) {
    celero::DoNotOptimizeAway(static_cast<long>(*itrB));
  }
}

BENCHMARK_F(HIter, HIterCachedPre, FixtureHIter, nSample, nIteration) {
  auto itrOrigB = this->aValuePair.begin(), itrOrigE = this->aValuePair.end();
  bench_hiter::IterVecLongCached itrB{&itrOrigB}, itrE{&itrOrigE};
  for (; itrB != itrE; ++itrB) {
    celero::DoNotOptimizeAway(static_cast<long>(*itrB));
  }
}

BENCHMARK_F(HIter, HIterCachedPost, FixtureHIter, nSample, nIteration) {
  auto itrOrigB = this->aValuePair.begin(), itrOrigE = this->aValuePair.end();
  bench_hiter::IterVecLongCached itrB{&itrOrigB}, itrE{&itrOrigE};
  for (; itrB != itrE; itrB++) {
    celero::DoNotOptimizeAway(static_cast<long>(*itrB));
  }
}
