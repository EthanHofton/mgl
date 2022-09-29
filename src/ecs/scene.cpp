#include "entity.hpp"

#include <mgl/ecs/components/camera3D.hpp>
#include <mgl/ecs/components/UUID.hpp>
#include <mgl/ecs/components/transform.hpp>

namespace mgl
{
    Scene::Scene()
    {
    }

    Scene::~Scene()
    {

    }

    Entity Scene::createEntity()
    {
        Entity e = Entity(m_registery.create(), this);
        e.addComponent<UUID>();
        return e;
    }

    void Scene::destroyEntity(Entity entity)
    {
        m_registery.destroy(entity);
    }

    void Scene::onEvent(Event &e)
    {
        auto view = m_registery.view<Camera3D*>();

        for (auto entity : view)
        {
            Camera3D* camera = view.get<Camera3D*>(entity);
            camera->onEvent(e);
        }
    }

    void Scene::onUpdate()
    {
        m_registery.view<Camera3D*>().each([](entt::entity entity, Camera3D *cam) {
            cam->onUpdate();
        });
    }
}