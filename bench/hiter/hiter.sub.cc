#include "hiter.sub.h"
#include <cppcfwv0/hiter-inl.h>

#include <vector>
#include <string>
#include <map>

CPPCFWV0_HITER_IMPL(bench_hiter::IterVecLong, std::vector<long>::iterator);

CPPCFWV0_HITER_IMPL_STR(bench_hiter::IterVecStr, std::vector<std::string>::iterator);

using MapSS = std::map<std::string, std::string>;
CPPCFWV0_HITER_IMPL_STR(bench_hiter::IterMapStr, MapSS::iterator);
