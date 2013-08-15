//
// Created by Alexandr on 29.07.13.
//


#import <Foundation/Foundation.h>

#define IMPL_ADDTHIS_EASY_NDK_METHOD() - (NSObject *)addThis_easyNDK:(NSObject *)params { \
    NSLog(@"addThis_easyNDK call"); \
    NSDictionary *parameters = (NSDictionary*) params; \
    NSLog(@"Passed params are : %@", parameters); \
    return [AddThisBridge dispatchNDKCall:parameters]; \
}


@interface AddThisBridge : NSObject

+ (NSObject *)dispatchNDKCall:(NSDictionary *)parameters;
+ (void)dispatchNDKCallback:(NSNotification*)notification;
@end