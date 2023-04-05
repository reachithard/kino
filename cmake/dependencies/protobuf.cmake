include(ExternalProject)
SET(PTOTOBUF_CONFIGURE_COMMAND cd ${KINO_SRC_PREFIX}/protobuf && mkdir -p build && cd build && cmake -DCMAKE_CXX_STANDARD=17 -DCMAKE_BUILD_TYPE=Release -Dprotobuf_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} ..)
SET(PTOTOBUF_BUILD_COMMAND cd ${KINO_SRC_PREFIX}/protobuf/build && make)
SET(PTOTOBUF_INSTALL_COMMAND cd ${KINO_SRC_PREFIX}/protobuf/build && make install)

ExternalProject_Add(protobuf
        INSTALL_DIR ${CMAKE_INSTALL_PREFIX}
        SOURCE_DIR  ${KINO_SRC_PREFIX}/protobuf
        # CONFIGURE_COMMAND ${CMAKE_COMMAND}
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/protobuf
        CONFIGURE_COMMAND ${PTOTOBUF_CONFIGURE_COMMAND}
        BUILD_COMMAND ${PTOTOBUF_BUILD_COMMAND}
        INSTALL_COMMAND ${PTOTOBUF_INSTALL_COMMAND}
        )