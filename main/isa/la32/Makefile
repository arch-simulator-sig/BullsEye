RM := rm -rf

GCCPREFIX ?=

LD := $(GCCPREFIX)ld
CC := $(GCCPREFIX)g++
AR := $(GCCPREFIX)ar

OBJDIR := .obj
ARCDIR := .build

CFLAG := -O3 -std=c++20 -flto -fwhole-program

# BullsEye library include path
GLOBAL_INC := ../../..

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


# static library
STATICOBJ := $(ARCDIR)/libjasse2-la32.a


.PHONY: clean


all: base main extension staticobj


extension: ext_nscscc


base:: $(BASE_OBJDIR) $(BASE_HPP) $(BASE_INL) $(BASE_OBJ)

ext_nscscc:: $(EXT_NSCSCC_OBJDIR) $(EXT_NSCSCC_HPP) $(EXT_NSCSCC_INL) $(EXT_NSCSCC_OBJ)

main:: $(MAIN_OBJDIR) $(MAIN_HPP) $(MAIN_INL) $(MAIN_OBJ)


staticobj: $(STATICOBJ)


$(BASE_OBJ): $(BASE_OBJDIR)/%.o : $(BASE_SRCDIR)/%.cpp
	$(CC) -o $@ $< -fPIE -c -I$(GLOBAL_INC) -I. $(CFLAG)


$(EXT_NSCSCC_OBJ): $(EXT_NSCSCC_OBJDIR)/%.o : $(EXT_NSCSCC_SRCDIR)/%.cpp
	$(CC) -o $@ $< -fPIE -c -I$(GLOBAL_INC) -I. $(CFLAG)


$(MAIN_OBJ): $(MAIN_OBJDIR)/%.o : $(MAIN_SRCDIR)/%.cpp
	$(CC) -o $@ $< -fPIE -c -I$(GLOBAL_INC) -I. $(CFLAG)


$(STATICOBJ): $(ARCDIR) $(MAIN_OBJ) $(BASE_OBJ) $(EXT_NSCSCC_OBJ)
	$(AR) -rcs $(STATICOBJ) $(MAIN_OBJ) $(BASE_OBJ) $(EXT_NSCSCC_OBJ)


$(ARCDIR) $(OBJDIR):
	test -d $@ || mkdir $@

$(BASE_OBJDIR):
	test -d $@ || mkdir -p $@

$(EXT_NSCSCC_OBJDIR):
	test -d $@ || mkdir -p $@

clean:
	$(RM) $(OBJDIR)
	$(RM) $(ARCDIR)
