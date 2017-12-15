//
//  main.c
//  objc-debug
//
//  Created by Alchemist on 2017/12/15.
//  Copyright © 2017年 alchemistxxd. All rights reserved.
//

#include <stdio.h>
#include <objc/objc-class.h>

#define let const __auto_type
#define var __auto_type

static let alloc = "alloc";
static let init = "init";
static let NSObject = "NSObject";

static inline void debug_objc(void);

int main(int argc, const char * argv[]) {
    debug_objc();
    return 0;
}

static inline void debug_objc(void) {
    let alloc_sel = sel_getUid(alloc);
    let init_sel = sel_getUid(init);
    let cls = objc_getClass(NSObject);
    
    let obj_1 = class_createInstance(cls, 0);
    let obj_2 = objc_msgSend(objc_msgSend((id)cls, alloc_sel), init_sel);
    
    object_dispose(obj_1);
    object_dispose(obj_2);
}
