#include "pimpl.sub.h"
#include "pimpl.sub-static.h"

#include <celero/Celero.h>
#include "../benchutils.h"

#include <map>
#include <vector>

namespace bench_pimpl {
  struct Direct {
    Direct(long a) { m[a]=a+1; }
    long get() { return m.begin()->first; }
    std::map<long, long> m;
  };
}

namespace {
  const int nObj = 8192;

  template <class Type>
  inline void runBenchPImpl() {
    std::vector<Type> a;
    a.reserve(nObj);
    for (auto i=0; i<nObj; i++) {
      celero::DoNotOptimizeAway(a.emplace_back(getInt()));
      celero::DoNotOptimizeAway(static_cast<long>(a.at(i).get()));
    }
  }
}

BASELINE(PImpl, None, 0, 0) {
  runBenchPImpl<bench_pimpl::Direct>();
}

BENCHMARK(PImpl, Dynamic, 0, 0) {
  runBenchPImpl<bench_pimpl::DynamicPImpl>();
}

BENCHMARK(PImpl, Static, 0, 0) {
  runBenchPImpl<bench_pimpl::StaticPImpl>();
}

namespace {
  template <class Type>
  inline void runBenchPImplCopy() {
    std::vector<bench_pimpl::Direct> a;
    a.reserve(nObj);
    a.emplace_back(getInt());
    for (auto i=1; i<nObj; i++) {
      celero::DoNotOptimizeAway(a.emplace_back(a.at(i-1)));
      celero::DoNotOptimizeAway(static_cast<long>(a.at(i).get()));
    }
  }

  template <class Type>
  inline void runBenchPImplMove() {
    std::vector<bench_pimpl::Direct> a;
    a.reserve(nObj);
    a.emplace_back(getInt());
    for (auto i=1; i<nObj; i++) {
      celero::DoNotOptimizeAway(a.emplace_back(std::move(a.at(i-1))));
      celero::DoNotOptimizeAway(static_cast<long>(a.at(i).get()));
    }
  }
}

BASELINE(PImplCopy, None, 0, 0) {
  runBenchPImplCopy<bench_pimpl::Direct>();
}

BENCHMARK(PImplCopy, Dynamic, 0, 0) {
  runBenchPImplCopy<bench_pimpl::DynamicPImpl>();
}

BENCHMARK(PImplCopy, Static, 0, 0) {
  runBenchPImplCopy<bench_pimpl::StaticPImpl>();
}

BASELINE(PImplMove, None, 0, 0) {
  runBenchPImplMove<bench_pimpl::Direct>();
}

BENCHMARK(PImplMove, Dynamic, 0, 0) {
  runBenchPImplMove<bench_pimpl::DynamicPImpl>();
}

BENCHMARK(PImplMove, Static, 0, 0) {
  runBenchPImplMove<bench_pimpl::StaticPImpl>();
}
