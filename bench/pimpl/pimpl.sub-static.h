#include <cppcfwv0/pimpl-static.h>

#include "config.h"

// Static version
namespace bench_pimpl {

  struct StaticPImpl {
    StaticPImpl(long a);
    long get();
  private:
    struct Impl; cppcfwv0::PImplS<Impl, config::sizeMapLong> pimpl;
  };

}
