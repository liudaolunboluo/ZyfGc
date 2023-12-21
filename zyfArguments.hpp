#ifndef SHARE_GC_ZYF_ZYFARGUMENTS_HPP
#define SHARE_GC_ZYF_ZYFARGUMENTS_HPP

#include "gc/shared/gcArguments.hpp"

class CollectedHeap;

class ZyfArguments : public GCArguments {
public:
  virtual void initialize();
  virtual size_t conservative_max_heap_alignment();
  virtual CollectedHeap* create_heap();
};

#endif // SHARE_GC_ZYF_ZYFARGUMENTS_HPP