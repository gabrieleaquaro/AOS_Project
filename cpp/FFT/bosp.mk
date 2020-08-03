
ifdef CONFIG_SAMPLES_CPP_FFT

# Targets provided by this project
.PHONY: samples_cpp_fft clean_samples_cpp_fft

# Add this to the "samples" targets
samples_cpp: samples_cpp_fft
clean_samples_cpp: clean_samples_cpp_fft

MODULE_SAMPLES_CPP_FFT=samples/cpp/FFT

samples_cpp_fft: external
	@echo
	@echo "==== Building FFT ($(BUILD_TYPE)) ===="
	@echo " Using GCC    : $(CC)"
	@echo " Target flags : $(TARGET_FLAGS)"
	@echo " Sysroot      : $(PLATFORM_SYSROOT)"
	@echo " BOSP Options : $(CMAKE_COMMON_OPTIONS)"
	@[ -d $(MODULE_SAMPLES_CPP_FFT)/build/$(BUILD_TYPE) ] || \
		mkdir -p $(MODULE_SAMPLES_CPP_FFT)/build/$(BUILD_TYPE) || \
		exit 1
	@cd $(MODULE_SAMPLES_CPP_FFT)/build/$(BUILD_TYPE) && \
		CC=$(CC) CFLAGS="$(TARGET_FLAGS)" \
		CXX=$(CXX) CXXFLAGS="$(TARGET_FLAGS)" \
		cmake $(CMAKE_COMMON_OPTIONS) ../.. || \
		exit 1
	@cd $(MODULE_SAMPLES_CPP_FFT)/build/$(BUILD_TYPE) && \
		make -j$(CPUS) install || \
		exit 1

clean_samples_cpp_fft:
	@echo
	@echo "==== Clean-up FFT Application ===="
	@[ ! -f $(BUILD_DIR)/usr/bin/fft ] || \
		rm -f $(BUILD_DIR)/etc/bbque/recipes/FFT*; \
		rm -f $(BUILD_DIR)/usr/bin/fft*
	@rm -rf $(MODULE_SAMPLES_CPP_FFT)/build
	@echo

else # CONFIG_SAMPLES_CPP_FFT

samples_cpp_fft:
	$(warning FFT module disabled by BOSP configuration)
	$(error BOSP compilation failed)

endif # CONFIG_SAMPLES_CPP_FFT

