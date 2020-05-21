
ifdef CONFIG_BOSP_SAMPLES_CPP
$(info [ BOSP Samples: including CPP...] )
-include samples/cpp/bosp.mk
endif

ifdef CONFIG_BOSP_SAMPLES_OPENCL
$(info [ BOSP Samples: including OpenCL... ])
-include samples/opencl/bosp.mk
endif

ifdef CONFIG_BOSP_SAMPLES_OPENCV
$(info [ BOSP Samples: including OpenCV... ])
-include samples/opencv/bosp.mk
endif

ifdef CONFIG_BOSP_SAMPLES_PYTHON
$(info [ BOSP Samples: including Python... ])
-include samples/python/bosp.mk
endif
