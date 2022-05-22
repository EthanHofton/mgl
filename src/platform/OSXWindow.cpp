#include <mgl/mglpch.hpp>
#include "OSXWindow.hpp"

namespace mgl
{
    static bool s_GLFWInit = false;

    Window* Window::create(const windowProps& t_props)
    {
        return new OSXWindow(t_props);
    }

    OSXWindow::OSXWindow(const windowProps& t_props)
    {
        init(t_props);
    }

    OSXWindow::~OSXWindow()
    {
        quit();
    }


    void OSXWindow::init(const windowProps& t_props)
    {
        // * set window data title and size
        m_data.m_title = t_props.m_title;
        m_data.m_size = t_props.m_size;

        // * log new window creation
        CORE_INFO("Creating window {} ({}, {})", m_data.m_title, m_data.m_size.x, m_data.m_size.y);

        // * check glfw is not allready initalized
        if (!s_GLFWInit)
        {
            // * call glfw init and store wather the initaization was successsfult
            int sucess = glfwInit();

            // * assert wather the initaization was succesful or not
            MGL_CORE_ASSERT(sucess, "Could not initaize GLFW");

            // * mark glfwinit as true
            s_GLFWInit = true;
        }

        // * create a new GLFW window
        m_window = glfwCreateWindow((int)m_data.m_size.x, (int)m_data.m_size.y, m_data.m_title.c_str(), nullptr, nullptr);
        // * set the current context to the window
        glfwMakeContextCurrent(m_window);
        // * set the user pointer to the window data struct
        // * this is so that when event callbacks are run, we have access to the window data
        glfwSetWindowUserPointer(m_window, &m_data);
        // * turn on vsync
        setVSync(true);
    }

    void OSXWindow::quit()
    {
        // * destroy the glfw window
        glfwDestroyWindow(m_window);
    }

    void OSXWindow::onUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    void OSXWindow::setVSync(bool t_enabled)
    {
        glfwSwapInterval((int)(t_enabled));
        m_data.m_vsync = t_enabled;
    }

    bool OSXWindow::isVSync() const
    {
        return m_data.m_vsync;
    }
}