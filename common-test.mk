

include ../../../common.mk


ifeq ("$(CXX)","clang++")
	CXXFLAGS	+=	-Wno-global-constructors	\
					-Wno-exit-time-destructors
endif


INC			= -I../../src/

LIB_PATH	= ../../bin/

WL_PATH_PF	= -Wl,-rpath,

LDFLAGS		=	$(addprefix				-L,$(LIB_PATH))	\
				$(addprefix	 $(WL_PATH_PF),$(LIB_PATH))

LIBS		= cppunit  dcel

LDLIBS		= $(addprefix -l,$(LIBS))

CURR_PWD	= "$(shell  cd ../../; pwd)"
LAST_DIR	= "$(shell basename $(CURR_PWD))"

#TARGET_DIR = ../bin/

TARGET =	$(TARGET_DIR)$(LAST_DIR)test


#	Targets
all:	$(TARGET)


#OUTPUT_OPTION = -o $@
#COMPILE.cpp = $(COMPILE.cc)
#COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c

$(BUILD)%.o: %.cpp
	$(BLUE)
	@printf "Compiling...\t%s\n" $@
	$(NORMAL)
	@$(COMPILE.cpp)  $(INC)  -c  $(OUTPUT_OPTION)  $<
	$(GREEN)
	@printf "\t-> compiled\n"
	$(NORMAL)


#LINK.cpp = $(LINK.cc)
#LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)

$(TARGET):	$(OBJS)
	$(PURPLE)
	@printf "Linking...\t%s\n" $@
	$(NORMAL)
	@$(LINK.cpp)  $(LDLIBS)  $(OUTPUT_OPTION)  $^
	$(GREEN)
	@printf "\t-> linked\n"
	$(NORMAL)



