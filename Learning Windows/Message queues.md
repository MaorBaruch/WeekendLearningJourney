The windows message queue is a way for the system and applications to notify windows procedures about certain things, for example about a keyboard stroke
![[Pasted image 20250823140440.png]]
Each message the system sends to a windows procedure has 4 parameters:
The window handle (HANDLE window_handle) - it identifies what window should get the message, the system uses it to know which message queue to send the message to.
message identifier - a named constant that identifies the purpose of the message, the window is using this identifier to determine how to handle the message.
there are many defined system message identifiers and they can be read here:
https://learn.microsoft.com/en-us/windows/win32/winmsg/about-messages-and-message-queues
values in the range 0x0400 (the value of [**WM_USER**](https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-user)) through 0x7FFF are available for message identifiers for private window classes.

there are also parameters, which are extra parameters that are sent with every message - these include WPARAM and LPARAM (WPARAM - unsigned 64bit, LPARAM -signed 64bit)

## Message Routing
### Message queue
There are two ways for the system to send messages to the various thread procedures, one is through a FIFO queue called a message queue, which is a system defined memory object that temporarily stores messages.
#### Queues type and creation
The system maintains a single system message queue and one queue for each GUI thread - in order to avoid the overhead of the queue creation for non GUI thread - the queue is created only when a call to a queue related function (for example GetMessageA)

#### The life of a message
whenever some event happens (for example, a mouse click) its driver will create a window message and post it to the system message queue.
The system removes the messages, one at a time, from the system message queue, examines them to determine the destination window, and then posts them to the message queue of the thread that created the destination window
The thread removes messages from its queue and directs the system to send them to the appropriate window procedure for processing

##### Internal view
The system posts a message to a thread's message queue by filing an MSG structure:
```cpp
typedef struct tagMSG { 
HWND hwnd; 
UINT message; 
WPARAM wParam; 
LPARAM lParam; 
DWORD time; 
POINT pt; 
DWORD lPrivate; 
} MSG, *PMSG, *NPMSG, *LPMSG;
```
The first 4 members of the MSG struct, are the same four values that are sent to the windows procedure as explained in the start of the page.
In the MSG struct there are extra members that are not sent to the window procedure which include these:
**time** - the time the message was posted
**pt** - the mouse cursor position when the message was posted
**lprivate** - not explained

When the thread wants the system to send the message to the window procedure it uses the function DispatchMessage:
``` cpp
LRESULT DispatchMessage( [in] const MSG *lpMsg );
```

#### Using the queue
In the GUI thread the usual implementation of the message queue looks like this:
``` cpp
MSG msg; 
BOOL bRet;
while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
{ 
	if (bRet == -1)
	{ 
	// handle the error and possibly exit 
	}
	else
	{
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	} 
	}
```
``` cpp
MSG msg; 
BOOL bRet;
while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
{ 
	if (bRet == -1)
	{ 
	// handle the error and possibly exit 
	}
	else
	{
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	} 
}
```
for more information about these functions read [[Message queues#Functions called by the thread]]

#### Special messages identifiers
There are special message types, which include WM_PAINT, WM_TIMER and WM_QUIT.
these message types are kept in the queue and forwarded to the window procedure only when the queue contains no other messages
###### WM_PAINT message combination
all WM_PAINT messages for the same window are always combined into one WM_PAINT message that includes all the area that needs to be painted.
This reduces the amount of times a window must be redraw the contents of its client area


### Nonqueued Messages
Nonqueued messages are messages that are sent directly to the window procedure, without going through the system or the thread message queue.
In the microsoft docs, it is not 100% defined which events cause nonqueued messages to be sent, it is only said that the system typically sends nonqueued messages to notify a window of events that affect it

## Related functions


### Called in Window Procedure
#### GetMessageTime
```
LONG GetMessageTime();
```
returns the message time (same one explained in the message queue's internal view ) of the last message that was returned by GetMessage

#### GetMessagePos
```
LONG GetMessagePos();
```
returns the message's mouse pos (same one explained in the message queue's internal view ) of the last message that was returned by GetMessage

### Functions called by the thread

#### WaitMessage
```cpp
BOOL WaitMessage();
```
suspends the thread until a message is received in the thread's message queue

#### GetMessage
``` c
BOOL GetMessage( 
	[out] LPMSG lpMsg,
	[in, optional] HWND hWnd,
	[in] UINT wMsgFilterMin, 
	[in] UINT wMsgFilterMax 
	);
```
The function retrieves  a message from the top of the thread's message queue*.
#### GetMessage Filters
It can also get filters, which limit the minimum and maximum message value (message identifier of the message) that can be received by the function.
The function will automatically dispatch all messages in the message queue until it finds a message that matches the filter, then it will retrieve it.


#### GetMessage Parameters
`lpMsg` - the message that the function retrieves

`hWnd` - A handle to the window whose messages are to be retrieved. The window must belong to the current thread.
If `hWnd` is **NULL**, **GetMessage** retrieves messages for any window that belongs to the current thread, and any messages on the current thread's message queue whose `hwnd` value is **NULL**

`wMsgFilterMin` - The integer value of the lowest message value to be retrieved
`wMsgFilterMax` - the integer value of the highest message to be retrieved
if both values are 0, no filter is applied and all messages are retrieved.
for more information about filters: [[Message queues#GetMessage Filters]]

#### TranslateMessage
```cpp
BOOL TranslateMessage( [in] const MSG *lpMsg );
```
This function purpose is to get a message that contains virtual key codes[^1] (for example WM_KEYDOWN) and translate this message to a message that contains the character it generated.
The function does not change the message itself, but adds a new message to the end of the queue with a type that depends on the type of the message that was translated:
WM_KEYDOWN -> WM_CHAR
WM_KEYUP -> WM_DEADCHAR
WM_SYSKEYDOWN -> WM_SYSCHAR
WM_SYSKEYUP -> WM_SYSDEADCHAR
more information about those messages: [Keyboard Input Notifications](https://learn.microsoft.com/en-us/windows/win32/inputdev/keyboard-input-notifications)


[^1]: codes in windows that represent a key/button in the mouse/keyboard the full list can be found here: [Virtual Key Codes](https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes) 

#### DispatchMessage
``` cpp
LRESULT DispatchMessage( [in] const MSG *lpMsg );
```
This function dispatches a message to the corresponding window procedure.
The message that is passed to the window procedure does not include the message posting time or the cursor position.

**The dispatch does not not happen directly from the thread, it is a system call that asks the system to dispatch the message to the procedure, there is no direct interaction between the thread and the window procedure here