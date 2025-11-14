cmake_minimum_required(VERSION 3.5)

project(advanced_gha)

find_package(VISP REQUIRED visp_core visp_io)

set(code_cpp
  src/print_npz_simple.cpp
)

foreach(cpp ${code_cpp})
  visp_add_target(${cpp})
endforeach()

file(COPY
    ${CMAKE_SOURCE_DIR}/python/print_npz.py

    # ViSP-images reference data
    # cnpy
    ${CMAKE_SOURCE_DIR}/npz/cnpy/visp_npz_test_data_cnpy_LE.npz
    ${CMAKE_SOURCE_DIR}/npz/cnpy/visp_npz_test_data_cnpy_BE.npz
    # NumPy
    ${CMAKE_SOURCE_DIR}/npz/numpy/visp_npz_test_data_numpy_LE.npz
    ${CMAKE_SOURCE_DIR}/npz/numpy/visp_npz_test_data_numpy_BE.npz

    DESTINATION ${CMAKE_BINARY_DIR}
)
