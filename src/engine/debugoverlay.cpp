#include "debugoverlay.hpp"
#include "imguiinterface.hpp"
#include "inputmanager.hpp"

using namespace Engine;


DebugOverlay::DebugOverlay(EngineCore * const engine):
m_core(engine)
{

}

void DebugOverlay::OnInit()
{
    // Make sure local render setting first defaut to engine default settings
    m_renderSettings = RenderSettings(m_core->Renderer()->GetRenderSettings());
}

void DebugOverlay::OnUpdate()
{
    // Issue panel drawing commands
    DrawPerfStats();
    DrawCameraInfo();
    DrawInputInfo();
    DrawRenderSettings();
}

void DebugOverlay::DrawPerfStats() const
{
    std::string fps = "";
    std::string frameTime = "";

    assert (m_core != nullptr);
    fps = std::to_string(m_core->FPS()->Get());
    frameTime = std::to_string(m_core->FPS()->GetMilliseconds());

    ImGui::Begin("Perf Stats Panel");
    ImGui::AlignTextToFramePadding();
    ImGui::Text("FPS: ", nullptr); ImGui::SameLine();
    ImGui::Text(fps.c_str(), nullptr);

    ImGui::Text("Frame Time: ", nullptr); ImGui::SameLine();
    ImGui::Text(frameTime.c_str(), nullptr);
    ImGui::End();
}

void DebugOverlay::DrawCameraInfo() const
{
    std::string near = std::to_string(m_core->Renderer()->GetCamera()->GetNearClip());
    std::string far = std::to_string(m_core->Renderer()->GetCamera()->GetFarClip());
    std::string fov = std::to_string(m_core->Renderer()->GetCamera()->GetFOV());
    std::string aspect = std::to_string(m_core->Renderer()->GetCamera()->GetAspect());\

    ImGui::Begin("Active Camera Info");
    ImGui::AlignTextToFramePadding();

    ImGui::Text("Near Clip: ", nullptr); ImGui::SameLine();
    ImGui::Text(near.c_str(), nullptr);

    ImGui::Text("Far Clip: ", nullptr); ImGui::SameLine();
    ImGui::Text(far.c_str(), nullptr);

    ImGui::Text("FOV: ", nullptr); ImGui::SameLine();
    ImGui::Text(fov.c_str(), nullptr);

    ImGui::Text("Aspect: ", nullptr); ImGui::SameLine();
    ImGui::Text(aspect.c_str(), nullptr);

    ImGui::End();
}

void DebugOverlay::DrawInputInfo() const
{
    ImGui::Begin("Input Info");
    ImGui::AlignTextToFramePadding();

    const Vec2 mousePos = InputManager::Instance().GetMouseScreenPos();
    const Vec2 mousePosNCD = InputManager::Instance().GetMouseNDCPos();
    const Vec3 worldMousePos = m_core->Renderer()->NDCToWorld(mousePosNCD);

    ImGui::Text("Mouse X: ", nullptr); ImGui::SameLine();
    ImGui::Text(std::to_string(mousePos.x).c_str(), nullptr);

    ImGui::Text("Mouse Y: ", nullptr); ImGui::SameLine();
    ImGui::Text(std::to_string(mousePos.y).c_str(), nullptr);

    ImGui::Text("Mouse X (NCD): ", nullptr); ImGui::SameLine();
    ImGui::Text(std::to_string(mousePosNCD.x).c_str(), nullptr);

    ImGui::Text("Mouse Y (NCD): ", nullptr); ImGui::SameLine();
    ImGui::Text(std::to_string(mousePosNCD.y).c_str(), nullptr);

    ImGui::Text("World Mouse X: ", nullptr); ImGui::SameLine();
    ImGui::Text(std::to_string(worldMousePos.x).c_str(), nullptr);

    ImGui::Text("World Mouse Y: ", nullptr); ImGui::SameLine();
    ImGui::Text(std::to_string(worldMousePos.y).c_str(), nullptr);

    ImGui::Text("World Mouse Z: ", nullptr); ImGui::SameLine();
    ImGui::Text(std::to_string(worldMousePos.z).c_str(), nullptr);

    ImGui::End();
}

void DebugOverlay::DrawRenderSettings ()
{
    UpdateEngineRenderSettings();

    ImGui::Begin("Render Settings");
    ImGui::AlignTextToFramePadding();

    ImGui::Checkbox("Draw Wireframe", &m_renderSettings.m_wireframe);
    ImGui::Checkbox("Draw Shadows", &m_renderSettings.m_shadows);
    ImGui::End();
}

void DebugOverlay::UpdateEngineRenderSettings()
{
    RenderSettings settings(m_core->Renderer()->GetRenderSettings());
    settings.m_wireframe = m_renderSettings.m_wireframe;
    settings.m_shadows = m_renderSettings.m_shadows;

    m_core->Renderer()->SetRenderSettings(settings);
}