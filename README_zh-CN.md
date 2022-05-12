
# objc4 runtime

![build_status](https://github.com/showxu/objc4/workflows/build/badge.svg) 
[![Join the chat at https://gitter.im/showxu/objc4](https://badges.gitter.im/showxu/objc4.svg)](https://gitter.im/showxu/objc4?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge) 
![support](https://img.shields.io/badge/support-macOS%20%7C%20iOS-orange.svg)

此项目为可调式版本的 `Objective-C` 运行时，当前最新版本为 `objc4-818.2`，原始版本的源码可以在苹果开源处[下载](https://opensource.apple.com/tarballs/objc4/)。

- [版本选择](#版本选择)
- [如何安装](#如何安装)
- [如何使用](#如何使用)
- [objc4 依赖](#objc4-依赖)
- [编译问题解决](#编译问题解决)
- [编译设置](#编译设置)
- [许可协议](#许可协议)


## **版本选择**

| macOS | macOS 版本 | Xcode 版本 | `objc4` 源码版本 |
| - | - | - | - |
| [![macOS Big Sur](https://img.shields.io/badge/macOS-Big%20Sur-blue?colorA=d23a70&colorB=181B2D)](https://developer.apple.com/macos/) | ![macOS Version](https://img.shields.io/badge/-11.0.1%20-181B2D) | [![Xcode 12.3](https://img.shields.io/badge/Xcode-12.3-blue?colorA=1A5DE3&colorB=2A2C3A)](https://developer.apple.com/xcode/) | [objc4-818.2](https://github.com/showxu/objc4/releases/tag/objc4-818.2) |
| [![macOS Catalina](https://img.shields.io/badge/macOS-Catalina-blue?colorA=314C78&colorB=181B2D)](https://developer.apple.com/macos/) | ![macOS Version](https://img.shields.io/badge/-10.15.4%20~%2010.15.6-181B2D) | [![Xcode 12.0](https://img.shields.io/badge/Xcode-12.0-blue?colorA=1A5DE3&colorB=2A2C3A)](https://developer.apple.com/xcode/) | [objc4-787.1](https://github.com/showxu/objc4/releases/tag/objc4-787.1) |
| [![macOS Catalina](https://img.shields.io/badge/macOS-Catalina-blue?colorA=314C78&colorB=181B2D)](https://developer.apple.com/macos/) | ![macOS Version](https://img.shields.io/badge/-10.15.1-181B2D) | [![Xcode 11.1](https://img.shields.io/badge/Xcode-11.1-blue?colorA=1A8DF8&colorB=2A2C3A)](https://developer.apple.com/xcode/) | [objc4-781](https://github.com/showxu/objc4/releases/tag/objc4-781) | 
| [![macOS High Sierra](https://img.shields.io/badge/macOS-High%20Sierra-blue?colorA=CC4027&colorB=181B2D)](https://developer.apple.com/macos/) | ![macOS Version](https://img.shields.io/badge/-10.13.x-181B2D) | [![Xcode 10.1](https://img.shields.io/badge/Xcode-10.1-blue?colorA=1A8DF8&colorB=2A2C3A)](https://developer.apple.com/xcode/) | [objc4-723](https://github.com/showxu/objc4/releases/tag/objc4-723) |


## **如何安装**

#### 手动安装
下载或者克隆仓库的代码，选择 **`objc scheme`** 并且编译。


## **如何使用**

在编译完成之后，手动把编译产物 `libobjc.A.dylib` 集成进工程并链接，进行项目中的调试。或者直接使用内置的 **objc-inspect** 的 `scheme` 直接进行调试。


## **objc4 依赖**

- [objc4-818.2](https://opensource.apple.com/tarballs/objc4/objc4-818.2.tar.gz)
- [xnu-7195.50.7.100.1](https://opensource.apple.com/tarballs/xnu/xnu-7195.50.7.100.1.tar.gz)
- [Libc-1439.40.11](https://opensource.apple.com/tarballs/Libc/Libc-1439.40.11.tar.gz)
- [dyld-832.7.1](https://opensource.apple.com/tarballs/dyld/dyld-832.7.1.tar.gz)
- [libauto-187.tar.gz](https://opensource.apple.com/tarballs/libauto/libauto-187.tar.gz)
- [libclosure-74](https://opensource.apple.com/tarballs/libclosure/libclosure-74.tar.gz)
- [libdispatch-1173.40.5](https://opensource.apple.com/tarballs/libdispatch/libdispatch-1173.40.5.tar.gz)
- [libplatform-220](https://opensource.apple.com/tarballs/libplatform/libplatform-220.tar.gz)
- [libpthread-416.40.3](https://opensource.apple.com/tarballs/libpthread/libpthread-416.40.3.tar.gz)


## **编译问题解决**

#### 私有头文件

| `objc` 头文件 | 缺失的 `#include` 文件 | 在源代码中的位置 |
|------|--------|---------|
| objc-os.h | `#include <sys/reason.h>` | /xnu-6153.41.3/bsd/sys/reason.h |
| objc-os.h | `#include <mach-o/dyld_priv.h>` | /dyld-733.6/include/mach-o/dyld_priv.h |
| objc-os.h | `#include <os/lock_private.h>` | /libplatform-220/private/os/lock_private.h |
| lock_private.h | `#include <os/base_private.h>` | /libplatform-220/private/os/base_private.h |
| objc-os.h | `#include <System/pthread_machdep.h>` | removed in latest Libc tarball (Libc-1353.41.1), this header should be commented-out |
| objc-class.mm | `#include <os/linker_set.h>` | /xnu-7195.50.7.100.1/os/linker_set.h |
| pthread_machdep.h | `#include <System/machine/cpu_capabilities.h>` | /xnu-6153.41.3/osfmk/machine/cpu_capabilities.h |
| objc-os.h | `#include <pthread/workqueue_private.h>` | /libpthread-416.40.3/private/workqueue_private.h | 
| objc-os.h | `#include <objc-shared-cache.h>` | /dyld-733.6/include/objc-shared-cache.h | 
| objc-errors.mm | `#include <_simple.h>` | /libplatform-220/private/_simple.h | 
| objc-block-trampolines.mm | `#include <Block_private.h>` | /libclosure-74/Block_private.h |
| objc-os.h | `#include <crt_externs.h>` | /Libc-1353.41.1/include/crt_externs.h |
| objc-runtime-new.mm | `#include <mach/shared_region.h>` | /xnu-6153.41.3/osfmk/mach/shared_region.h |
| objc-cache.mm  | `#include <kern/restartable.h>` | /xnu-6153.41.3/osfmk/mach/restartable.defs, build from xnu kernel |
| objc-os.h | `#include_next <CrashReporterClient.h>` => `#include <CrashReporterClient.h>` | /Libc-825.24/include/CrashReporterClient.h | 
| NSObject.mm | `#include <os/reason_private.h>` | /xnu-7195.50.7.100.1/os/reason_private |
| NSObject.mm | `#include <os/variant_private.h>` | /xnu-7195.50.7.100.1/os/reason_private |
| objc-exception.mm | `#include <objc/objc-abi.h>` | removed |
| objc-gdb.h | `#include <objc/maptable.h>` | removed |


#### 私有头文件中引用缺失的头文件

| 私有头文件 | 缺失的 `#include` 文件 | 在源代码中的位置 |
|------|--------|---------|
| tsd_private.h | `#include <os/tsd.h>` | /xnu-6153.41.3/libsyscall/os/tsd.h |
| tsd_private.h | `#include <pthread/spinlock_private.h>` | /libpthread-416.40.3/private/spinlock_private.h |
| lock_private.h | `#include <pthread/tsd_private.h>` | /libpthread-416.40.3/private/tsd_private.h |
| workqueue_private.h | `#include <pthread/qos_private.h>` | /llibpthread-416.40.3/private/qos_private.h |
| qos_private.h | `#include <sys/qos_private.h>`  | /libpthread-416.40.3/sys/qos_private.h |


#### Bridge OS

在开发者使用的 macosx sdk 中，`bridgeos (e.g. __has_feature(attribute_availability_bridgeos))` 这个 `attribute` 无法使用，`bridgeos availability` 相关的代码需要被移除。


#### dyld

在最新的 dyld-733.6 (dyld-421.2 later) 中，苹果使用使用这个脚本 [ruby script](https://opensource.apple.com/source/dyld/dyld-733.6/bin/expand.rb) 来生成并展开平台版本相关的 `Macro`，具体的平台版本定义在 YAML 文件中的 `versionSets`，生成之后的版本代码会插入在头文件 `dyld_priv.h` 中的 `@MAC_VERSION_DEFS@`, `@IOS_VERSION_DEFS@`, `@WATCHOS_VERSION_DEFS@`, `@TVOS_VERSION_DEFS@` · `@BRIDGEOS_VERSION_DEFS@`，进一步了解 [dyld](https://opensource.apple.com/source/dyld)。


#### XNU

`<kern/restartable.h>` 这个头文件，是在编译 xun kernel 时，由脚本通过 `restartable.defs` 这个文件而生成，同时这个编译生成的头文件和提供给开发者的 sdk 中的 `/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/Kernel.framework/Versions/A/Headers/kern/restartable.h` 有所不同。


#### Cambria framework

暂时没找到这个 `framework` 的出处，相关代码先作注释处理。可能与 `link flag` 中的 `-loah` 和 `lib oah` 有关，相关代码先作注释处理。

```objc
// File objc-cache.mm
// 
// Line 87 ~ 88
#include <Cambria/Traps.h>
#include <Cambria/Cambria.h>
// 
// ···
//
// Line 1121 ～ 1128 
if (oah_is_current_process_translated()) {
    kern_return_t ret = objc_thread_get_rip(threads[count], (uint64_t*)&pc);
    if (ret != KERN_SUCCESS) {
        pc = PC_SENTINEL;
    }
} else {
    pc = _get_pc_for_thread (threads[count]);
}
```


#### `#include <os/feature_private.h>`

暂时没找到这个头文件的出处，相关代码先作注释处理。

```objc
// File objc-runtime.mm
// 
// ···
//
// Line 36
#include <os/feature_private.h> // os_feature_enabled_simple()
//
// ···
//
// Line 444 ～ 446
if (!os_feature_enabled_simple(objc4, preoptimizedCaches, true)) {
    DisablePreoptCaches = true;
}
// 
```


#### `dyld_fall_2020_os_versions`, `dyld_fall_2018_os_versions`

在 `Apple Open Source` 中发现 `xnu-7195.50.7.100.1/bsd/kern/kern_mman.c` 中有这样一个函数。

```c
static uint32_t
proc_2020_fall_os_sdk(void)
```

猜测 `dyld_xxxx_os_versions` 可能与这个函数以及 `dyld build-scripts` 有关，暂时作注释处理。


#### `dyld_platform_version_macOS_`, `dyld_platform_version_iOS_`, `dyld_platform_version_tvOS_`, `dyld_platform_version_watchOS_`, `dyld_platform_version_bridgeOS_`

这些 `Macro` 由此脚本 [dyld build-scripts](https://opensource.apple.com/source/dyld/dyld-832.7.1/build-scripts/) 生成，暂时作注释处理。


#### `STATIC_ASSERT`

```bash
objc4/runtime/objc-runtime-new.mm:176:1: '_static_assert' declared as an array with a negative size
```

暂时作注释处理。


## **编译设置**
| XCCONFIG KEY | XCCONFIG VALUE |
|-------------|-------|
| `HEADER_SEARCH_PATHS` | $(SRCROOT)/../macosx.internal/System/Library/Frameworks/System.framework/PrivateHeaders, also append `$(inherited)` to target objc |
| `GCC_PREPROCESSOR_DEFINITIONS` | LIBC_NO_LIBCRASHREPORTERCLIENT, also append `$(inherited)` to target objc |
| `ORDER_FILE` | $(SRCROOT)/libobjc.order |
| `OTHER_LDFLAGS[sdk=macosx*]` | -lc++abi -Xlinker -sectalign -Xlinker __DATA -Xlinker __objc_data -Xlinker 0x1000 -Xlinker -interposable_list -Xlinker interposable.txt, remove build setting in target objc |
| `OTHER_LDFLAGS[sdk=iphoneos*][arch=*]` | -lc++abi -Wl,-segalign,0x4000 -Xlinker -sectalign -Xlinker __DATA -Xlinker __objc_data -Xlinker 0x1000 -Xlinker -interposable_list -Xlinker interposable.txt, remove build setting in target objc |
| `OTHER_LDFLAGS[sdk=iphonesimulator*][arch=*]` | -lc++abi -Xlinker -interposable_list -Xlinker interposable.txt, remove build setting in target objc |


### 运行脚本
外部开发者的 `sdk` 并没有 `macosx.internal` 这个版本，因此 `objc target` 的 `Run Script` 中 `-sdk` 的参数需要从 `macosx.internal` 修改为 `macosx`。


## 许可协议

此项目遵守 **MIT** 许可协议。原始的 `objc4` 项目以及源代码遵守 **APPLE PUBLIC SOURCE LICENSE Version 2.0**。
