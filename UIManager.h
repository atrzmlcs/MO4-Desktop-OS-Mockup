#pragma once
#include <unordered_map>
#include <string>
#include "AWindow.h"

class UIManager {
private:
    std::unordered_map<std::string, AWindow*> windows;

    UIManager() = default;
    ~UIManager() = default;

    // Prevent copying in Singleton pattern
    UIManager(const UIManager&) = delete;
    UIManager& operator=(const UIManager&) = delete;

public:
    static UIManager& getInstance() {
        static UIManager instance;
        return instance;
    }

    void registerWindow(const std::string& name, AWindow* window) {
        windows[name] = window;
    }

    AWindow* getWindow(const std::string& name) {
        auto it = windows.find(name);
        if (it != windows.end()) {
            return it->second;
        }
        return nullptr;
    }

    void showWindow(const std::string& name) {
        auto it = windows.find(name);
        if (it != windows.end() && it->second != nullptr) {
            it->second->show();
        }
    }

    void hideWindow(const std::string& name) {
        auto it = windows.find(name);
        if (it != windows.end() && it->second != nullptr) {
            it->second->hide();
        }
    }

    void renderAllWindows() {
        for (auto& pair : windows) {
            if (pair.second != nullptr) {
                pair.second->draw();
            }
        }
    }
};

// Include application headers AFTER UIManager class definition
// so that Taskbar.h and BIOSBootWindow.h can safely call UIManager::getInstance()
#include "Desktop.h"
#include "Taskbar.h"
#include "TaskManagerUI.h"
#include "FileExplorer.h"
#include "Settings.h"