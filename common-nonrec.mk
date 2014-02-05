
#	Colors
BLUE   := @printf '\033[1;34m'
NORMAL := @printf '\033[1;0m'
RED    := @printf '\033[1;31m'
GREEN  := @printf '\033[1;32m'
YELLOW := @printf '\033[0;33m'
PURPLE := @printf '\033[0;35m'
CYAN   := @printf '\033[0;36m'

#	Modify these variables according to the wishes
CXX := clang++
RELEASE :=

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

#	Quiet or verbose
Q = @

#-------------------------------------------------------------------------------
#	Library part
#-------------------------------------------------------------------------------

source-dir := src
binary-dir := obj
linked-dir := bin

#	$(call module-dirs, directory)
#	E.g. ./dh ./dcel
module-dirs := $(subst /module.mk,,$(shell find $$1 -name "module.mk"))

#	E.g.   dh   dcel
module-names := $(notdir $(module-dirs))

#	E.g.	build-x86_64
build-dir-pre := build-$(shell uname -i)
ifdef RELEASE
	build-dir = $(addsuffix -release,$(build-dir-pre))
else
	build-dir = $(addsuffix -debug,$(build-dir-pre))
endif

#	E.g.	build-x86_64/dh  build-x86_64/dcel
build-dirs := $(addprefix $(build-dir)/,$(module-names))

#	$(call module-binary-dir, module-name)
module-binary-dir = $(addsuffix /$(binary-dir),					\
						$(addprefix $(build-dir)/,$1))

#	$(call module-binary-dir, module-name)
module-linked-dir = $(addsuffix /$(linked-dir),					\
						$(addprefix $(build-dir)/,$1))

ifneq "$(MAKECMDGOALS)" "clean"

	#	Creating the build related directories
	unused-var0 := $(shell  mkdir -p $(build-dir))
	unused-var1 := $(shell  mkdir -p $(build-dirs);					\
							mkdir -p $(foreach mod,$(module-names),	\
												$(call module-binary-dir,$(mod)));	\
							mkdir -p $(foreach mod,$(module-names),	\
												$(call module-linked-dir,$(mod))))
endif

# $(call source-to-object, source-file-list)
source-to-object =	$(addprefix $(build-dir)/,					\
						$(subst $(source-dir),$(binary-dir),	\
							$(subst .cpp,.o,$1)))

#	$(call module-directory, module-name)
module-directory = $1

#	$(call module-sources, module-name)
module-sources = $(wildcard $1/$(source-dir)/*.cpp)

#	$(call module-includes, module-name)
module-includes = $1/$(source-dir)

#	$(call module-objects, module-source-files)
module-objects = $(call source-to-object,$1)

#	$(call module-linked-object, module-name, linked-object-name)
module-linked-object =	$(addsuffix /$(linked-dir)/$2,	\
							$(addprefix $(build-dir)/,$1))

#	$(call module-library, module-name)
module-library = $(call module-linked-object,$1,lib$1.so)

#	E.g. build-x86_64/dcel/obj/%.o
#	$(call module-objects-target, module-name)
module-objects-target = $(addsuffix /%.o,$(call module-binary-dir,$1))

#	E.g. dcel/src/%.cpp
#	$(call module-objects-prerequisites, module-name)
module-objects-prerequisites = $(addsuffix /$(source-dir)/%.cpp,$1)


#DEPEND.cpp = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH)
DEPEND.cpp = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH)

# $(call make-depend, source-file, object-file, depend-file, include-dirs)
define make-depend
	$(CYAN)
	@printf "\tMake depend file...\t%s" "$3"
	$(NORMAL)
	$Q$(DEPEND.cpp)	-MM		\
					-MP		\
					-MF "$3"\
					-MT "$2"\
					$(addprefix -I,$4)	\
					$1
	$(CYAN)
	@printf "\t...done.\n"
	$(NORMAL)
endef
#-MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"


#OUTPUT_OPTION = -o $@
#COMPILE.cpp = $(COMPILE.cc)
#COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c

# $(call compile-sources-to-objects, target, source-files)
define compile-sources-to-objects
	$(BLUE)
	@printf "Compiling...\t%s\n" $1
	$(NORMAL)
	$Q$(COMPILE.cpp)  -fPIC  -o $1  $2
	$(GREEN)
	@printf "\t-> compiled\n"
	$(NORMAL)
endef


#LINK.cpp = $(LINK.cc)
#LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)

# $(call link-objects-to-library, target, object-files)
define link-objects-to-library
	$(PURPLE)
	@printf "Linking...\t%s\n" $1
	$(NORMAL)
	$Q$(LINK.cpp)  -shared  -o $1  $2
	$(GREEN)
	@printf "\t-> linked\n"
	$(NORMAL)
endef


#-------------------------------------------------------------------------------
#	Executable part
#-------------------------------------------------------------------------------

test-dir := test

#	E.g. build-x86_64/dcel/test/bin
#	$(call module-binary-dir, module-name)
module-test-binary-dir = $(addsuffix /$(test-dir)/$(binary-dir),		\
							$(addprefix $(build-dir)/,$1))

#	$(call module-binary-dir, module-name)
module-test-linked-dir = $(addsuffix /$(test-dir)/$(linked-dir),		\
							$(addprefix $(build-dir)/,$1))

#	E.g.	build-x86_64/dh/test  build-x86_64/dcel/test
test-dirs := $(addsuffix /$(test-dir),$(build-dirs))

ifneq "$(MAKECMDGOALS)" "clean"

	#	Creating the build related directories
	unused-var2 := $(shell  mkdir -p $(test-dirs))
	unused-var3 := $(shell	mkdir -p $(foreach mod,$(module-names),			\
												$(call module-test-binary-dir,$(mod)));	\
							mkdir -p $(foreach mod,$(module-names),			\
												$(call module-test-linked-dir,$(mod))))
endif

#	$(call module-test-directory, module-name)
module-test-directory = $(addsuffix /$(test-dir),$1)

##	$(call module-test-sources, module-name)
module-test-sources = $(call module-sources,$1)

##	$(call module-test-includes, module-name)
module-test-includes = $(call module-includes,$1)  $(call module-includes,$(subst /$(test-dir),,$1))

##	$(call module-test-objects, module-source-files)
module-test-objects = $(call source-to-object,$1)

##	$(call module-test-executable, module-name)
module-test-executable = $(call module-linked-object,$1,$(subst /,,$1))


#	E.g. build-x86_64/dcel/test/obj/%.o
#	$(call module-test-objects-target, module-name)
module-test-objects-target = $(addsuffix /%.o,$(call module-binary-dir,$1))

#	E.g. dcel/test/src/%.cpp
#	$(call module-test-objects-prerequisites, module-name)
module-test-objects-prerequisites = $(addsuffix /$(source-dir)/%.cpp,$1)

#OUTPUT_OPTION = -o $@
#COMPILE.cpp = $(COMPILE.cc)
#COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c

# $(call compile-sources-to-test-objects, target, sources, include-dirs)
define compile-sources-to-test-objects
	$(BLUE)
	@printf "Compiling...\t%s\n" $1
	$(NORMAL)
	$Q$(COMPILE.cpp)  $(addprefix -I,$3)  -o $1  $2
	$(GREEN)
	@printf "\t-> compiled\n"
	$(NORMAL)
endef

#LINK.cpp = $(LINK.cc)
#LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)

# $(call link-test-objects-to-executable, target, objects, library-dirs)
define link-test-objects-to-executable
	$(PURPLE)
	@printf "Linking...\t%s\n" $1
	$(NORMAL)
	$Q$(LINK.cpp)  $(addprefix -l,$3)  -o $1  $2
	$(GREEN)
	@printf "\t-> linked\n"
	$(NORMAL)
endef

#	$(call add-compilation-flags)
define add-compilation-flags
	CXXFLAGS +=	-Wno-global-constructors	\
				-Wno-exit-time-destructors
endef

#	$(call subtract-compilation-flags)
define subtract-compilation-flags
	CXXFLAGS = $(filter-out -Wno-global-constructors -Wno-exit-time-destructors,$(CXXFLAGS))
endef

#	$(call preset-compilation-flags)
define preset-compilation-flags
	$(if $(filter-out "clang++","$(CXX)"),,$(eval $(call add-compilation-flags)))
endef

#	$(call reset-compilation-flags)
define reset-compilation-flags
	$(if $(filter-out "clang++","$(CXX)"),,$(eval $(call subtract-compilation-flags)))
endef

#-------------------------------------------------------------------------------
#	Targets
#-------------------------------------------------------------------------------

programs :=
libraries :=

#	$(call module-inclusion, module-name)
define module-inclusion
	include $(addsuffix /module.mk,$1)
endef

#	$(call module-target-retrieval, module-name)
define module-target-retrieval
	libraries += $$($1-lib)-target
	programs  += $$($1-test-exe)-target
endef

#	$(call build-message, print-out)
define build-message
	$(GREEN)
	@printf "\nBuilding..."
	$(RED)
	@printf "\t%s\n"	$1
	$(NORMAL)
	@printf "\twith flags: %s\n" "$(CXXFLAGS)"
endef

#	$(call post-build-message)
define post-build-message
	$(GREEN)
	@printf "Build is done.\n"
	$(NORMAL)
endef

.PHONY: all
all:

$(eval $(foreach mod,$(module-names),							\
	$(eval $(call module-inclusion,$(mod)))))

$(eval $(foreach mod,$(module-names),							\
	$(eval $(call $(mod)-target-with-prerequisites))))

$(eval $(foreach mod,$(module-names),							\
	$(eval $(call $(mod)-test-target-with-prerequisites))))

$(eval $(foreach mod,$(module-names),							\
	$(eval $(call module-target-retrieval,$(mod)))))

.PHONY: all
all:  $(libraries)  $(programs)

.PHONY: run-tests
run-tests: $(programs)
	$(foreach mod,$(module-names),							\
					@$(addprefix ./,$($(mod)-test-exe)) ||:)

.PHONY: clean-message
clean-message:
	$(GREEN)
	@printf "\nCleaning... $(build-dir)\n"
	$(NORMAL)

#RM = rm -f

clean: clean-message
	$(RED)
	$Q$(RM) -rv  $(build-dir)
	$(NORMAL)


.PHONY: test
test:
	@printf "src: %s \n" 	$(dcel-sources)
	@printf "lib: %s \n" 	$(dcel-lib)




