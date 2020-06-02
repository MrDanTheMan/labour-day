#ifndef PREFAB_HPP_
#define PREFAB_HPP_

#include "iresource.hpp"
#include "entityserialiser.hpp"

#include <string>
#include <memory>

namespace Engine
{
    class Prefab : public IResource
    {
        public:
        static std::unique_ptr<Prefab> FromJSON(const std::string &filepath);
        void Unload() override;

        private:
        std::unique_ptr<Entity> m_entity;

    };
}

#endif