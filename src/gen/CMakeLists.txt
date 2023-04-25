include_directories(${CMAKE_CURRENT_SOURCE_DIR})

FILE(GLOB ASYNC_SRCS async/*.cpp)
add_library(async STATIC ${ASYNC_SRCS})

FILE(GLOB GEN_SRCS *.cpp)
add_library(gen STATIC ${GEN_SRCS})