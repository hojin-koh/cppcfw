#include "iters.sub.h"
// Include the implementation part
#include <cppcfwv0/hiter-inl.h>

#include <vector>
#include <forward_list>
#include <string>
#include <map>

using MapFloat = std::map<float, float>;
CPPCFWV0_HITERBASE_INST(test_hiter::IterMapFloat, MapFloat::iterator);

namespace test_hiter {
  std::pair<const int, int> const IterMapFloat::getValue() const {
    const auto& itr {pimpl->m_itr};
    return std::pair(itr->first, itr->second);
  }
}

CPPCFWV0_HITER_INST(test_hiter::IterVecInt, std::vector<int>::iterator);

CPPCFWV0_HITER_INST(test_hiter::IterSListStr, std::forward_list<std::string>::iterator);

using MapStrInt = std::map<std::string, int>;
CPPCFWV0_HITER_INST(test_hiter::IterMapStrInt, MapStrInt::iterator);
