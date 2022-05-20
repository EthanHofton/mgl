#include <mgl/core/scene.hpp>

namespace mgl
{
    std::vector<std::string> Scene::s_scenes;

    Scene::Scene(Window *t_window, std::string t_entityId) : Entity(t_entityId), m_parent(t_window)
    {
        s_scenes.push_back(getEntityId());
        active(false);
    }

    Scene::~Scene() {}

    void Scene::imguiShowSceneHierarchy()
    {
        ImGui::Begin(getEntityId().c_str());
        ImGui::End();
    }
}