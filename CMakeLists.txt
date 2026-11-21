cmake_minimum_required(VERSION 3.24)

option(DOWNLOAD_DEPENDENCIES
       "Download the pinned LLVM and camada releases instead of using installed copies"
       OFF)
# Before project(): the downloaded LLVM is an LTO build, so its toolchain has
# to be the compiler and linker.
include(cmake/Dependencies.cmake)

project(vereda LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build type" FORCE)
endif()

find_package(LLVM CONFIG REQUIRED)
if(LLVM_VERSION_MAJOR LESS 21 OR LLVM_VERSION_MAJOR GREATER 23)
  message(FATAL_ERROR "LLVM ${LLVM_PACKAGE_VERSION} found at ${LLVM_DIR}; 21 to 23 is supported")
endif()
message(STATUS "Using LLVM ${LLVM_PACKAGE_VERSION} from ${LLVM_DIR}")
find_package(camada CONFIG REQUIRED)
message(STATUS "Using camada from ${camada_DIR}")

llvm_map_components_to_libnames(llvm_libs core irreader support passes)

# One static library for every stage; the driver and the unit tests link it.
add_library(libvereda STATIC
  src/ir/load.cpp
  src/encode/encoder.cpp
  src/walker/walker.cpp
  src/solver/solver.cpp)
set_target_properties(libvereda PROPERTIES OUTPUT_NAME vereda)
target_include_directories(libvereda PUBLIC src)
target_include_directories(libvereda SYSTEM PUBLIC ${LLVM_INCLUDE_DIRS})
separate_arguments(llvm_definitions NATIVE_COMMAND "${LLVM_DEFINITIONS}")
target_compile_definitions(libvereda PUBLIC ${llvm_definitions})
if(NOT LLVM_ENABLE_RTTI)
  target_compile_options(libvereda PUBLIC -fno-rtti)
endif()
target_link_libraries(libvereda PUBLIC ${llvm_libs} camada::camada)

add_executable(vereda src/driver/main.cpp)
target_link_libraries(vereda PRIVATE libvereda)

enable_testing()
add_test(NAME smoke COMMAND vereda "${CMAKE_CURRENT_SOURCE_DIR}/tests/smoke.ll")
set_tests_properties(smoke PROPERTIES PASS_REGULAR_EXPRESSION "VERIFICATION SUCCESSFUL")
add_test(NAME vereda_loop
         COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vereda.py" --bin $<TARGET_FILE:vereda>
                 --clang "${LLVM_TOOLS_BINARY_DIR}/clang" --dump-ir
                 "${CMAKE_CURRENT_SOURCE_DIR}/tests/loop.c")
set_tests_properties(vereda_loop PROPERTIES
                     PASS_REGULAR_EXPRESSION "phi i32"
                     FAIL_REGULAR_EXPRESSION "mustprogress|nsw|nuw|inbounds|optnone|noundef")

# Reachability tests: <name>.c is verified through the driver and its output
# must match <expected>.
function(vereda_reach_test name expected)
  add_test(NAME ${name}
           COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vereda.py" --bin $<TARGET_FILE:vereda>
                   --clang "${LLVM_TOOLS_BINARY_DIR}/clang"
                   "${CMAKE_CURRENT_SOURCE_DIR}/tests/${name}.c")
  set_tests_properties(${name} PROPERTIES PASS_REGULAR_EXPRESSION "${expected}")
endfunction()
vereda_reach_test(reach_true "VERIFICATION SUCCESSFUL")
vereda_reach_test(assert_false "assert_false.c:7:3\n  assertion fails\n\nVERIFICATION FAILED")
vereda_reach_test(reach_false "reach_false.c:12:5\n  reach_error is reachable\n\nVERIFICATION FAILED")
