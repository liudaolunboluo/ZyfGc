#ifndef SHARE_VM_GC_ZYF_ZYFTHREADLOCALDATA_HPP
#define SHARE_VM_GC_ZYF_ZYFTHREADLOCALDATA_HPP

#include "runtime/thread.hpp"
#include "utilities/debug.hpp"

class ZyfThreadLocalData {
private:
  size_t _ergo_tlab_size;
  int64_t _last_tlab_time;

  ZyfThreadLocalData() :
          _ergo_tlab_size(0),
          _last_tlab_time(0) {}

  static ZyfThreadLocalData* data(Thread* thread) {
    assert(UseZyfGC, "Sanity");
    return thread->gc_data<ZyfThreadLocalData>();
  }

public:
  static void create(Thread* thread) {
    new (data(thread)) ZyfThreadLocalData();
  }

  static void destroy(Thread* thread) {
    data(thread)->~ZyfThreadLocalData();
  }

  static size_t ergo_tlab_size(Thread *thread) {
    return data(thread)->_ergo_tlab_size;
  }

  static int64_t last_tlab_time(Thread *thread) {
    return data(thread)->_last_tlab_time;
  }

  static void set_ergo_tlab_size(Thread *thread, size_t val) {
    data(thread)->_ergo_tlab_size = val;
  }

  static void set_last_tlab_time(Thread *thread, int64_t time) {
    data(thread)->_last_tlab_time = time;
  }
};

#endif // SHARE_VM_GC_ZYF_ZYFTHREADLOCALDATA_HPP
