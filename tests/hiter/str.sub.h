#pragma once
// Include the header part
#include <cppcfwv0/hiter.h>
#include <cppcfwv0/strfwd.h>

namespace test_hiter {

  struct IterVecStr : public ::cppcfwv0::HIter<IterVecStr, std::string> {};

}
