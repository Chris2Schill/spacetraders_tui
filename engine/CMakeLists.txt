project(game_engine)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

set(SOURCES
    core/uuid.cpp
    # renderer/renderer.cpp
    # renderer/renderer2d.cpp
    # renderer/framebuffer.cpp
    # renderer/index_buffer.cpp
    # renderer/texture.cpp
    # renderer/render_command.cpp
    # renderer/shader.cpp
    # renderer/vertex_array.cpp
    # renderer/vertex_buffer.cpp
    # renderer/vertex_buffer_layout.cpp
    # renderer/world.cpp
    # renderer/uniform_buffer.cpp
    # renderer/renderer_api.cpp
    # renderer/orthographic_camera.cpp
    # platform/opengl/opengl_uniform_buffer.cpp
    # platform/opengl/opengl_texture.cpp
    scene/scene.cpp
    scene/entity.cpp
    scene/scene_camera.cpp
    input/mouse.cpp
    input/filesystem.cpp
    input/keyboard.cpp
)

add_library(game_engine STATIC ${SOURCES})
target_link_libraries(game_engine PUBLIC GLEW::glew glfw)
target_include_directories(game_engine PUBLIC
    ..
    ../entt/single_include
)
