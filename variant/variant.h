#pragma once

#include <combaseapi.h>

namespace win32 {
    class variant {
    public:
        variant() {
            VariantInit(&this->vt);
        };
        ~variant() {
            VariantClear(&this->vt);
        };
        VARIANT* getVariant() {
            return &this->vt;
        }
    private:
        VARIANT vt;
    };
}