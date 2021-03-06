#ifndef TEST_SCENE_HPP_
#define TEST_SCENE_HPP_

#include "engine/enginecore.hpp"
#include "engine/renderable.hpp"
#include "engine/model.hpp"
#include "engine/entity.hpp"
#include "engine/gltex.hpp"
#include "engine/assetcache.hpp"

class TestScene
{
    private:
    std::unique_ptr<Engine::AssetCache> m_cache;
    std::unique_ptr<Engine::Camera> m_camera;
    
    Engine::EngineCore* m_core;

    public:
    void Initialize(Engine::EngineCore *core);
    void Free();

    Engine::Camera* Cam();

};

#endif