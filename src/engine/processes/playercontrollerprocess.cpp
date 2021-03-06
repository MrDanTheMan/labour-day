#include "playercontrollerprocess.hpp"
#include "../components/playercontrollercomponent.hpp"

using namespace Engine::Processes;

void PlayerControllerProcess::OnUpdate(Engine::Entity * const entity)
{
    auto playerCom = entity->Components().GetFirst<Components::PlayerControllerComponent>();

    assert (playerCom != nullptr);
    assert (entity->IsRoot());

    // Auto posses movement component if one exist on the same entity
    // This will only happen if the controller is not already possessing one
    if(playerCom->AutoPossesses() && playerCom->GetCapturedMovement() == nullptr)
    {
        auto movCom = entity->Components().GetFirst<Engine::Components::MovementComponent>();
        if(movCom != nullptr)
        {
            playerCom->CaptureComponent(movCom);
        }
    }

    // Resolve movmenet on captured component
    if(playerCom->GetCapturedMovement() != nullptr)
    {
        const Vec3 dir = playerCom->GetMovementDir();
        if(dir == Vec3(0,0,0))
        {
            playerCom->GetCapturedMovement()->SetPendingMovement(false);
        }
        else
        {
            playerCom->GetCapturedMovement()->SetPendingMovement(true);
            playerCom->GetCapturedMovement()->SetDirection(dir);
        }
        
    }
}

bool PlayerControllerProcess::IsValidEntity(Engine::Entity * const entity)
{
    if(entity->Components().GetFirst<Components::PlayerControllerComponent>() != nullptr)
    {
        return true;
    }

    return false;
}