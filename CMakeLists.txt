cmake_minimum_required(VERSION 3.16)
project(PathTracing)

add_executable(path-tracing.out
  src/main.cc
  src/image.cc
  src/vector3d.cc
  src/random.cc
  src/ray.cc
  src/hit.cc
  src/material.cc
  src/sphere.cc
  src/tracer.cc
  src/camera.cc
  )

target_compile_options(path-tracing.out PUBLIC -Ofast -Wall -Wextra -pedantic -flto)
target_link_libraries(path-tracing.out ${SOURCES} -flto)
  
# MPI executable
find_package(MPI)
IF(MPI_FOUND)
  add_executable(path-tracing-mpi.out
    src/main-mpi.cc
    src/image.cc
    src/vector3d.cc
    src/random.cc
    src/ray.cc
    src/hit.cc
    src/material.cc
    src/sphere.cc
    src/tracer.cc
    src/camera.cc
    )

  target_compile_options(path-tracing-mpi.out PUBLIC -Ofast -g -Wall -Wextra -pedantic -flto)
  target_link_libraries(path-tracing-mpi.out ${SOURCES} ${MPI_LIBRARIES} MPI::MPI_CXX)
ENDIF()
