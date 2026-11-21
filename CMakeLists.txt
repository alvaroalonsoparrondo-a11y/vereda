cmake_minimum_required(VERSION 3.24)

option(DOWNLOAD_DEPENDENCIES
       "Download the pinned LLVM and camada releases instead of using installed copies"
       OFF)
# Before project(): the downloaded LLVM is an LTO build, so its toolchain has
# to be the compiler and linker.
include(cmake/Dependencies.cmake)

project(vereda VERSION 0.1.0 LANGUAGES C CXX)

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
target_compile_definitions(libvereda PUBLIC ${llvm_definitions}
  VEREDA_VERSION="${PROJECT_VERSION}" VEREDA_CAMADA_VERSION="${camada_VERSION}")
if(NOT LLVM_ENABLE_RTTI)
  target_compile_options(libvereda PUBLIC -fno-rtti)
endif()
target_link_libraries(libvereda PUBLIC ${llvm_libs} camada::camada)

add_executable(vereda src/driver/main.cpp)
target_link_libraries(vereda PRIVATE libvereda)

enable_testing()
add_subdirectory(regression)
