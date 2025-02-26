# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/toyot/Documents/programming/8.semester/lec5/cmake-build-release/_deps/googlebenchmark-src")
  file(MAKE_DIRECTORY "C:/Users/toyot/Documents/programming/8.semester/lec5/cmake-build-release/_deps/googlebenchmark-src")
endif()
file(MAKE_DIRECTORY
  "C:/Users/toyot/Documents/programming/8.semester/lec5/cmake-build-release/_deps/googlebenchmark-build"
  "C:/Users/toyot/Documents/programming/8.semester/lec5/cmake-build-release/_deps/googlebenchmark-subbuild/googlebenchmark-populate-prefix"
  "C:/Users/toyot/Documents/programming/8.semester/lec5/cmake-build-release/_deps/googlebenchmark-subbuild/googlebenchmark-populate-prefix/tmp"
  "C:/Users/toyot/Documents/programming/8.semester/lec5/cmake-build-release/_deps/googlebenchmark-subbuild/googlebenchmark-populate-prefix/src/googlebenchmark-populate-stamp"
  "C:/Users/toyot/Documents/programming/8.semester/lec5/cmake-build-release/_deps/googlebenchmark-subbuild/googlebenchmark-populate-prefix/src"
  "C:/Users/toyot/Documents/programming/8.semester/lec5/cmake-build-release/_deps/googlebenchmark-subbuild/googlebenchmark-populate-prefix/src/googlebenchmark-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/toyot/Documents/programming/8.semester/lec5/cmake-build-release/_deps/googlebenchmark-subbuild/googlebenchmark-populate-prefix/src/googlebenchmark-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/toyot/Documents/programming/8.semester/lec5/cmake-build-release/_deps/googlebenchmark-subbuild/googlebenchmark-populate-prefix/src/googlebenchmark-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
