RM := rm -rf

SH := bash

GCCPREFIX ?=

LD := $(GCCPREFIX)ld
CC := $(GCCPREFIX)g++
AR := $(GCCPREFIX)ar

OBJDIR := .obj
ARCDIR := .build

CFLAG := -O3 -std=c++20 -flto -fwhole-program

BE_ROOT 	:= $(K221_BE_ROOT)
MODEL_ROOT 	:= ..

GLOBAL_INC += $(K221_CFLAGS_INC_VERILATOR)
GLOBAL_INC += -I$(MODEL_ROOT)/.verilated
GLOBAL_INC += -I$(BE_ROOT)


# main components
MAIN_OBJDIR := $(OBJDIR)
MAIN_SRCDIR := .

MAIN_INL := $(foreach sdir, $(MAIN_SRCDIR), $(wildcard $(sdir)/*.inl))
MAIN_INL += $(foreach sdir, $(MAIN_SRCDIR), $(wildcard $(sdir)/*/*.inl))

MAIN_HPP := $(foreach sdir, $(MAIN_SRCDIR), $(wildcard $(sdir)/*.hpp))
MAIN_HPP += $(foreach sdir, $(MAIN_SRCDIR), $(wildcard $(sdir)/*/*.hpp))

MAIN_SRC := $(foreach sdir, $(MAIN_SRCDIR), $(wildcard $(sdir)/*.cpp))
MAIN_SRC += $(foreach sdir, $(MAIN_SRCDIR), $(wildcard $(sdir)/*/*.cpp))

MAIN_OBJ := $(patsubst $(MAIN_SRCDIR)/%.cpp, $(MAIN_OBJDIR)/%.o, $(MAIN_SRC))


.PHONY: staticobj verilated clean

# static library
STATICOBJ := $(ARCDIR)/libds232.a

all: main staticobj

main:: checkconfig verilated $(OBJDIR) $(MAIN_HPP) $(MAIN_INL) $(MAIN_OBJ)

staticobj: $(ARCDIR) $(STATICOBJ)

verilated:
	@test -f $(MODEL_ROOT)/.verilated/Vthinpad_verilated.h \
	|| $(SH) $(MODEL_ROOT)/verilate.sh -H

checkconfig:
ifneq ($(K221_BE_GLOBALCONFIG), true)
	@echo "You need to run .globalconfig first!"
	@exit 1
endif


$(MAIN_OBJ): $(MAIN_OBJDIR)/%.o : $(MAIN_SRCDIR)/%.cpp
	@test -d $(dir $@) || mkdir -p $(dir $@)
	$(CC) -o $@ $< -fPIE -c -I. $(GLOBAL_INC) $(CFLAG)


$(STATICOBJ): $(ARCDIR) $(MAIN_OBJ)
	$(AR) -rcs $(STATICOBJ) $(MAIN_OBJ)


$(ARCDIR) $(OBJDIR):
	test -d $@ || mkdir $@

clean:
	-$(RM) $(OBJDIR)
	-$(RM) $(ARCDIR)
