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

        // * begin tab bar
        if (ImGui::BeginTabBar("MyTabBar"))
        {
            // * begin scene graph tab
            if (ImGui::BeginTabItem("Scene Graph"))
            {
                // * create a new tree with this scene as the starting node
                if (ImGui::TreeNode(getEntityId().c_str()))
                {
                    for (auto child : getChildren())
                    {
                        imguiChildTree(child);
                    }
                    

                    ImGui::TreePop();
                }


                // * end scene graph tab
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Other thing"))
            {
                ImGui::EndTabItem();
            }

            // * close tab bar
            ImGui::EndTabBar();
        }
        

        // * close imgui window
        ImGui::End();
    }

    void Scene::imguiChildTree(std::string t_child)
    {
        ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_None;
        if (!Entity::getEntity<Entity>(t_child)->hasChildren())
        {
            treeFlags |= ImGuiTreeNodeFlags_Leaf;
            treeFlags |= ImGuiTreeNodeFlags_Bullet;
        }

        bool nodeOpen = ImGui::TreeNodeEx(t_child.c_str(), treeFlags);

        ImGui::SameLine(ImGui::GetWindowWidth() - 65);
        if (ImGui::SmallButton("Inspect"))
        {
            // t_e->shouldShowImguiInspector(true);
        }

        if (nodeOpen)
        {
            for (auto child : Entity::getEntity<Entity>(t_child)->getChildren())
            {
                imguiChildTree(child);
            }

            ImGui::TreePop();
        }
    }
}