#include <cppcfwv0/pimpl.h>

// Naive version of pimpl
namespace bench_pimpl {

  struct DynamicPImpl {
    DynamicPImpl(long a);
    long get();
  private:
    struct Impl; cppcfwv0::PImpl<Impl> pimpl;
  };

}
