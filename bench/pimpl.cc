#include <celero/Celero.h>
#include "benchutils.h"

#include <cppcfwv0/pimpl.h>
#include <cppcfwv0/pimpl-inl.h>

#include <map>

namespace bench_pimpl {
  struct Direct {
    Direct(long a) { m[a]=a+1; }
    long get() { return m.begin()->first; }
    std::map<long, long> m;
  };

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
}


BASELINE(PImpl, None, 2000, 0) {
  bench_pimpl::Direct obj(getInt());
  celero::DoNotOptimizeAway(static_cast<long>(obj.get()));
}

BENCHMARK(PImpl, Dynamic, 2000, 0) {
  bench_pimpl::DynamicPImpl obj(getInt());
  celero::DoNotOptimizeAway(static_cast<long>(obj.get()));
}
