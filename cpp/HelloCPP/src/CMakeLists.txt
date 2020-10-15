
cmake_minimum_required(VERSION 3.0)

set (BOSP_SYSROOT ${CMAKE_INSTALL_PREFIX})
find_package(BbqRTLib REQUIRED)

#----- Add compilation dependencies
include_directories(${BBQUE_RTLIB_INCLUDE_DIR})

#----- Add "hellocpp" target application
set(HELLOCPP_SRC version HelloCPP_exc HelloCPP_main)
add_executable(hellocpp ${HELLOCPP_SRC})

#----- Linking dependencies
target_link_libraries(
	hellocpp
	${Boost_LIBRARIES}
	${BBQUE_RTLIB_LIBRARY}
)

# Use link path ad RPATH
set_property(TARGET hellocpp PROPERTY
	INSTALL_RPATH_USE_LINK_PATH TRUE)

#----- Install the HelloCPP files
install (TARGETS hellocpp RUNTIME
	DESTINATION ${HELLOCPP_PATH_BINS})

#----- Generate and Install HelloCPP configuration file
configure_file (
	"${PROJECT_SOURCE_DIR}/HelloCPP.conf.in"
	"${PROJECT_BINARY_DIR}/HelloCPP.conf"
)
install (FILES "${PROJECT_BINARY_DIR}/HelloCPP.conf"
	DESTINATION ${HELLOCPP_PATH_CONFIG})
