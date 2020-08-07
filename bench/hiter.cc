#include <celero/Celero.h>
#include "benchutils.h"

#include <cppcfwv0/hiter.h>
#include <cppcfwv0/hiter-inl.h>

#include <vector>

namespace bench_hiter {
  struct IterVecLong : public ::cppcfwv0::HIter<IterVecLong, long> {
    using HIter::HIter;
  };
}

template <>
struct cppcfwv0::HIter<bench_hiter::IterVecLong, long>::Impl : public ::cppcfwv0::HIterImpl<bench_hiter::IterVecLong, cppcfwv0::HIter<bench_hiter::IterVecLong, long>::Impl, std::vector<long>::iterator> {
  using HIterImpl::HIterImpl;
};
template class ::cppcfwv0::HIter<bench_hiter::IterVecLong, long>;


struct FixtureHIter : public celero::TestFixture {
  using TestFixture::TestFixture;

  std::vector<long> aValue;

  virtual std::vector<celero::TestFixture::ExperimentValue> getExperimentValues() const override {
    std::vector<celero::TestFixture::ExperimentValue> problemSpace;
    problemSpace.push_back(1024);
    problemSpace.push_back(524288);
    return problemSpace;
  }

  void setUp(const celero::TestFixture::ExperimentValue& experimentValue) override {
    this->aValue.reserve(experimentValue.Value);
    std::generate_n(std::back_inserter(this->aValue), experimentValue.Value, getInt);
  }

  void tearDown() override {
    std::vector<long>().swap(this->aValue); // force reallocation
  }

};

BASELINE_F(HIter, Direct, FixtureHIter, 128, 8) {
  auto itrOrigB {this->aValue.begin()}, itrOrigE {this->aValue.end()};
  for (; itrOrigB != itrOrigE; itrOrigB++) {
    celero::DoNotOptimizeAway(static_cast<long>(*itrOrigB));
  }
}

BENCHMARK_F(HIter, HIter, FixtureHIter, 128, 8) {
  auto itrOrigB = this->aValue.begin(), itrOrigE = this->aValue.end();
  bench_hiter::IterVecLong itrB{&itrOrigB}, itrE{&itrOrigE};
  for (; itrB != itrE; ++itrB) {
    celero::DoNotOptimizeAway(static_cast<long>(*itrB));
  }
}

//BENCHMARK_F(FileWrite, fwrite_with_fflush, StdFileFixture, 30, 5000)
//{
//    fwrite(buffer.data(), sizeof(char), buffer.size() * sizeof(char), file);
//      fflush(file);
//}
