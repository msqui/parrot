include_directories(
  ${tbb_include_dir}
)
link_directories(${tbb_lib_dir})

file(
  GLOB_RECURSE
  source_files
  src/*
)

add_library(${PROJECT_NAME}
  SHARED
  ${source_files}
)

target_link_libraries(
  ${PROJECT_NAME}
  ${tbb_lib_name}
)