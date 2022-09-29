#include "entity.hpp"

namespace mgl
{
    Entity::Entity(entt::entity t_entity, Scene *t_scene) : m_entity(t_entity), m_scene(t_scene) {}

    int Entity::getDrawableDataSize()
    {
        int size = 0;

        if (m_scene->m_entityGetters.find(m_entity) != m_scene->m_entityGetters.end())
        {
            for (auto callback : m_scene->m_entityGetters[m_entity])
            {
                size += callback.getDataSize();   
            }
        }

        return size;
    }

    void Entity::getDrawableData(void* t_data)
    {
        if (m_scene->m_entityGetters.find(m_entity) != m_scene->m_entityGetters.end())
        {
            struct componentData
            {
                void* data;
                int dataSize;
                int dataStride;
            };

            int verticeStide = 0;
            std::vector<componentData> compoentsData;
            for (auto callback : m_scene->m_entityGetters[m_entity])
            {
                // * init temp data buffer
                int dataSize = callback.getDataSize();
                int dataStride = callback.getStride();
                void *data = malloc(dataSize);

                callback.getData(data);

                componentData c;
                c.data = data;
                c.dataSize = dataSize;
                c.dataStride = dataStride;
                compoentsData.push_back(c);

                verticeStide += dataStride;

            }

            int dataOffset = 0;
            for (componentData component : compoentsData)
            {
                int passes = 0;
                for (int i = 0; i < component.dataSize; i+=component.dataStride)
                {
                    memcpy((void*)((char*)t_data+(verticeStide*passes)+dataOffset), (void*)((char*)component.data + i), component.dataStride);
                    passes++;
                }

                dataOffset += component.dataStride;
                free(component.data);
            }
        }
    }
}