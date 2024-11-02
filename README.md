# wos-gaming-samples
Samples to help with Qualcomm Adreno GPU detection and Windows on Snapdragon detection. Platforms `ARM64` and `ARM64EC` can be built after installing build tools in **Setup** section.

## Prerequisites
* Visual Studio 2022 with:
   * Workloads: `Desktop development with C++` and `Game development with C++`
   * Individual Components: `MSVC v143 - VS 2022 C++ ARM64/ARM64EC build tools (Latest)` and `Windows SDK (build 10.0.22621.0) or newer`
* Cmake 3.31 or newer recommended (Cmake 3.20+ works but has conflicting preprocessor defines in ARM64EC build)

## Display Adapter Detect
DXGI sample showcasing how to detect the Qualcomm Adreno GPU. Once the adapter is found, the D3D11 or D3D12 device can be created using the adapter.

### Building
Run `build.bat` to generate solution files. Open `DisplayAdapterDetect.sln` and compile in each build directory.

## Windows on Snapdragon Detect
Sample showcasing dedection if the system is Windows on Snapdragon and if the x86/x64 application is running in emulation.

### Building
Run `build.bat` to generate solution files. Open `WindowsOnSnapdragonDetect.sln` and compile in each build directory.

## License
[Please see License](LICENSE.txt)
