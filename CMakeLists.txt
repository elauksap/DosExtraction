################################################################
## Directories definition.
################################################################
set(SHARE_DIR "${CMAKE_SOURCE_DIR}/config")    # Directory containing test and configuration files.

set(BINDIR "${CMAKE_BINARY_DIR}/bin" )    # Directory where to store the executable.
set(DOCDIR "${CMAKE_BINARY_DIR}/doc" )    # Directory where to store the API documentation.
set(LIBDIR "${CMAKE_BINARY_DIR}/lib" )    # Directory where to store the project shared library.

##--------------- Do not edit below this line ----------------##

cmake_minimum_required(VERSION 2.8)
project(DOS_Extraction CXX)

################################################################
## Set up some variables.
################################################################
set(SIMULATE "simulate_dos")    # Name of the test source file to compile.
set(FIT "fit_dos")    # Name of the test source file to compile.

set(DOS_EXTRACTION "dosextraction")    # Name of the shared library.

set(LIB_INSTALLDIR "${CMAKE_INSTALL_PREFIX}/lib/")    # Installation directory for the shared library.
set(INC_INSTALLDIR "${CMAKE_INSTALL_PREFIX}/include/${DOS_EXTRACTION}")    # Installation directory for the header files.
set(BIN_INSTALLDIR "${CMAKE_INSTALL_PREFIX}/bin/")    # Installation directory for the executable.
set(SHARE_INSTALLDIR "${CMAKE_INSTALL_PREFIX}/share/${DOS_EXTRACTION}")    # Installation directory for test and configuration files.

set(SRCDIR  "${CMAKE_SOURCE_DIR}/src" )    # Directory where to find the library sources.
set(TESTDIR "${CMAKE_SOURCE_DIR}/test")    # Directory where to find the test sources.

file(GLOB SIMULATE_SRC ${TESTDIR}/${SIMULATE}.cc)
file(GLOB FIT_SRC ${TESTDIR}/${FIT}.cc)
file(GLOB SRCS ${SRCDIR}/*.cc ${SRCDIR}/*.cpp)
file(GLOB HDRS ${SRCDIR}/*.h ${SRCDIR}/*.hpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${LIBDIR}")
set(EXECUTABLE_OUTPUT_PATH "${BINDIR}")

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall --pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING    # Default build type: Release.
      "Choose the type of build, options are: None Debug MinSizeRel Release RelWithDebInfo."
      FORCE)
endif()

################################################################
## Dependencies and third-party libraries.
################################################################
include_directories(SYSTEM "${CMAKE_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/include")

find_package(Eigen3 3.2 REQUIRED)
include_directories(SYSTEM ${EIGEN3_INCLUDE_DIR})

find_package(OpenMP)

if(OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

find_package(Gnuplot REQUIRED)

find_package(Boost 1.50 REQUIRED COMPONENTS iostreams system filesystem)
include_directories(SYSTEM ${Boost_INCLUDE_DIR})

################################################################
## Documentation generation settings.
################################################################
set(DOXYFILE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/doc")
set(DOXYFILE_OUTPUT_DIR "${DOCDIR}")
set(DOXYFILE_LATEX "ON")

include(RunDoxygen)

################################################################
## Artistic style.
################################################################
# find_package(AStyle)

# if(ASTYLE_FOUND)
#     add_custom_target(astyle ALL
#         COMMAND ${ASTYLE_EXECUTABLE} -q -A1 -s4 -C -S -N -Y -f -p -H -E ${SRCS} ${HDRS} ${SIMULATE_SRC} ${FIT_SRC}
#         COMMENT "Formatting source codes..."
#         WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
# endif()

################################################################
## Copy test and configuration files; create documentation dir.
################################################################
file(COPY ${SHARE_DIR} DESTINATION ${CMAKE_BINARY_DIR})
file(MAKE_DIRECTORY ${DOCDIR})

################################################################
## Shared library.
################################################################
add_library(${DOS_EXTRACTION} SHARED ${SRCS})

set_target_properties(${DOS_EXTRACTION} PROPERTIES OUTPUT_NAME "${DOS_EXTRACTION}")    # Shared library filename.
target_link_libraries(${DOS_EXTRACTION} ${Boost_LIBRARIES})

################################################################
## Target 1.
################################################################
add_executable(${SIMULATE} ${SIMULATE_SRC})

set_target_properties(${SIMULATE} PROPERTIES OUTPUT_NAME "${SIMULATE}"    # Executable filename.
                                  INSTALL_RPATH "${LIB_INSTALLDIR}")    # rpath after installation.
target_link_libraries(${SIMULATE} ${DOS_EXTRACTION})

################################################################
## Target 2.
################################################################
add_executable(${FIT} ${FIT_SRC})

set_target_properties(${FIT} PROPERTIES OUTPUT_NAME "${FIT}"    # Executable filename.
                             INSTALL_RPATH "${LIB_INSTALLDIR}")    # rpath after installation.
target_link_libraries(${FIT} ${DOS_EXTRACTION})

################################################################
## Installation.
################################################################
install(TARGETS ${DOS_EXTRACTION} DESTINATION "${LIB_INSTALLDIR}")
install(FILES ${HDRS} DESTINATION "${INC_INSTALLDIR}")

install(DIRECTORY ${SHARE_DIR} DESTINATION "${SHARE_INSTALLDIR}")

install(TARGETS ${SIMULATE} DESTINATION "${BIN_INSTALLDIR}")
install(TARGETS ${FIT} DESTINATION "${BIN_INSTALLDIR}")

################################################################
## Uninstallation.
################################################################
add_custom_target(uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_MODULE_PATH}/Uninstall.cmake"
)
