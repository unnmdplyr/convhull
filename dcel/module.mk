
#-------------------------------------------------------------------------------
#	Library part
#-------------------------------------------------------------------------------

current-makefile := $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
current-dir := $(subst /,,$(dir $(current-makefile)))

$(current-dir)-dir = $(call module-directory,$(current-dir))
$(current-dir)-src = $(call module-sources,$($(current-dir)-dir))
$(current-dir)-inc = $(call module-includes,$($(current-dir)-dir))
$(current-dir)-obj = $(call module-objects,$($(current-dir)-src))
$(current-dir)-lib = $(call module-library,$($(current-dir)-dir))

#	E.g. dcel-target-with-prerequisites
define $(current-dir)-target-with-prerequisites

#	E.g. dcel-build-message
.PHONY: $(current-dir)-build-message
$(current-dir)-build-message:
	$(call build-message, $($(current-dir)-lib))

#	E.g. dcel-post-build-message
.PHONY: $(current-dir)-post-build-message
$(current-dir)-post-build-message:
	$(call post-build-message)

#	E.g. build-x86_64/dcel/obj/%.o: dcel/src/%.cpp
$(call module-objects-target, $(current-dir)): $(call module-objects-prerequisites, $(current-dir))
	$(call make-depend,$$<,$$@,$$(subst .o,.d,$$@),)
	$(call compile-sources-to-objects,$$@,$$<)

#	E.g. build-x86_64/dcel/bin/libdcel.so: build-x86_64/dcel/obj/*.o
$($(current-dir)-lib): $($(current-dir)-obj)
	$(call link-objects-to-library,$$@,$$^)

#	\brief	This is public target.
#	E.g. build-x86_64/dcel/bin/libdcel.so-target:	dcel-build-message					\
#													build-x86_64/dcel/bin/libdcel.so	\
#													dcel-post-build-message
.PHONY: $($(current-dir)-lib)-target
$($(current-dir)-lib)-target:	$(current-dir)-build-message		\
								$($(current-dir)-lib)				\
								$(current-dir)-post-build-message
endef


#-------------------------------------------------------------------------------
#	Test part
#-------------------------------------------------------------------------------

$(current-dir)-test-dir = $(call module-test-directory,$(current-dir))
$(current-dir)-test-src = $(call module-test-sources,$($(current-dir)-test-dir))
$(current-dir)-test-inc = $(call module-test-includes,$($(current-dir)-test-dir))
$(current-dir)-test-obj = $(call module-test-objects,$($(current-dir)-test-src))
$(current-dir)-test-exe = $(call module-test-executable,$($(current-dir)-test-dir))

#	E.g. build-x86_64/dcel/bin/
dirs-of-libraries-to-link = $(call module-linked-dir,$(current-dir))

WL_PATH_PF = -Wl,-rpath,

#	$(call preset-link-flags)
define preset-link-flags

	LDFLAGS =	$(addprefix -L,$(dirs-of-libraries-to-link))	\
				$(addprefix $(WL_PATH_PF),$(dirs-of-libraries-to-link))

	#	libcppuint-1.12-1 and libcppuint-dev packages needed
	libraries-to-link = cppunit  $(current-dir)
endef

#	$(call reset-link-flags)
define reset-link-flags
	WL_PATH_PF =
	LDFLAGS =
endef

#	E.g. dcel-test-target-with-prerequisites
define $(subst /,-,$($(current-dir)-test-dir))-target-with-prerequisites

#	E.g. dcel-test-build-message
.PHONY: $(subst /,-,$($(current-dir)-test-dir))-build-message
$(subst /,-,$($(current-dir)-test-dir))-build-message:
	$(call build-message, $($(current-dir)-test-exe))

#	E.g. dcel-test-post-build-message
.PHONY: $(subst /,-,$($(current-dir)-test-dir))-post-build-message
$(subst /,-,$($(current-dir)-test-dir))-post-build-message:
	$(call post-build-message)

#	E.g. build-x86_64/dcel/test/obj/%.o: dcel/test/src/%.cpp
$(call module-test-objects-target,$($(current-dir)-test-dir)): $(call module-test-objects-prerequisites,$($(current-dir)-test-dir))
	$(eval $(call preset-compilation-flags))
	$(call make-depend,$$<,$$@,$$(subst .o,.d,$$@),$($(current-dir)-test-inc))
	$(call compile-sources-to-test-objects,$$@,$$<,$($(current-dir)-inc))
	$(eval $(call  reset-compilation-flags))

#	E.g. build-x86_64/dcel/test/bin/dceltest: build-x86_64/dcel/test/obj/*.o
$($(current-dir)-test-exe): $($(current-dir)-test-obj)
	$(eval $(call preset-link-flags))
	$(call link-test-objects-to-executable,$$@,$$^,$(libraries-to-link))
	$(eval $(call  reset-link-flags))

#	\brief	This is public target.
#	E.g. build-x86_64/dcel/test/bin/dceltest-target:	build-x86_64/dcel/bin/libdcel.so-target	\
#														dcel-test-build-message					\
#														build-x86_64/dcel/test/bin/dceltest		\
#														dcel-test-post-build-message			\
.PHONY: $($(current-dir)-test-exe)-target
$($(current-dir)-test-exe)-target:	$($(current-dir)-lib)-target								\
									$(subst /,-,$($(current-dir)-test-dir))-build-message		\
									$($(current-dir)-test-exe)									\
									$(subst /,-,$($(current-dir)-test-dir))-post-build-message

#	E.g. dcel-run-test-message
.PHONY: $(current-dir)-run-test-message
$(current-dir)-run-test-message:
	$(call test-message, $($(current-dir)-test-exe))

#	E.g. dcel-post-run-test-message
.PHONY: $(current-dir)-post-run-test-message
$(current-dir)-post-run-test-message:
	$(call post-test-message)

#	E.g. dcel-run-test
.PHONY: $(current-dir)-run-test
$(current-dir)-run-test:
	@$(addprefix ./,$($(current-dir)-test-exe)) || :

#	\brief	This is public target.
#	E.g. dcel-run-test-target:  build-x86_64/dcel/test/bin/dceltest-target	\
#								dcel-run-test-message						\
#								dcel-run-test								\
#								dcel-post-run-test-message
.PHONY: $(current-dir)-run-test-target
$(current-dir)-run-test-target: $($(current-dir)-test-exe)-target	\
								$(current-dir)-run-test-message		\
								$(current-dir)-run-test				\
								$(current-dir)-post-run-test-message
endef














