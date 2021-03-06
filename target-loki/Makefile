ifndef name
  name := loki
endif

ifndef DESTDIR
  DESTDIR := /
endif

processors := arm gsu hg51b lr35902 r65816 spc700 upd96050
include processor/Makefile

include sfc/Makefile
include gb/Makefile

ui_objects := ui-loki ui-settings ui-input
ui_objects += ui-interface ui-debugger
ui_objects += ui-presentation ui-terminal
ui_objects += ruby phoenix
ui_objects += $(if $(call streq,$(platform),windows),resource)

ifeq ($(platform),windows)
  ruby := video.wgl audio.xaudio2 input.windows
else ifeq ($(platform),macosx)
  ruby := video.cgl audio.openal input.carbon
else ifeq ($(platform),linux)
  ruby := video.glx audio.alsa input.udev
else ifeq ($(platform),bsd)
  ruby := video.glx audio.openal input.x
endif

include ruby/Makefile
link += $(rubylink)

include phoenix/Makefile
link += $(phoenixlink)

objects := $(ui_objects) $(objects)
objects := $(patsubst %,obj/%.o,$(objects))

obj/ui-loki.o: $(ui)/loki.cpp $(call rwildcard,$(ui)/)
obj/ui-settings.o: $(ui)/settings/settings.cpp $(call rwildcard,$(ui)/)
obj/ui-input.o: $(ui)/input/input.cpp $(call rwildcard,$(ui)/)
obj/ui-interface.o: $(ui)/interface/interface.cpp $(call rwildcard,$(ui)/)
obj/ui-debugger.o: $(ui)/debugger/debugger.cpp $(call rwildcard,$(ui)/)
obj/ui-presentation.o: $(ui)/presentation/presentation.cpp $(call rwildcard,$(ui)/)
obj/ui-terminal.o: $(ui)/terminal/terminal.cpp $(call rwildcard,$(ui)/)

obj/ruby.o: ruby/ruby.cpp $(call rwildcard,ruby/)
	$(compiler) $(rubyflags) -c $< -o $@

obj/phoenix.o: phoenix/phoenix.cpp $(call rwildcard,phoenix/)
	$(compiler) $(phoenixflags) -c $< -o $@

obj/resource.o: $(ui)/resource.rc
ifeq ($(arch),win32)
	windres --target=pe-i386 $(ui)/resource.rc obj/resource.o
else
	windres $(ui)/resource.rc obj/resource.o
endif

build: $(objects)
ifeq ($(platform),windows)
	$(strip $(compiler) -shared -o out/phoenix.dll obj/phoenix.o $(phoenixlink))
	$(strip $(compiler) -o out/$(name) $(subst obj/phoenix.o,,$(objects)) $(link) -Lout -lphoenix)
else ifeq ($(platform),macosx)
	if [ -d out/$(name).app ]; then rm -r out/$(name).app; fi
	mkdir out/$(name).app
	mkdir out/$(name).app/Contents
	mkdir out/$(name).app/Contents/MacOS
	mkdir out/$(name).app/Contents/Resources
	cp data/Info.plist out/$(name).app/Contents/Info.plist
	$(strip $(compiler) -o out/$(name).app/Contents/MacOS/$(name) $(objects) $(link))
else
	$(strip $(compiler) -o out/$(name) $(objects) $(link))
endif

resource:
	sourcery $(ui)/resource/resource.bml $(ui)/resource/resource.cpp $(ui)/resource/resource.hpp

install:
ifeq ($(platform),windows)
else ifeq ($(platform),macosx)
	install -d $(DESTDIR)/Library/Application\ Support/$(name)
	cp -R profile/* $(DESTDIR)/Library/Application\ Support/$(name)
	#chmod -R 777 $(DESTDIR)/Library/Application\ Support/$(name)
else
	install -d $(DESTDIR)$(prefix)/bin/
	cp out/$(name) $(DESTDIR)$(prefix)/bin/$(name)
	install -d $(DESTDIR)/usr/share/loki
	cp -R profile/* $(DESTDIR)/usr/share/loki
	#chmod -R 777 $(DESTDIR)/usr/share/loki
endif

uninstall:
ifeq ($(platform),windows)
else ifeq ($(platform),macosx)
else
	rm $(DESTDIR)$(prefix)/bin/$(name)
endif
