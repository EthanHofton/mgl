#include "perspectiveProjection.hpp"
#include <mgl/core/application.hpp>

namespace mgl
{
    PerspectiveProjection::PerspectiveProjection()
    {
        glm::vec2 size = Application::get().getWindow().getSize();
        float width = size.x;
        float height = size.y;
        float z_near = GAME_CONFIG()["z_near_perspective"].GetFloat();
        float z_far = GAME_CONFIG()["z_far_perspective"].GetFloat();
        float fov = GAME_CONFIG()["fov"].GetFloat();
        m_projection = glm::perspective(fov, width/height, z_near, z_far);
    }

    PerspectiveProjection::~PerspectiveProjection() {}

    void PerspectiveProjection::onEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        dispatcher.dispatch<WindowResizeEvent>(MGL_BIND_FN(PerspectiveProjection::onWindowResize));
    }

    bool PerspectiveProjection::onWindowResize(WindowResizeEvent &e)
    {
        float z_near = GAME_CONFIG()["z_near_perspective"].GetFloat();
        float z_far = GAME_CONFIG()["z_far_perspective"].GetFloat();
        float fov = GAME_CONFIG()["fov"].GetFloat();
        m_projection = glm::perspective(fov, e.getSize().x/e.getSize().y, z_near, z_far);

        return false;
    }
}