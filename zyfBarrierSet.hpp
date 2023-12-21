#ifndef SHARE_VM_GC_ZYF_BARRIERSET_HPP
#define SHARE_VM_GC_ZYF_BARRIERSET_HPP

#include "gc/shared/barrierSet.hpp"

// No interaction with application is required for Zyf, and therefore
// the barrier set is empty.
class ZyfBarrierSet: public BarrierSet {
  friend class VMStructs;

public:
  ZyfBarrierSet();

  virtual void print_on(outputStream *st) const {}

  virtual void on_thread_create(Thread* thread);
  virtual void on_thread_destroy(Thread* thread);

  template <DecoratorSet decorators, typename BarrierSetT = ZyfBarrierSet>
  class AccessBarrier: public BarrierSet::AccessBarrier<decorators, BarrierSetT> {};
};

template<>
struct BarrierSet::GetName<ZyfBarrierSet> {
  static const BarrierSet::Name value = BarrierSet::ZyfBarrierSet;
};

template<>
struct BarrierSet::GetType<BarrierSet::ZyfBarrierSet> {
  typedef ::ZyfBarrierSet type;
};

#endif // SHARE_VM_GC_ZYF_BARRIERSET_HPP