#include <cppcfwv0/hiter.h>

namespace bench_hiter {
  struct IterVecLongCached : public ::cppcfwv0::HIter<IterVecLongCached, long> {
    using HIter::HIter;
  };
}
