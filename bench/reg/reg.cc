#include "reg.sub.h"

#include <celero/Celero.h>
#include "../benchutils.h"

#include <vector>
#include <map>
#include <string>
#include <memory>

namespace {
  const int nSample = 128;
  const int nIteration = 8;
}

struct FixtureRegAdd : public celero::TestFixture {
  using TestFixture::TestFixture;

  std::vector<long> aValue;
  std::vector<std::string> aStr;

  virtual std::vector<celero::TestFixture::ExperimentValue> getExperimentValues() const override {
    std::vector<celero::TestFixture::ExperimentValue> problemSpace;
    problemSpace.push_back(8192);
    return problemSpace;
  }

  void setUp(const celero::TestFixture::ExperimentValue& experimentValue) override {
    this->aValue.reserve(experimentValue.Value);
    this->aStr.reserve(experimentValue.Value);
    std::generate_n(std::back_inserter(this->aValue), experimentValue.Value, getInt);
    for (int i=0; i<experimentValue.Value; i++) {
      this->aStr.push_back(std::to_string(this->aValue.at(i)) + '_' + std::to_string(i));
    }
  }

  void tearDown() override {
    std::vector<long>().swap(this->aValue); // force reallocation
    std::vector<std::string>().swap(this->aStr);
  }

};

BASELINE_F(RegAdd, Direct, FixtureRegAdd, nSample, nIteration) {
  std::map<std::string, std::pair<long, std::string>> mBench;
  for (int i=0; i<this->aValue.size(); i++) {
    celero::DoNotOptimizeAway(
        mBench.insert({this->aStr.at(i), {this->aValue.at(i), this->aStr.at(i)}})
        );
  }
}

BENCHMARK_F(RegAdd, Reg, FixtureRegAdd, nSample, nIteration) {
  bench_reg::RegLong reg;
  for (int i=0; i<this->aValue.size(); i++) {
    celero::DoNotOptimizeAway([&](){
        reg.add(this->aStr.at(i).c_str(), this->aValue.at(i), this->aStr.at(i).c_str());
        return 0;
        }());
  }
}

BENCHMARK_F(RegAdd, RegLiteral, FixtureRegAdd, nSample, nIteration) {
  bench_reg::RegLong reg;
  for (int i=0; i<this->aValue.size(); i++) {
    celero::DoNotOptimizeAway([&](){
        reg.addLiteral(this->aStr.at(i).c_str(), this->aValue.at(i), this->aStr.at(i).c_str());
        return 0;
        }());
  }
}




struct FixtureRegQuery : public celero::TestFixture {
  using TestFixture::TestFixture;

  std::vector<long> aValue;
  std::vector<std::string> aStr;
  std::map<std::string, std::pair<long, std::string>> mBench;
  std::unique_ptr<bench_reg::RegLong> pReg {new bench_reg::RegLong};

  virtual std::vector<celero::TestFixture::ExperimentValue> getExperimentValues() const override {
    std::vector<celero::TestFixture::ExperimentValue> problemSpace;
    problemSpace.push_back(8192);
    return problemSpace;
  }

  void setUp(const celero::TestFixture::ExperimentValue& experimentValue) override {
    this->aValue.reserve(experimentValue.Value);
    this->aStr.reserve(experimentValue.Value);
    std::generate_n(std::back_inserter(this->aValue), experimentValue.Value, getInt);
    for (int i=0; i<experimentValue.Value; i++) {
      const std::string key {std::to_string(this->aValue.at(i)) + '_' + std::to_string(i)};
      this->aStr.push_back(key);
      this->mBench.insert({key, {this->aValue.at(i), key}});
      this->pReg->add(key.c_str(), this->aValue.at(i), key.c_str());
    }
  }

  void tearDown() override {
    std::vector<long>().swap(this->aValue); // force reallocation
    std::vector<std::string>().swap(this->aStr);
    std::map<std::string, std::pair<long, std::string>>().swap(this->mBench);
    this->pReg.reset();
  }

};

BASELINE_F(RegQuery, Direct, FixtureRegQuery, nSample, nIteration) {
  for (const auto& str : this->aStr) {
    celero::DoNotOptimizeAway(
        mBench.at(str)
        );
  }
}

BENCHMARK_F(RegQuery, Reg, FixtureRegQuery, nSample, nIteration) {
  const auto& reg = *(this->pReg);
  for (const auto& pStr : reg) {
    celero::DoNotOptimizeAway(
        reg.get(pStr)
        );
  }
}
