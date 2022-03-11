// GetCatalogStatus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <atlbase.h>
#include <atlcom.h>
#include <searchapi.h>
using namespace std;


HRESULT GetSearchInterfaces(ISearchManager** ppManager, ISearchCatalogManager** ppCatalog)
{
    *ppManager = NULL;
    *ppCatalog = NULL;

    CComPtr<ISearchManager> spManager;
    HRESULT hr = CoCreateInstance(__uuidof(CSearchManager), NULL, CLSCTX_LOCAL_SERVER, IID_PPV_ARGS(&spManager));
    if (SUCCEEDED(hr))
    {
        CComPtr<ISearchCatalogManager> spCatalog;
        hr = spManager->GetCatalog(L"SystemIndex", &spCatalog);
        if (SUCCEEDED(hr))
        {
            *ppManager = spManager.Detach();
            *ppCatalog = spCatalog.Detach();
        }
    }
    return hr;
}

PCWSTR StatusString(CatalogStatus cs)
{
    switch (cs)
    {
    case CATALOG_STATUS_IDLE:
        return L"Idle";
    case CATALOG_STATUS_PAUSED:
        return L"Paused";
    case CATALOG_STATUS_RECOVERING:
        return L"Recovering";
    case CATALOG_STATUS_FULL_CRAWL:
        return L"FullCrawl";
    case CATALOG_STATUS_INCREMENTAL_CRAWL:
        return L"IncrementalCrawl";
    case CATALOG_STATUS_PROCESSING_NOTIFICATIONS:
        return L"ProcessingNotifications";
    case CATALOG_STATUS_SHUTTING_DOWN:
        return L"ShuttingDown";
    }
    return L"???";
}

PCWSTR ReasonString(CatalogPausedReason cr)
{
    switch (cr)
    {
    case CATALOG_PAUSED_REASON_NONE:
        return L"None";
    case CATALOG_PAUSED_REASON_HIGH_IO:
        return L"HighIO";
    case CATALOG_PAUSED_REASON_HIGH_CPU:
        return L"HighCPU";
    case CATALOG_PAUSED_REASON_HIGH_NTF_RATE:
        return L"HighNTFRate";
    case CATALOG_PAUSED_REASON_LOW_BATTERY:
        return L"LowBattery";
    case CATALOG_PAUSED_REASON_LOW_MEMORY:
        return L"LowMemory";
    case CATALOG_PAUSED_REASON_LOW_DISK:
        return L"LowDisk";
    case CATALOG_PAUSED_REASON_DELAYED_RECOVERY:
        return L"RecoveryDelay";
    case CATALOG_PAUSED_REASON_USER_ACTIVE:
        return L"UserActivity";
    case CATALOG_PAUSED_REASON_EXTERNAL:
        return L"External";
    case CATALOG_PAUSED_REASON_UPGRADING:
        return L"Upgrade";
    }
    return L"???";
}


void GetCatalogStatus()
{
    CComPtr<ISearchManager> spManager;
    CComPtr<ISearchCatalogManager> spCatalog;

    HRESULT hr = GetSearchInterfaces(&spManager, &spCatalog);
    if (SUCCEEDED(hr))
    {

        DWORD dwIndexedCount = 0;
        DWORD dwAddCount = 0;
        DWORD dwModifyCount = 0;
        DWORD dwZeroSeconds = 0;

        while (1)
        {
            CatalogStatus status;
            CatalogPausedReason reason;

            spCatalog->GetCatalogStatus(&status, &reason);

            printf("Catalog State: %S  Reason: %S\n", StatusString(status), ReasonString(reason));
            Sleep(1000); // 1 sec
        }

    }
}

int main()
{
    std::cout << "Hello World!\n";
    HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        GetCatalogStatus();
        CoUninitialize();
    }
    return 0;
}

