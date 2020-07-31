#include <celero/Celero.h>
#include "benchutils.h"

#include <cppcfwv0/pimpl.h>
#include <cppcfwv0/pimpl-inl.h>
#include <cppcfwv0/pimpl-static.h>
#include <cppcfwv0/pimpl-static-inl.h>

#include <map>
#include <vector>

namespace bench_pimpl {
  struct Direct {
    Direct(long a) { m[a]=a+1; }
    long get() { return m.begin()->first; }
    std::map<long, long> m;
  };

  // Naive version

  struct DynamicPImpl {
    DynamicPImpl(long a);
    long get();
  private:
    struct Impl; cppcfwv0::PImpl<Impl> pimpl;
  };

  struct DynamicPImpl::Impl {
    Impl(long a) { m[a] = a+1; }
    long get() { return m.begin()->first; }
  private:
    std::map<long, long> m;
  };

  DynamicPImpl::DynamicPImpl(long a) : pimpl(a) {}
  long DynamicPImpl::get() { return pimpl->get(); }

  // Static version

  struct StaticPImpl {
    StaticPImpl(long a);
    long get();
  private:
    struct Impl; cppcfwv0::PImplS<Impl, 96> pimpl;
  };

  struct StaticPImpl::Impl {
    Impl(long a) { m[a] = a+1; }
    long get() { return m.begin()->first; }
  private:
    std::map<long, long> m;
  };

  StaticPImpl::StaticPImpl(long a) : pimpl(a) {}
  long StaticPImpl::get() { return pimpl->get(); }
}

namespace {
  const int nSample = 2000;
  const int nLoop = 4;
  const int nObj = 512;

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

BASELINE(PImpl, None, nSample, nLoop) {
  runBenchPImpl<bench_pimpl::Direct>();
}

BENCHMARK(PImpl, Dynamic, nSample, nLoop) {
  runBenchPImpl<bench_pimpl::DynamicPImpl>();
}

BENCHMARK(PImpl, Static, nSample, nLoop) {
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

BASELINE(PImplCopy, None, nSample, nLoop) {
  runBenchPImplCopy<bench_pimpl::Direct>();
}

BENCHMARK(PImplCopy, Dynamic, nSample, nLoop) {
  runBenchPImplCopy<bench_pimpl::DynamicPImpl>();
}

BENCHMARK(PImplCopy, Static, nSample, nLoop) {
  runBenchPImplCopy<bench_pimpl::StaticPImpl>();
}

BASELINE(PImplMove, None, nSample, nLoop) {
  runBenchPImplMove<bench_pimpl::Direct>();
}

BENCHMARK(PImplMove, Dynamic, nSample, nLoop) {
  runBenchPImplMove<bench_pimpl::DynamicPImpl>();
}

BENCHMARK(PImplMove, Static, nSample, nLoop) {
  runBenchPImplMove<bench_pimpl::StaticPImpl>();
}
