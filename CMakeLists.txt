cmake_minimum_required(VERSION 3.14)

project(labour-day CXX)

# Binary output paths
set(CMAKE_BINARY_DIR ./bin/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Find Dependencies
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

# Project sources
set(PROJECT_SOURCE_DIR ./src/)
include_directories(${PROJECT_SOURCE_DIR})

# Main project (user) source files
set(SOURCES 
${PROJECT_SOURCE_DIR}/main.cpp
${PROJECT_SOURCE_DIR}/app.cpp
${PROJECT_SOURCE_DIR}/engine/glfwinterface.cpp
${PROJECT_SOURCE_DIR}/engine/glewinterface.cpp
${PROJECT_SOURCE_DIR}/engine/gfx.cpp
${PROJECT_SOURCE_DIR}/engine/enginecore.cpp
${PROJECT_SOURCE_DIR}/engine/shadersource.cpp
${PROJECT_SOURCE_DIR}/engine/shaderprog.cpp
${PROJECT_SOURCE_DIR}/engine/shadersemantics.cpp
${PROJECT_SOURCE_DIR}/engine/runtimeshaders.cpp
${PROJECT_SOURCE_DIR}/engine/mesh.cpp
${PROJECT_SOURCE_DIR}/engine/meshgen.cpp
${PROJECT_SOURCE_DIR}/engine/renderable.cpp
${PROJECT_SOURCE_DIR}/engine/commonrenderer.cpp
${PROJECT_SOURCE_DIR}/engine/camera.cpp
${PROJECT_SOURCE_DIR}/engine/window.cpp 
${PROJECT_SOURCE_DIR}/engine/transform.cpp
${PROJECT_SOURCE_DIR}/engine/inputmanager.cpp
${PROJECT_SOURCE_DIR}/engine/entity.cpp
${PROJECT_SOURCE_DIR}/engine/entityserialiser.cpp
${PROJECT_SOURCE_DIR}/engine/entitycomponent.cpp
${PROJECT_SOURCE_DIR}/engine/entitycomponentcollection.cpp
${PROJECT_SOURCE_DIR}/engine/level.cpp
${PROJECT_SOURCE_DIR}/engine/lights.cpp
${PROJECT_SOURCE_DIR}/engine/lightscache.cpp
${PROJECT_SOURCE_DIR}/engine/model.cpp
${PROJECT_SOURCE_DIR}/engine/modelinstance.cpp
${PROJECT_SOURCE_DIR}/engine/ecssys.cpp
${PROJECT_SOURCE_DIR}/engine/entityprocess.cpp
${PROJECT_SOURCE_DIR}/engine/texture2d.cpp
${PROJECT_SOURCE_DIR}/engine/tags.cpp
${PROJECT_SOURCE_DIR}/engine/gltex.cpp
${PROJECT_SOURCE_DIR}/engine/sysutils.cpp
${PROJECT_SOURCE_DIR}/engine/material.cpp
${PROJECT_SOURCE_DIR}/engine/shaderparam.cpp
${PROJECT_SOURCE_DIR}/engine/shaderparamcollection.cpp
${PROJECT_SOURCE_DIR}/engine/iresource.cpp
${PROJECT_SOURCE_DIR}/engine/resourcecache.cpp
${PROJECT_SOURCE_DIR}/engine/assetcache.cpp
${PROJECT_SOURCE_DIR}/engine/prefab.cpp
${PROJECT_SOURCE_DIR}/engine/contentserialisation.cpp
${PROJECT_SOURCE_DIR}/engine/contentserialiser.cpp
${PROJECT_SOURCE_DIR}/engine/gametime.cpp
${PROJECT_SOURCE_DIR}/engine/imguiinterface.cpp
${PROJECT_SOURCE_DIR}/engine/fpscounter.cpp
${PROJECT_SOURCE_DIR}/engine/debugoverlay.cpp
${PROJECT_SOURCE_DIR}/engine/event.cpp
${PROJECT_SOURCE_DIR}/engine/shadowframebuffer.cpp
${PROJECT_SOURCE_DIR}/engine/shadowmaprenderer.cpp
${PROJECT_SOURCE_DIR}/engine/components/transformcomponent.cpp
${PROJECT_SOURCE_DIR}/engine/components/modelcomponent.cpp
${PROJECT_SOURCE_DIR}/engine/components/wobblecomponent.cpp
${PROJECT_SOURCE_DIR}/engine/components/cameracomponent.cpp
${PROJECT_SOURCE_DIR}/engine/components/controllercomponent.cpp
${PROJECT_SOURCE_DIR}/engine/components/playercontrollercomponent.cpp
${PROJECT_SOURCE_DIR}/engine/components/movementcomponent.cpp
${PROJECT_SOURCE_DIR}/engine/components/terraincomponent.cpp
${PROJECT_SOURCE_DIR}/engine/components/lightcomponent.cpp
${PROJECT_SOURCE_DIR}/engine/processes/wobbleprocess.cpp
${PROJECT_SOURCE_DIR}/engine/processes/controllerprocess.cpp
${PROJECT_SOURCE_DIR}/engine/processes/playercontrollerprocess.cpp
${PROJECT_SOURCE_DIR}/engine/processes/movementprocess.cpp
${PROJECT_SOURCE_DIR}/external/imgui/imgui.cpp
${PROJECT_SOURCE_DIR}/external/imgui/imgui_draw.cpp
${PROJECT_SOURCE_DIR}/external/imgui/imgui_tables.cpp
${PROJECT_SOURCE_DIR}/external/imgui/imgui_widgets.cpp
${PROJECT_SOURCE_DIR}/external/imgui/imgui_demo.cpp
${PROJECT_SOURCE_DIR}/external/imgui/backends/imgui_impl_glfw.cpp
${PROJECT_SOURCE_DIR}/external/imgui/backends/imgui_impl_opengl3.cpp
${PROJECT_SOURCE_DIR}/testscene.cpp
${PROJECT_SOURCE_DIR}/testentity.cpp 
${PROJECT_SOURCE_DIR}/testproc.cpp)

add_executable(labour-day ${SOURCES})


# Link GLFW and OpenGL
target_include_directories(labour-day PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(labour-day glfw OpenGL::GL)
