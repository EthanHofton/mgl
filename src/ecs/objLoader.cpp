#include "objLoader.hpp"

#include "components/UUID.hpp"
#include "components/transform.hpp"
#include "components/modelIndices.hpp"
#include "components/modelPoints.hpp"

namespace mgl
{
    static std::vector<std::future<void>> m_modelLoads;

    Entity loadObj(Scene *t_scene, std::string t_file)
    {
        Entity e = t_scene->createEntity();

        addObjToEntity(e, t_file);

        return e;
    }

    Entity loadObjAsync(Scene *t_scene, std::string t_file)
    {
        Entity e = t_scene->createEntity();

        m_modelLoads.push_back(std::async(std::launch::async, &addObjToEntity, e, t_file));

        return e;
    }

    void addObjToEntity(Entity e, std::string t_file)
    {
        const aiScene* scene = aiImportFile(t_file.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
        if (!scene)
        {
            MGL_CORE_ERROR("model {} not found: {}", t_file, aiGetErrorString());
        }

        // * load all meshes (assimp seperate a model into a mesh for each material)
        
        std::vector<glm::vec3> positions;
        std::vector<unsigned int> indices;
        int indicieOffset = 0;
        for (unsigned int meshIdx = 0; meshIdx < scene->mNumMeshes; meshIdx++)
        {
            aiMesh *mesh = scene->mMeshes[meshIdx];

            // * get vertices
            for (unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                aiVector3D vert = mesh->mVertices[i];

                positions.push_back({vert.x, vert.y, vert.z});
            }

            // * get indices
            std::vector<unsigned int> meshIndicies;
            meshIndicies.reserve(mesh->mNumFaces * 3u);
            for (unsigned int i = 0; i < mesh->mNumFaces; i++)
            {
                if (mesh->mFaces[i].mNumIndices != 3u)
                {
                    MGL_CORE_CRITICAL("model not triangle detected...");
                    assert(mesh->mFaces[i].mNumIndices == 3u);
                }

                for (int x = 0; x < 3; x++)
                {
                    meshIndicies.push_back(mesh->mFaces[i].mIndices[x]);
                }
            }
            int maxVal = *std::max_element(meshIndicies.begin(), meshIndicies.end()) + 1;
            for (unsigned int indice : meshIndicies)
            {
                indices.push_back(indice + indicieOffset);
            }
            indicieOffset += maxVal;

        }
        
        aiReleaseImport(scene);

        e.addComponent<ModelIndices>(indices);
        e.addDrawableComponent<ModelPoints>(&ModelPoints::getData, &ModelPoints::getSize, &ModelPoints::getStep, positions);

        MGL_CORE_INFO("model {} load compleated", t_file);
    }
}