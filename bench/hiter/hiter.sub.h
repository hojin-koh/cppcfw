#include <cppcfwv0/hiter.h>

namespace bench_hiter {
  struct IterVecLong : public ::cppcfwv0::HIter<IterVecLong, long> {
    using HIter::HIter;
  };

  struct IterVecStr : public ::cppcfwv0::HIter<IterVecStr, const char*> {
    using HIter::HIter;
  };

  struct IterMapStr : public ::cppcfwv0::HIter<IterMapStr, const char*> {
    using HIter::HIter;
  };
}
