add_subdirectory(domain)
add_subdirectory(infrastructure)

set(SOURCE_FILES Server.cpp)

add_library(libserver STATIC ${SOURCE_FILES})
target_include_directories(libserver PUBLIC ../include/)
target_link_libraries(libserver ${Boost_LIBRARIES})
target_link_libraries(libserver Threads::Threads)
target_link_libraries(libserver libstudent)
target_link_libraries(libserver libidgenerator)
target_link_libraries(libserver libstudentrepository)
target_link_libraries(libserver libstudentcontroller)

set(SERVER_SOURCE_FILES main.cpp)

add_executable(server ${SERVER_SOURCE_FILES})
target_link_libraries(server libserver)