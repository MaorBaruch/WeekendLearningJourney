#pragma once
#include <windows.h>

enum class message_identifiers {
    key_down = WM_KEYDOWN,
    key_up = WM_KEYUP,

};
class MessageQueue {
static constexpr HWND ALL_WINDOWS = nullptr;
static constexpr int NO_FILTER = 0;

public:
    static void do_loop();
};