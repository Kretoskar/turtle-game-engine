#include "Turtle/Rendering/UserInterface.h"
#include "Turtle/Core/Logger.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

bool Turtle::UserInterface::Init(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glslVersion = "#version 440 core";
    ImGui_ImplOpenGL3_Init(glslVersion);

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 5.3f;
    style.FrameRounding = 2.3f;
    style.ScrollbarRounding = 0;

    style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 0.90f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);
    // style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.85f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.01f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.87f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.55f, 0.53f, 0.55f, 0.51f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.91f);
    //  style.Colors[ImGuiCol_ComboBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.99f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.70f, 0.70f, 0.70f, 0.62f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.30f, 0.30f, 0.30f, 0.84f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.48f, 0.72f, 0.89f, 0.49f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.50f, 0.69f, 0.99f, 0.68f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.30f, 0.69f, 1.00f, 0.53f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.44f, 0.61f, 0.86f, 1.00f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.38f, 0.62f, 0.83f, 1.00f);
    //  style.Colors[ImGuiCol_Column] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    //  style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.70f, 0.60f, 0.60f, 1.00f);
    //  style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.90f, 0.70f, 0.70f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
    //   style.Colors[ImGuiCol_CloseButton] = ImVec4(0.50f, 0.50f, 0.90f, 0.50f);
    //   style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.70f, 0.70f, 0.90f, 0.60f);
    //   style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
    //style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

    ImGuiIO& io = ImGui::GetIO();

    char result[100];

    strcpy(result, RESOURCES_PATH);
    strcat(result, "Pixeled.ttf");

    io.Fonts->AddFontFromFileTTF(result, 32);

    return true;
}

void Turtle::UserInterface::CreateFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    CreateConsoleWidget();
    CreateSceneWidget();
    CreateDetailsWidget();
    CreateToolbarWidget();
}

void Turtle::UserInterface::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Turtle::UserInterface::Cleanup()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Turtle::UserInterface::UpdateEntityMap(std::map<Entity, TurtleString> entityMap)
{
    //std move?

    _entityMap = entityMap;
}

void Turtle::UserInterface::CreateConsoleWidget()
{
    ImVec2 HorCenterVerBottomPos = ImGui::GetMainViewport()->GetCenter();
    HorCenterVerBottomPos.y = ImGui::GetMainViewport()->Size.y;

    ImVec2 ConsoleWindowSize = ImGui::GetMainViewport()->Size;
    ConsoleWindowSize.y /= 4;

    ImGuiWindowFlags flags = 0;
    ImGui::SetNextWindowBgAlpha(0.9f);
    ImGui::SetNextWindowPos(HorCenterVerBottomPos, ImGuiCond_Always, ImVec2(0.5f, 1.0f));
    ImGui::SetNextWindowSize(ConsoleWindowSize, ImGuiCond_Always);
    ImGui::Begin("CONSOLE", nullptr, flags);

    for (unsigned int i = 0; i < Turtle::Logger::loggedLineBufferCurrCount; i++)
    {
        switch (Turtle::Logger::logLinesVerbosity[i]) {
        case Turtle::Error:
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
            break;
        case Turtle::Warning:
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));
            break;
        case Turtle::Message:
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
            break;
        }

        ImGui::Text(Turtle::Logger::logLines[i].c_str());

        ImGui::PopStyleColor();
    }

    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
    {
        ImGui::SetScrollHereY(0.0f);
    }

    ImGui::End();
}

void Turtle::UserInterface::CreateSceneWidget()
{
    ImVec2 SceneWindowSize = ImGui::GetMainViewport()->Size;
    SceneWindowSize.x /= 5;
    SceneWindowSize.y = (SceneWindowSize.y / 4) * 3;

    ImGuiWindowFlags flags = 0;
    
    ImGui::SetNextWindowBgAlpha(0.8f);
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(SceneWindowSize, ImGuiCond_Always);
    ImGui::Begin("SCENE", nullptr, flags);

    for (auto& entity : _entityMap)
    {
        ImGui::Button(entity.second.Get());
    }
   

    ImGui::End();
}

void Turtle::UserInterface::CreateDetailsWidget()
{
    ImVec2 DetailsWindowSize = ImGui::GetMainViewport()->Size;
    DetailsWindowSize.x /= 5;
    DetailsWindowSize.y = (DetailsWindowSize.y / 4) * 3;

    ImGuiWindowFlags flags = 0;

    ImGui::SetNextWindowBgAlpha(0.8f);
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetMainViewport()->Size.x, 0.0f), ImGuiCond_Always, ImVec2(1.0f, 0.0f));
    ImGui::SetNextWindowSize(DetailsWindowSize, ImGuiCond_Always);
    ImGui::Begin("DETAILS", nullptr, flags);

    ImGui::End();
}

void Turtle::UserInterface::CreateToolbarWidget()
{
    ImVec2 TopWindowSize = ImGui::GetMainViewport()->Size;
    TopWindowSize.x /= 5;
    TopWindowSize.x *= 3;
    TopWindowSize.y = (TopWindowSize.y / 12);

    ImGuiWindowFlags flags = 0;

    ImGui::SetNextWindowBgAlpha(0.8f);
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetMainViewport()->Size.x / 2, 0.0f), ImGuiCond_Always, ImVec2(0.5f, 0.0f));
    ImGui::SetNextWindowSize(TopWindowSize, ImGuiCond_Always);
    ImGui::Begin("TOOLBAR", nullptr, flags);
    ImGui::Button("SAVE", ImVec2(ImGui::GetMainViewport()->Size.x / 16, ImGui::GetMainViewport()->Size.y / 32));
    ImGui::SameLine();
    ImGui::Button("LOAD", ImVec2(ImGui::GetMainViewport()->Size.x / 16, ImGui::GetMainViewport()->Size.y / 32));
    ImGui::End();
}
