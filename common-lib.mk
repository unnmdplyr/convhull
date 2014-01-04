
include ../../common.mk


CURR_PWD	= "$(shell  cd ../; pwd)"
LAST_DIR	= "$(shell basename $(CURR_PWD))"

TARGET =	$(TARGET_DIR)lib$(LAST_DIR).so


#	Targets
all:	build_msg	$(TARGET)

$(BUILD)%.o: %.cpp
	$(call compile-src-to-lib,	$@, $<)

$(TARGET):	$(OBJS)
	$(call link-objs-to-lib,	$@, $^)

