project(game_engine)



find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

add_subdirectory(vendor/sol2)
add_subdirectory(vendor/entt)
add_subdirectory(vendor/imgui-docking)
add_subdirectory(vendor/SFML)

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui-docking)
message("IMGUI_DIR="${IMGUI_DIR})
add_subdirectory(vendor/imgui-sfml)


set(SOURCES
    app/app.cpp
    app/glfw_opengl_imgui_layer.cpp
)

add_library(imgui_app STATIC ${SOURCES})
target_compile_definitions(imgui_app PRIVATE -DIMGUI_IMPL_OPENGL_LOADER_GLFW -DIMGUI_FREETYPE_ENABLE sfml_graphics fPic)
target_link_libraries(imgui_app PUBLIC imgui glfw OpenGL::GL util)
target_include_directories(imgui_app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
    core/uuid.cpp
    core/log.cpp
    # renderer/renderer.cpp
    # # renderer/renderer2d.cpp
    # renderer/index_buffer.cpp
    # # renderer/texture.cpp
    # # renderer/render_command.cpp
    # renderer/shader.cpp
    # renderer/vertex_buffer.cpp
    # renderer/vertex_buffer_layout.cpp
    # # renderer/world.cpp
    # renderer/uniform_buffer.cpp
    # renderer/renderer_api.cpp
    # # renderer/orthographic_camera.cpp
    # renderer/editor_camera.cpp
    # renderer/x86_64/framebuffer.cpp
    # # renderer/x86_64/camera.cpp
    # renderer/x86_64/vertex_array.cpp
    # # renderer/camera.cpp
    # platform/opengl/opengl_uniform_buffer.cpp
    # # platform/opengl/opengl_texture.cpp
    # platform/opengl/OpenGLRendererAPI.cpp
    # drawables/rect.cpp
    # drawables/text.cpp
    scene/scene.cpp
    scene/entity.cpp
    scene/scene_camera.cpp
    script_engine/script_engine.cpp
    script_engine/glm_lua_bindings.cpp
    input/mouse.cpp
    input/filesystem.cpp
    input/keyboard.cpp
    input/input_system.cpp
)

find_package(OpenGL REQUIRED)

set(LUA_VERSION lua5.3)

add_library(game_engine STATIC ${SOURCES})
target_link_libraries(game_engine PUBLIC
    GLEW::glew
    glfw
    OpenGL::OpenGL
    EnTT::EnTT
    sol2::sol2
    ${LUA_VERSION}-c++
    crypto
    ssl
    imgui_app
    ImGui-SFML::ImGui-SFML
)
target_include_directories(game_engine PUBLIC
    ..
    ..vendor/glm
    /usr/include/${LUA_VERSION}
    ${CMAKE_SOURCE_DIR}/vendor
    ${CMAKE_SOURCE_DIR}/gui/vendor/imgui-docking
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# target_include_directories(embedlua PRIVATE /usr/include/lua5.1)
# target_compile_definitions(embedlua PUBLIC "LUABIND_USE_CXX11")
# target_link_directories(embedlua PUBLIC /usr/lib/x86_64-linux-gnu)
# target_link_libraries(embedlua PRIVATE lua5.1-c++ sfml-graphics EnTT::EnTT sol2::sol2)
