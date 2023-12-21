#ifndef SHARE_VM_GC_ZYF_COLLECTORPOLICY_HPP
#define SHARE_VM_GC_ZYF_COLLECTORPOLICY_HPP

#include "gc/shared/collectorPolicy.hpp"

class ZyfCollectorPolicy: public CollectorPolicy {
protected:
  virtual void initialize_alignments() {
    size_t page_size = UseLargePages ? os::large_page_size() : os::vm_page_size();
    size_t align = MAX2((size_t)os::vm_allocation_granularity(), page_size);
    //表示内存空间（Space）的对齐方式。内存空间是指 JVM 中用于存储对象的区域，例如堆（Heap）中的各个分代区域。_space_alignment 参数定义了这些内存空间的对齐方式，确保对象在内存中按照特定的对齐规则进行存储。对齐可以提高内存访问的效率，并有助于减少内存碎片化。
    _space_alignment = align;
    //表示堆（Heap）的对齐方式。堆是 JVM 中用于分配和存储对象的主要区域。_heap_alignment 参数定义了堆的对齐方式，确保堆的起始地址和大小按照特定的对齐规则进行分配。对齐可以提高内存访问的效率，并有助于减少内存碎片化。
    _heap_alignment  = align;
  }

public:
  ZyfCollectorPolicy() : CollectorPolicy() {};
};

#endif // SHARE_VM_GC_ZYF_COLLECTORPOLICY_HPP