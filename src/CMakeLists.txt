cmake_minimum_required(VERSION 3.16.3)
project(stats C)
add_subdirectory("deps/piot/clog/src/lib")
add_subdirectory("deps/piot/tiny-libc/src/lib")
add_subdirectory("deps/piot/monotonic-time-c/src/lib")
add_subdirectory("lib")