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