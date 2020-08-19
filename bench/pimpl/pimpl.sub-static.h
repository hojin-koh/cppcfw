#include <cppcfwv0/pimpl-static.h>

// Static version
namespace bench_pimpl {

  struct StaticPImpl {
    StaticPImpl(long a);
    long get();
  private:
    struct Impl; cppcfwv0::PImplS<Impl, 96> pimpl;
  };

}
