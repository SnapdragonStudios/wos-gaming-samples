//============================================================================================================
//
//
//                  Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
//                                 SPDX-License-Identifier: BSD-3-Clause-Clear
//
//
//============================================================================================================

#include <format>
#include <iostream>
#include <cassert>

// winrt::com_ptr
#include <winrt/base.h>

// DXGI
#include <dxgi1_6.h>
#pragma comment(lib, "DXGI.lib")

// Qualcomm Vendor Id
constexpr UINT QCOMVendorId = 'Q' | ('C' << 8) | ('O' << 16) | ('M' << 24);

int main()
{
    // Create DXGI factory to enumerate adapters
    winrt::com_ptr<IDXGIFactory7> factory;
    constexpr UINT dxgiFactoryFlags = 0;
    HRESULT result = CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory));
    assert(SUCCEEDED(result));

    // For each adapter, check if Qualcomm vendor id
    winrt::com_ptr<IDXGIAdapter1> adapter;
    BOOL bQCOMAdapterFound = FALSE;
    for (UINT adapterIndex = 0;
        DXGI_ERROR_NOT_FOUND != factory->EnumAdapters1(adapterIndex, adapter.put());
        ++adapterIndex)
    {
        // Get adapter description to check Vendor ID
        DXGI_ADAPTER_DESC1 adapterDesc{};
        adapter->GetDesc1(&adapterDesc);

        // Disregard Basic Render Driver adapter
        if (adapterDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
        {
            continue;
        }

        // Use first Qualcomm adapter
        if (adapterDesc.VendorId == QCOMVendorId)
        {
            bQCOMAdapterFound = TRUE;

            std::wcout << std::format(
                L"Qualcomm Adreno GPU found:\n"
                L"\tDescription         = {}\n"
                "\tVendor ID           = {:X}\n"
                "\tDedicated Video Mem = {} bytes\n"
                "\tDedicated Sys Mem   = {} bytes\n"
                "\tShared Sys Mem      = {} bytes\n",
                adapterDesc.Description,
                adapterDesc.VendorId,
                adapterDesc.DedicatedVideoMemory,
                adapterDesc.DedicatedSystemMemory,
                adapterDesc.SharedSystemMemory);

            break;
        }
    }

    // If Qualcomm GPU adapter available create the device
    if (bQCOMAdapterFound)
    {
        // Create the device using the found Qualcomm Adreno GPU adapter
        // using D3D12CreateDevice or D3D11CreateDevice
    }
    else
    {
        std::wcout << "No Qualcomm GPU found\n";
    }

    return 0;
}
