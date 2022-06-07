#include "reg.sub.h"

#include <celero/Celero.h>
#include "../benchutils.h"

#include <vector>
#include <string>
#include <map>
#include <cstdlib> // itoa etc.



using bench_reg::RegPod;
using PairAns = std::pair<std::string, std::pair<long, std::string>>;
using MapAns = std::map<std::string, std::pair<long, std::string>>;

struct FixtureReg : public celero::TestFixture {
  using TestFixture::TestFixture;

  MapAns* pmAnswer;
  RegPod* pReg;

  virtual std::vector<celero::TestFixture::ExperimentValue> getExperimentValues() const override {
    std::vector<celero::TestFixture::ExperimentValue> problemSpace;
    problemSpace.push_back(32768);
    return problemSpace;
  }

  void setUp(const celero::TestFixture::ExperimentValue& experimentValue) override {
    pmAnswer = new MapAns;
    pReg = new RegPod;

    for (int i=0; i<experimentValue.Value; i++) {
      PairAns tmp {std::to_string(i), {getInt(), getStr()}};
      pmAnswer->insert(tmp);
      pReg->add(std::to_string(i).c_str(), tmp.second.first, tmp.second.second.c_str());
    }
  }

  void tearDown() override {
    delete pmAnswer;
    delete pReg;
  }

};

BASELINE_F(RegAdd, Ref, FixtureReg, 0, 0) {
  MapAns mBench;
  for (const auto& e : *pmAnswer) {
    celero::DoNotOptimizeAway(mBench.insert({e.first.c_str(), {e.second.first, e.second.second.c_str()}}));
  }
}

BENCHMARK_F(RegAdd, Reg, FixtureReg, 0, 0) {
  RegPod regBench;
  for (const auto& e : *pmAnswer) {
    celero::DoNotOptimizeAway(regBench.add(e.first.c_str(), e.second.first, e.second.second.c_str()));
  }
}


BASELINE_F(RegIter, Ref, FixtureReg, 0, 0) {
  for (const auto& e : *pmAnswer) {
    celero::DoNotOptimizeAway(e.first);
    celero::DoNotOptimizeAway(e.second.first);
    celero::DoNotOptimizeAway(e.second.second);
  }
}

BENCHMARK_F(RegIter, Reg, FixtureReg, 0, 0) {
  for (const auto& e : *pReg) {
    celero::DoNotOptimizeAway(e.first);
    celero::DoNotOptimizeAway(e.second.first);
    celero::DoNotOptimizeAway(e.second.second);
  }
}
