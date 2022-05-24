#include <mgl/mglpch.hpp>
#include "OSXWindow.hpp"

#ifdef MGL_PLATFORM_OSX

#include <mgl/events/keyEvent.hpp>
#include <mgl/events/applicationEvent.hpp>
#include <mgl/events/mouseEvent.hpp>

#include <GL/glew.h>

namespace mgl
{
    static bool s_GLFWInit = false;
    static bool s_GLEWInit = false;

    static void GLFWErrorCallback(int t_error, const char* t_description)
    {
        MGL_CORE_ERROR("GLFW Error ({}): {}", t_error, t_description);
    }

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
        MGL_CORE_INFO("Creating window {} ({}, {})", m_data.m_title, m_data.m_size.x, m_data.m_size.y);

        // * check glfw is not allready initalized
        if (!s_GLFWInit)
        {
            // * call glfw init and store wather the initaization was successsfult
            int sucess = glfwInit();

            // * assert wather the initaization was succesful or not
            MGL_CORE_ASSERT(sucess, "Could not initaize GLFW");

            // * set glfw error callback
            glfwSetErrorCallback(GLFWErrorCallback);

            // * mark glfwinit as true
            s_GLFWInit = true;
        }

        // * define the version and compatibilty settings
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

        // * create a new GLFW window
        m_window = glfwCreateWindow((int)m_data.m_size.x, (int)m_data.m_size.y, m_data.m_title.c_str(), nullptr, nullptr);
        // * set the current context to the window
        glfwMakeContextCurrent(m_window);
        // * set the user pointer to the window data struct
        // * this is so that when event callbacks are run, we have access to the window data
        glfwSetWindowUserPointer(m_window, &m_data);

        // * turn on vsync
        setVSync(true);

        // * set GLFW callbacks
        // * glfw window resize event callback function
        glfwSetWindowSizeCallback(m_window, [](GLFWwindow * t_window, int t_width, int t_height)
        {
            // * get the user data from the window
            windowData &wdata = *(windowData*)glfwGetWindowUserPointer(t_window);
            // * set a window resize
            wdata.m_size = {t_width, t_height};

            // * create a window resize event
            WindowResizeEvent event({t_width, t_height});
            // * run the window event callback with the created event
            wdata.m_eventCallback(event);
        });

        // * glfw window close callback function
        glfwSetWindowCloseCallback(m_window, [](GLFWwindow *t_window)
        {
            // * get the user data from the windows
            windowData &wdata = *(windowData*)glfwGetWindowUserPointer(t_window);
            // * create a window close event
            WindowCloseEvent event;
            // * run the window event callback function with the created event
            wdata.m_eventCallback(event);
        });

        // * glfw key event callback
        glfwSetKeyCallback(m_window, [](GLFWwindow *t_window, int t_key, int t_scancode, int t_action, int t_mods)
        {
            // * get the user data from the windows
            windowData &wdata = *(windowData*)glfwGetWindowUserPointer(t_window);

            // * go thorugh each action possiblity
            switch (t_action)
            {
                case GLFW_PRESS:
                {
                    // * create a key press event with no repetes
                    KeyPressedEvent event(t_key, 0);
                    // * run the callback function with this event
                    wdata.m_eventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    // * create a key released event with the key
                    KeyReleasedEvent event(t_key);
                    // * run the callback function with this event
                    wdata.m_eventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    // * create a key pressed event with repetes and the given key
                    KeyPressedEvent event(t_key, 1);
                    // * run the callback function with this events
                    wdata.m_eventCallback(event);
                    break;
                }
            }
        });

        // * glfw mouse event callback
        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* t_window, int t_button, int t_action, int t_mods)
        {
            // * get the user data from the windows
            windowData &wdata = *(windowData*)glfwGetWindowUserPointer(t_window);

            // * go thorugh each action possiblity
            switch (t_action)
            {
                case GLFW_PRESS:
                {
                    // * create a new mouse pressed event
                    MouseButtonPressedEvent event(t_button);
                    // * run the callback function with this events
                    wdata.m_eventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    // * create a new mouse released event
                    MouseButtonReleasedEvent event(t_button);
                    // * run the callback function with this events
                    wdata.m_eventCallback(event);
                    break;
                }
            }
        });

        // * glfw set mouse scroll callback function
        glfwSetScrollCallback(m_window, [](GLFWwindow *t_window, double t_x, double t_y)
        {
            // * get the user data from the windows
            windowData &wdata = *(windowData*)glfwGetWindowUserPointer(t_window);
            // * create a mouse scroll event
            MouseScrolledEvent event({t_x, t_y});
            // * run the window event callback function with the created event
            wdata.m_eventCallback(event);
        });

        // * glfw mouse moved event
        glfwSetCursorPosCallback(m_window, [](GLFWwindow *t_window, double t_x, double t_y)
        {
            // * get the user data from the windows
            windowData &wdata = *(windowData*)glfwGetWindowUserPointer(t_window);
            // * create a mouse scroll event
            MouseMovedEvent event({t_x, t_y});
            // * run the window event callback function with the created event
            wdata.m_eventCallback(event);
        });

        if (!s_GLEWInit)
        {
            // * initalise glew
            glewExperimental = GL_TRUE;

            // * initalize glew
            int glewSucces = glewInit();
            MGL_CORE_ASSERT(glewSucces == GLEW_OK, "GLEW Error: Could not initialize");

            MGL_CORE_INFO("GLEW intialized: OpenGL Version: {}", std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));

            s_GLEWInit = true;
        }
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

#endif