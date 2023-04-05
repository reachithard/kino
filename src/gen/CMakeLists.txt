FILE(GLOB ASYNC_SRCS async/*.cpp)
add_library(async STATIC ${ASYNC_SRCS})