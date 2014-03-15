
#-------------------------------------------------------------------------------
#	Library part
#-------------------------------------------------------------------------------

thvch-dir = $(call module-directory,thvch)
thvch-src = $(call module-sources,$(thvch-dir))
thvch-inc = $(call module-includes,$(thvch-dir))
thvch-obj = $(call module-objects,$(thvch-src))
thvch-dep = $(call module-dependencies,$(thvch-obj))
thvch-lib = $(call module-library,$(thvch-dir))

#	E.g. thvch-target-with-prerequisites
define thvch-target-with-prerequisites

#	E.g. thvch-build-message
.PHONY: thvch-build-message
thvch-build-message:
	$(call build-message, $(thvch-lib))

#	E.g. thvch-post-build-message
.PHONY: thvch-post-build-message
thvch-post-build-message:
	$(call post-build-message)

#	E.g. build-x86_64/thvch/obj/%.o: thvch/src/%.cpp
$(call module-objects-target, thvch):

#	E.g. build-x86_64/thvch/bin/libthvch.so: build-x86_64/thvch/obj/*.o
$(thvch-lib):

#	\brief	This is public target.
#	E.g. build-x86_64/thvch/bin/libthvch.so-target:	thvch-build-message					\
#													build-x86_64/thvch/bin/libthvch.so	\
#													thvch-post-build-message
.PHONY: $(thvch-lib)-target
$(thvch-lib)-target:	thvch-build-message		\
						$(thvch-lib)			\
						thvch-post-build-message
endef


#-------------------------------------------------------------------------------
#	Test part
#-------------------------------------------------------------------------------

thvch-test-dir = $(call module-test-directory,thvch)
thvch-test-src = $(call module-test-sources,$(thvch-test-dir))
thvch-test-inc = $(call module-test-includes,$(thvch-test-dir))  $(addsuffix /include,dh dcel)
thvch-test-obj = $(call module-test-objects,$(thvch-test-src))
thvch-test-dep = $(call module-test-dependencies,$(thvch-test-obj))
thvch-test-exe = $(call module-test-executable,$(thvch-test-dir))


#	test dir prefix. E.g. thvch-test
thvch-tdp = $(subst /,-,$(thvch-test-dir))

#	$(call thvch-test-preset-link-flags)
define $(thvch-tdp)-preset-link-flags

	#	E.g. thvch-test-dirs-of-libraries-to-link = build-x86_64/thvch/bin/
	$(eval $(thvch-tdp)-dirs-of-libraries-to-link = $(call module-linked-dir,thvch))

	LDFLAGS =	$(addprefix -L,$($(thvch-tdp)-dirs-of-libraries-to-link))	\
				$(addprefix $(WL_PATH_PF),$($(thvch-tdp)-dirs-of-libraries-to-link))

	#	libcppuint-1.12-1 and libcppuint-dev packages needed
	$(thvch-tdp)-libraries-to-link = cppunit
endef

#	$(call thvch-test-reset-link-flags)
define $(thvch-tdp)-reset-link-flags
	LDFLAGS =
endef

#	E.g. thvch-test-target-with-prerequisites
define $(thvch-tdp)-target-with-prerequisites

#	E.g. thvch-test-build-message
.PHONY: $(thvch-tdp)-build-message
$(thvch-tdp)-build-message:
	$(call build-message, $(thvch-test-exe))

#	E.g. thvch-test-post-build-message
.PHONY: $(thvch-tdp)-post-build-message
$(thvch-tdp)-post-build-message:
	$(call post-build-message)

#	E.g. build-x86_64/thvch/test/obj/%.o: thvch/test/src/%.cpp
$(call module-test-objects-target,$(thvch-test-dir)): $(call module-test-objects-prerequisites,$(thvch-test-dir))
	$(eval $(call preset-compilation-flags))
	$(call make-depend,$$<,$$@,$$(subst .o,.d,$$@),$(thvch-test-inc))
	$(call compile-sources-to-test-objects,$$@,$$<,$(thvch-test-inc))
	$(eval $(call  reset-compilation-flags))

#	E.g. build-x86_64/thvch/test/bin/thvchtest: build-x86_64/thvch/test/obj/*.o
$(thvch-test-exe): $(thvch-test-obj)
	$(eval $(call $(thvch-tdp)-preset-link-flags))
	$(call link-test-objects-to-executable,$$@,$$^,$($(thvch-tdp)-libraries-to-link))
	$(eval $(call $(thvch-tdp)-reset-link-flags))

#	\brief	This is public target.
#	E.g. build-x86_64/thvch/test/bin/thvchtest-target:	build-x86_64/thvch/bin/libthvch.so-target	\
#														thvch-test-build-message					\
#														build-x86_64/thvch/test/bin/thvchtest		\
#														thvch-test-post-build-message
.PHONY: $(thvch-test-exe)-target
$(thvch-test-exe)-target:	$(thvch-lib)-target					\
							$(thvch-tdp)-build-message			\
							$(thvch-test-exe)					\
							$(thvch-tdp)-post-build-message

#	E.g. thvch-run-test-message
.PHONY: thvch-run-test-message
thvch-run-test-message:
	$(call test-message, $(thvch-test-exe))

#	E.g. thvch-post-run-test-message
.PHONY: thvch-post-run-test-message
thvch-post-run-test-message:
	$(call post-test-message)

#	E.g. thvch-run-test
.PHONY: thvch-run-test
thvch-run-test:
	@$(addprefix ./,$(thvch-test-exe)) || :

#	\brief	This is public target.
#	E.g. thvch-run-test-target:		build-x86_64/thvch/test/bin/thvchtest-target	\
#									thvch-run-test-message							\
#									thvch-run-test									\
#									thvch-post-run-test-message
.PHONY: thvch-run-test-target
thvch-run-test-target:	$(thvch-test-exe)-target	\
						thvch-run-test-message		\
						thvch-run-test				\
						thvch-post-run-test-message

#	E.g. thvch-debug-test-target:  build-x86_64/thvch/test/bin/thvchtest-target
.PHONY: thvch-debug-test-target
thvch-debug-test-target: $(thvch-test-exe)-target
	$(call start-debugging,$(thvch-test-exe))

endef














