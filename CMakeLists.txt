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

add_executable(vereda src/main.cpp)
target_include_directories(vereda SYSTEM PRIVATE ${LLVM_INCLUDE_DIRS})
separate_arguments(llvm_definitions NATIVE_COMMAND "${LLVM_DEFINITIONS}")
target_compile_definitions(vereda PRIVATE ${llvm_definitions})
if(NOT LLVM_ENABLE_RTTI)
  target_compile_options(vereda PRIVATE -fno-rtti)
endif()
target_link_libraries(vereda PRIVATE ${llvm_libs} camada::camada)

enable_testing()
add_test(NAME smoke COMMAND vereda "${CMAKE_CURRENT_SOURCE_DIR}/tests/smoke.ll")
set_tests_properties(smoke PROPERTIES PASS_REGULAR_EXPRESSION "main\nsolver: sat")
add_test(NAME vereda_loop
         COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/vereda.py" --bin $<TARGET_FILE:vereda>
                 --clang "${LLVM_TOOLS_BINARY_DIR}/clang" --dump-ir
                 "${CMAKE_CURRENT_SOURCE_DIR}/tests/loop.c")
set_tests_properties(vereda_loop PROPERTIES
                     PASS_REGULAR_EXPRESSION "phi i32"
                     FAIL_REGULAR_EXPRESSION "mustprogress|nsw|nuw|inbounds|optnone|noundef")
