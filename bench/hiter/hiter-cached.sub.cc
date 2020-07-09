#include "hiter-cached.sub.h"
#include <cppcfwv0/hiter-inl.h>

#include <vector>

typedef std::vector<std::pair<int, long>> VecCached;
CPPCFWV0_HITER_IMPL(bench_hiter::IterVecLongCached, long, VecCached::iterator) {
  using HIterImpl::HIterImpl;
  void invalidateCache() {
    m_isCacheValid = false;
  }
  void ensureCache() const {
    if (!m_isCacheValid) {
      m_cache = m_itr->second;
      m_isCacheValid = true;
    }
  }
  const long& getRef() const {
    ensureCache();
    return m_cache;
  }
  long& getRef() {
    ensureCache();
    return m_cache;
  }
  const long* getPtr() const {
    ensureCache();
    return &m_cache;
  }
  long* getPtr() {
    ensureCache();
    return &m_cache;
  }
private:
  mutable bool m_isCacheValid {false};
  mutable long m_cache;
};
