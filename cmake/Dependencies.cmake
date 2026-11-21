# DOWNLOAD_DEPENDENCIES=ON fetches the pinned LLVM and camada release archives
# into <build>/deps once and points find_package at them. The official LLVM
# release is an LTO build (its .a files hold bitcode), so its own clang and lld
# become the compiler and linker. OFF leaves LLVM_DIR, camada_DIR and the
# compiler to the user. Included before project().
if(NOT DOWNLOAD_DEPENDENCIES)
  return()
endif()

# ponytail: only the Linux x86_64 archives are pinned; add a URL and hash per
# platform when someone builds elsewhere.
cmake_host_system_information(RESULT host_os QUERY OS_NAME)
cmake_host_system_information(RESULT host_cpu QUERY OS_PLATFORM)
if(NOT host_os STREQUAL "Linux" OR NOT host_cpu STREQUAL "x86_64")
  message(FATAL_ERROR
    "DOWNLOAD_DEPENDENCIES only pins Linux x86_64 archives; install LLVM and camada and set LLVM_DIR and camada_DIR")
endif()

set(LLVM_RELEASE_NAME "LLVM-21.1.8-Linux-X64")
set(LLVM_URL "https://github.com/llvm/llvm-project/releases/download/llvmorg-21.1.8/${LLVM_RELEASE_NAME}.tar.xz")
set(LLVM_SHA256 "b3b7f2801d15d50736acea3c73982994d025b01c2f035b91ae3b49d1b575732b")
set(CAMADA_URL "https://github.com/mikhailramalho/camada/releases/download/v0.23/camada-linux-x64.tar.gz")
set(CAMADA_SHA256 "f3d45dc34a6f10476707ef228136b19bc4cfefbd696ca59d7c45de5b2597a3e9")

set(DEPS_DIR "${CMAKE_BINARY_DIR}/deps")

# Downloads and extracts one archive into ${DEPS_DIR}/<name>. <marker> is a
# path under it that exists only after a complete extraction, so a rerun is
# free. The archive is kept: file(DOWNLOAD) skips a download whose file
# already matches the hash.
function(download_dep name url sha256 marker)
  set(prefix "${DEPS_DIR}/${name}")
  if(EXISTS "${prefix}/${marker}")
    return()
  endif()
  get_filename_component(archive_name "${url}" NAME)
  set(archive "${DEPS_DIR}/${archive_name}")
  message(STATUS "Downloading ${name} from ${url}")
  file(DOWNLOAD "${url}" "${archive}" EXPECTED_HASH SHA256=${sha256}
       SHOW_PROGRESS STATUS status)
  list(GET status 0 rc)
  if(NOT rc EQUAL 0)
    file(REMOVE "${archive}")
    message(FATAL_ERROR "Failed to download ${name}: ${status}")
  endif()
  message(STATUS "Extracting ${archive_name}")
  file(REMOVE_RECURSE "${prefix}")
  file(ARCHIVE_EXTRACT INPUT "${archive}" DESTINATION "${prefix}")
  if(NOT EXISTS "${prefix}/${marker}")
    message(FATAL_ERROR "${archive_name} has no ${marker}")
  endif()
endfunction()

download_dep(llvm "${LLVM_URL}" "${LLVM_SHA256}"
             "${LLVM_RELEASE_NAME}/lib/cmake/llvm/LLVMConfig.cmake")
set(llvm_prefix "${DEPS_DIR}/llvm/${LLVM_RELEASE_NAME}")
set(LLVM_DIR "${llvm_prefix}/lib/cmake/llvm" CACHE PATH "LLVM package directory" FORCE)
set(CMAKE_C_COMPILER "${llvm_prefix}/bin/clang")
set(CMAKE_CXX_COMPILER "${llvm_prefix}/bin/clang++")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-fuse-ld=lld")

download_dep(camada "${CAMADA_URL}" "${CAMADA_SHA256}"
             "lib/cmake/camada/camadaConfig.cmake")
set(camada_DIR "${DEPS_DIR}/camada/lib/cmake/camada"
    CACHE PATH "camada package directory" FORCE)
