include_directories(${CMAKE_SOURCE_DIR}/src)
do_unit_test(gen_async gtest_inlet.cpp)
target_link_libraries(gen_async PRIVATE async)
target_sources(gen_async PRIVATE
        gen/async/test_actor.cpp
        gen/async/test_asio_sample.cpp)