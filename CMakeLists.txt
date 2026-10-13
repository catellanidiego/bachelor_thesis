cmake_minimum_required(VERSION 3.20)
project(tesi)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Werror=vla")

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

enable_testing()
add_executable(main main.cpp src/Timecounter.cpp)

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(main PRIVATE Eigen3::Eigen)

add_executable(test_RK45 test/test_RK45.cpp)
target_include_directories(test_RK45 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(test_RK45 PRIVATE Eigen3::Eigen)
add_test(NAME RK45 COMMAND test_RK45)

add_executable(test_a_Coulomb test/Test_Calculate_a_Coulomb.cpp)
target_include_directories(test_a_Coulomb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME a_Coulomb COMMAND test_a_Coulomb)

add_executable(test_a_White test/Test_Calculate_a_D_White.cpp)
target_include_directories(test_a_White PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME a_White COMMAND test_a_White)

add_executable(test_a_Stokes test/Test_Calculate_a_D_Stokes.cpp)
target_include_directories(test_a_Stokes PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME a_Stokes COMMAND test_a_Stokes)

add_executable(test_K test/Test_Calculate_K.cpp)
target_include_directories(test_K PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME K COMMAND test_K)

add_executable(test_U test/Test_Calculate_U.cpp)
target_include_directories(test_U PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME U COMMAND test_U)

add_executable(test_Re test/Test_Calculate_Re.cpp)
target_include_directories(test_Re PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME Re COMMAND test_Re)