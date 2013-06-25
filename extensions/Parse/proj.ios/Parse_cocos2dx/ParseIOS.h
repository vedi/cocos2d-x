//
//  ParseIOS.h
//  ParseIOS
//
//  Created by Alexandr on 06/24/13.
//  Copyright (c) 2013 VedideV. All rights reserved.
//

#import <Foundation/Foundation.h>

#define IMPL_PARSE_EASY_NDK_METHOD() - (NSObject *)parse_easyNDK:(NSObject *)params { \
NSLog(@"parse_easyNDK call"); \
NSDictionary *parameters = (NSDictionary*) params; \
NSLog(@"Passed params are : %@", parameters); \
return [ParseIOS dispatchNDKCall:parameters]; \
}

@interface ParseIOS : NSObject

+ (NSObject *)dispatchNDKCall:(NSDictionary *)parameters;
+ (void)dispatchNDKCallback:(NSNotification*)notification;
+ (void)registerForRemoteNotifications:(NSData *)deviceToken;
+ (void)receiveRemoteNotification:(NSDictionary *)userInfo;

@end
