## objc4  ![GitHub repo size in bytes](https://img.shields.io/github/repo-size/showxu/objc4.svg?colorA=24292e&colorB=24292e&style=flat) ![license](https://img.shields.io/github/license/showxu/objc4.svg?colorA=24292e&colorB=24292e&style=flat)

![platform](https://img.shields.io/badge/platform-macOS%20%7C%20Windows-orange.svg)

![language](https://img.shields.io/badge/language-C%20%7C%20Objective--C%2B%2B-ff69b4.svg?colorB=6866fb&label=main%20language)
![GitHub top language](https://img.shields.io/github/languages/top/showxu/objc4.svg?colorB=6866fb)
![GitHub language count](https://img.shields.io/github/languages/count/showxu/objc4.svg?colorB=28b9fe)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/showxu/objc4.svg?colorB=28b9fe)




#### Requirement 

- Xcode 9.0 +

#### Target dependencies tarballs

- [Libc-825.40.1.tar.gz](https://opensource.apple.com/tarballs/Libc/Libc-825.24.tar.gz)
- [dyld-519.2.1.tar.gz](https://opensource.apple.com/tarballs/dyld/dyld-519.2.1.tar.gz)
- [libauto-187.tar.gz](https://opensource.apple.com/tarballs/libauto/libauto-187.tar.gz)
- [libclosure-67.tar.gz](https://opensource.apple.com/tarballs/libclosure/libclosure-67.tar.gz)
- [libdispatch-913.1.6.tar.gz](https://opensource.apple.com/tarballs/libdispatch/libdispatch-913.1.6.tar.gz)
- [libplatform-161.tar.gz](https://opensource.apple.com/tarballs/libplatform/libplatform-161.tar.gz)
- [libpthread-301.1.6.tar.gz](https://opensource.apple.com/tarballs/libpthread/libpthread-301.1.6.tar.gz)
- [objc4-723.tar.gz](https://opensource.apple.com/tarballs/objc4/objc4-723.tar.gz)
- [xnu-4570.1.46.tar.gz](https://opensource.apple.com/tarballs/xnu/xnu-4570.1.46.tar.gz)


#### Build Precondition

##### Missing Private Header 

1. `#include <sys/reason.h>`

        /xnu-4570.1.46/bsd/sys/reason.h

2. `#include <mach-o/dyld_priv.h>`

        /dyld-519.2.1/include/mach-o/dyld_priv.h

3. `#include <os/lock_private.h>`

        /libplatform-161/private/os/lock_private.h

4. `#include <System/pthread_machdep.h>`

        /Libc-825.24/pthreads/pthread_machdep.h

5. `#include <os/base_private.h>`

        /libplatform-161/private/os/base_private.h

6. `#include <System/machine/cpu_capabilities.h>` 

        /xnu-4570.1.46/osfmk/machine/cpu_capabilities.h

7. `#include <CrashReporterClient.h>` 

        /Libc-825.24/include/CrashReporterClient.h

8. `#include <_simple.h>`

        /Libc-825.24/gen/_simple.h

9. `#include <Block_private.h>`

        /libclosure-67/Block_private.h

10. `#include <pthread/workqueue_private.h>`

        /libpthread-301.1.6/private/workqueue_private.h

11. `#include <System/pthread_machdep.h>`

        /Libc-825.40.1/pthreads/pthread_machdep.h

12. `#include <objc-shared-cache.h>`

        /dyld-519.2.1/include/objc-shared-cache.h

13. `#include <Block_private.h>`
    
        /libclosure-67/Block_private.h


###### Unincluded Private Header

1. `#include <pthread/tsd_private.h>`
        
        /libpthread/libpthread-301.1.6/private/tsd_private.h

2. `#include <os/tsd.h>`

        /xnu-4570.1.46/libsyscall/os/tsd.h


3. `#include <pthread/qos_private.h>`

        /libpthread/libpthread-301.1.6/private/qos_private.h

4. `#include <sys/qos_private.h>`

        /libpthread-301.1.6/sys/qos_private.h
        

##### Project Configuration

- HEADER_SEARCH_PATHS = $(SRCROOT)/../macosx.internal/System/Library/Frameworks/System.framework/PrivateHeaders

- GCC_PREPROCESSOR_DEFINITIONS = LIBC_NO_LIBCRASHREPORTERCLIENT

- ORDER_FILE = $(SRCROOT)/libobjc.order

- OTHER_LDFLAGS[sdk=macosx*] = -lc++abi -Xlinker -sectalign -Xlinker __DATA -Xlinker __objc_data -Xlinker 0x1000 -Xlinker -interposable_list -Xlinker interposable.txt

- OTHER_LDFLAGS[sdk=iphoneos*][arch=*] = -lc++abi -Wl,-segalign,0x4000 -Xlinker -sectalign -Xlinker __DATA -Xlinker __objc_data -Xlinker 0x1000 -Xlinker -interposable_list -Xlinker interposable.txt -isystem -iframework
- OTHER_LDFLAGS[sdk=iphonesimulator*][arch=*] = -lc++abi -Xlinker -interposable_list -Xlinker interposable.txt

