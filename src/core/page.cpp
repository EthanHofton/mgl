#include <mgl/core/page.hpp>

namespace mgl
{
    std::map<std::string, Page*> Page::s_pages;

    Page::Page(Window *t_window, std::string t_pageId) : m_parent(t_window), m_pageId(t_pageId)
    {
        s_pages[m_pageId] = this;
        CORE_INFO("Created Page with id '{}'", t_pageId);
    }

    Page::~Page()
    {
        auto pageInstance = s_pages.find(m_pageId);
        if (pageInstance != s_pages.end())
        {
            s_pages.erase(pageInstance);
        }

        CORE_INFO("Deleting Page with id '{}'", m_pageId);
    }

    void Page::imguiShowSceneHierarchy()
    {
        std::string pageTitle = m_pageId + " Scence";
        ImGui::Begin(pageTitle.c_str());
        ImGui::End();
    }
}