RM := rm -rf

LD := $(K221_LD)
CC := $(K221_CC)
CXX := $(K221_CXX)
AR := $(K221_AR)

OBJDIR := .obj
ARCDIR := $(K221_YASIO_LD_LIBRARY_PATH)

CFLAG := $(K221_GLOBAL_CFLAGS)

# main components
MAIN_OBJDIR := $(OBJDIR)
MAIN_SRCDIR := .

MAIN_INL += $(foreach sdir, $(MAIN_SRCDIR), $(wildcard $(sdir)/*.inl))
MAIN_INL += $(foreach sdir, $(MAIN_SRCDIR), $(wildcard $(sdir)/*/*.inl))

MAIN_HPP += $(foreach sdir, $(MAIN_SRCDIR), $(wildcard $(sdir)/*.hpp))
MAIN_HPP += $(foreach sdir, $(MAIN_SRCDIR), $(wildcard $(sdir)/*/*.hpp))

MAIN_SRC += $(foreach sdir, $(MAIN_SRCDIR), $(wildcard $(sdir)/*.cpp))
MAIN_SRC += $(foreach sdir, $(MAIN_SRCDIR), $(wildcard $(sdir)/*/*.cpp))

MAIN_OBJ := $(patsubst $(MAIN_SRCDIR)/%.cpp, $(MAIN_OBJDIR)/%.o, $(MAIN_SRC))

# static library
STATICOBJ := $(K221_YASIO_LD_LIBRARY)


.PHONY: clean


all: main staticobj


main: $(OBJDIR) $(MAIN_INL) $(MAIN_HPP) $(MAIN_OBJ)

staticobj: checkconfig $(STATICOBJ)


checkconfig:
ifneq ($(K221_BE_GLOBALCONFIG), true)
	@echo "You need to run .globalconfig first!"
	@exit 1
endif


$(MAIN_OBJ): $(MAIN_OBJDIR)/%.o : $(MAIN_SRCDIR)/%.cpp
	$(CCACHE) $(CXX) -o $@ $< -fPIE -c -I.. $(CFLAG)


$(STATICOBJ): $(ARCDIR) $(MAIN_OBJ)
	$(AR) -rcs $@ $(MAIN_OBJ)


$(ARCDIR) $(OBJDIR):
	test -d $@ || mkdir $@


clean:
	$(RM) $(OBJDIR)
	$(RM) $(ARCDIR)
