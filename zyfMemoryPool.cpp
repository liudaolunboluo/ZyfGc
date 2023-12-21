#include "precompiled.hpp"
#include "gc/zyf/zyfArguments.hpp"
#include "gc/zyf/zyfMemoryPool.hpp"

ZyfMemoryPool::ZyfMemoryPool(ZyfHeap* heap) :
        _heap(heap),
        CollectedMemoryPool("Zyf Heap",
                            heap->capacity(),
                            heap->max_capacity(),
                            false) {
  assert(UseZyfGC, "sanity");
}

MemoryUsage ZyfMemoryPool::get_memory_usage() {
  size_t initial_sz = initial_size();
  size_t max_sz     = max_size();
  size_t used       = used_in_bytes();
  size_t committed  = committed_in_bytes();

  return MemoryUsage(initial_sz, used, committed, max_sz);
}