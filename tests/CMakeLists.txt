# Every *.c or *.ll directly under a suite directory is a test, and so is
# every <suite>/<name>/main.c for tests with several files. The test's comment
# header describes it; see run.py. The suite name is the ctest label, so
# `ctest -L vereda` runs one suite.
set(REGRESS_TIMEOUT 300 CACHE STRING "Per-test timeout in seconds")
# Tests imported from ESBMC (tests/import_esbmc.py) are many, so a test
# that runs long there is cut short and counts as failed.
set(ESBMC_REGRESS_TIMEOUT 60 CACHE STRING "Per-test timeout in seconds for suites esbmc*")

file(GLOB suites LIST_DIRECTORIES true RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
     "${CMAKE_CURRENT_SOURCE_DIR}/*")
foreach(suite IN LISTS suites)
  if(NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${suite}")
    continue()
  endif()
  file(GLOB tests LIST_DIRECTORIES false CONFIGURE_DEPENDS
       "${CMAKE_CURRENT_SOURCE_DIR}/${suite}/*.c"
       "${CMAKE_CURRENT_SOURCE_DIR}/${suite}/*.ll"
       "${CMAKE_CURRENT_SOURCE_DIR}/${suite}/*/main.c")
  foreach(test IN LISTS tests)
    # The last extension only: some test names hold dots.
    get_filename_component(name "${test}" NAME_WLE)
    if(name STREQUAL "main")
      get_filename_component(name "${test}" DIRECTORY)
      get_filename_component(name "${name}" NAME)
    endif()
    set(timeout "${REGRESS_TIMEOUT}")
    if(suite MATCHES "^esbmc")
      set(timeout "${ESBMC_REGRESS_TIMEOUT}")
    endif()
    add_test(NAME "${suite}/${name}"
             COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/run.py"
                     --vereda "${CMAKE_SOURCE_DIR}/vereda.py" --bin $<TARGET_FILE:vereda>
                     --clang "${LLVM_TOOLS_BINARY_DIR}/clang" --timeout "${timeout}" "${test}")
    # run.py stops the run itself, so that a timeout can be an expected
    # failure; ctest's limit is only a backstop.
    math(EXPR backstop "${timeout} + 60")
    # run.py exits 77 for a KNOWNBUG or FUTURE test that fails as expected.
    set_tests_properties("${suite}/${name}" PROPERTIES LABELS "${suite}" TIMEOUT "${backstop}"
                         SKIP_RETURN_CODE 77)
  endforeach()
endforeach()
