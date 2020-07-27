#include <celero/Celero.h>
#include "benchutils.h"

#include <cppcfwv0/pimpl.h>
#include <cppcfwv0/pimpl-inl.h>
#include <cppcfwv0/pimpl-static.h>
#include <cppcfwv0/pimpl-static-inl.h>

#include <map>

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
  const int nLoop = 2048;
}

BASELINE(PImpl, None, nSample, nLoop) {
  bench_pimpl::Direct obj(getInt());
  celero::DoNotOptimizeAway(static_cast<long>(obj.get()));
}

BENCHMARK(PImpl, Dynamic, nSample, nLoop) {
  bench_pimpl::DynamicPImpl obj(getInt());
  celero::DoNotOptimizeAway(static_cast<long>(obj.get()));
}

BENCHMARK(PImpl, Static, nSample, nLoop) {
  bench_pimpl::StaticPImpl obj(getInt());
  celero::DoNotOptimizeAway(static_cast<long>(obj.get()));
}
