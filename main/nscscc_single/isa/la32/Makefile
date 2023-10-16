RM := rm -rf

GCCPREFIX ?=

LD := $(GCCPREFIX)ld
CC := $(GCCPREFIX)g++
AR := $(GCCPREFIX)ar

OBJDIR := .obj
ARCDIR := .build

CFLAG := -O3 -std=c++20

# BullsEye library include path
GLOBAL_INC := ../../..

# base components directory
BASE_OBJDIR := $(OBJDIR)/base
BASE_SRCDIR := base

BASE_HPP := $(foreach sdir, $(BASE_SRCDIR), $(wildcard $(sdir)/*.hpp))
BASE_SRC := $(foreach sdir, $(BASE_SRCDIR), $(wildcard $(sdir)/*.cpp))
BASE_OBJ := $(patsubst $(BASE_SRCDIR)/%.cpp, $(BASE_OBJDIR)/%.o, $(BASE_SRC))

# extended components directory
EXT_OBJDIR := $(OBJDIR)/ext
EXT_SRCDIR := .

EXT_NSCSCC_OBJDIR := $(EXT_OBJDIR)/la32_nscscc
EXT_NSCSCC_SRCDIR := $(EXT_SRCDIR)/la32_nscscc

EXT_NSCSCC_HPP := $(foreach sdir, $(EXT_NSCSCC_SRCDIR), $(wildcard $(sdir)/*.hpp))
EXT_NSCSCC_SRC := $(foreach sdir, $(EXT_NSCSCC_SRCDIR), $(wildcard $(sdir)/*.cpp))
EXT_NSCSCC_OBJ := $(patsubst $(EXT_NSCSCC_SRCDIR)/%.cpp, $(EXT_NSCSCC_OBJDIR)/%.o, $(EXT_NSCSCC_SRC))

# main components
MAIN_OBJDIR := $(OBJDIR)
MAIN_SRCDIR := .

MAIN_HPP := $(wildcard $(MAIN_SRCDIR)/*.hpp)
MAIN_SRC := $(wildcard $(MAIN_SRCDIR)/*.cpp)
MAIN_OBJ := $(patsubst $(MAIN_SRCDIR)/%.cpp, $(MAIN_OBJDIR)/%.o, $(MAIN_SRC))


# static library
STATICLIB := $(ARCDIR)/libjasse-la32.a


.PHONY: clean


all: base main extension staticlib


extension: ext_nscscc


main: $(OBJDIR) $(MAIN_HPP) $(MAIN_OBJ)

base: $(BASE_OBJDIR) $(BASE_HPP) $(BASE_OBJ)

ext_nscscc: $(EXT_NSCSCC_OBJDIR) $(EXT_NSCSCC_HPP) $(EXT_NSCSCC_OBJ)


staticlib: $(STATICLIB)


$(BASE_OBJ): $(BASE_OBJDIR)/%.o : $(BASE_SRCDIR)/%.cpp
	$(CC) -o $@ $< -MMD -c -I$(GLOBAL_INC) -I. $(CFLAG)

$(EXT_NSCSCC_OBJ): $(EXT_NSCSCC_OBJDIR)/%.o : $(EXT_NSCSCC_SRCDIR)/%.cpp
	$(CC) -o $@ $< -MMD -c -I$(GLOBAL_INC) -I. $(CFLAG)


$(MAIN_OBJ): $(MAIN_OBJDIR)/%.o : $(MAIN_SRCDIR)/%.cpp
	$(CC) -o $@ $< -MMD -c -I$(GLOBAL_INC) -I. $(CFLAG)


$(STATICLIB): $(ARCDIR) $(MAIN_OBJ) $(BASE_OBJ) $(EXT_NSCSCC_OBJ)
	$(AR) -rcs $@ $(MAIN_OBJ) $(BASE_OBJ) $(EXT_NSCSCC_OBJ)


$(ARCDIR) $(OBJDIR):
	test -d $@ || mkdir $@

$(BASE_OBJDIR):
	test -d $@ || mkdir -p $@

$(EXT_NSCSCC_OBJDIR):
	test -d $@ || mkdir -p $@

clean:
	$(RM) $(OBJDIR)
	$(RM) $(ARCDIR)
