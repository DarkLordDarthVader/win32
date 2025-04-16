#pragma once

#include <combaseapi.h>
#include <wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")

namespace win32 {
    class wmi {
    public:
        wmi() {
            HRESULT hr = CoInitializeEx(
                NULL, 
                COINIT_MULTITHREADED
            );
            hr = CoInitializeSecurity(
                NULL, 
                -1, 
                NULL, 
                NULL, 
                RPC_C_AUTHN_LEVEL_DEFAULT, 
                RPC_C_IMP_LEVEL_IMPERSONATE, 
                NULL, 
                EOAC_NONE, 
                NULL
            );
        };
        ~wmi() {
            CoUninitialize();
        };
        void newQuery(LPCWSTR strNamespace, LPCWSTR strWQL, LPCWSTR strProperty, VARIANT* pVariant) {
            IWbemLocator* pIWbemLocator                 { nullptr };
            IWbemServices* pIWbemServices               { nullptr };
            IEnumWbemClassObject* pIEnumWbemClassObject { nullptr };
            IWbemClassObject* pIWbemClassObject         { nullptr };

            HRESULT hr = CoCreateInstance(
                CLSID_WbemLocator, 
                NULL, 
                CLSCTX_INPROC_SERVER, 
                IID_IWbemLocator, 
                (LPVOID*)&pIWbemLocator
            );
            hr = pIWbemLocator->ConnectServer(
                (BSTR)strNamespace, 
                NULL, 
                NULL, 
                NULL, 
                0, 
                NULL, 
                NULL, 
                &pIWbemServices
            );
            hr = CoSetProxyBlanket(
                (IUnknown*)pIWbemServices, 
                RPC_C_AUTHN_WINNT, 
                RPC_C_AUTHZ_NONE, 
                NULL, 
                RPC_C_AUTHN_LEVEL_CALL, 
                RPC_C_IMP_LEVEL_IMPERSONATE, 
                NULL, 
                EOAC_NONE
            );
            hr = pIWbemServices->ExecQuery(
                (BSTR)L"WQL", 
                (BSTR)strWQL, 
                WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 
                NULL, 
                &pIEnumWbemClassObject
            );
            unsigned long uReturned;
            hr = pIEnumWbemClassObject->Next(
                WBEM_INFINITE, 
                1, 
                &pIWbemClassObject, 
                &uReturned
            );
            hr = pIWbemClassObject->Get(
                strProperty, 
                0, 
                pVariant, 
                0, 
                0
            );

            pIWbemClassObject->Release();
            pIEnumWbemClassObject->Release();
            pIWbemServices->Release();
            pIWbemLocator->Release();
        }
    };
}