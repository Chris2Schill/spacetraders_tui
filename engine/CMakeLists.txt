project(game_engine)

add_subdirectory(sol2)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

set(SOURCES
    core/uuid.cpp
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
)

find_package(OpenGL REQUIRED)

add_library(game_engine STATIC ${SOURCES})
target_link_libraries(game_engine PUBLIC GLEW::glew glfw OpenGL::OpenGL sol2::sol2 lua5.2-c++)
target_include_directories(game_engine PUBLIC
    ..
    ../entt/single_include
    /usr/include/lua5.2
)

# target_include_directories(embedlua PRIVATE /usr/include/lua5.1)
# target_compile_definitions(embedlua PUBLIC "LUABIND_USE_CXX11")
# target_link_directories(embedlua PUBLIC /usr/lib/x86_64-linux-gnu)
# target_link_libraries(embedlua PRIVATE lua5.1-c++ sfml-graphics EnTT::EnTT sol2::sol2)
