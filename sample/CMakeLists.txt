set(EXECUTABLE_OUTPUT_PATH out/${CMAKE_BUILD_TYPE})

add_definitions(-DCLOCK)

include(FindBoost)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREAD ON)
find_package(
  Boost
  1.48.0
  REQUIRED program_options
)

include_directories(
  ../lib/src
  ${Boost_INCLUDE_DIRS}
)

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}/../${LIB_SUBDIR}/${LIBRARY_OUTPUT_PATH}
  ${tbb_lib_dir}
  ${Boost_INCLUDE_DIRS}
)

file(
  GLOB_RECURSE
  sample_source_files
  src/*
)

add_executable(sample
  ${sample_source_files}
)

target_link_libraries(sample
  ${PROJECT_NAME}
  ${tbb_lib_name}
  ${Boost_LIBRARIES}
)