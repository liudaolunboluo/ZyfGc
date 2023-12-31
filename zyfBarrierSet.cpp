#include "precompiled.hpp"
#include "runtime/thread.hpp"
#include "gc/zyf/zyfBarrierSet.hpp"
#include "gc/zyf/zyfThreadLocalData.hpp"
#include "gc/shared/collectorPolicy.hpp"
#include "gc/shared/barrierSet.hpp"
#include "gc/shared/barrierSetAssembler.hpp"
#ifdef COMPILER1
#include "gc/shared/c1/barrierSetC1.hpp"
#endif
#ifdef COMPILER2
#include "gc/shared/c2/barrierSetC2.hpp"
#endif

ZyfBarrierSet::ZyfBarrierSet() : BarrierSet(
                                     make_barrier_set_assembler<BarrierSetAssembler>(),
                                     make_barrier_set_c1<BarrierSetC1>(),
                                     make_barrier_set_c2<BarrierSetC2>(),
                                     BarrierSet::FakeRtti(BarrierSet::ZyfBarrierSet)) {}

void ZyfBarrierSet::on_thread_create(Thread *thread)
{
    ZyfThreadLocalData::create(thread);
}

void ZyfBarrierSet::on_thread_destroy(Thread *thread)
{
    ZyfThreadLocalData::destroy(thread);
}
