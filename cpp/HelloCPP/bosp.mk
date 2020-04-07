
ifdef CONFIG_SAMPLES_CPP_HELLOCPP

# Targets provided by this project
.PHONY: samples_cpp_hellocpp clean_samples_cpp_hellocpp

# Add this to the "samples" targets
samples_cpp: samples_cpp_hellocpp
clean_samples_cpp: clean_samples_cpp_hellocpp

MODULE_SAMPLES_CPP_HELLOCPP=samples/cpp/HelloCPP

samples_cpp_hellocpp: external
	@echo
	@echo "==== Building HelloCPP ($(BUILD_TYPE)) ===="
	@echo " Using GCC    : $(CC)"
	@echo " Target flags : $(TARGET_FLAGS)"
	@echo " Sysroot      : $(PLATFORM_SYSROOT)"
	@echo " BOSP Options : $(CMAKE_COMMON_OPTIONS)"
	@[ -d $(MODULE_SAMPLES_CPP_HELLOCPP)/build/$(BUILD_TYPE) ] || \
		mkdir -p $(MODULE_SAMPLES_CPP_HELLOCPP)/build/$(BUILD_TYPE) || \
		exit 1
	@cd $(MODULE_SAMPLES_CPP_HELLOCPP)/build/$(BUILD_TYPE) && \
		CC=$(CC) CFLAGS="$(TARGET_FLAGS)" \
		CXX=$(CXX) CXXFLAGS="$(TARGET_FLAGS)" \
		cmake $(CMAKE_COMMON_OPTIONS) ../.. || \
		exit 1
	@cd $(MODULE_SAMPLES_CPP_HELLOCPP)/build/$(BUILD_TYPE) && \
		make -j$(CPUS) install || \
		exit 1

clean_samples_cpp_hellocpp:
	@echo
	@echo "==== Clean-up HelloCPP Application ===="
	@[ ! -f $(BUILD_DIR)/usr/bin/hellocpp ] || \
		rm -f $(BUILD_DIR)/etc/bbque/recipes/HelloCPP*; \
		rm -f $(BUILD_DIR)/usr/bin/hellocpp*
	@rm -rf $(MODULE_SAMPLES_CPP_HELLOCPP)/build
	@echo

else # CONFIG_SAMPLES_CPP_HELLOCPP

samples_cpp_hellocpp:
	$(warning HelloCPP module disabled by BOSP configuration)
	$(error BOSP compilation failed)

endif # CONFIG_SAMPLES_CPP_HELLOCPP

