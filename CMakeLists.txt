cmake_minimum_required (VERSION 2.6)

project (parrot)

set(LIBRARY_OUTPUT_PATH out/${CMAKE_BUILD_TYPE})

SET(LIB_SUBDIR lib)
SET(SAMPLE_SUBDIR sample)
SET(TEST_SUBDIR test)

add_subdirectory(${LIB_SUBDIR})

add_subdirectory(${SAMPLE_SUBDIR}
  EXCLUDE_FROM_ALL
)

add_subdirectory(${TEST_SUBDIR}
  EXCLUDE_FROM_ALL
)
