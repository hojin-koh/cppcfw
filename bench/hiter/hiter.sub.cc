#include "hiter.sub.h"
#include <cppcfwv0/hiter-inl.h>

#include <vector>
#include <string>
#include <map>

CPPCFWV0_HITER_INST(bench_hiter::IterVecLong, std::vector<long>::iterator);

CPPCFWV0_HITERBASE_INST(bench_hiter::IterVecLongIndir, std::vector<long>::iterator);

namespace bench_hiter {
  long const IterVecLongIndir::getValue() const {
    return *pimpl->m_itr;
  }
}

CPPCFWV0_HITER_INST(bench_hiter::IterVecStr, std::vector<std::string>::iterator);

CPPCFWV0_HITERBASE_INST(bench_hiter::IterVecStrIndir, std::vector<std::string>::iterator);

namespace bench_hiter {
  const char* IterVecStrIndir::getValue() const {
    return pimpl->m_itr->c_str();
  }
}
