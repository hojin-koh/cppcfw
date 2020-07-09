#include <cppcfwv0/hiter.h>

namespace bench_hiter {
  struct IterVecLongIndir : public ::cppcfwv0::HIter<IterVecLongIndir, long> {
    using HIter::HIter;
  };
}
