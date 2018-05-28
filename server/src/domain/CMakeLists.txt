project(student)

set(HEADER_FILES domain/Student.h crow_all.h)
set(SOURCE_FILES Student.cpp)

add_library(libstudent STATIC ${SOURCE_FILES})
target_include_directories(libstudent PUBLIC ../../include/domain)
