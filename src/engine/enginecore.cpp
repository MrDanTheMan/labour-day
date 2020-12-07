#include "enginecore.hpp"
#include "debugging.hpp"
#include "inputmanager.hpp"

using namespace Engine;

EngineCore::EngineCore():
m_gfx(nullptr),
m_glfw(nullptr),
m_mainWin(nullptr)
{
}

bool EngineCore::Initialize()
{
    assert (m_gfx == nullptr);
    assert (m_glfw == nullptr);
    
    m_glfw = std::make_unique<GLFWInterface>();
    if(!m_glfw->Initialize())
    {
        D_ERR("Failed to initialize GLFW context !");
        return false;
    }

    m_mainWin = std::make_unique<Window>();
    if(m_mainWin == nullptr || m_mainWin->GetHandle() == nullptr)
    {
        D_ERR("Failed to initialize GLFW window !");
        return false;
    }

    glfwMakeContextCurrent(m_mainWin->GetHandle());
    m_gfx = std::make_unique<Gfx>();
    if(!m_gfx->Init())
    {
        D_ERR("Failed to initialize gfx !");
        return false;
    }

    m_runtimeShaders = std::make_unique<RuntimeShaders>();
    m_runtimeShaders->Init();
    m_renderer = std::make_unique<CommonRenderer>(m_runtimeShaders.get());
    m_time = std::make_unique<GameTime>();
    m_imgui = std::make_unique<IMGuiInterface>();
    m_imgui->Init(m_mainWin.get());

    m_ecs = std::make_unique<ECSSys>();
    m_ecs->Init(128);
    RegisterStdComponents();


    return true;
}

bool EngineCore::Initialize(const EngineCoreSettings &settings)
{
    assert (m_gfx == nullptr);
    assert (m_glfw == nullptr);

    m_glfw = std::make_unique<GLFWInterface>();

    if(!m_glfw->Initialize())
    {
        return false;
    }

    m_mainWin = std::make_unique<Window>(settings.m_windowWidth, settings.m_windowHeight);
    if(m_mainWin == nullptr || m_mainWin->GetHandle() == nullptr)
    {
        D_ERR("Failed to initialize GLFW window !");
        return false;
    }

    glfwMakeContextCurrent(m_mainWin->GetHandle());
    m_gfx = std::make_unique<Gfx>();
    if(!m_gfx->Init())
    {
        D_ERR("Failed to initialize gfx !");
        return false;
    }

    InputManager::Instance().Initialize(*m_mainWin);
    m_runtimeShaders = std::make_unique<RuntimeShaders>();
    m_runtimeShaders->Init();
    m_renderer = std::make_unique<CommonRenderer>(m_runtimeShaders.get());
    m_time = std::make_unique<GameTime>();
    m_imgui = std::make_unique<IMGuiInterface>();
    m_imgui->Init(m_mainWin.get());
    

    m_ecs = std::make_unique<ECSSys>();
    m_ecs->Init(128);
    RegisterStdComponents();

    return true;
}

void EngineCore::Terminate()
{
    assert (m_glfw != nullptr);
    assert (m_glfw->Initialized());
    assert (m_ecs != nullptr);

    m_ecs->Terminate();

    m_imgui->Free();
    m_imgui.reset(nullptr);

    m_glfw->Terminate();
    m_glfw.release();
    m_glfw = nullptr;
}

void EngineCore::RedrawMainWindow()
{
    assert (m_glfw != nullptr);
    assert (m_glfw->Initialized());
    assert (m_mainWin != nullptr);
    assert (m_mainWin->Ready());
    assert (m_renderer != nullptr);

    glfwPollEvents();
    m_renderer->DrawRenderables();
}

void EngineCore::ClearMainWindow()
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void EngineCore::PresentMainWindow()
{
    assert (m_glfw != nullptr);
    assert (m_glfw->Initialized());
    assert (m_mainWin != nullptr);
    assert (m_mainWin->Ready());
    assert (m_renderer != nullptr);

    glfwSwapBuffers(m_mainWin->GetHandle());
}

const bool EngineCore::MainWindowActive() const
{
    assert (m_glfw != nullptr);
    assert (m_glfw->Initialized());
    assert (m_mainWin != nullptr);

    return m_mainWin->Ready();
}

CommonRenderer* EngineCore::Renderer()
{
    return m_renderer.get();
}

RuntimeShaders* EngineCore::Shaders() const
{
    return m_runtimeShaders.get();
}

ECSSys* EngineCore::ECS() const
{
    return m_ecs.get();
}

void EngineCore::RegisterStdComponents()
{
    EntitySerialiser::RegisterComponentSerialiser<Components::ModelComponentSerialiser>();
    EntitySerialiser::RegisterComponentSerialiser<Components::WobbleComponentSerialiser>();
}

void EngineCore::IncrementTime()
{
    assert (m_time != nullptr);
    m_time->Tick();
}

double EngineCore::GetDeltaTime() const
{
    assert (m_time != nullptr);
    return m_time->DeltaTime();
}

double EngineCore::GetGameTime() const
{
    assert (m_time != nullptr);
    return m_time->CurrentTime();
}

IMGuiInterface * EngineCore::IMGui() const
{
    return m_imgui.get();
}