
# `objc4`  ![GitHub repo size in bytes](https://img.shields.io/github/repo-size/showxu/objc4.svg?colorA=24292e&colorB=24292e&style=flat) ![license](https://img.shields.io/github/license/showxu/objc4.svg?colorA=24292e&colorB=24292e&style=flat)

![platform](https://img.shields.io/badge/platform-macOS%20%7C%20Windows-orange.svg)

![language](https://img.shields.io/badge/language-C%20%7C%20Objective--C%2B%2B-ff69b4.svg?colorB=6866fb&label=main%20language)
![GitHub top language](https://img.shields.io/github/languages/top/showxu/objc4.svg?colorB=6866fb)
![GitHub language count](https://img.shields.io/github/languages/count/showxu/objc4.svg?colorB=28b9fe)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/showxu/objc4.svg?colorB=28b9fe)


## Requirement

[![Xcode 9.0+](https://img.shields.io/badge/Xcode-9.0%2B-blue.svg?colorA=3caefc&colorB=1d1d1d)](https://developer.apple.com/xcode/)

## Target dependencies tarballs

- [Libc-825.40.1.tar.gz](https://opensource.apple.com/tarballs/Libc/Libc-825.24.tar.gz)
- [dyld-519.2.1.tar.gz](https://opensource.apple.com/tarballs/dyld/dyld-519.2.1.tar.gz)
- [libauto-187.tar.gz](https://opensource.apple.com/tarballs/libauto/libauto-187.tar.gz)
- [libclosure-67.tar.gz](https://opensource.apple.com/tarballs/libclosure/libclosure-67.tar.gz)
- [libdispatch-913.1.6.tar.gz](https://opensource.apple.com/tarballs/libdispatch/libdispatch-913.1.6.tar.gz)
- [libplatform-161.tar.gz](https://opensource.apple.com/tarballs/libplatform/libplatform-161.tar.gz)
- [libpthread-301.1.6.tar.gz](https://opensource.apple.com/tarballs/libpthread/libpthread-301.1.6.tar.gz)
- [objc4-723.tar.gz](https://opensource.apple.com/tarballs/objc4/objc4-723.tar.gz)
- [xnu-4570.1.46.tar.gz](https://opensource.apple.com/tarballs/xnu/xnu-4570.1.46.tar.gz)


## Build Phases

![Private Header Missing](https://img.shields.io/badge/Private%20Header-Missing-ff2600.svg)

| file | header | tarball |
|------|--------|---------|
| `objc-os.h` | `#include <sys/reason.h>` | `/xnu-4570.1.46/bsd/sys/reason.h` |
| `objc-os.h` | `#include <mach-o/dyld_priv.h>` | `/dyld-519.2.1/include/mach-o/dyld_priv.h` |
| `objc-os.h` | `#include <os/lock_private.h>` | `/libplatform-161/private/os/lock_private.h` |
| `lock_private.h` | `#include <os/base_private.h>` | `/libplatform-161/private/os/base_private.h` |
| `lock_private.h` | `#include <System/pthread_machdep.h>` | `/Libc-825.24/pthreads/pthread_machdep.h` |
| `objc-os.h` | `#include <System/pthread_machdep.h>` | `/Libc-825.24/pthreads/pthread_machdep.h` |
| `pthread_machdep.h` | `#include <System/machine/cpu_capabilities.h>` | `/xnu-4570.1.46/osfmk/machine/cpu_capabilities.h` |
| `objc-os.h` | `#include <CrashReporterClient.h>` | `/Libc-825.24/include/CrashReporterClient.h` | 
| `objc-os.h` | `#include <pthread/workqueue_private.h>` | `/libpthread-301.1.6/private/workqueue_private.h` | 
| `objc-os.h` | `#include <objc-shared-cache.h>` | `/dyld-519.2.1/include/objc-shared-cache.h` | 
| `objc-errors.mm` | `#include <_simple.h>` | `/Libc-825.24/gen/_simple.h` | 
| `objc-block-trampolines.mm` | `#include <Block_private.h>` | `/libclosure-67/Block_private.h` |


![Private Header Uninclude](https://img.shields.io/badge/Private%20Header-Uninclude-ffb900.svg)

| file | header | tarball |
|------|--------|---------|
| `tsd_private.h` | `#include <os/tsd.h>` | `/xnu-4570.1.46/libsyscall/os/tsd.h` |
| `tsd_private.h`| `#include <pthread/spinlock_private.h>` | `/libpthread-301.1.6/private/spinlock_private.h` |
| `objc-os.h` | `#include <pthread/tsd_private.h>` | `/libpthread/libpthread-301.1.6/private/tsd_private.h` |
| `objc-os.h` | `#include <pthread/qos_private.h>` | `/libpthread/libpthread-301.1.6/private/qos_private.h` |
| `qos_private.h` | `#include <sys/qos_private.h>`  | `/libpthread-301.1.6/sys/qos_private.h` |


## Build Setting

| Declaration | Value |
|-------------|-------|
| `HEADER_SEARCH_PATHS` | `$(SRCROOT)/../macosx.internal/System/Library/Frameworks/System.framework/PrivateHeaders` |
| `GCC_PREPROCESSOR_DEFINITIONS` | `LIBC_NO_LIBCRASHREPORTERCLIENT` |
| `ORDER_FILE` | `$(SRCROOT)/libobjc.order` |
| `OTHER_LDFLAGS[sdk=macosx*]` | `-lc++abi -Xlinker -sectalign -Xlinker __DATA -Xlinker __objc_data -Xlinker 0x1000 -Xlinker -interposable_list -Xlinker interposable.txt` |
| `OTHER_LDFLAGS[sdk=iphoneos*][arch=*]` | `-lc++abi -Wl,-segalign,0x4000 -Xlinker -sectalign -Xlinker __DATA -Xlinker __objc_data -Xlinker 0x1000 -Xlinker -interposable_list -Xlinker interposable.txt -isystem -iframework` |
| `OTHER_LDFLAGS[sdk=iphonesimulator*][arch=*]` | `-lc++abi -Xlinker -interposable_list -Xlinker interposable.txt` |

