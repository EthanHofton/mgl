#include <mgl/core/scene.hpp>

namespace mgl
{
    std::vector<std::string> Scene::s_scenes;

    Scene::Scene(std::string t_entityId, Window *t_window) : Entity(t_entityId), m_parent(t_window)
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