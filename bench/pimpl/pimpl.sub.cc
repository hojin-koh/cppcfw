#include "pimpl.sub.h"
#include <cppcfwv0/pimpl-inl.h>

#include <map>

namespace bench_pimpl {

  struct DynamicPImpl::Impl {
    Impl(long a) { m[a] = a+1; }
    long get() { return m.begin()->first; }
  private:
    std::map<long, long> m;
  };

  DynamicPImpl::DynamicPImpl(long a) : pimpl(a) {}
  long DynamicPImpl::get() { return pimpl->get(); }

}

template class ::cppcfwv0::PImpl<::bench_pimpl::DynamicPImpl::Impl>;
