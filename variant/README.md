```cpp
#include "variant.h"
#include "wmi.h"

int main() {
    win32::variant vt;
    VARIANT* pVariant = vt.getVariant();

    win32::wmi wmi;
    wmi.newQuery(
        L"ROOT\\CIMV2",
        L"SELECT * FROM Win32_ComputerSystem",
        L"UserName",
        pVariant
    );

    BSTR property = (*pVariant).bstrVal;
}
```
