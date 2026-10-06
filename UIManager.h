#pragma once
#include <map>
#include <memory>
#include <string>
#include "AWindow.h"

class UIManager {
public:
    static UIManager& getInstance() {
        static UIManager instance;
        return instance;
    }

    void registerWindow(const std::string& name, std::shared_ptr<AWindow> window) {
        windows[name] = window;
    }

    void showWindow(const std::string& name) {
        if (windows.find(name) != windows.end()) {
            windows[name]->show();
        }
    }

    void hideWindow(const std::string& name) {
        if (windows.find(name) != windows.end()) {
            windows[name]->hide();
        }
    }

    void renderAllWindows() {
        for (auto& [name, window] : windows) {
            if (window->isShown()) {
                window->draw();
            }
        }
    }

private:
    UIManager() = default;
    ~UIManager() = default;
    UIManager(const UIManager&) = delete;
    UIManager& operator=(const UIManager&) = delete;

    std::map<std::string, std::shared_ptr<AWindow>> windows;
};