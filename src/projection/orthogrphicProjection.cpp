#include "orthogrphicProjection.hpp"
#include <mgl/core/application.hpp>

namespace mgl
{
    OrthogrphicProjection::OrthogrphicProjection()
    {
        glm::vec2 size = Application::get().getWindow().getSize();
        float width = size.x;
        float height = size.y;
        float z_near = GAME_CONFIG()["z_near_ortho"].GetInt();
        float z_far = GAME_CONFIG()["z_far_ortho"].GetInt();
        m_projection = glm::ortho(0.0f, width, height, 0.0f, z_near, z_far);
    }

    OrthogrphicProjection::~OrthogrphicProjection(){}

    void OrthogrphicProjection::onEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        dispatcher.dispatch<WindowResizeEvent>(MGL_BIND_FN(OrthogrphicProjection::onWindowResize));
    }

    bool OrthogrphicProjection::onWindowResize(WindowResizeEvent& e)
    {
        float z_near = GAME_CONFIG()["z_near_ortho"].GetInt();
        float z_far = GAME_CONFIG()["z_far_ortho"].GetInt();
        m_projection = glm::ortho(0.0f, e.getSize().x, e.getSize().y, 0.0f, z_near, z_far);
        return false;
    }
}