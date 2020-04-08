//
//  base.h
//  objc-inspect
//
//  Created by 0xxd0 on 2016/12/2.
//  Copyright © 2016年 0xxd0. All rights reserved.
//

_Pragma("once")

#if defined(__cplusplus)
extern "C" {
#endif
    
// Introduce Swift let
#pragma mark - Swift let
#ifdef __cplusplus
    #define let const auto
#else
    #define let const __auto_type
#endif

// Introduce Swift var
#pragma mark - Swift var
#ifdef __cplusplus
    #define var auto
#else
    #define var __auto_type
#endif

// Introduce Swift defer
#pragma mark - Swift defer
typedef void (^defer_block_t)(void);

_Pragma("clang diagnostic push")
_Pragma("clang diagnostic ignored \"-Wunused-function\"")
static inline void cleanup(__strong defer_block_t *block) {
    (*block)();
}
_Pragma("clang diagnostic pop")

#define defer_block(id) \
    defer_block ## id

#define defer_at(line) \
    defer_block(line)

#define defer \
    __strong defer_block_t defer_at(__LINE__) \
        __attribute__((cleanup(cleanup), unused)) = ^

#if defined(__cplusplus)
}
#endif
