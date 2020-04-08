# objc4 
 
[![VSTS Build](https://alchemistxxd.visualstudio.com/_apis/public/build/definitions/e0656143-5484-4af8-8aa3-01f9baba5da1/1/badge)](https://alchemistxxd.visualstudio.com/Apple%20Open%20Source/_git/objc4) [![Travis](https://img.shields.io/travis/0xxd0/objc4.svg?style=flat)](https://www.travis-ci.org/0xxd0/objc4) [![Join the chat at https://gitter.im/0xxd0/objc4](https://badges.gitter.im/0xxd0/objc4.svg)](https://gitter.im/0xxd0/objc4?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge) ![support](https://img.shields.io/badge/support-macOS%20%7C%20iOS-orange.svg) ![GitHub top language](https://img.shields.io/github/languages/top/0xxd0/objc4.svg?colorB=6866fb) ![GitHub repo size in bytes](https://img.shields.io/github/repo-size/0xxd0/objc4.svg?colorA=24292e&colorB=24292e&style=flat)

This project is a buildable version of Objective-C runtime (latest objc 723) on [Apple Open Source](https://opensource.apple.com/tarballs/objc4/)

- [Requirement](#requirement)
- [Installation](#installation)
- [Target dependencies tarballs](#target-dependencies-tarballs)
- [Build Phases](#build-phases)
    - **Header** - [Missing Private Header](#missing-private-header), [Uninclude Private Header](#uninclude-private-header)
- [Build Setting](#build-setting)
- [License](#license)


## Requirement

[![Xcode 9.0+](https://img.shields.io/badge/Xcode-9.0%2B-blue.svg?colorA=3caefc&colorB=24292e)](https://developer.apple.com/xcode/)

## Installation

### Manually

Download zip or clone repo and integrate into your project manually.

## objc4 tarballs
- [objc4-781](https://opensource.apple.com/tarballs/objc4/objc4-781.tar.gz)
- [xnu-6153.41.3](https://opensource.apple.com/tarballs/xnu/xnu-6153.41.3.tar.gz)
- [Libc-825.24](https://opensource.apple.com/tarballs/Libc/Libc-825.24.tar.gz)
- [Libc-1353.41.1](https://opensource.apple.com/tarballs/Libc/Libc-1353.41.1.tar.gz)
- [dyld-733.6](https://opensource.apple.com/tarballs/dyld/dyld-733.6.tar.gz)
- [libauto-187.tar.gz](https://opensource.apple.com/tarballs/libauto/libauto-187.tar.gz)
- [libclosure-74](https://opensource.apple.com/tarballs/libclosure/libclosure-74.tar.gz)
- [libdispatch-1173.40.5](https://opensource.apple.com/tarballs/libdispatch/libdispatch-1173.40.5.tar.gz)
- [libplatform-220](https://opensource.apple.com/tarballs/libplatform/libplatform-220.tar.gz)
- [libpthread-416.40.3](https://opensource.apple.com/tarballs/libpthread/libpthread-416.40.3.tar.gz)

## Build Phases

### Private Header 

| file | header | tarball | description |
|------|--------|---------| ------------ |
| objc-os.h | `#include <sys/reason.h>` | /xnu-6153.41.3/bsd/sys/reason.h |
| objc-os.h | `#include <mach-o/dyld_priv.h>` | /dyld-733.6/include/mach-o/dyld_priv.h |
| objc-os.h | `#include <os/lock_private.h>` | /libplatform-220/private/os/lock_private.h |
| lock_private.h | `#include <os/base_private.h>` | /libplatform-220/private/os/base_private.h |
| objc-os.h | `#include <System/pthread_machdep.h>` | removed in latest Libc tarball (Libc-1353.41.1) | this header should be commonented |
| pthread_machdep.h | `#include <System/machine/cpu_capabilities.h>` | /xnu-6153.41.3/osfmk/machine/cpu_capabilities.h |
| objc-os.h | `#include <pthread/workqueue_private.h>` | /libpthread-416.40.3/private/workqueue_private.h | 
| objc-os.h | `#include <objc-shared-cache.h>` | /dyld-733.6/include/objc-shared-cache.h | 
| objc-errors.mm | `#include <_simple.h>` | /libplatform-220/private/_simple.h | 
| objc-block-trampolines.mm | `#include <Block_private.h>` | /libclosure-74/Block_private.h |
| objc-os.h | `#include <crt_externs.h>` | /Libc-1353.41.1/include/crt_externs.h |
| objc-runtime-new.mm | `#include <mach/shared_region.h>` | /xnu-6153.41.3/osfmk/mach/shared_region.h |
| objc-cache.mm  | `#include <kern/restartable.h>` | /xnu-6153.41.3/osfmk/mach/restartable.defs | build from xnu kernel |
| objc-os.h | `#include <CrashReporterClient.h>` | /Libc-825.24/include/CrashReporterClient.h | 

#### Private Header Included Header
| file | header | tarball |
|------|--------|---------|
| tsd_private.h | `#include <os/tsd.h>` | /xnu-6153.41.3/libsyscall/os/tsd.h |
| tsd_private.h | `#include <pthread/spinlock_private.h>` | /libpthread-416.40.3/private/spinlock_private.h |
| lock_private.h | `#include <pthread/tsd_private.h>` | /libpthread-416.40.3/private/tsd_private.h |
| workqueue_private.h | `#include <pthread/qos_private.h>` | /llibpthread-416.40.3/private/qos_private.h |
| qos_private.h | `#include <sys/qos_private.h>`  | /libpthread-416.40.3/sys/qos_private.h |

#### Bridge OS

On public macosx sdk (aka. Xcode 11.3.1), bridgeos (e.g. `__has_feature(attribute_availability_bridgeos)`) is unavailable, bridgeos availability should be removed.

#### dyld

In latest dyld-733.6 (aka. dyld-421.2 later), apple use this [ruby script](https://opensource.apple.com/source/dyld/dyld-733.6/bin/expand.rb) to expand versions, platfrom versions from a versionSets which defined in a YAML file, code generated by this script will be inserted after `@PLATFORM_VERSION_DEFS@`, `@IOS_PLATFORM_VERSION_DEFS@`, blah blah  in `dyld_priv.h`. For more detail please refer to [dyld](https://opensource.apple.com/source/dyld).

#### XNU

`<kern/restartable.h>` is generated form `restartable.defs` in xnu tarball during building xun kernel, which is a littel different from the one that shipped with public sdk that located in `/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/Kernel.framework/Versions/A/Headers/kern/restartable.h`.

## Build Setting
| Declaration | Value |
|-------------|-------|
| HEADER_SEARCH_PATHS | $(SRCROOT)/../macosx.internal/System/Library/Frameworks/System.framework/PrivateHeaders |
| GCC_PREPROCESSOR_DEFINITIONS | LIBC_NO_LIBCRASHREPORTERCLIENT |
| ORDER_FILE | $(SRCROOT)/libobjc.order |
| OTHER_LDFLAGS[sdk=macosx*] | -lc++abi -Xlinker -sectalign -Xlinker __DATA -Xlinker __objc_data -Xlinker 0x1000 -Xlinker -interposable_list -Xlinker interposable.txt |
| OTHER_LDFLAGS[sdk=iphoneos*][arch=*] | -lc++abi -Wl,-segalign,0x4000 -Xlinker -sectalign -Xlinker __DATA -Xlinker __objc_data -Xlinker 0x1000 -Xlinker -interposable_list -Xlinker interposable.txt -isystem -iframework |
| OTHER_LDFLAGS[sdk=iphonesimulator*][arch=*] | -lc++abi -Xlinker -interposable_list -Xlinker interposable.txt |

### Run Script
Evidently public macosx sdk is our only choice, we need to update value of parameter `-sdk` from `macosx.internal` to `macosx` in run script of objc target. 

## License
This project is released under the **Apache License 2.0**. The objc4 project is released under the **APPLE PUBLIC SOURCE LICENSE Version 2.0**.

[![license](https://img.shields.io/github/license/0xxd0/objc4.svg?colorA=24292e&colorB=24292e&style=flat)](https://github.com/0xxd0/objc4/blob/master/LICENSE)

