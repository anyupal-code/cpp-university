cmake_minimum_required(VERSION 3.20)
project(cpp_course CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Предупреждения — полезно для обучения
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

# Уроки — раскомментируем по мере готовности
add_subdirectory(lesson-01-intro)
add_subdirectory(lesson-02-memory-types)
add_subdirectory(lesson-03-control-flow)
add_subdirectory(lesson-04-functions)
add_subdirectory(lesson-05-pointers)
add_subdirectory(lesson-06-memory-safety)
add_subdirectory(lesson-07-arrays)
add_subdirectory(lesson-08-2d-strings-files)
add_subdirectory(lesson-09-structs-oop-intro)
add_subdirectory(lesson-10-test-demo)
add_subdirectory(lesson-11-classes)
add_subdirectory(lesson-12-objects-collections)