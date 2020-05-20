
ifdef CONFIG_SAMPLES_PYTHON_PYSAMPLE

# Targets provided by this project
.PHONY: samples_python_pysample clean_samples_python_pysample

# Add this to the "samples" targets
samples_python: samples_python_pysample
clean_samples_python: clean_samples_python_pysample

MODULE_SAMPLES_PYTHON_PYSAMPLE=samples/python/PySample

samples_python_pysample: external
	@echo
	@echo "==== Building PySample ($(BUILD_TYPE)) ===="
	@echo " Using GCC    : $(CC)"
	@echo " Target flags : $(TARGET_FLAGS)"
	@echo " Sysroot      : $(PLATFORM_SYSROOT)"
	@echo " BOSP Options : $(CMAKE_COMMON_OPTIONS)"
	@[ -d $(MODULE_SAMPLES_PYTHON_PYSAMPLE)/build/$(BUILD_TYPE) ] || \
		mkdir -p $(MODULE_SAMPLES_PYTHON_PYSAMPLE)/build/$(BUILD_TYPE) || \
		exit 1
	@cd $(MODULE_SAMPLES_PYTHON_PYSAMPLE)/build/$(BUILD_TYPE) && \
		CC=$(CC) CFLAGS="$(TARGET_FLAGS)" \
		CXX=$(CXX) CXXFLAGS="$(TARGET_FLAGS)" \
		cmake $(CMAKE_COMMON_OPTIONS) ../.. || \
		exit 1
	@cd $(MODULE_SAMPLES_PYTHON_PYSAMPLE)/build/$(BUILD_TYPE) && \
		make -j$(CPUS) install || \
		exit 1

clean_samples_python_pysample:
	@echo
	@echo "==== Clean-up PySample Application ===="
	@[ ! -f $(BUILD_DIR)/usr/bin/pysample ] || \
		rm -f $(BUILD_DIR)/etc/bbque/recipes/PySample*; \
		rm -f $(BUILD_DIR)/usr/bin/pysample*
	@rm -rf $(MODULE_SAMPLES_PYTHON_PYSAMPLE)/build
	@echo

else # CONFIG_SAMPLES_PYTHON_PYSAMPLE

samples_python_pysample:
	$(warning PySample module disabled by BOSP configuration)
	$(error BOSP compilation failed)

endif # CONFIG_SAMPLES_PYTHON_PYSAMPLE

