add_executable(test_complex test_complex.cpp)

add_executable(test_rational test_rational.cpp)

add_executable(test_dynarr test_dynarr.cpp)

add_executable(test_stack test_stack.cpp)

add_executable(test_stack_list test_stack_list.cpp)

target_link_libraries(test_complex complex)
target_link_libraries(test_rational rational)
target_link_libraries(test_dynarr dynarr)
target_link_libraries(test_stack stackarr)
target_link_libraries(test_stack_list stacklst)