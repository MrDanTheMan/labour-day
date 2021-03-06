#ifndef CAMERA_COMPONENT_HPP_
#define CAMERA_COMPONENT_HPP_

#include "../entitycomponent.hpp"
#include "../entityserialiser.hpp"
#include "../transform.hpp"
#include "../camera.hpp"
#include "transformcomponent.hpp"

namespace Engine
{
    namespace Components
    {
        class CameraComponentSerialiser : public EntityComponentSerialiser
        {
            public:
            CameraComponentSerialiser();
            virtual ~CameraComponentSerialiser() override ; 

            virtual bool Deserialise(
                EntityComponent* pComponent, 
                const ContentEntityComponentInfo * pComponentInfo,
                const ResourceCache *pResourceCache) const override;

            virtual bool DeserialiseAdd(
                Entity* pEntity, 
                const ContentEntityComponentInfo * pComponentInfo,
                const ResourceCache *pResourceCache) const override;
        };

        class CameraComponent: public TransformComponent
        {
            public:
            CameraComponent();
            CameraComponent(const CameraComponent &rhs);
            virtual ~CameraComponent();
            virtual std::unique_ptr<EntityComponent> Duplicate() const override;
            virtual void Init() override;
            
            void SetActive(const bool active);
            bool IsActive() const;

            void SetNearClip(const float val);
            void SetFarClip(const float val);
            void SetFOV(const float val);
            void SetAspect(const float val);
            void SetOffsetTranslation(const Vec3 &offset);
            void SetOffsetRotation(const Vec3 &offset);

            const float GetNearClip() const;
            const float GetFarClip() const;
            const float GetFOV() const;
            const float GetAspect() const;
            Vec3 GetOffsetTranslation() const;
            Vec3 GetOffsetRotation() const;
            const Camera * const CameraHandle() const;

            virtual void OnTransformChanged(const Transform &tr) override;


            private:
            void UpdateTransform();

            Transform m_offset;
            Camera m_cam;
            bool m_isActive;
        };
    }
}

#endif