#ifndef TRANSFORM_COMPONENT_HPP_
#define TRANSFORM_COMPONENT_HPP_

#include "../entitycomponent.hpp"
#include "../entityserialiser.hpp"
#include "../transform.hpp"

namespace Engine
{
    namespace Components
    {
        class TransformComponentSerialiser : public EntityComponentSerialiser
        {
            public:
            TransformComponentSerialiser();
            virtual ~TransformComponentSerialiser();
            virtual bool Deserialise(EntityComponent* pComponent, const ContentEntityComponentInfo * pComponentInfo) const override;
            virtual bool DeserialiseAdd(Entity* pEntity, const ContentEntityComponentInfo * pComponentInfo) const override;
        };


        class TransformComponent : public EntityComponent
        {
            public:
            TransformComponent() = default;
            TransformComponent(const TransformComponent &rhs) = default;
            virtual ~TransformComponent() override;

            void Init() override;
            std::unique_ptr<EntityComponent> Duplicate() const override;

            Transform & GetTransform();
            const Transform & GetTransform() const;

            private:
            Transform m_tr;
        } ;
    }
}

#endif