#
#	Necessary packages:
#	===================
#
#		- libcppuint-1.12-1
#		- libcppuint-dev
#

CXX = clang++

#	Debug version
CXXFLAGS =	-O0 -g -Weverything  -fmessage-length=0  --std=c++11				\
													-Wno-c++98-compat			\
													-Wno-global-constructors	\
													-Wno-exit-time-destructors
#CXXFLAGS =	-O0 -g -Wall -fmessage-length=0

#	Release version
#CXXFLAGS =	-O3    -Wall -fmessage-length=0

BUILD=		build

#CH_SRC	=	polytope.cpp

SRC  =		$(wildcard *.cpp)
#$(CH_SRC)

OBJ  =		$(patsubst %.cpp, %.o, $(SRC) )

OBJS =		$(addprefix ../$(BUILD)/, $(OBJ) )

INC  =		-I../../src/

LIB_PATH =	../../bin/

LDFLAGS =	-L$(LIB_PATH)  -Wl,-rpath,$(LIB_PATH)

LDLIBS =	-lcppunit  -ldcel

TARGET_DIR = bin

TARGET =	../$(TARGET_DIR)/dceltest

BLUE   = @echo -e -n '\033[1;34m'
NORMAL = @echo -e -n '\033[1;0m'
RED    = @echo -e -n '\033[1;31m'
GREEN  = @echo -e -n '\033[1;32m'
YELLOW = @echo -e -n '\033[0;33m'
PURPLE = @echo -e -n '\033[0;35m'
CYAN   = @echo -e -n '\033[0;36m'


../$(BUILD)/%.o: %.cpp
	$(BLUE)
	@echo -n "Compiling...  " $@
	$(NORMAL)
	@echo "\twith flags: " $(CXXFLAGS)
	@$(CXX)  $<  $(CXXFLAGS)  $(INC)  -c  -o  $@
	$(GREEN)
	@echo "\t-> compiled"
	$(NORMAL)


$(TARGET):	$(OBJS)
	$(PURPLE)
	@echo "Linking...   " $@
	$(NORMAL)
	@$(CXX)  -o  $@  $(OBJS)   $(LDLIBS)  $(LDFLAGS)
	$(GREEN)
	@echo "\t-> linked"
	$(NORMAL)


all:	$(TARGET)


clean:
	$(RED)
	@rm  -frv  $(OBJS)  $(TARGET)  *~
	$(NORMAL)

test:
	@echo
	@echo src: $(SRC)
	@echo
	@echo obj: $(OBJ)
	@echo
	@echo objs: $(OBJS)
	@echo
