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
#include <winrt/base.h>

// Requires linker dependency "DXGI.lib"
#include <dxgi1_6.h>

constexpr UINT QCOM_VENDOR_ID = ('Q' | ('C' << 8) | ('O' << 16) | ('M' << 24));

int main() {
    // Create DXGI factory to enumerate adapters
    winrt::com_ptr<IDXGIFactory7> factory;
    constexpr UINT dxgiFactoryFlags = 0;
    const HRESULT result = CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory));
    if (FAILED(result)) {
        std::wcout << std::format(L"CreateDXGIFactory2 failed {:X}\n", result);
        return 0;
    }

    // Find the required adapter by vendor id
    winrt::com_ptr<IDXGIAdapter1> vendorAdapter;
    for (UINT adapterIndex = 0;
        DXGI_ERROR_NOT_FOUND != factory->EnumAdapters1(adapterIndex, vendorAdapter.put());
        ++adapterIndex) {
        // Get adapter description to check vendor id
        DXGI_ADAPTER_DESC1 adapterDesc{};
        vendorAdapter->GetDesc1(&adapterDesc);

        // Disregard Basic Render Driver adapter
        if (adapterDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
            continue;
        }

        // Use first found adapter matching vendor id
        if (adapterDesc.VendorId == QCOM_VENDOR_ID) {
            std::wcout << std::format(
                L"Qualcomm Adreno GPU adapter found:\n"
                L"  Description             = {}\n"
                L"  Vendor Id               = {:X}\n"
                L"  Dedicated Video Memory  = {} bytes\n"
                L"  Dedicated System Memory = {} bytes\n"
                L"  Shared System Memory    = {} bytes\n",
                adapterDesc.Description,
                adapterDesc.VendorId,
                adapterDesc.DedicatedVideoMemory,
                adapterDesc.DedicatedSystemMemory,
                adapterDesc.SharedSystemMemory);
            break;
        }
        // Release if not matching vendor id
        else {
            vendorAdapter = nullptr;
        }
    }

    // If required vendor adapter not found, return
    if (vendorAdapter == nullptr) {
        std::wcout << "Qualcomm Adreno GPU adapter not found\n";
        return 0;
    }

    // Create the device using adapter
    // with D3D12CreateDevice or D3D11CreateDevice

    return 0;
}
