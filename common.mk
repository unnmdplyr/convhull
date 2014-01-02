

#	Modify these variables according to the wishes
CXX := clang++
#RELEASE :=

CXXFLAGS	+=	-fmessage-length=0

ifeq ("$(CXX)","clang++")
	CXXFLAGS	+=	-Weverything	--std=c++11	-Wno-c++98-compat
else
	CXXFLAGS	+=	-Wall			--std=c++11
endif

ifdef RELEASE
	CXXFLAGS	+= -O3
else
	CXXFLAGS	+= -O0 -g
endif


#	Colors
BLUE   = @printf '\033[1;34m'
NORMAL = @printf '\033[1;0m'
RED    = @printf '\033[1;31m'
GREEN  = @printf '\033[1;32m'
YELLOW = @printf '\033[0;33m'
PURPLE = @printf '\033[0;35m'
CYAN   = @printf '\033[0;36m'



#	Common variables
BUILD		= ../build/

SRC			= $(wildcard *.cpp)

NOT_DIR_OBJS= $(patsubst %.cpp, %.o, $(SRC) )

OBJS		= $(addprefix $(BUILD), $(NOT_DIR_OBJS) )

CURR_PWD	= "$(shell  cd ../; pwd)"
LAST_DIR	= "$(shell basename $(CURR_PWD))"

TARGET_DIR = ../bin/

#TARGET =	$(TARGET_DIR)lib$(LAST_DIR).so


#	Targets
all:	build_msg	$(TARGET)

#OUTPUT_OPTION = -o $@
#COMPILE.cpp = $(COMPILE.cc)
#COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c

$(BUILD)%.o: %.cpp
	$(BLUE)
	@printf "Compiling...\t%s\n" $@
	$(NORMAL)
	@$(COMPILE.cpp)  -fPIC  $(OUTPUT_OPTION)  $<
	$(GREEN)
	@printf "\t-> compiled\n"
	$(NORMAL)

#LINK.cpp = $(LINK.cc)
#LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)

$(TARGET):	$(OBJS)
	$(PURPLE)
	@printf "Linking...\t%s\n" $@
	$(NORMAL)
	@$(LINK.cpp)  -shared  $(OUTPUT_OPTION)  $^
	$(GREEN)
	@printf "\t-> linked\n"
	$(NORMAL)


.PHONY: build_msg
build_msg:
	$(GREEN)
	@printf "\nBuilding...\t%s\n"	$(TARGET)
	$(NORMAL)
	@printf "\twith flags: %s\n" "$(CXXFLAGS)"


.PHONY: clean_msg
clean_msg:
	$(GREEN)
	@printf "\nCleaning... $(TARGET)\n"
	$(NORMAL)


#RM = rm -f

clean_pattern = .  ..  ../..

clean:	clean_msg
	$(RED)
	@$(RM)  -rv  $(OBJS)  $(TARGET)  $(addsuffix /*~,$(clean_pattern))
	$(NORMAL)

