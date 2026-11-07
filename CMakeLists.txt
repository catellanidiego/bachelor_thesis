cmake_minimum_required(VERSION 3.20)
project(tesi)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Werror=vla")
if (NOT CMAKE_BUILD_TYPE) 
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
endif()

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_library(pendulum STATIC
	src/CSV_Writer.cpp
	src/Calculate_C_D_sphere_White.cpp
	src/Calculate_C_D_wire.cpp
	src/Calculate_K.cpp
	src/Calculate_Re.cpp
	src/Calculate_U.cpp
	src/Calculate_a_D_sphere_Stokes.cpp
	src/Calculate_a_D_sphere_no_Stokes.cpp
	src/Calculate_a_D_wire.cpp
	src/Calculate_a_friction.cpp
	src/Calculate_p_f.cpp
	src/Is_close.cpp
	src/Load_config.cpp
	src/Timecounter.cpp
)
target_include_directories(pendulum PUBLIC ${CMAKE_CURENT_SOURCE_DIR}/include)
target_link_libraries(pendulum PUBLIC Eigen3::Eigen)

enable_testing()
add_executable(main main.cpp)
target_link_libraries(main PRIVATE pendulum)

add_executable (mu_eq src/Calculate_mu_eq.cpp)
target_link_libraries(mu_eq PRIVATE pendulum)

add_executable (data_for_mu_eq src/Read_data_for_mu_eq_search.cpp)
target_link_libraries(data_for_mu_eq PRIVATE pendulum)

add_executable (data_period src/Calculate_T_A_theta.cpp)
target_link_libraries(data_period PRIVATE pendulum)

add_executable(test_RK45 test/Test_RK45.cpp)
target_link_libraries(test_RK45 PRIVATE pendulum)
add_test(NAME RK45 COMMAND test_RK45)

add_executable(test_a_friction test/Test_Calculate_a_friction.cpp)
target_link_libraries(test_a_friction PRIVATE pendulum)
add_test(NAME a_friction COMMAND test_a_friction)

add_executable(test_a_no_Stokes test/Test_Calculate_a_D_no_Stokes.cpp)
target_link_libraries(test_a_no_Stokes PRIVATE pendulum)
add_test(NAME a_no_Stokes COMMAND test_a_no_Stokes)

add_executable(test_a_Stokes test/Test_Calculate_a_D_Stokes.cpp)
target_link_libraries(test_a_Stokes PRIVATE pendulum)
add_test(NAME a_Stokes COMMAND test_a_Stokes)

add_executable(test_K test/Test_Calculate_K.cpp)
target_link_libraries(test_K PRIVATE pendulum)
add_test(NAME K COMMAND test_K)

add_executable(test_U test/Test_Calculate_U.cpp)
target_link_libraries(test_U PRIVATE pendulum)
add_test(NAME U COMMAND test_U)

add_executable(test_Re test/Test_Calculate_Re.cpp)
target_link_libraries(test_Re PRIVATE pendulum)
add_test(NAME Re COMMAND test_Re)

add_executable(test_C_D_wire test/Test_Calculate_C_D_wire.cpp)
target_link_libraries(test_C_D_wire PRIVATE pendulum)
add_test(NAME C_D_wire COMMAND test_C_D_wire)

add_executable(test_a_D_wire test/Test_Calculate_a_D_wire.cpp)
target_link_libraries(test_a_D_wire PRIVATE pendulum)
add_test(NAME a_D_wire COMMAND test_a_D_wire)
