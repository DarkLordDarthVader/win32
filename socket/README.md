```cpp
#include "socket.h"

int main() {
    win32::socket sock(
        L"127.0.0.1",
        L"5555"
    );
    sock.open();
    sock.connect();
    sock.send(
        "hello world!", 
        13
    );
    char buf[10];
    sock.recv(
        buf, 
        10
    );
    sock.close();
}
```
