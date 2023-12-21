
#include "precompiled.hpp"
#include "gc/zyf/zyfArguments.hpp"
#include "gc/zyf/zyfCollectorPolicy.hpp"
#include "gc/zyf/zyfHeap.hpp"
#include "gc/shared/gcArguments.inline.hpp"
#include "runtime/globals.hpp"
#include "runtime/globals_extension.hpp"



size_t ZyfArguments::conservative_max_heap_alignment()
{
    return UseLargePages ? os::large_page_size() : os::vm_page_size();
}

void ZyfArguments::initialize()
{
    GCArguments::initialize();

    assert(UseZyfGC, "Sanity");

    // Forcefully exit when OOME is detected. Nothing we can do at that point.
    if (FLAG_IS_DEFAULT(ExitOnOutOfMemoryError))
    {
        FLAG_SET_DEFAULT(ExitOnOutOfMemoryError, true);
    }

    // Warn users that non-resizable heap might be better for some configurations.
    // We are not adjusting the heap size by ourselves, because it affects startup time.
    if (InitialHeapSize != MaxHeapSize)
    {
        log_warning(gc)("Consider setting -Xms equal to -Xmx to avoid resizing hiccups");
    }

    // Warn users that AlwaysPreTouch might be better for some configurations.
    // We are not turning this on by ourselves, because it affects startup time.
    if (FLAG_IS_DEFAULT(AlwaysPreTouch) && !AlwaysPreTouch)
    {
        log_warning(gc)("Consider enabling -XX:+AlwaysPreTouch to avoid memory commit hiccups");
    }

    if (ZYFMaxTLABSize < MinTLABSize)
    {
        log_warning(gc)("ZYFMaxTLABSize < MinTLABSize, adjusting it to " SIZE_FORMAT, MinTLABSize);
        ZYFMaxTLABSize = MinTLABSize;
    }

    if (!ZYFElasticTLAB && ZYFElasticTLABDecay)
    {
        log_warning(gc)("Disabling ZYFElasticTLABDecay because ZYFElasticTLAB is disabled");
        FLAG_SET_DEFAULT(ZYFElasticTLABDecay, false);
    }

#ifdef COMPILER2
    // Enable loop strip mining: there are still non-GC safepoints, no need to make it worse
    if (FLAG_IS_DEFAULT(UseCountedLoopSafepoints))
    {
        FLAG_SET_DEFAULT(UseCountedLoopSafepoints, true);
        if (FLAG_IS_DEFAULT(LoopStripMiningIter))
        {
            FLAG_SET_DEFAULT(LoopStripMiningIter, 1000);
        }
    }
#endif
}

CollectedHeap *ZyfArguments::create_heap()
{
    return create_heap_with_policy<ZyfHeap, ZyfCollectorPolicy>();
}