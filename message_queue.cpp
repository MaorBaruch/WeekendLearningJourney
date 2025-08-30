#include "message_queue.h"
#include <iostream>

void MessageQueue::do_loop() {
    MSG msg;
    while (GetMessageA(&msg, ALL_WINDOWS, NO_FILTER, NO_FILTER)) {
        std::cout << msg.message << "\n";
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}
