cmake_minimum_required(VERSION 3.20)
project(kino)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/output)
set(CMAKE_VERBOSE_MAKEFILE ON)

option(KINO_PLATFORM_EXTENSIONS "Enable platform specific extensions, requires extra dependencies" ON)
option(KINO_UPDATE_CHECK "Enable automatic update check" ON)
option(KINO_USE_CCACHE "Use ccache when available" ON)
option(KINO_SPELL_CHECK "Enable spell cheching support" ON)
option(KINO_SVGZ_ICON "Compress the SVG icon of kino" ON)
option(KINO_ASAN "Compile with AddressSanitizer" OFF)
option(KINO_BUILD_DEPENDENCIES "build dependencies" OFF)
option(KINO_TESTS "Unit test by gtest" ON)
option(STRICT_OPTIONS "Error on compile warning, used by CI" OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Options are: None, Debug, Release, RelWithDebInfo, MinSizeRel." FORCE)
endif()

if(KINO_BUILD_DEPENDENCIES)
    set(KINO_SRC_PREFIX ${CMAKE_SOURCE_DIR}/thirdparty)
    include(cmake/dependencies/asio.cmake)
    include(cmake/dependencies/googltest.cmake)
    include(cmake/dependencies/protobuf.cmake)
else(KINO_BUILD_DEPENDENCIES)
    include_directories(${CMAKE_INSTALL_PREFIX}/include)

    add_subdirectory(src)

    if (KINO_TESTS)
        include(CTest)
        enable_testing()
        add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)

        include(cmake/utils/gtest.cmake)
        add_subdirectory(test)
    endif(KINO_TESTS)
endif(KINO_BUILD_DEPENDENCIES)