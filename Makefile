include ./micropython/py/mkenv.mk
-include mpconfigport.mk

CC = nspire-gcc 
AS  = nspire-as
CXX = nspire-g++
LD  = nspire-ld
GENZEHN = genzehn

ZEHNFLAGS = --name "TurtleOS" --author "TurtleForGaming" --notice "Alternative PseudoOS" --version 01 --compress
PROG = TurtleOS

BUILD = build

QSTR_DEFS = micropython-include/qstrdefsport.h   # qstr definitions (must come before including py.mk)
UNAME_S := $(shell uname -s) # OS name, for simple autoconfig
NOSTRIP := 1                 # Disable stripping of the main executable, relocation info is needed by genzehn
# DEBUG := 1

INC =  -I.
INC += -I./micropython/
INC += -I./micropython-include/
INC += -I./micropython/py
INC += -I$(BUILD)

include ./micropython/py/py.mk

# Debugging/Optimization
ifdef DEBUG
	COPT = -O0 -g
else
	COPT = -Ofast -fomit-frame-pointer -flto
endif


CWARN = -Wall  -Wno-error=cpp -Wno-error=format -Wno-narrowing
CFLAGS = $(INC) $(CWARN) -ansi -std=gnu99 $(CFLAGS_MOD) $(COPT) $(CFLAGS_EXTRA)
LDFLAGS = $(LDFLAGS_MOD) -lm $(LDFLAGS_EXTRA) -Wl, ./nspireio/lib/libnspireio.a

CXX += $(INC) $(CWARN)

# source files
# SRC_C  = $(shell find . -maxdepth 1 -name \*.c*)
# SRC_C += $(shell find apps/ -maxdepth 1 -name \*.c*)
# SRC_C += $(shell find drivers/ -maxdepth 1 -name \*.c*)

# SRC_QSTR += $(SRC_C)

OBJ  = $(PY_O) 

OBJ += $(patsubst %.cpp, %.o, $(shell find .       -maxdepth 1 -name \*.c*))
OBJ += $(patsubst %.cpp, %.o, $(shell find apps    -maxdepth 1 -name \*.c*))
OBJ += $(patsubst %.cpp, %.o, $(shell find drivers -maxdepth 1 -name \*.c*))

allaa: $(OBJ)

include ./micropython/py/mkrules.mk

all: $(PROG).tns

$(PROG).tns: $(PROG) 
	+genzehn --input $^ --output $@.zehn $(ZEHNFLAGS)
	+make-prg $@.zehn $@
	+rm $@.zehn

clean:
	+@echo $(SRC_C)
	+@echo 
	+@echo $(addprefix $(BUILD)/, $(SRC_C:.cpp=.o)) 
	rm -f *.o 
	rm -f */*.o
	rm -f */*/*.o 
	rm -f */*/*/*.o 
	rm -f */*/*/*/*.o 
	rm -f */*/*/*/*/*.o 
	rm -rf $(BUILD)/
	rm -f $(DISTDIR)/$(EXE).tns $(DISTDIR)/$(EXE).elf $(DISTDIR)/$(EXE).prg.tns






# DEBUG = FALSE

# include ./micropython/py/mkenv.mk
# -include mpconfigport.mk


# NOSTRIP := 1
# # DEBUG := 1

# QSTR_DEFS = qstrdefsport.h
# UNAME_S := $(shell uname -s)

# NOSTRIP := 1
# # DEBUG := 1

# include ./micropython/py/py.mk # include py core make definitions

# INC += -I.
# # INC += -I./micropython/
# # INC = -I./micropython/py
# INC += -I./nspireio/include
# INC += -I$(BUILD)
# COPT = -O0 -g

# CWARN = -Wall -Wno-error=cpp -Wno-narrowing -Wno-error=format -Wno-error=format

# CFLAGS = $(INC) $(CWARN) -ansi -std=gnu99 $(CFLAGS_MOD) $(COPT) $(CFLAGS_EXTRA)
# LDFLAGS = $(LDFLAGS_MOD) -lm $(LDFLAGS_EXTRA) -Wl, ./nspireio/lib/libnspireio.a

# # source files
# SRC_C = $(shell find . -name \*.c)
# SRC_QSTR += $(SRC_C)
# OBJ = $(PY_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o))

# include ./micropython/py/mkrules.mk


# ZEHNFLAGS = --name "TurtleOS"

# OBJS = $(patsubst %.c, %.o, $(shell find . -name \*.c))
# OBJS += $(patsubst %.cpp, %.o, $(shell find . -name \*.cpp))
# OBJS += $(patsubst %.S, %.o, $(shell find . -name \*.S))
# EXE = TurtleOS
# DISTDIR = .
# vpath %.tns $(DISTDIR)
# vpath %.elf $(DISTDIR)


# all: $(EXE).prg.tns

# %.o: %.c
# 	$(GCC) $(CWARN) $(INC) -c $< -o $@

# %.o: %.cpp
# 	$(GXX) $(CWARN) $(INC) -c $< -o $@
	
# %.o: %.S
# 	$(AS) -c $< -o $@

# $(EXE).elf: $(OBJS)
# 	mkdir -p $(DISTDIR)
# 	$(LD) $^ -o $(DISTDIR)/$@ $(LDFLAGS)

# $(EXE).tns: $(EXE).elf
# 	$(GENZEHN) --input $(DISTDIR)/$^ --output $(DISTDIR)/$@ $(ZEHNFLAGS)

# $(EXE).prg.tns: $(EXE).tns
# 	make-prg $(DISTDIR)/$^ $(DISTDIR)/$@

# clean:
# 	rm -f */*.o */*/*.o */*/*/*.o */*/*/*/*.o */*/*/*/*/*.o *.o $(DISTDIR)/$(EXE).tns $(DISTDIR)/$(EXE).elf $(DISTDIR)/$(EXE).prg.tns


# all: $(PROG).tns

# $(PROG).tns: $(PROG)
# 	+genzehn --input $^ --output $@.zehn $(ZEHNFLAGS)
# 	+make-prg $@.zehn $@
# 	+rm $@.zehn



















# GCCFLAGS = -Wno-unused-variable -Wno-narrowing -Wall -W -marm -I./nspireio/include
# LDFLAGS = ./nspireio/lib/libnspireio.a
# ZEHNFLAGS = --name "TurtleOS"


# OBJS = $(patsubst %.c, %.o, $(shell find . -depth -name \*.c))
# OBJS += $(patsubst %.cpp, %.o, $(shell find . -depth -name \*.cpp))
# OBJS += $(patsubst %.S, %.o, $(shell find . -depth -name \*.S))
# EXE = TurtleOS
# DISTDIR = .
# vpath %.tns $(DISTDIR)
# vpath %.elf $(DISTDIR)


# all: $(EXE).prg.tns

# %.o: %.c
	# $(GCC) $(GCCFLAGS) -c $< -o $@

# %.o: %.cpp
	# $(GXX) $(GCCFLAGS) -c $< -o $@
	
# %.o: %.S
	# $(AS) -c $< -o $@

# $(EXE).elf: $(OBJS)
	# mkdir -p $(DISTDIR)
	# $(LD) $^ -o $(DISTDIR)/$@ $(LDFLAGS)

# $(EXE).tns: $(EXE).elf
	# $(GENZEHN) --input $(DISTDIR)/$^ --output $(DISTDIR)/$@ $(ZEHNFLAGS)

# $(EXE).prg.tns: $(EXE).tns
	# make-prg $(DISTDIR)/$^ $(DISTDIR)/$@

# clean:
	# rm -f */*.o *.o $(DISTDIR)/$(EXE).tns $(DISTDIR)/$(EXE).elf $(DISTDIR)/$(EXE).prg.tns
