###############################################################################
# The AEM Edge Detector Application
################################################################################

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set (BOSP_SYSROOT ${CMAKE_INSTALL_PREFIX})

find_package(BbqRTLib REQUIRED)

#----- Check for the required OpenCV library
find_package(OpenCV REQUIRED)

#----- Add compilation dependencies
include_directories(${BBQUE_RTLIB_INCLUDE_DIR} 
	            ${OpenCV_INCLUDE_DIRS}
)

#----- Add "houghcircles" target application
set(EDGEDETECTOR_SRC version EdgeDetector_exc EdgeDetector_main)
add_executable(edgedetector ${EDGEDETECTOR_SRC})

#----- Linking dependencies
target_link_libraries(
	edgedetector
	${Boost_LIBRARIES}
	${BBQUE_RTLIB_LIBRARY}
	${OpenCV_LIBS} 
)

# Use link path ad RPATH
set_property(TARGET edgedetector PROPERTY
	INSTALL_RPATH_USE_LINK_PATH TRUE)

#----- Install the EdgeDetector files
install (TARGETS edgedetector RUNTIME
	DESTINATION ${EDGEDETECTOR_PATH_BINS})

#----- Generate and Install EdgeDetector configuration file
configure_file (
	"${PROJECT_SOURCE_DIR}/EdgeDetector.conf.in"
	"${PROJECT_BINARY_DIR}/EdgeDetector.conf"
)
install (FILES "${PROJECT_BINARY_DIR}/EdgeDetector.conf"
	DESTINATION ${EDGEDETECTOR_PATH_CONFIG})
