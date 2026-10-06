#pragma once
#include "AWindow.h"
#include "UIConfig.h"
#include "UIManager.h"

class Desktop : public AWindow {
public:
    Desktop() : AWindow("Desktop") {}

    void draw() override {
        if (!isVisible) return;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        float taskbarHeight = 50.0f * UIConfig::getScaleFactor();

        // Canvas occupies all space above the taskbar
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y - taskbarHeight));

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                                 ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoSavedSettings;

        if (ImGui::Begin(windowName.c_str(), nullptr, flags)) {
            ImGui::Text("CSOPESY OS Workstation");
            ImGui::Separator();
            ImGui::Spacing();

            // Desktop Shortcut
            if (ImGui::Button("Launch Task Manager\n[Process Monitor]", UIConfig::scale(ImVec2(180, 60)))) {
                UIManager::getInstance().showWindow("TaskManager");
            }
        }
        endWindow();
    }
};