#
#	Necessary packages:
#	===================
#
#		- libsdl1.2-dev and its dependencies (approx. 41 packages and 50 MB)

CXX = clang++

#	Debug version
#CXXFLAGS =	-O0 -g -Wall -fmessage-length=0  -DDEBUG
CXXFLAGS =	-O0 -g -Weverything -fmessage-length=0  -std=c++11   -Wno-c++98-compat

#	Release version
#CXXFLAGS =	-O3    -Wall -fmessage-length=0

BUILD=		build

SRC  =		$(wildcard *.cpp)

TEMPLATE_SRC =

BLACKLISTED_SRC =

USEFUL_SRC = $(filter-out $(TEMPLATE_SRC) $(BLACKLISTED_SRC), $(SRC))

OBJ  =		$(patsubst %.cpp, %.o, $(USEFUL_SRC) )

OBJS =		$(addprefix ../$(BUILD)/, $(OBJ) )

SDL  =		`sdl-config --cflags --libs`

#LDFLAGS	=

#LDLIBS	=

TARGET_DIR = bin

TARGET =	../$(TARGET_DIR)/libdcel.so


BLUE   = @echo -e -n '\033[1;34m'
NORMAL = @echo -e -n '\033[1;0m'
RED    = @echo -e -n '\033[1;31m'
GREEN  = @echo -e -n '\033[1;32m'
PURPLE = @echo -e -n '\033[0;35m'

#OUTPUT_OPTION = -o $@
#COMPILE.cpp = $(COMPILE.cc)
#COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c

../$(BUILD)/%.o: %.cpp
	$(BLUE)
	@echo -n "Compiling...  " $@
	$(NORMAL)
	@echo "\t\twith flags: " $(CXXFLAGS)
	@$(COMPILE.cpp)  -fPIC  $(OUTPUT_OPTION)  $<
	$(GREEN)
	@echo "\t-> compiled"
	$(NORMAL)

#LINK.cpp = $(LINK.cc)
#LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)

$(TARGET):	$(OBJS)
	$(PURPLE)
	@echo "Linking...   " $@
	$(NORMAL)
	@$(LINK.cpp)  -shared  $(OUTPUT_OPTION)  $^
	$(GREEN)
	@echo "\t-> linked"
	$(NORMAL)

all:	build_msg  $(TARGET)

.PHONY: build_msg
build_msg:
	$(GREEN)
	@printf "\nBuilding... $(TARGET)\n"
	$(NORMAL)


#RM = rm -f

clean:
	$(RED)
	@$(RM)  -rv  $(OBJS)  $(TARGET)  *~
	$(NORMAL)

test:
	@printf "CXX:" $(CXX)
	@printf "obj:" $(OBJ)
	@printf "CXXFLAGS: %s\n" $(CXXFLAGS)
	@printf "CPPFLAGS: %s\n" $(CPPFLAGS)
	@printf "LDLIBS: %s\n" $(LDLIBS)
	@printf "LDFLAGS: %s\n" $(LDFLAGS)

