
#-------------------------------------------------------------------------------
#	Library part
#-------------------------------------------------------------------------------

#current-makefile := $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
#current-dir := $(subst /,,$(dir $(current-makefile)))

dh-dir = $(call module-directory,dh)
dh-src = $(call module-sources,$(dh-dir))
dh-inc = $(call module-includes,$(dh-dir))
dh-obj = $(call module-objects,$(dh-src))
dh-dep = $(call module-dependencies,$(dh-obj))
dh-lib = $(call module-library,$(dh-dir))

#	E.g. dh-target-with-prerequisites
define dh-target-with-prerequisites

#	E.g. dh-build-message
.PHONY: dh-build-message
dh-build-message:
	$(call build-message, $(dh-lib))

#	E.g. dh-post-build-message
.PHONY: dh-post-build-message
dh-post-build-message:
	$(call post-build-message)

#	E.g. build-x86_64/dh/obj/%.o: dh/src/%.cpp
$(call module-objects-target, dh): $(call module-objects-prerequisites, dh)
	$(call make-depend,$$<,$$@,$$(subst .o,.d,$$@),)
	$(call compile-sources-to-objects,$$@,$$<)

#	E.g. build-x86_64/dh/bin/libdh.so: build-x86_64/dh/obj/*.o
$(dh-lib): $(dh-obj)
	$(call link-objects-to-library,$$@,$$^)

#	\brief	This is public target.
#	E.g. build-x86_64/dh/bin/libdh.so-target:	dh-build-message					\
#													build-x86_64/dh/bin/libdh.so	\
#													dh-post-build-message
.PHONY: $(dh-lib)-target
$(dh-lib)-target:	dh-build-message		\
								$(dh-lib)				\
								dh-post-build-message
endef


#-------------------------------------------------------------------------------
#	Test part
#-------------------------------------------------------------------------------

dh-test-dir = $(call module-test-directory,dh)
dh-test-src = $(call module-test-sources,$(dh-test-dir))
dh-test-inc = $(call module-test-includes,$(dh-test-dir))
dh-test-obj = $(call module-test-objects,$(dh-test-src))
dh-test-dep = $(call module-test-dependencies,$(dh-test-obj))
dh-test-exe = $(call module-test-executable,$(dh-test-dir))


#	test dir prefix. E.g. dh-test
dh-tdp = $(subst /,-,$(dh-test-dir))

#	$(call dh-test-preset-link-flags)
define $(dh-tdp)-preset-link-flags
	
	#	E.g. dh-test-dirs-of-libraries-to-link = build-x86_64/dh/bin/
	$(eval $(dh-tdp)-dirs-of-libraries-to-link = $(call module-linked-dir,dh))
	
	LDFLAGS =	$(addprefix -L,$($(dh-tdp)-dirs-of-libraries-to-link))	\
				$(addprefix $(WL_PATH_PF),$($(dh-tdp)-dirs-of-libraries-to-link))

	#	libcppuint-1.12-1 and libcppuint-dev packages needed
	$(dh-tdp)-libraries-to-link = cppunit  dh
endef

#	$(call dh-test-reset-link-flags)
define $(dh-tdp)-reset-link-flags
	LDFLAGS =
endef

#	E.g. dh-test-target-with-prerequisites
define $(dh-tdp)-target-with-prerequisites

#	E.g. dh-test-build-message
.PHONY: $(dh-tdp)-build-message
$(dh-tdp)-build-message:
	$(call build-message, $(dh-test-exe))

#	E.g. dh-test-post-build-message
.PHONY: $(dh-tdp)-post-build-message
$(dh-tdp)-post-build-message:
	$(call post-build-message)

#	E.g. build-x86_64/dh/test/obj/%.o: dh/test/src/%.cpp
$(call module-test-objects-target,$(dh-test-dir)): $(call module-test-objects-prerequisites,$(dh-test-dir))
	$(eval $(call preset-compilation-flags))
	$(call make-depend,$$<,$$@,$$(subst .o,.d,$$@),$(dh-test-inc))
	$(call compile-sources-to-test-objects,$$@,$$<,$(dh-inc))
	$(eval $(call  reset-compilation-flags))

#	E.g. build-x86_64/dh/test/bin/dhtest: build-x86_64/dh/test/obj/*.o
$(dh-test-exe): $(dh-test-obj)
	$(eval $(call $(dh-tdp)-preset-link-flags))
	$(call link-test-objects-to-executable,$$@,$$^,$($(dh-tdp)-libraries-to-link))
	$(eval $(call $(dh-tdp)-reset-link-flags))

#	\brief	This is public target.
#	E.g. build-x86_64/dh/test/bin/dhtest-target:	build-x86_64/dh/bin/libdh.so-target	\
#													dh-test-build-message				\
#													build-x86_64/dh/test/bin/dhtest		\
#													dh-test-post-build-message			\
.PHONY: $(dh-test-exe)-target
$(dh-test-exe)-target:	$(dh-lib)-target								\
									$(dh-tdp)-build-message				\
									$(dh-test-exe)						\
									$(dh-tdp)-post-build-message

#	E.g. dh-run-test-message
.PHONY: dh-run-test-message
dh-run-test-message:
	$(call test-message, $(dh-test-exe))

#	E.g. dh-post-run-test-message
.PHONY: dh-post-run-test-message
dh-post-run-test-message:
	$(call post-test-message)

#	E.g. dh-run-test
.PHONY: dh-run-test
dh-run-test:
	@$(addprefix ./,$(dh-test-exe)) || :

#	\brief	This is public target.
#	E.g. dh-run-test-target:	build-x86_64/dh/test/bin/dhtest-target	\
#								dh-run-test-message						\
#								dh-run-test								\
#								dh-post-run-test-message
.PHONY: dh-run-test-target
dh-run-test-target: $(dh-test-exe)-target	\
					dh-run-test-message		\
					dh-run-test				\
					dh-post-run-test-message

#	E.g. dh-debug-test-target:  build-x86_64/dh/test/bin/dhtest-target
.PHONY: dh-debug-test-target
dh-debug-test-target: $(dh-test-exe)-target
	$(call start-debugging,$(dh-test-exe))

endef














