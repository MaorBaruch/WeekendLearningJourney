#include <cstdint>
#include <iostream>
#include <memory>
#include <windows.h>

#include "message_queue.h"
enum class KeyState: uint64_t
{
    key_down = WM_KEYDOWN,
    key_up = WM_KEYUP
};

LRESULT CALLBACK keyboardHookHandler(int nCode, WPARAM wparam, LPARAM lparam)
{
    if (nCode == HC_ACTION)
    {
        if (static_cast<KeyState>(wparam) == KeyState::key_down)
        {
            auto kbd_struct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lparam);

            std::cout << static_cast<char>(kbd_struct->vkCode) << std::endl;
        }

    }
    return CallNextHookEx(nullptr, nCode, wparam, lparam);
}
int main() {
    SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHookHandler, nullptr, 0);
    MessageQueue::do_loop();
}
