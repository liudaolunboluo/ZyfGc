#ifndef SHARE_VM_GC_ZYF_ZYFMONITORINGSUPPORT_HPP
#define SHARE_VM_GC_ZYF_ZYFMONITORINGSUPPORT_HPP

#include "memory/allocation.hpp"

class GenerationCounters;
class ZyfSpaceCounters;
class ZyfHeap;

class ZyfMonitoringSupport : public CHeapObj<mtGC> {
private:
  GenerationCounters*   _heap_counters;
  ZyfSpaceCounters* _space_counters;

public:
  ZyfMonitoringSupport(ZyfHeap* heap);
  void update_counters();
};

#endif // SHARE_VM_GC_ZYF_ZYFMONITORINGSUPPORT_HPP
