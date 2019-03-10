include ../nall/Makefile
include ../phoenix/Makefile

ifndef DESTDIR
  DESTDIR := /
endif

ifndef prefix
  prefix := /usr/local/lib
endif

flags := $(flags) -O3 -fomit-frame-pointer -I..

all:
	$(compiler) $(cppflags) $(flags) -fPIC -o obj/ananke.o -c ananke.cpp
ifeq ($(platform),windows)
	$(compiler) $(phoenixflags) -fPIC -o obj/phoenix.o -c ../phoenix/phoenix.cpp
	$(compiler) $(link) -shared -o phoenix.dll obj/phoenix.o $(phoenixlink)
	$(compiler) $(link) -shared -o ananke.dll obj/ananke.o -L. -lphoenix
else ifeq ($(platform),macosx)
	$(compiler) $(link) -shared -dynamiclib -undefined suppress -flat_namespace -o libananke.dylib obj/ananke.o
else
	$(compiler) $(link) -shared -Wl,-soname,libananke.so.1 -o libananke.so obj/ananke.o
endif

resource: force
	sourcery resource/resource.bml resource/resource.cpp resource/resource.hpp

clean:
	-@$(call delete,obj/*.o)
	-@$(call delete,*.dll)
	-@$(call delete,*.so)

install: uninstall
ifeq ($(platform),windows)
else ifeq ($(platform),macosx)
	#if [ ! -d ~/Library/Application\ Support/ananke ]; then install -d ~/Library/Application\ Support/ananke; fi
	install -d $(DESTDIR)$(path)
	cp libananke.dylib $(DESTDIR)$(prefix)/libananke.1.dylib
	ln -s $(prefix)/libananke.1.dylib $(DESTDIR)$(prefix)/libananke.dylib
else
	#if [ ! -d ~/.config/ananke ]; then install -d ~/.config/ananke; fi
	install -d $(DESTDIR)$(prefix)
	cp libananke.so $(DESTDIR)$(prefix)/libananke.so.1
	ln -s $(prefix)/libananke.so.1 $(DESTDIR)$(prefix)/libananke.so
endif

uninstall:
ifeq ($(platform),windows)
else ifeq ($(platform),macosx)
	if [ -f $(DESTDIR)$(prefix)/libananke.dylib ]; then rm $(DESTDIR)$(prefix)/libananke.dylib; fi
	if [ -f $(DESTDIR)$(prefix)/libananke.1.dylib ]; then rm $(DESTDIR)$(prefix)/libananke.1.dylib; fi
else
	if [ -f $(DESTDIR)$(prefix)/libananke.so ]; then rm $(DESTDIR)$(prefix)/libananke.so; fi
	if [ -f $(DESTDIR)$(prefix)/libananke.so.1 ]; then rm $(DESTDIR)$(prefix)/libananke.so.1; fi
endif

force:
