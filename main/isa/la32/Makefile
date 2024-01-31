RM := rm -rf

LD := $(K221_LD)
CC := $(K221_CC)
CXX := $(K221_CXX)
AR := $(K221_AR)

CCACHE := $(K221_CCACHE)

OBJDIR := .obj
ARCDIR := $(K221_BE_JASSE2_LA32_LD_LIBRARY_PATH)

CFLAG := $(K221_GLOBAL_CFLAGS)

# BullsEye library include path
GLOBAL_INC += $(K221_BE_ROOT)

# base components directory
BASE_OBJDIR := $(OBJDIR)/base
BASE_SRCDIR := base

BASE_INL := $(foreach sdir, $(BASE_SRCDIR), $(wildcard $(sdir)/*.inl))
BASE_HPP := $(foreach sdir, $(BASE_SRCDIR), $(wildcard $(sdir)/*.hpp))
BASE_SRC := $(foreach sdir, $(BASE_SRCDIR), $(wildcard $(sdir)/*.cpp))
BASE_OBJ := $(patsubst $(BASE_SRCDIR)/%.cpp, $(BASE_OBJDIR)/%.o, $(BASE_SRC))

# extended components directory
EXT_OBJDIR := $(OBJDIR)/ext
EXT_SRCDIR := .

EXT_NSCSCC_OBJDIR := $(EXT_OBJDIR)/la32_nscscc
EXT_NSCSCC_SRCDIR := $(EXT_SRCDIR)/la32_nscscc

EXT_NSCSCC_INL := $(foreach sdir, $(EXT_NSCSCC_SRCDIR), $(wildcard $(sdir)/*.inl))
EXT_NSCSCC_HPP := $(foreach sdir, $(EXT_NSCSCC_SRCDIR), $(wildcard $(sdir)/*.hpp))
EXT_NSCSCC_SRC := $(foreach sdir, $(EXT_NSCSCC_SRCDIR), $(wildcard $(sdir)/*.cpp))
EXT_NSCSCC_OBJ := $(patsubst $(EXT_NSCSCC_SRCDIR)/%.cpp, $(EXT_NSCSCC_OBJDIR)/%.o, $(EXT_NSCSCC_SRC))

# main components
MAIN_OBJDIR := $(OBJDIR)
MAIN_SRCDIR := .

MAIN_INL := $(wildcard $(MAIN_SRCDIR)/*.inl)
MAIN_HPP := $(wildcard $(MAIN_SRCDIR)/*.hpp)
MAIN_SRC := $(wildcard $(MAIN_SRCDIR)/*.cpp)
MAIN_OBJ := $(patsubst $(MAIN_SRCDIR)/%.cpp, $(MAIN_OBJDIR)/%.o, $(MAIN_SRC))

# addon components
ADDON_OBJDIR := $(OBJDIR)/addon
ADDON_SRCDIR := addon

ADDON_INL := $(foreach sdir, $(ADDON_SRCDIR), $(wildcard $(sdir)/*.inl))
ADDON_HPP := $(foreach sdir, $(ADDON_SRCDIR), $(wildcard $(sdir)/*.hpp))
ADDON_SRC := $(foreach sdir, $(ADDON_SRCDIR), $(wildcard $(sdir)/*.cpp))
ADDON_OBJ := $(patsubst $(ADDON_SRCDIR)/%.cpp, $(ADDON_OBJDIR)/%.o, $(ADDON_SRC))


# static library
STATICOBJ := $(K221_BE_JASSE2_LA32_LD_LIBRARY)


.PHONY: clean


all: base main extension addon staticobj


extension: ext_nscscc


base:: checkconfig $(BASE_OBJDIR) $(BASE_HPP) $(BASE_INL) $(BASE_OBJ)

ext_nscscc:: checkconfig $(EXT_NSCSCC_OBJDIR) $(EXT_NSCSCC_HPP) $(EXT_NSCSCC_INL) $(EXT_NSCSCC_OBJ)

main:: checkconfig $(MAIN_OBJDIR) $(MAIN_HPP) $(MAIN_INL) $(MAIN_OBJ)

addon:: checkconfig $(ADDON_OBJDIR) $(ADDON_HPP) $(ADDON_INL) $(ADDON_OBJ)


staticobj: checkconfig $(STATICOBJ)


checkconfig:
ifneq ($(K221_BE_GLOBALCONFIG), true)
	@echo "You need to run .globalconfig first!"
	@exit 1
endif


$(BASE_OBJ): $(BASE_OBJDIR)/%.o : $(BASE_SRCDIR)/%.cpp
	$(CCACHE) $(CXX) -o $@ $< -fPIE -c -I$(GLOBAL_INC) -I. $(CFLAG)


$(EXT_NSCSCC_OBJ): $(EXT_NSCSCC_OBJDIR)/%.o : $(EXT_NSCSCC_SRCDIR)/%.cpp
	$(CCACHE) $(CXX) -o $@ $< -fPIE -c -I$(GLOBAL_INC) -I. $(CFLAG)


$(MAIN_OBJ): $(MAIN_OBJDIR)/%.o : $(MAIN_SRCDIR)/%.cpp
	$(CCACHE) $(CXX) -o $@ $< -fPIE -c -I$(GLOBAL_INC) -I. $(CFLAG)


$(ADDON_OBJ): $(ADDON_OBJDIR)/%.o : $(ADDON_SRCDIR)/%.cpp
	$(CCACHE) $(CXX) -o $@ $< -fPIE -c -I$(GLOBAL_INC) -I. $(CFLAG)


$(STATICOBJ): $(ARCDIR) $(MAIN_OBJ) $(BASE_OBJ) $(EXT_NSCSCC_OBJ) $(ADDON_OBJ)
	$(AR) -rcs $(STATICOBJ) $(MAIN_OBJ) $(BASE_OBJ) $(EXT_NSCSCC_OBJ) $(ADDON_OBJ)


$(ARCDIR) $(OBJDIR):
	test -d $@ || mkdir $@

$(BASE_OBJDIR):
	test -d $@ || mkdir -p $@

$(EXT_NSCSCC_OBJDIR):
	test -d $@ || mkdir -p $@

$(ADDON_OBJDIR):
	test -d $@ || mkdir -p $@

clean:
	$(RM) $(OBJDIR)
	$(RM) $(ARCDIR)
