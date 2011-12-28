enable_testing()

set(EXECUTABLE_OUTPUT_PATH out)

include(FindGTest)
find_package(GTest REQUIRED)

include_directories(
  ../lib/src
  ${GTEST_INCLUDE_DIRS}
)

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}/../${LIB_SUBDIR}/${LIBRARY_OUTPUT_PATH}
  ${tbb_lib_dir}
)

file(
  GLOB_RECURSE
  test_source_files
  src/*
)

add_executable(test
  ${test_source_files}
)

target_link_libraries(test
  ${PROJECT_NAME}
  ${tbb_lib_name}
  ${GTEST_BOTH_LIBRARIES}
)
