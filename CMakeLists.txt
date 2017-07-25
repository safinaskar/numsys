cmake_minimum_required (VERSION 3.1) # 3.1 adds C_STANDARD
project (numsys LANGUAGES CXX)
add_executable (numsys numsys.cpp)
set_property (TARGET numsys PROPERTY CXX_STANDARD 14)
target_link_libraries (numsys -lsh)
install (TARGETS numsys DESTINATION bin)
