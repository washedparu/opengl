cmake_minimum_required(VERSION 3.27)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project("opengl")


set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(EXTERNAL_DIR "${CMAKE_SOURCE_DIR}/external")


file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
	${SRC_DIR}/*.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})    

target_include_directories(opengl PUBLIC 
	"${INCLUDE_DIR}"
    "${EXTERNAL_DIR}"
)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
)

target_link_libraries(${PROJECT_NAME}
    OpenGL::GL
    glfw
    GLEW::GLEW
)