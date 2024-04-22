add_executable(test_complex test_complex.cpp)

add_executable(test_rational test_rational.cpp)

add_executable(test_dynarr test_dynarr.cpp)

add_executable(test_stack test_stackarr.cpp)

add_executable(test_stack_list test_stacklst.cpp)

add_executable(test_queue_list test_queuelst.cpp)

add_executable(test_queue_arr test_queuearr.cpp)

add_executable(test_queue_lst_pr test_queuelstpr.cpp)

add_executable(test_bitset test_bitset.cpp)

add_executable(test_bitset_txt test_bitset_txt.cpp)

add_executable(test_template test_stacklstt.cpp)

target_link_libraries(test_complex complex)
target_link_libraries(test_rational rational)
target_link_libraries(test_dynarr dynarr)
target_link_libraries(test_stack stackarr)
target_link_libraries(test_stack_list stacklst)
target_link_libraries(test_queue_list queuelst)
target_link_libraries(test_queue_arr queuearr)
target_link_libraries(test_queue_lst_pr queuelstpr)
target_link_libraries(test_bitset bitset)
target_link_libraries(test_bitset_txt bitset)
target_link_libraries(test_template stacklstt complex)