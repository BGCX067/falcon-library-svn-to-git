include(../../CMakeDefinitions.txt)
include_directories(.. ../..)

create_exec_test(call)
create_exec_test(cut_and_place)
create_exec_test(generator)
create_exec_test(placeholder_functor)
create_exec_test(short_circuit)
create_exec_test(store_if)
