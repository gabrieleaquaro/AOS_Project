
ifdef CONFIG_SAMPLES_OPENCV_EDGEDETECTOR

# Targets provided by this project
.PHONY: samples_opencv_edgedetector clean_samples_opencv_edgedetector

# Add this to the "samples" targets
samples_opencv: samples_opencv_edgedetector
clean_samples_opencv: clean_samples_opencv_edgedetector

MODULE_SAMPLES_OPENCV_EDGEDETECTOR=samples/opencv/edge_detector

samples_opencv_edgedetector: external
	@echo
	@echo "==== Building Edge Detector Application ($(BUILD_TYPE)) ===="
	@echo " Using GCC    : $(CC)"
	@echo " Target flags : $(TARGET_FLAGS)"
	@echo " Sysroot      : $(BOSP_SYSROOT)"
	@echo " BOSP Options : $(CMAKE_COMMON_OPTIONS)"
	@[ -d $(MODULE_SAMPLES_OPENCV_EDGEDETECTOR)/build/$(BUILD_TYPE) ] || \
		mkdir -p $(MODULE_SAMPLES_OPENCV_EDGEDETECTOR)/build/$(BUILD_TYPE) || \
		exit 1
	@cd $(MODULE_SAMPLES_OPENCV_EDGEDETECTOR)/build/$(BUILD_TYPE) && \
		CC=$(CC) CFLAGS="$(TARGET_FLAGS)" \
		CXX=$(CXX) CXXFLAGS="$(TARGET_FLAGS)" \
		cmake $(CMAKE_COMMON_OPTIONS) ../.. || \
		exit 1
	@cd $(MODULE_SAMPLES_OPENCV_EDGEDETECTOR)/build/$(BUILD_TYPE) && \
		make -j$(CPUS) install || \
		exit 1

clean_samples_opencv_edgedetector:
	@echo
	@echo "==== Clean-up EdgeDetector Application ===="
	@rm -rf $(MODULE_SAMPLES_OPENCV_EDGEDETECTOR)/build
	@echo

else # CONFIG_SAMPLES_OPENCV_EDGEDETECTOR

samples_opencv_edgedetector:
	$(warning Edge Detector module disabled by BOSP configuration)
	$(error BOSP compilation failed)

endif # CONFIG_SAMPLES_OPENCV_EDGEDETECTOR

