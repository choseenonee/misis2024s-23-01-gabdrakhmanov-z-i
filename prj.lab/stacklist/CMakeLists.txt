add_library(stacklist stacklist.cpp stacklist.hpp)

target_link_libraries(stacklist complex)

set_property(TARGET stacklist PROPERTY CXX_STANDARD 20)

target_include_directories(stacklist PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS stacklist)