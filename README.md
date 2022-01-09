- [Graphitti v2](#graphitti-v2)
  - [An accelerated generalized graph simulator](#an-accelerated-generalized-graph-simulator)
- [v2 Main Features](#v2-main-features)
- [Why SYCL?](#why-sycl)
- [Build Guide](#build-guide)
  - [Dependencies](#dependencies)
    - [`vcpkg`](#vcpkg)
    - [`CMake`](#cmake)
    - [`Ninja`](#ninja)
    - [oneAPI DPC++ compiler](#oneapi-dpc-compiler)
    - [CUDA Toolkit](#cuda-toolkit)
    - [(Optional) Visual Studio IDE/Code](#optional-visual-studio-idecode)
    - [SYCL](#sycl)
  - [Building Graphitti v2](#building-graphitti-v2)

# Graphitti v2 
## An accelerated generalized graph simulator
This project is an attempt to rewrite the UWB INL's [Graphitti](https://github.com/UWB-Biocomputing/Graphitti) project, in modern C++17 and using [SYCL](https://www.khronos.org/sycl/) to enable heterogeneously accelerated compute of the simulator.

# v2 Main Features
- Modernized C++17 style, language feature usage, and containers
- Architecture refactor 
- Reformat input files in JSON, Workbench files in HDF5 only 
- SYCL for single-source heterogeneous programming
- Windows and Linux support (MacOS support is theoretical)
- `vcpkg` for package dependency resolution
- `CMakePresets` for automatic build configuration
- TODO: anything else we wanna mention ?

# Why SYCL?
It is a relatively new specification that enables single-source heterogeneous programming; in other words, there's no need for any other file extensions like `.cu` or `.cl`. It utilizes C++17 with no language extensions, and so feels more intuitive to program with for users that are not familiar with the specifics of accelerated programming models. Most importantly, SYCL aims to be cross-platform and ubuquitous among accelerated devices (i.e. not tied to any specific type of accelerator, so long as the backend is supported); For this particular repository, we focus on Windows/Linux support and only using a CUDA backend, so an NVIDIA device is required to run the simulator. The specific SYCL implementation we are working with is the [open-source oneAPI DPC++ compiler](https://github.com/intel/llvm).  
As SYCL becomes more mature, and more implementations offer a wider variety platforms/backends, we expect to be able to have this simulator switch between different implementations with ease - or, better yet, have just one implementation that handles _all_ accelerated device types.

# Build Guide

## Dependencies

### `vcpkg`
Follow [this](https://vcpkg.io/en/getting-started.html) guide to install `vcpkg` on your platform. It's pretty straightforward - there's no need to install any packages on your own, since `Graphitti v2` will install the required packages so long as `vcpkg` can be found. _You will need to edit the `CMakePresets.json` file with the proper `VCPKG_ROOT` directory of your platform and installation_.

### `CMake`
A relatively modern `CMake` install - the project requires minimum `3.21.x`.

### `Ninja`
This project uses `Ninja` as the generator - just install the latest one.

### oneAPI DPC++ compiler
Please follow [this](https://intel.github.io/llvm-docs/GetStartedGuide.html) guide, specifically with the NVIDIA CUDA backend, on how to build the SYCL toolchain and compiler. _You will need to edit the `CMakePresets.json` file with the proper `SYCL_LLVM_DIR`_.

### CUDA Toolkit
Preferably 11.5, but any relatively recent version of the toolkit should work. It should be noted that the particular SYCL CUDA-backend implementation requires a device that has a compute capability of at least 5.0 - that means Kepler cards and below are not supported.

### (Optional) Visual Studio IDE/Code
Visual Studio Code is a lightweight cross-platform editor, if you are not on a Windows machine then we recommend you use this as your main development platform since it has a handful of useful plugins and automates the build process. 
Alternatively, if you are on a Windows machine, you have the option of using the Visual Studio IDE; this is a bit heavier, but has all of the bells and whistles you could need, and readily integrates with CMake projects as well. *However, Visual Studio is required for building SYCL, as its `x64 Native Tools Command Prompt for VS 20XX` CLI sets up the correct environment variables for building.*

### SYCL 
[This](https://intel.github.io/llvm-docs/GetStartedGuide.html) post shows how to build the open-source DPC++ compiler; specifically, you need to follow the all of the instructions for the base and CUDA backend. Please be sure that the sample CUDA code can be built and run on your device before proceeding - we use this modified `clang++` compiler to compile our `Graphitti v2` code! Since this is just a fork of the `LLVM` project, you can also build some of its other tools that will be necessary for the project, such as `lld`. 

## Building Graphitti v2

1. Go to `CMakePresets.json` and edit the following environment variables:
   1. `VCPKG_ROOT` to wherever the top level directory of your `vcpkg` installation resides on your system.
   2. `SYCL_LLVM_DIR` to wherever the build directory of your sycl `llvm` cloned repository resides on your system. This is where the actual binaries and libraries were built after following the [SYCL](#sycl) section's guide.
2. To actually get CMake to configure and build the project:
   1. If your editor supports `CMakePresets` automatically, then choose the correct configuration for your platform, configure the project, then build it afterwards. Pretty straightforward.
   2. If you are trying to build the project from command line, then type in `cmake --preset "configuration-name"` to configure the project. Then go inside the `build/"configuration-name"` folder generated from the configure step of CMake and invoke the `Ninja` builder to actually build the executable.