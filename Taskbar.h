#pragma once
#include <ctime>
#include <iomanip>
#include <sstream>
#include <GLFW/glfw3.h>
#include "AWindow.h"
#include "UIConfig.h"
#include "UIManager.h"

class Taskbar : public AWindow {
public:
    Taskbar() : AWindow("Taskbar") {}

    void draw() override {
        if (!isVisible) return;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        float taskbarHeight = 50.0f * UIConfig::getScaleFactor();

        ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + viewport->Size.y - taskbarHeight));
        ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, taskbarHeight));

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
                                 ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus;

        if (ImGui::Begin(windowName.c_str(), nullptr, flags)) {
            // Button 1: Placeholder App 1 (e.g. File Explorer)
            if (ImGui::Button("Files", UIConfig::scale(ImVec2(70, 30)))) {
                UIManager::getInstance().showWindow("FileExplorer");
            }
            ImGui::SameLine();

            // Button 2: Placeholder App 2 (e.g. System Settings)
            if (ImGui::Button("Settings", UIConfig::scale(ImVec2(80, 30)))) {
                UIManager::getInstance().showWindow("Settings");
            }
            ImGui::SameLine();

            // Button 3: Task Manager
            if (ImGui::Button("Task Manager", UIConfig::scale(ImVec2(120, 30)))) {
                UIManager::getInstance().showWindow("TaskManager");
            }
            ImGui::SameLine();

            // Dedicated PWR Button for Shutdown
            if (ImGui::Button("PWR", UIConfig::scale(ImVec2(50, 30)))) {
                GLFWwindow* window = glfwGetCurrentContext();
                if (window) glfwSetWindowShouldClose(window, GLFW_TRUE);
            }

            // Real-Time Clock
            std::string timeStr = getCurrentTimeString();
            float textWidth = ImGui::CalcTextSize(timeStr.c_str()).x;
            ImGui::SameLine(ImGui::GetWindowWidth() - textWidth - (20.0f * UIConfig::getScaleFactor()));
            ImGui::Text("%s", timeStr.c_str());
        }
        endWindow();
    }

private:
    std::string getCurrentTimeString() {
        std::time_t now = std::time(nullptr);
        std::tm localTime;
#if defined(_WIN32)
        localtime_s(&localTime, &now);
#else
        localtime_r(&now, &localTime);
#endif
        std::ostringstream oss;
        oss << std::put_time(&localTime, "%I:%M:%S %p");
        return oss.str();
    }
};