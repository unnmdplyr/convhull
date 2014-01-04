

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
	CXXFLAGS	+= -O0 -g3
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

DEPS		= $(subst .o,.d,$(OBJS))

TARGET_DIR	= ../bin/


#	Functions

ifneq "$(MAKECMDGOALS)" "clean"
	-include $(DEPS)
endif

#DEPEND.cpp = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH)
DEPEND.cpp = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH)

# $(call make-depend, source-file, object-file, depend-file)
define make-depend
	$(CYAN)
	@printf "\tMake depend file...\t%s" "$3"
	$(NORMAL)
	@$(DEPEND.cpp)	-MM		\
					-MP		\
					-MF "$3"\
					-MT "$2"\
					$(INC)	\
					$1
	$(CYAN)
	@printf "\t...done.\n"
	$(NORMAL)
endef
#-MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"


#OUTPUT_OPTION = -o $@
#COMPILE.cpp = $(COMPILE.cc)
#COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c

# $(call compile-src-to-lib, target, srcs)
define compile-src-to-lib
	$(BLUE)
	@printf "Compiling...\t%s\n" $1
	$(NORMAL)
	@$(COMPILE.cpp)  -fPIC  $(OUTPUT_OPTION)  $2
	$(GREEN)
	@printf "\t-> compiled\n"
	$(NORMAL)
endef

#LINK.cpp = $(LINK.cc)
#LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)

# $(call link-objs-to-lib, target, objects)
define link-objs-to-lib
	$(PURPLE)
	@printf "Linking...\t%s\n" $1
	$(NORMAL)
	@$(LINK.cpp)  -shared  $(OUTPUT_OPTION)  $2
	$(GREEN)
	@printf "\t-> linked\n"
	$(NORMAL)
endef



#OUTPUT_OPTION = -o $@
#COMPILE.cpp = $(COMPILE.cc)
#COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c

# $(call compile-src-to-exec, target, srcs)
define compile-src-to-exec
	$(BLUE)
	@printf "Compiling...\t%s\n" $1
	$(NORMAL)
	@$(COMPILE.cpp)  $(INC)  -c  $(OUTPUT_OPTION)  $2
	$(GREEN)
	@printf "\t-> compiled\n"
	$(NORMAL)
endef

#LINK.cpp = $(LINK.cc)
#LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)

# $(call link-objs-to-exec, target, objects)
define link-objs-to-exec
	$(PURPLE)
	@printf "Linking...\t%s\n" $1
	$(NORMAL)
	@$(LINK.cpp)  $(LDLIBS)  $(OUTPUT_OPTION)  $2
	$(GREEN)
	@printf "\t-> linked\n"
	$(NORMAL)
endef


#	Targets
all:


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
	@$(RM)  -rv  $(OBJS)  $(TARGET)  $(addsuffix /*~,$(clean_pattern))  $(DEPS)
	$(NORMAL)

