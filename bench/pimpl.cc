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
}

BASELINE(PImpl, None, nSample, nLoop) {
  std::vector<bench_pimpl::Direct> a;
  a.reserve(nObj);
  for (auto i=0; i<nObj; i++) {
    celero::DoNotOptimizeAway(a.emplace_back(getInt()));
    celero::DoNotOptimizeAway(static_cast<long>(a[i].get()));
  }
}

BENCHMARK(PImpl, Dynamic, nSample, nLoop) {
  std::vector<bench_pimpl::DynamicPImpl> a;
  a.reserve(nObj);
  for (auto i=0; i<nObj; i++) {
    celero::DoNotOptimizeAway(a.emplace_back(getInt()));
    celero::DoNotOptimizeAway(static_cast<long>(a[i].get()));
  }
}

BENCHMARK(PImpl, Static, nSample, nLoop) {
  std::vector<bench_pimpl::StaticPImpl> a;
  a.reserve(nObj);
  for (auto i=0; i<nObj; i++) {
    celero::DoNotOptimizeAway(a.emplace_back(getInt()));
    celero::DoNotOptimizeAway(static_cast<long>(a[i].get()));
  }
}
