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

    void Scene::imguiInspector()
    {
        // * open new imgui window
        ImGui::Begin(getEntityId().c_str());

        if (ImGui::BeginTabBar("MyTabBar"))
        {
            if (ImGui::BeginTabItem("Scene Graph"))
            {
                // if (ImGui::TreeNode("Scene Graph"))
                // {
                //     ImGui::TreePop();
                // }
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Other thing"))
            {
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
        

        // * close imgui window
        ImGui::End();
    }
}