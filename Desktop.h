#pragma once
#include "AWindow.h"
#include "imgui.h"

class Desktop : public AWindow {
public:
    Desktop() : AWindow("Desktop") {}

    void draw() override {
        if (!isVisible) return;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
                                 ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus;

        // Remove window padding to make the gradient flush with the screen edges
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        if (ImGui::Begin("DesktopBG", nullptr, flags)) {
            // Draw a smooth corner-to-corner color gradient
            ImDrawList* drawList = ImGui::GetWindowDrawList();
            ImVec2 p_min = ImGui::GetCursorScreenPos();
            ImVec2 p_max = ImVec2(p_min.x + viewport->Size.x, p_min.y + viewport->Size.y);
            
            ImU32 col_top_left  = ImGui::GetColorU32(ImVec4(0.05f, 0.15f, 0.35f, 1.0f)); // Deep Blue
            ImU32 col_top_right = ImGui::GetColorU32(ImVec4(0.10f, 0.30f, 0.50f, 1.0f)); // Mid Blue
            ImU32 col_bot_right = ImGui::GetColorU32(ImVec4(0.02f, 0.10f, 0.20f, 1.0f)); // Dark Blue
            ImU32 col_bot_left  = ImGui::GetColorU32(ImVec4(0.01f, 0.05f, 0.15f, 1.0f)); // Very Dark

            drawList->AddRectFilledMultiColor(p_min, p_max, col_top_left, col_top_right, col_bot_right, col_bot_left);

            // Desktop text overlay
            ImGui::SetCursorPos(ImVec2(20, 20));
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 0.5f), "CSOPESY OS v1.0");
        }
        ImGui::End();
        ImGui::PopStyleVar(); // Restore padding
    }
};