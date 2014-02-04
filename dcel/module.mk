
#-------------------------------------------------------------------------------
#	Library part
#-------------------------------------------------------------------------------

current-dir := dcel

$(current-dir)-dir = $(call module-directory,$(current-dir))
$(current-dir)-src = $(call module-sources,$($(current-dir)-dir))
$(current-dir)-inc = $(call module-includes,$($(current-dir)-dir))
$(current-dir)-obj = $(call module-objects,$($(current-dir)-src))
$(current-dir)-lib = $(call module-library,$($(current-dir)-dir))

#	E.g. dcel-target-with-prerequisites
define $(current-dir)-target-with-prerequisites

#	E.g. build-x86_64/dcel/obj/%.o: dcel/src/%.cpp
$(call module-objects-target, $(current-dir)): $(call module-objects-prerequisites, $(current-dir))
	$(call make-depend,$$<,$$@,$$(subst .o,.d,$$@),)
	$(call compile-sources-to-objects,$$@,$$<)

#	E.g. build-x86_64/dcel/bin/libdcel.so: build-x86_64/dcel/obj/*.o
$($(current-dir)-lib): $($(current-dir)-obj)
	$(call link-objects-to-library,$$@,$$^)
endef


#-------------------------------------------------------------------------------
#	Test part
#-------------------------------------------------------------------------------

$(current-dir)-test-dir = $(call module-test-directory,$(current-dir))
$(current-dir)-test-src = $(call module-test-sources,$($(current-dir)-test-dir))
$(current-dir)-test-inc = $(call module-test-includes,$($(current-dir)-test-dir))
$(current-dir)-test-obj = $(call module-test-objects,$($(current-dir)-test-src))
$(current-dir)-test-exe = $(call module-test-executable,$($(current-dir)-test-dir))


ifeq ("$(CXX)","clang++")
	CXXFLAGS	+=	-Wno-global-constructors	\
					-Wno-exit-time-destructors
endif

#	E.g. dcel-test-target-with-prerequisites
define $(subst /,-,$($(current-dir)-test-dir))-target-with-prerequisites

#	E.g. build-x86_64/dcel/bin/
dirs-of-libraries-to-link = $(warning <<<<---------  $(call module-linked-dir,$(current-dir)))$(call module-linked-dir,$(current-dir))

$(warning ---->>> $(dirs-of-libraries-to-link))

WL_PATH_PF = -Wl,-rpath,

LDFLAGS =	$(addprefix -L,$(dirs-of-libraries-to-link))	\
			$(addprefix $(WL_PATH_PF),$(dirs-of-libraries-to-link))

libraries-to-link = cppunit  $(current-dir)

#	E.g. build-x86_64/dcel/test/obj/%.o: dcel/test/src/%.cpp
$(call module-test-objects-target,$($(current-dir)-test-dir)): $(call module-test-objects-prerequisites,$($(current-dir)-test-dir))
	$(call make-depend,$$<,$$@,$$(subst .o,.d,$$@),$$($$(current-dir)-test-inc))
	$(call compile-sources-to-test-objects,$$@,$$<)

#	E.g. build-x86_64/dcel/test/bin/dceltest:  build-x86_64/dcel/bin/libdcel.so  build-x86_64/dcel/test/obj/*.o
$($(current-dir)-test-exe): $($(current-dir)-lib) $($(current-dir)-test-obj)
	$(call link-test-objects-to-executable,$$@,$$^,$$(libraries-to-link))
endef











