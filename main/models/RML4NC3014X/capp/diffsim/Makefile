RM := rm -rf

GCCPREFIX ?=

LD := $(GCCPREFIX)ld
CC := $(GCCPREFIX)g++
AR := $(GCCPREFIX)ar

CCACHE := ccache

OBJDIR := .obj
ARCDIR := .build

CFLAG := $(K221_GLOBAL_CFLAGS) -DSERIAL_SERVER -DVM_TRACE

MODEL_ROOT 	:= ../..

GLOBAL_INC += $(K221_CFLAGS_INC_VERILATOR)
GLOBAL_INC += -I$(MODEL_ROOT)/.verilated
GLOBAL_INC += -I$(MODEL_ROOT)/csrc

GLOBAL_INC += -I$(K221_BE_ROOT)


#
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
MAIN := $(ARCDIR)/appmain.a

all: main staticobj

main:: checkconfig $(OBJDIR) $(MAIN_HPP) $(MAIN_INL) $(MAIN_OBJ)

staticobj: $(ARCDIR) $(MAIN)


checkconfig:
ifneq ($(K221_BE_GLOBALCONFIG), true)
	@echo "You need to run .globalconfig first!"
	@exit 1
endif


$(MAIN_OBJ): $(MAIN_OBJDIR)/%.o : $(MAIN_SRCDIR)/%.cpp
	@test -d $(dir $@) || mkdir -p $(dir $@)
	$(CCACHE) $(CC) $(CFLAG) -o $@ $< -fPIE -c -I. $(GLOBAL_INC)


$(MAIN): $(ARCDIR) $(MAIN_OBJ)
	$(AR) -rcs $(MAIN) $(MAIN_OBJ)


$(ARCDIR) $(OBJDIR):
	test -d $@ || mkdir $@

clean:
	-$(RM) $(OBJDIR)
	-$(RM) $(ARCDIR)
