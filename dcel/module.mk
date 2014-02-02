
current-dir := dcel

$(current-dir)-dir = $(call module-directory,$(current-dir))
$(current-dir)-src = $(call module-sources,$($(current-dir)-dir))
$(current-dir)-inc = $(call module-includes,$($(current-dir)-dir))
$(current-dir)-obj = $(call module-objects,$($(current-dir)-src))
$(current-dir)-lib = $(call module-library,$($(current-dir)-dir))

#   build-x86_64/dcel/obj/polytope.o
#$(BUILD)%.o: $(current-dir)
#	$(call make-depend,$<,$@,$(subst .o,.d,$@))
#	$(call compile-src-to-lib,$@,$<)

define $(current-dir)-target-with-prerequisites

$(addsuffix /%.o,$(call module-binary-dir,$(current-dir))): $(addsuffix /$(source-dir)/%.cpp,$(current-dir))
	$(call make-depend,$$<,$$@,$$(subst .o,.d,$$@))
	$(call compile-sources-to-objects,$$@,$$<)

$($(current-dir)-lib): $($(current-dir)-obj)
	$(call link-objects-to-library,$$@,$$^)
endef


