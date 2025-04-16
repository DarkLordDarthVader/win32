```cpp
#include "wmi.h"

int main() {
    VARIANT vt;
    VariantInit(&vt);

    win32::wmi wmi;
    wmi.newQuery(
        L"ROOT\\CIMV2", 
        L"SELECT * FROM Win32_ComputerSystem", 
        L"UserName", 
        &vt
    );

    BSTR property = vt.bstrVal;
    VariantClear(&vt);
}
```
