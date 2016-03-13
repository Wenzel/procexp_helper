cmake_minimum_required(VERSION 2.8)

# set cmake module path, to search in cmake/modules first
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
#-----------------------------------------------------------------------------
#                               MODULES
#-----------------------------------------------------------------------------
# include(static_analysis)
# include(doxygen)
# include(ccache)
#-----------------------------------------------------------------------------
#                           GENERAL CONFIGURATION
#-----------------------------------------------------------------------------
project(testdbus CXX)
#-----------------------------------------------------------------------------
#                              DEPENDENCIES
#-----------------------------------------------------------------------------

# widgets
find_package(Qt5 REQUIRED COMPONENTS Core DBus)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#-----------------------------------------------------------------------------
#                           BUILD TYPES & FLAGS
#-----------------------------------------------------------------------------
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++14 -fdiagnostics-color")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Werror -O2")

# strip binary in release mode
if(CMAKE_BUILD_TYPE MATCHES "RELEASE")
    set(CMAKE_EXE_LINKER_FLAGS "-s")
endif()
#-----------------------------------------------------------------------------
#                               SOURCES
#-----------------------------------------------------------------------------
set(HELPER_XML_PATH "${CMAKE_CURRENT_BINARY_DIR}/procexphelper.xml")

# .h -> xml
qt5_generate_dbus_interface(procexphelper.h ${HELPER_XML_PATH})
# .xml -> adapter class
qt5_add_dbus_adaptor(HELPER_SRC_DBUS
    ${HELPER_XML_PATH}
    procexphelper.h # parentheader
    ProcexpHelper # classname
    ProcexpHelperAdaptor # [basename]
    ProcexpHelperAdaptor # [classname]
)
# .xml -> interface class
qt5_add_dbus_interface(HELPER_SRC_DBUS
    ${HELPER_XML_PATH}
    ProcexpHelperInterface
)


add_executable(server
    server.cpp
    procexphelper.cpp
    toto.cpp
    ${HELPER_SRC_DBUS}
)

add_executable(client
    client.cpp
    toto.cpp
    procexphelper.cpp
    ${HELPER_SRC_DBUS}
)

target_link_libraries(server Qt5::Core Qt5::DBus)
target_link_libraries(client Qt5::Core Qt5::DBus)

# include(uninstall)
# add_subdirectory("${CMAKE_SOURCE_DIR}/cmake/cpack") # enable packaging with CPack
#-----------------------------------------------------------------------------
#                               BUILD SUMMARY
#-----------------------------------------------------------------------------
message(STATUS " ↳ Compiler     → ${CMAKE_CXX_COMPILER}")
message(STATUS " ↳ Prefix       → ${CMAKE_INSTALL_PREFIX}")
message(STATUS " ↳ Build        → ${CMAKE_BUILD_TYPE}")
message(STATUS " ↳ Sanitizers   → ${COMPILER_SANITIZER}")
message(STATUS " ↳ CXX Flags    → ${CMAKE_CXX_FLAGS}")
