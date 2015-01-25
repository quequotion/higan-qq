#if defined(DEBUGGER)
  #error "bsnes: debugger not supported with accuracyfast profile."
#endif

#include <sfc/cpu/cpu.hpp>
#include <sfc/smp/smp.hpp>
#include <sfc/alt/dsp/dsp.hpp>
#include <sfc/ppu/ppu.hpp>
