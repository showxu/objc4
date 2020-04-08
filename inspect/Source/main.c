//
//  main.c
//  objc-inspect
//
//  Created by 0xxd0 on 2017/12/15.
//  Copyright © 2017年 0xxd0. All rights reserved.
//

/// System Headers
#include <CoreFoundation/CFRunLoop.h>
#include <objc/objc-class.h>
#include <Block.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/// Private Headers
#include "base.h"

static inline void run_objc_inspect(void);

static inline void runLoop_source_perform(void *info) {
    let perform = (void (^)(void))info;
    !perform ?: (perform)();
    run_objc_inspect();
}

static let runLoop_get_source = ^(id perform_block) {
    static var src_0 = (CFRunLoopSourceRef)nil;
    var src_ctx = (CFRunLoopSourceContext) {
        0, perform_block, nil, nil, nil, nil, nil, nil, nil, runLoop_source_perform
    };
    if (src_0 != nil) {
        CFRunLoopSourceGetContext(src_0, &src_ctx);
        src_ctx.info = perform_block;
        goto done;
    }
    src_0 = CFRunLoopSourceCreate(kCFAllocatorDefault, 0, &src_ctx);
done:
    return src_0;
};

let objc_inspect = ^{
    static var cls_ls = (Class *)nil;
    if (!cls_ls) {
        printf("Class list: \n");
        var cls_c = (uint)0;
        cls_ls = objc_copyClassList(&cls_c);
        for (var i = 0; i < cls_c; i++) {
            let cls = cls_ls[i];
            printf("%d. %s\n", i, class_getName(cls));
        }
    }
 
    printf("Please specify which Class to be inspect: ");
    let buf_size = (size_t)100;
    let c_str = (char *)malloc(sizeof(char) * buf_size);
    defer {
        free(c_str);
    };
    fgets(c_str, buf_size, stdin);
    let cls = objc_getClass(strtok(c_str, "\n"));
    
    printf("Class Method list: \n");
    var cls_mtd_c = (uint)0;
    let cls_mtd_ls = class_copyMethodList(object_getClass((id)cls), &cls_mtd_c);
    defer {
        free(cls_mtd_ls);
    };
    for (var i = 0; i < cls_mtd_c; i++) {
        let method = cls_mtd_ls[i];
        printf("%d. +%s\n", i, sel_getName(method_getName(method)));
    }
    
    printf("Instance Method list: \n");
    var ins_mtd_c = (uint)0;
    let ins_mtd_ls = class_copyMethodList(cls, &ins_mtd_c);
    defer {
        free(ins_mtd_ls);
    };
    for (var i = 0; i < ins_mtd_c; i++) {
        let method = ins_mtd_ls[i];
        printf("%d. -%s\n", i, sel_getName(method_getName(method)));
    }
    
    let sel_str = (char *)malloc(sizeof(char) *buf_size);
    defer {
        free(sel_str);
    };
    var obj = (id)cls;
    goto input;
    do {
        let sel = sel_getUid(sel_str);
        let is_cls = object_isClass(obj);
        
        let msgSend = (id (*)(id, SEL))objc_msgSend;
        obj = msgSend(obj, sel) ?: obj;
        printf("Message: %c[%s %s] \n\n", is_cls ? '+' : '-', class_getName(object_getClass(obj)), sel_getName(sel));
input:
        printf("Please specify sel, type enter for terminate: ");
        fgets(sel_str, buf_size, stdin);
    } while (strtok(sel_str, "\n"));
        
    printf("Awaiting for next inspection \n\n");
};

static inline void run_objc_inspect(void) {
    let copyed_blk = _Block_copy((id)objc_inspect);
    let src_0 = runLoop_get_source(copyed_blk);
    if (CFRunLoopContainsSource(CFRunLoopGetCurrent(), src_0, kCFRunLoopDefaultMode)) {
        goto done;
    }
    CFRunLoopAddSource(CFRunLoopGetCurrent(), src_0, kCFRunLoopDefaultMode);
done:
    CFRunLoopSourceSignal(src_0);
    CFRunLoopWakeUp(CFRunLoopGetCurrent());
}

int main(int argc, const char * argv[]) {
    run_objc_inspect();
    CFRunLoopRun();
    return 0;
}
