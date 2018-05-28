set(ID_GEN_SRC IncrementalConcurrentIdGenerator.cpp)

add_library(libidgenerator STATIC ${ID_GEN_SRC})
target_include_directories(libidgenerator PUBLIC ../../include/infrastructure)


set(REPOSITORY_HDR infrastructure/StudentRepository.h)
set(REPOSITORY_SRC StudentRepository.cpp)

add_library(libstudentrepository STATIC ${REPOSITORY_SRC})
target_include_directories(libstudentrepository PUBLIC ../../include/infrastructure)
target_link_libraries(libstudentrepository libstudent)

set(CONTROLLER_HDR infrastructure/StudentController.h)
set(CONTROLLER_SRC StudentController.cpp)

add_library(libstudentcontroller STATIC ${CONTROLLER_SRC})
target_include_directories(libstudentcontroller PUBLIC ../../include/infrastructure)
target_link_libraries(libstudentcontroller libstudent)
target_link_libraries(libstudentcontroller libstudentrepository)