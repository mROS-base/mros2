
if (DEFINED MROS2_POSIX_OPTION_FILEPATH)
	include(${MROS2_POSIX_OPTION_FILEPATH})
else()
	message(STATUS "MROS2_POSIX_OPTION_FILEPATH is not defined")
	include(cmake-build/default-cmake-options.cmake)
endif()

# ASSERTION CHECK 
if (NOT DEFINED cmsis_DIR)
	message(FATAL " cmsis_DIR is not defined")
endif()
if (NOT DEFINED lwip_DIR)
	message(FATAL " lwip_DIR is not defined")
endif()
message(STATUS "CMAKE_OS_POSIX=" ${CMAKE_OS_POSIX})

set(MROS2_DIR "${PROJECT_SOURCE_DIR}")
include(cmake-build/Filelists.cmake)


add_library(
	mros2 STATIC
	${mros2_SRCS}
)

target_include_directories(
	mros2

	#embeddedRTPS
	PRIVATE ${MROS2_DIR}/embeddedRTPS/include
	PRIVATE ${MROS2_DIR}/embeddedRTPS/thirdparty/Micro-CDR/include
	PRIVATE ${RTPS_CONFIG_INCLUDE_DIR}

	#mROS2
	PRIVATE ${MROS2_DIR}/include
	PRIVATE ${MROS2_DIR}/mros2_msgs

	#CMSIS INCLUDES
	PRIVATE ${cmsis_DIR}/include

	#LWIP INCLUDES
	PRIVATE ${lwip_DIR}/include/lwip
	PRIVATE ${lwip_DIR}/include/posix
	PRIVATE ${lwip_DIR}/include/system
	PRIVATE ${lwip_DIR}/include/netif
)

set(INSTALL_CMAKE_DIR ${PROJECT_SOURCE_DIR}/public)
message(STATUS "INSTALL_CMAKE_DIR=" ${INSTALL_CMAKE_DIR})

install(
	DIRECTORY ${MROS2_DIR}/include/
	DESTINATION ${INSTALL_CMAKE_DIR}/include/mros2
)

install(
	DIRECTORY ${MROS2_DIR}/mros2_msgs/
	DESTINATION ${INSTALL_CMAKE_DIR}/include/mros2_msgs
)

install(
	DIRECTORY ${MROS2_DIR}/embeddedRTPS/include/rtps/
	DESTINATION ${INSTALL_CMAKE_DIR}/include/rtps
)
install(
	DIRECTORY ${MROS2_DIR}/embeddedRTPS/thirdparty/Micro-CDR/include/ucdr/
	DESTINATION ${INSTALL_CMAKE_DIR}/include/ucdr
)

install(
	TARGETS mros2 
	DESTINATION     ${INSTALL_CMAKE_DIR} 
	EXPORT			mros2-export
	LIBRARY         DESTINATION lib
	INCLUDES        DESTINATION include
	PUBLIC_HEADER   DESTINATION include
)
install(
	EXPORT			mros2-export 
    FILE			mros2-config.cmake
	DESTINATION		${INSTALL_CMAKE_DIR}
    EXPORT_LINK_INTERFACE_LIBRARIES
)
