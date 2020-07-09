#include "pimpl.sub-static.h"
#include <cppcfwv0/pimpl-static-inl.h>

#include <map>

namespace bench_pimpl {

  struct StaticPImpl::Impl {
    Impl(long a) { m[a] = a+1; }
    long get() { return m.begin()->first; }
  private:
    std::map<long, long> m;
  };

  StaticPImpl::StaticPImpl(long a) : pimpl(a) {}
  long StaticPImpl::get() { return pimpl->get(); }

}

template class ::cppcfwv0::PImplS<::bench_pimpl::StaticPImpl::Impl, 96>;
