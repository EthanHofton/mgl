#ifndef UUID_hpp
#define UUID_hpp

#include <mgl/mglpch.hpp>

namespace mgl
{
    struct UUID
    {
        UUID() { m_uuid = uuidGen::get(); }
        std::string regenerate() { m_uuid = uuidGen::get(); return m_uuid; }
        std::string getUUID() { return m_uuid; }

    private:

        std::string m_uuid;
    };
}

#endif