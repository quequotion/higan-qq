fc_objects := fc-interface fc-system fc-controller
fc_objects += fc-cartridge fc-cheat
fc_objects += fc-memory fc-cpu fc-apu fc-ppu
fc_objects += fc-vsarcade
objects += $(fc_objects)

obj/fc-interface.o: $(fc)/interface/interface.cpp $(call rwildcard,$(fc)/interface/)
obj/fc-system.o: $(fc)/system/system.cpp $(call rwildcard,$(fc)/system/)
obj/fc-controller.o: $(fc)/controller/controller.cpp $(call rwildcard,$(fc)/controller/)
obj/fc-cartridge.o: $(fc)/cartridge/cartridge.cpp $(call rwildcard,$(fc)/cartridge/)
obj/fc-cheat.o: $(fc)/cheat/cheat.cpp $(call rwildcard,$(fc)/cheat/)
obj/fc-memory.o: $(fc)/memory/memory.cpp $(call rwildcard,$(fc)/memory/)
obj/fc-cpu.o: $(fc)/cpu/cpu.cpp $(call rwildcard,$(fc)/cpu/)
obj/fc-apu.o: $(fc)/apu/apu.cpp $(call rwildcard,$(fc)/apu/)
obj/fc-ppu.o: $(fc)/ppu/ppu.cpp $(call rwildcard,$(fc)/ppu/)

obj/fc-vsarcade.o: $(fc)/arcade/vs/vs.cpp $(call rwildcard,$(fc)/arcade/vs/)
