#ifndef APP_HPP_
#define APP_HPP_

#include "engine/enginecore.hpp"
#include "engine/debugoverlay.hpp"
#include "testscene.hpp"

class App
{
    public:
    bool Initialize();
    void Run();
    void Exit();
    Engine::EngineCore* Engine();

    private:
    void UpdateGame(const double deltaTime);
    void DrawGame();
    void UpdateUI();
    void DrawUI();

    private:
    std::unique_ptr<Engine::EngineCore> m_core;
    std::unique_ptr<Engine::DebugOverlay> m_overlay;
    std::unique_ptr<TestScene> m_testScene;
};

#endif