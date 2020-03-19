

ifdef CONFIG_BOSP_SAMPLES_OPENCL

samples: samples_opencl

clean_samples: clean_samples_opencl

-include samples/opencl/hellocl/bosp.mk
#_include_dont_edit_#

endif
