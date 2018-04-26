project(server)

add_subdirectory(src)

add_library(libserver STATIC ${LIB_SERVER_SOURCE_FILES})
target_include_directories(libserver PUBLIC include)
target_link_libraries(libserver ${Boost_LIBRARIES})
target_link_libraries(libserver Threads::Threads)


add_executable(server ${SERVER_SOURCE_FILES})
target_link_libraries(server libserver)

