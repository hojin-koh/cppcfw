#include <cppcfwv0/hiter.h>

namespace bench_hiter {
  struct IterVecLong : public ::cppcfwv0::HIter<IterVecLong, long> {
    using HIter::HIter;
  };
}
