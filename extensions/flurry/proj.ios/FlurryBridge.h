/*
 * Copyright (c) 2013 VedideV
 *
 */
#ifndef __flurry__FlurryBridge__
#define __flurry__FlurryBridge__

#import <Foundation/Foundation.h>


@interface FlurryBridge : NSObject

+ (NSObject *)dispatchNDKCall:(NSDictionary *)parameters;
+ (void)dispatchNDKCallback:(NSNotification*)notification;
@end

#endif // __flurry__FlurryBridge__