###############################################################################
# The AEM FFT Application
################################################################################

cmake_minimum_required(VERSION 3.0)

#----- Check for the required RTLib library
find_package(BbqRTLib REQUIRED)


#----- Add "fft" target application
set(FFT_SRC version FFT_exc FFT_main)

add_executable(fft ${FFT_SRC})

add_definitions(-DFANN_FFT_NN_FILEPATH="${CMAKE_SOURCE_DIR}/fann.config/fft.nn")

#----- Headers
include_directories(
	${BBQUE_RTLIB_INCLUDE_DIR}
)


#----- Linking dependencies
target_link_libraries(
	fft
	${Boost_LIBRARIES}
	${BBQUE_RTLIB_LIBRARY}
	fann
)

# Use link path ad RPATH
set_property(TARGET fft PROPERTY
	INSTALL_RPATH_USE_LINK_PATH TRUE)

#----- Install the FFT files
install (TARGETS fft RUNTIME
	DESTINATION ${FFT_PATH_BINS})

#----- Generate and Install FFT configuration file
configure_file (
	"${PROJECT_SOURCE_DIR}/FFT.conf.in"
	"${PROJECT_BINARY_DIR}/FFT.conf"
)
install (FILES "${PROJECT_BINARY_DIR}/FFT.conf"
	DESTINATION ${FFT_PATH_CONFIG})
