cmake_minimum_required(VERSION 3.25)
project(learningOpenGL C)
set(CMAKE_C_STANDARD 99)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

#target_link_libraries(gamequestionmark -lOpenGL32 -lfreeGLUT)

add_executable(${PROJECT_NAME} dvd.c)

IF (WIN32)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} wsock32 ws2_32)
ENDIF ()
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLUT_LIBRARIES})





project(dvd C)
set(CMAKE_C_STANDARD 99)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

#target_link_libraries(gamequestionmark -lOpenGL32 -lfreeGLUT)

add_executable(dvd dvd.c)

IF (WIN32)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} wsock32 ws2_32)
ENDIF ()
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLUT_LIBRARIES})



project(learningstuff C)
set(CMAKE_C_STANDARD 99)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

#target_link_libraries(gamequestionmark -lOpenGL32 -lfreeGLUT)

add_executable(learningstuff learningstuff.c)

IF (WIN32)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} wsock32 ws2_32)
ENDIF ()
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLUT_LIBRARIES})