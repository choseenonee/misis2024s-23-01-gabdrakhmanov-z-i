add_executable(app app.cpp)

find_package(implot CONFIG REQUIRED)
target_link_libraries(app PRIVATE implot::implot queuearrt queuelstt stackarrt stacklstt)

add_subdirectory(robobuba)