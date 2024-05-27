cmake_minimum_required(VERSION 3.0.0)
project(z2r8xs_korszam_hf1 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(z2r8xs_korszam_hf1 main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
