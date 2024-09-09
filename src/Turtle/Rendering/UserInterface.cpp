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

    return true;
}

void Turtle::UserInterface::CreateFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImVec2 HorCenterVerBottomPos = ImGui::GetMainViewport()->GetCenter();
    HorCenterVerBottomPos.y = ImGui::GetMainViewport()->Size.y;

    ImVec2 ConsoleWindowSize = ImGui::GetMainViewport()->Size;
    ConsoleWindowSize.y /= 4;

    if (Turtle::Logger::loggedLineBufferCurrCount > 0)
    {
        ImGuiWindowFlags flags = 0;
        ImGui::SetNextWindowBgAlpha(0.8f);
        ImGui::SetNextWindowPos(HorCenterVerBottomPos, ImGuiCond_Always, ImVec2(0.5f, 1.0f));
        ImGui::SetNextWindowSize(ConsoleWindowSize, ImGuiCond_Always);
        ImGui::Begin("Console", nullptr, flags);


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