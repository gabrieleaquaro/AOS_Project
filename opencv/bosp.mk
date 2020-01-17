
ifdef CONFIG_BOSP_SAMPLES_OPENCV

samples: samples_opencv

clean_samples: clean_samples_opencv

-include opencv/background_learning/bosp.mk

endif
