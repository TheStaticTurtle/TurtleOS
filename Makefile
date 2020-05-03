GCC = nspire-gcc 
AS  = nspire-as
GXX = nspire-g++
LD  = nspire-ld
GENZEHN = genzehn

ZEHNFLAGS = --name "TurtleOS" --author "TurtleForGaming" --notice "Alternative PseudoOS" --version 01 --compress
PROG = TurtleOS
DISTDIR = .

GCCFLAGS = -Wno-unused-variable -Wno-narrowing -Wall -W -marm -I./nspireio/include
LDFLAGS = ./nspireio/lib/libnspireio.a
ZEHNFLAGS = --name "TurtleOS"

OBJS = $(patsubst %.c, %.o, $(shell find . -maxdepth 2 -depth -name \*.c))
OBJS += $(patsubst %.cpp, %.o, $(shell find . -maxdepth 2 -depth -name \*.cpp))
OBJS += $(patsubst %.S, %.o, $(shell find . -maxdepth 2 -depth -name \*.S))

INC += -I. -I./micropython/ -I./micropython-include/ -I./micropython/py

vpath %.tns $(DISTDIR)
vpath %.elf $(DISTDIR)

all: $(PROG).prg.tns

%.o: %.c
	$(GCC) $(GCCFLAGS) $(INC) -c $< -o $@

%.o: %.cpp
	$(GXX) $(GCCFLAGS) $(INC) -c $< -o $@
	
%.o: %.S
	$(AS) -c $< -o $@

$(PROG).elf: $(OBJS)
	mkdir -p $(DISTDIR)
	$(LD) $^ -o $(DISTDIR)/$@ $(LDFLAGS)

$(PROG).tns: $(PROG).elf
	$(GENZEHN) --input $(DISTDIR)/$^ --output $(DISTDIR)/$@ $(ZEHNFLAGS)

$(PROG).prg.tns: $(PROG).tns
	make-prg $(DISTDIR)/$^ $(DISTDIR)/$@

clean:
	rm -f */*.o *.o $(DISTDIR)/$(PROG).tns $(DISTDIR)/$(PROG).elf $(DISTDIR)/$(PROG).prg.tns
