//
// Created by Fedor Shubin on 7/1/13.
//

#import "NativeViewBridge.h"
#import "NativeViewManager.h"
#import "IOSNDKHelper.h"

@implementation NativeViewBridge {
}

+ (NSObject *)dispatchNDKCall:(NSDictionary *)parameters {
    NSString *methodName = [parameters objectForKey:@"method"];

    NSMutableDictionary *retParameters = [NSMutableDictionary dictionary];
    if ([methodName isEqualToString:@"init"]) {
        [NativeViewManager init];
    } else if ([methodName isEqualToString:@"createAndShowNative"]) {
        NSDictionary *viewParams = (NSDictionary*)[parameters objectForKey:@"viewParams"];
        NSString *viewKey = (NSString*)[parameters objectForKey:@"viewKey"];
        NSString *viewData = (NSString*)[parameters objectForKey:@"viewData"];
        NSNumber *x = (NSNumber*)[parameters objectForKey:@"x"];
        NSNumber *y = (NSNumber*)[parameters objectForKey:@"y"];
        NSNumber *w = (NSNumber*)[parameters objectForKey:@"w"];
        NSNumber *h = (NSNumber*)[parameters objectForKey:@"h"];

        [NativeViewManager createAndShowNativeWithKey:viewKey viewParams:viewParams viewData:viewData x:x y:y w:w h:h];
    }
    else if ([methodName isEqualToString:@"sendMessage"]) {
        NSString *viewKey = (NSString*)[parameters objectForKey:@"viewKey"];
        NSString *messageData = (NSString*)[parameters objectForKey:@"messageData"];

        [NativeViewManager nativeSendMessage:viewKey messageData:messageData];
    }
    else if ([methodName isEqualToString:@"closeNative"]) {
        NSString *viewKey = (NSString*)[parameters objectForKey:@"viewKey"];

        [NativeViewManager closeNative:viewKey];
    }
    else {
        NSLog(@"Unsupported method %@", methodName);
    }
    return retParameters;
}

+ (void)dispatchNDKCallback:(NSString *)key withParameters:(NSDictionary *)parameters {
    [IOSNDKHelper sendMessage:key withParameters:parameters];
}

@end