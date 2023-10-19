RM := rm -rf

GCCPREFIX ?=

LD := $(GCCPREFIX)ld
CC := $(GCCPREFIX)g++
AR := $(GCCPREFIX)ar

OBJDIR := .obj
ARCDIR := $(K221_BE_N1_SOC_LA32_LD_LIBRARY_PATH)

CFLAG := -O3 -std=c++20 -flto -fwhole-program

GLOBAL_INC += $(K221_CFLAGS_INC_YASIO)
GLOBAL_INC += $(K221_CFLAGS_INC_BE_MAIN)


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


# static library
STATICOBJ := $(K221_BE_N1_SOC_LA32_LD_LIBRARY)

all: main staticobj

main:: checkconfig $(OBJDIR) $(MAIN_HPP) $(MAIN_INL) $(MAIN_OBJ)

staticobj: checkconfig $(ARCDIR) $(STATICOBJ)


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
