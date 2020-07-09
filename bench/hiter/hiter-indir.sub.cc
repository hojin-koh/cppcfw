#include "hiter-indir.sub.h"
#include <cppcfwv0/hiter-inl.h>

#include <vector>

typedef std::vector<std::pair<int, long>> VecIndir;
CPPCFWV0_HITER_IMPL(bench_hiter::IterVecLongIndir, long, VecIndir::iterator) {
  using HIterImpl::HIterImpl;
  const long& getRef() const {
    return m_itr->second;
  }
  long& getRef() {
    return m_itr->second;
  }
  const long* getPtr() const {
    return &(m_itr->second);
  }
  long* getPtr() {
    return &(m_itr->second);
  }
};
