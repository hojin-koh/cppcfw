#include "cached.sub.h"
// Include the implementation part
#include <cppcfwv0/hiter-inl.h>

#include <vector>
#include <utility>

typedef std::vector<std::pair<long, int>> VecCached;
CPPCFWV0_HITER_IMPL(test_hiter::IterVecCached, int, VecCached::iterator) {
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
  const int& getRef() const {
    ensureCache();
    return m_cache;
  }
  int& getRef() {
    ensureCache();
    return m_cache;
  }
  const int* getPtr() const {
    ensureCache();
    return &m_cache;
  }
  int* getPtr() {
    ensureCache();
    return &m_cache;
  }
private:
  mutable bool m_isCacheValid {false};
  mutable int m_cache;
};
