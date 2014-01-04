
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

TARGET =	$(TARGET_DIR)$(LAST_DIR)test


#	Targets
all:	build_msg	$(TARGET)

$(BUILD)%.o: %.cpp
	$(call make-depend,$<,$@,$(subst .o,.d,$@))
	$(call compile-src-to-exec,	$@, $<)

$(TARGET):	$(OBJS)
	$(call link-objs-to-exec,	$@, $^)



