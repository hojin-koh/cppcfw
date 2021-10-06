#include "indir.sub.h"
// Include the implementation part
#include <cppcfwv0/hiter-inl.h>

#include <vector>
#include <utility>

typedef std::vector<std::pair<long, int>> VecIndir;
CPPCFWV0_HITER_IMPL(test_hiter::IterVecIndir, int, VecIndir::iterator) {
  using HIterImpl::HIterImpl;
  const int& getRef() const {
    return m_itr->second;
  }
  int& getRef() {
    return m_itr->second;
  }
  const int* getPtr() const {
    return &(m_itr->second);
  }
  int* getPtr() {
    return &(m_itr->second);
  }
};
