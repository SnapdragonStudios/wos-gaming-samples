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
#include <Windows.h>

// Target processor architecture for build
enum class BuildArchitecture { X86, X64, ARM64, ARM64EC, Unknown };

// Get build architecture
constexpr BuildArchitecture gBuildArchitecture =
// Microsoft-specific predefined macros
#if defined(_M_IX86)
BuildArchitecture::X86
#elif defined(_M_ARM64)
BuildArchitecture::ARM64
#elif defined(_M_X64) && defined(_M_AMD64) && defined(_M_ARM64EC)
BuildArchitecture::ARM64EC
#elif defined(_M_X64) && defined(_M_AMD64) && !defined(_M_ARM64EC)
BuildArchitecture::X64
#else
BuildArchitecture::Unknown
#endif
;

int main() {
    // Check for valid build architecture
    if constexpr (gBuildArchitecture == BuildArchitecture::Unknown) {
        std::cout << "Could not determine build architecture\n";
        return 0;
    }

    // Get native architecture of the system
    USHORT process, nativeMachineArchitecture;
    const BOOL bSuccess = IsWow64Process2(GetCurrentProcess(), &process, &nativeMachineArchitecture);
    if (bSuccess == FALSE) {
        std::cout << std::format("Error: IsWow64Process2() failed, GetLastError() {:x}\n", GetLastError());
        return 0;
    }

    // Determine if Windows on Snapdragon
    const bool bWindowsOnSnapdragon = nativeMachineArchitecture == IMAGE_FILE_MACHINE_ARM64;

    // Determine if x86/x64 application is running in emulation
    const bool bEmulation = bWindowsOnSnapdragon && (
        gBuildArchitecture == BuildArchitecture::X64 ||
        gBuildArchitecture == BuildArchitecture::X86 ||
        gBuildArchitecture == BuildArchitecture::ARM64EC);

    std::cout << std::format("Windows on Snapdragon: {}\nEmulation: {}\n", bWindowsOnSnapdragon, bEmulation);

    return 0;
}
