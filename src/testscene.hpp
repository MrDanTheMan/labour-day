#ifndef TEST_SCENE_HPP_
#define TEST_SCENE_HPP_

#include "engine/enginecore.hpp"
#include "engine/renderable.hpp"
#include "engine/model.hpp"
#include "engine/entity.hpp"

class TestScene
{
    private:
    std::unique_ptr<Engine::Renderable> m_triangle;
    std::unique_ptr<Engine::Model> m_triangleModel;
    std::unique_ptr<Engine::Camera> m_camera;
    Engine::EngineCore* m_core;
    Engine::Entity* m_asset;

    public:
    void Initialize(Engine::EngineCore *core);
    void Update();

    Engine::Renderable* TestTriangle();
    Engine::Entity* Asset();
    Engine::Camera* Cam();

};

#endif