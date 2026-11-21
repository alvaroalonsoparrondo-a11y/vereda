# Every *.c or *.ll directly under a suite directory is a test, and so is
# every <suite>/<name>/main.c for tests with several files. The test's comment
# header describes it; see run.py. The suite name is the ctest label, so
# `ctest -L vereda` runs one suite.
set(REGRESS_TIMEOUT 300 CACHE STRING "Per-test timeout in seconds")

file(GLOB suites LIST_DIRECTORIES true RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
     "${CMAKE_CURRENT_SOURCE_DIR}/*")
foreach(suite IN LISTS suites)
  if(NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${suite}")
    continue()
  endif()
  file(GLOB tests CONFIGURE_DEPENDS
       "${CMAKE_CURRENT_SOURCE_DIR}/${suite}/*.c"
       "${CMAKE_CURRENT_SOURCE_DIR}/${suite}/*.ll"
       "${CMAKE_CURRENT_SOURCE_DIR}/${suite}/*/main.c")
  foreach(test IN LISTS tests)
    get_filename_component(name "${test}" NAME_WE)
    if(name STREQUAL "main")
      get_filename_component(name "${test}" DIRECTORY)
      get_filename_component(name "${name}" NAME)
    endif()
    add_test(NAME "${suite}/${name}"
             COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/run.py"
                     --vereda "${CMAKE_SOURCE_DIR}/vereda.py" --bin $<TARGET_FILE:vereda>
                     --clang "${LLVM_TOOLS_BINARY_DIR}/clang" "${test}")
    set_tests_properties("${suite}/${name}" PROPERTIES LABELS "${suite}"
                         TIMEOUT "${REGRESS_TIMEOUT}")
  endforeach()
endforeach()
