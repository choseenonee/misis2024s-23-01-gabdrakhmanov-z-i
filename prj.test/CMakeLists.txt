add_executable(test_complex test_complex.cpp)

add_executable(test_rational test_rational.cpp)

add_executable(test_dynarr test_dynarr.cpp)

target_link_libraries(test_complex complex)
target_link_libraries(test_rational rational)
target_link_libraries(test_dynarr dynarr)