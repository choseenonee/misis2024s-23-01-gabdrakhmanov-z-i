add_library(stack stack.cpp stack.hpp)

target_link_libraries(stack complex)

set_property(TARGET stack PROPERTY CXX_STANDARD 20)

target_include_directories(stack PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:include>
        )

install(TARGETS stack)