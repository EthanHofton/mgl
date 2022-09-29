#ifndef objLoader_hpp
#define objLoader_hpp

#include "entity.hpp"

#include <future>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/material.h>

namespace mgl
{
    Entity loadObj(Scene *t_scene, std::string t_file);
    Entity loadObjAsync(Scene *t_scene, std::string t_file);

    void addObjToEntity(Entity e, std::string t_file);
}

#endif