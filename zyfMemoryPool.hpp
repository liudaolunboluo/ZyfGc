#ifndef SHARE_VM_GC_ZYF_ZYFMEMORYPOOL_HPP
#define SHARE_VM_GC_ZYF_ZYFMEMORYPOOL_HPP

#include "gc/zyf/zyfHeap.hpp"
#include "services/memoryPool.hpp"
#include "services/memoryUsage.hpp"
#include "utilities/macros.hpp"

class ZyfMemoryPool : public CollectedMemoryPool {
private:
  ZyfHeap* _heap;

public:
  ZyfMemoryPool(ZyfHeap* heap);
  size_t committed_in_bytes() { return _heap->capacity();     }
  size_t used_in_bytes()      { return _heap->used();         }
  size_t max_size()     const { return _heap->max_capacity(); }
  MemoryUsage get_memory_usage();
};

#endif // SHARE_VM_GC_Zyf_ZyfMEMORYPOOL_HPP