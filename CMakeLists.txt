cmake_minimum_required( VERSION 3.1 )
project( aaa-client-monitor )

set( CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

set( CMAKE_CXX_STANDARD 11 )

set( PLUGIN_VERSION 4 )
set( LIB_AAA_CL_MON XrdAaaClientMonitor-${PLUGIN_VERSION} )

find_package( Xrootd REQUIRED )
# find_package( XercesC REQUIRED )
# find_package( Pcre REQUIRED )

if( CMAKE_COMPILER_IS_GNUCXX )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror" )
endif()

if( CMAKE_COMPILER_IS_GNUCC )
  set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror" )
endif()

# include_directories( "${PROJECT_SOURCE_DIR}" "${XROOTD_INCLUDES}" "${XERCES_INCLUDES}" "${PCRE_INCLUDES}" )
include_directories( "${PROJECT_SOURCE_DIR}" "${XROOTD_INCLUDES}" )

add_library( ${LIB_AAA_CL_MON} MODULE src/AaaClientMonitor.cc src/AaaClientMonitor.hh )
# target_link_libraries(${LIB_AAA_CL_MON} ${XROOTD_UTILS} ${XERCES_LIB} ${PCRE_LIB})
target_link_libraries(${LIB_AAA_CL_MON} ${XROOTD_UTILS})

if (NOT DEFINED CMAKE_INSTALL_LIBDIR)
  SET(CMAKE_INSTALL_LIBDIR "lib")
endif()

install(
  TARGETS ${LIB_AAA_CL_MON}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} )

install(
  FILES ${CMAKE_SOURCE_DIR}/src/AaaClientMonitor.hh
  DESTINATION include )

set_target_properties(
  ${LIB_AAA_CL_MON}
  PROPERTIES
  VERSION   "0.0.1"
  SOVERSION "0"
  LINK_INTERFACE_LIBRARIES "" )

