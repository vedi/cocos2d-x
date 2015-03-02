//
// Created by Alexandr on 29.07.13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#import <Foundation/Foundation.h>

#define IMPL_SHARE_EASY_NDK_METHOD() - (NSObject *)share_easyNDK:(NSObject *)params { \
NSLog(@"share_easyNDK call"); \
NSDictionary *parameters = (NSDictionary*) params; \
NSLog(@"Passed params are : %@", parameters); \
return [ShareBridge dispatchNDKCall:parameters]; \
}


@interface ShareBridge : NSObject

+ (NSObject *)dispatchNDKCall:(NSDictionary *)parameters;
+ (void)dispatchNDKCallback:(NSNotification*)notification;

+ (void)shareText:(NSString *)textForShare;

@end