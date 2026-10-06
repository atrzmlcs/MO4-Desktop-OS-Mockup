#pragma once
#include "AWindow.h"
#include "UIConfig.h"
#include "UIManager.h"

class BIOSBootWindow : public AWindow {
public:
    BIOSBootWindow() : AWindow("BIOSBootWindow"), bootProgress(0.0f), bootComplete(false) {
        show(); // Active by default on application launch
    }

    void draw() override {
        if (!isVisible) return;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                                 ImGuiWindowFlags_NoSavedSettings;

        if (ImGui::Begin(windowName.c_str(), &isVisible, flags)) {
            ImGui::SetWindowFontScale(1.2f * UIConfig::getScaleFactor());
            
            ImGui::Text("CSOPESY BIOS v1.0.0");
            ImGui::Text("Checking System Memory... OK");
            ImGui::Text("Mounting Virtual File System... OK");
            ImGui::Separator();
            ImGui::Spacing();

            if (bootProgress < 1.0f) {
                bootProgress += 0.005f; // Simulates OS startup sequence delay
            } else if (!bootComplete) {
                bootComplete = true;
                hide();
                
                // Hand off to Desktop & Taskbar after boot completes
                UIManager::getInstance().showWindow("Desktop");
                UIManager::getInstance().showWindow("Taskbar");
            }

            ImGui::ProgressBar(bootProgress, ImVec2(-1.0f, 0.0f), "Loading OS Services...");
        }
        endWindow();
    }

private:
    float bootProgress;
    bool bootComplete;
};