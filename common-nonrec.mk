
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
build-dir := build-$(shell uname -i)

#	E.g.	build-x86_64/dh  build-x86_64/dcel
build-dirs := $(addprefix $(build-dir)/,$(module-names))

#	$(call module-binary-dir, module-name)
module-binary-dir = $(addsuffix /$(binary-dir),					\
						$(addprefix $(build-dir)/,$1))

#	$(call module-binary-dir, module-name)
module-linked-dir = $(addsuffix /$(linked-dir),					\
						$(addprefix $(build-dir)/,$1))

#	Creating the build related directories
unused-var0 := $(shell mkdir -p $(build-dir) )
unused-var1 := $(shell mkdir -p $(build-dirs);					\
					mkdir -p $(foreach mod,$(module-names),$(call module-binary-dir,$(mod)));	\
					mkdir -p $(foreach mod,$(module-names),$(call module-linked-dir,$(mod))))

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
	@$(DEPEND.cpp)	-MM		\
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
	@$(COMPILE.cpp)  -fPIC  -o $1  $2
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
	@$(LINK.cpp)  -shared  -o $1  $2
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

#	Creating the build related directories
unused-var2 := $(shell mkdir -p $(test-dirs) )
unused-var3 := $(shell	mkdir -p $(foreach mod,$(module-names),			\
											$(call module-test-binary-dir,$(mod)));	\
						mkdir -p $(foreach mod,$(module-names),			\
											$(call module-test-linked-dir,$(mod))))

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
	@$(COMPILE.cpp)  $(addprefix -I,$3)  -c  -o $1  $2
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
	@$(LINK.cpp)  $(addprefix -l,$3)  -o $1  $2
	$(GREEN)
	@printf "\t-> linked\n"
	$(NORMAL)
endef


#-------------------------------------------------------------------------------
#	Targets
#-------------------------------------------------------------------------------

programs :=
libraries :=

#	$(call module-targets, module-name)
define module-targets
	include $(addsuffix /module.mk,$1)

	libraries += $$($1-lib)
	programs  += $$($1-test-exe)
endef

.PHONY: all
all:

$(eval $(foreach mod,$(module-names),							\
	$(eval $(call module-targets,$(mod)))))

$(eval $(foreach mod,$(module-names),							\
	$(eval $(call $(mod)-target-with-prerequisites))))

$(eval $(foreach mod,$(module-names),							\
	$(eval $(call $(mod)-test-target-with-prerequisites))))

.PHONY: preparation
preparation:
#	@printf "%s \n" $(dcel-lib)
#	$(eval $(call module-targets,dcel))
	@printf "dir: %s \n" $(dcel-dir)
	@printf "src: %s \n" $(dcel-src)
	@printf "inc: %s \n" $(dcel-inc)
	@printf "obj: %s \n" $(dcel-obj)
	@printf "lib: %s \n" $(dcel-lib)
	@printf "mod: %s \n" $(module-names)
	@printf "libraries: %s \n" $(libraries)
	@printf "modbindir: %s \n" $(call module-binary-dir,dcel)
	@printf "\n"
	@printf "test-dirs: %s \n" $(test-dirs)
	@printf "test-dir: %s \n" $(dcel-test-dir)
	@printf "test-src: %s \n" $(dcel-test-src)
	@printf "test-inc: %s \n" $(dcel-test-inc)
	@printf "test-obj: %s \n" $(dcel-test-obj)
	@printf "test-exe: %s \n" $(dcel-test-exe)

.PHONY: all
all: preparation $(libraries) $(programs)

.PHONY: libraries
libraries: preparation  $(libraries)
	@printf "libraries: %s \n" $(libraries)



#RM = rm -f

clean:
	$(RM) -rv  $(build-dir)

.PHONY: test
test:
	@printf "%s \n" 	$(dcel-sources)
	@printf "%s \n" 	$(dcel-lib)
#@printf "module-dirs: %s\n" $(call module-dirs, .)
#@printf "%s\n" $(build-dir)
#@printf "%s\n" $(build-dirs)
#@printf "module names: %s\n" $(module-names)
#	$(eval $(call assemble-module-sources,dcel))
#@printf "src: %s\n" $(dcel-source)
#@printf "inc: %s\n" $(dcel-includes)
#@printf "obj: %s %s\n" $(call source-to-object,$(dcel-source))
#	$(eval $(call assemble-module-objects,dcel))
#	@printf "obj3: %s\n" $(dcel-objects)
#	$(eval $(call module-targets,dcel))
#	$(dcel-lib)



#	$(call module-target-prerequisites, module-name)
#define module-target-prerequisites
#$(warning ramper $$($1-lib))
#$($1-lib): $($1-obj)
#	$(eval $(call link-objects-to-library,$@,$^))
#endef

#$(eval $(foreach mod,$(module-names),				\
#	$(eval $(call module-targets,$(mod)))))

#$(eval $(call module-target-prerequisites,dcel))

#$(eval $(foreach mod,$(module-names),				\
#	$(eval $(call module-target-prerequisites,$(mod)))))

#$(foreach mod,$(module-names),			\
#	$(eval $(call module-target-prerequisites,$(mod))))
