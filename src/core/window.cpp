#include <mgl/core/window.hpp>

namespace mgl
{
    Window::Window(std::string t_title)
    {
        m_graphicsInstance = Graphics::instance();
        m_graphicsInstance->title(t_title);
        m_graphicsInstance->clearColor(glm::vec4(1,1,1,1));
        m_graphicsInstance->init();
        
        m_isRunning = m_graphicsInstance->initalised();
        
        Config::instance();
        
        m_activeScene = "";
        m_timerInstance = Timer::instance();
        
        m_frameRate = (float)(GAME_CONFIG()["fps"].GetInt());
        m_inputManager = InputManager::instance();

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
        
        Logger::instance();
    }

    Window::~Window()
    {
        Graphics::release();
        m_graphicsInstance = nullptr;
        
        Timer::release();
        m_timerInstance = nullptr;
        
        InputManager::release();
        m_inputManager = nullptr;

        glDeleteBuffers(1, &m_vao);
        
        // * make sure all entites are deleted
        Entity::deleteAllEntities();
        
        Logger::release();
        Config::release();
        
    }

    void Window::setActiveScene(std::string t_entityId)
    {
        // * set the old scences activity to false
        if (m_activeScene != "")
        {
            Entity::getEntity<Scene>(m_activeScene)->activePropagate(false);
        }

        // * log scene change
        CORE_INFO("setting active scene with id: {0}", t_entityId);
        // * set new active scene
        m_activeScene = t_entityId;
        // * set the new scence activity to true
        Entity::getEntity<Scene>(m_activeScene)->activePropagate(true);
    }

    void Window::run()
    {
        while (m_isRunning)
        {
            m_timerInstance->tick();
            
            if (m_timerInstance->getDeltaTime() >= (1.0 / m_frameRate))
            {
                while (m_graphicsInstance->pollEvent())
                {
                    ImGui_ImplSDL2_ProcessEvent(&m_graphicsInstance->getEvent());
                    m_inputManager->giveEvents(m_graphicsInstance->getEvent());
                    
                    if (m_activeScene != "")
                    {
                        Entity::getEntity<Scene>(m_activeScene)->onEvent(m_graphicsInstance->getEvent());
                    }
                    
                    if (m_graphicsInstance->getEvent().type == SDL_QUIT)
                    {
                        m_isRunning = false;
                        break;
                    }
                }
                
                // * early update
                earlyUpdate();
                
                // * update
                update();
                
                // * render
                draw();
                
                // * late update
                lateUpdate();
            }
        }
    }

    void Window::earlyUpdate()
    {
        m_timerInstance->reset();
        m_inputManager->update();
    }

    void Window::update()
    {
        if (m_activeScene != "")
        {
            // * update scence first
            Entity::getEntity<Scene>(m_activeScene)->update();

            // * update other entites without scene
            // * loop through all the entites in existance
            // * update if the are not the scence and not active
            for (auto entity : Entity::getAllEntites())
            {
                if (entity != m_activeScene)
                {
                    if (Entity::getEntity<Entity>(entity)->isActive())
                    {
                        // * proform an entity update if the entity is active
                        Entity::getEntity<Entity>(entity)->update();
                    }
                }
            }

        }
    }

    void Window::lateUpdate()
    {
        m_inputManager->updatePrevInput();
    }
    
    void Window::draw()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        m_graphicsInstance->screenClear();
        m_graphicsInstance->screenClearColor();
        
        if (m_activeScene != "")
        {
            Entity::getEntity<Scene>(m_activeScene)->onDraw();
        }
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        m_graphicsInstance->swapBuffers();
    }
}