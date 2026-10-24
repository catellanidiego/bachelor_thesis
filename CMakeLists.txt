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

add_executable (mu_eq src/Calculate_mu_eq.cpp)
target_include_directories(mu_eq PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(mu_eq PRIVATE Eigen3::Eigen)

add_executable (data_for_mu_eq src/Read_data_for_mu_eq_search.cpp)
target_include_directories(data_for_mu_eq PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable (data src/Calculate_T_A_theta.cpp)
target_include_directories(data PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(test_RK45 test/Test_RK45.cpp)
target_include_directories(test_RK45 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(test_RK45 PRIVATE Eigen3::Eigen)
add_test(NAME RK45 COMMAND test_RK45)

add_executable(test_a_friction test/Test_Calculate_a_friction.cpp)
target_include_directories(test_a_friction PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME a_friction COMMAND test_a_friction)

add_executable(test_a_no_Stokes test/Test_Calculate_a_D_no_Stokes.cpp)
target_include_directories(test_a_no_Stokes PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME a_no_Stokes COMMAND test_a_no_Stokes)

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

add_executable(test_C_D_wire test/Test_Calculate_C_D_wire.cpp)
target_include_directories(test_C_D_wire PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME C_D_wire COMMAND test_C_D_wire)

add_executable(test_a_D_wire test/Test_Calculate_a_D_wire.cpp)
target_include_directories(test_a_D_wire PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME C_a_wire COMMAND test_a_D_wire)