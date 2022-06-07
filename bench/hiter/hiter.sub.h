#include <cppcfwv0/hiter.h>

namespace bench_hiter {
  struct IterVecLong : public ::cppcfwv0::HIter<IterVecLong, long> {};

  struct IterVecLongIndir : public ::cppcfwv0::HIterBase<IterVecLongIndir, long> {
    long const getValue() const;
  };

  struct IterVecStr : public ::cppcfwv0::HIter<IterVecStr, const char*> {};

  struct IterVecStrIndir : public ::cppcfwv0::HIterBase<IterVecStrIndir, const char*> {
    const char* getValue() const;
  };

}
