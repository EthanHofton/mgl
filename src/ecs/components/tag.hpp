#ifndef tag_hpp
#define tag_hpp

#include <mgl/mglpch.hpp>

namespace mgl
{
    struct Tag
    {
        Tag(std::string t_tag) : m_tag(t_tag) {}
        Tag() : m_tag("Entity") {}

        std::string m_tag;
    };
}

#endif