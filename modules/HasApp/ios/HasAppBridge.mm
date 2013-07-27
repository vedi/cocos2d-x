//
// Created by Fedor Shubin on 7/1/13.
//

#import "HasAppBridge.h"
#import "HasAppManager.h"
#import "IOSNDKHelper.h"

@implementation HasAppBridge {
}

+ (NSObject *)dispatchNDKCall:(NSDictionary *)parameters {
    NSString *methodName = [parameters objectForKey:@"method"];

    NSMutableDictionary *retParameters = [NSMutableDictionary dictionary];
    if ([methodName isEqualToString:@"init"]) {
        NSDictionary *initParams = [parameters objectForKey:@"initParams"];
        [HasAppManager init: initParams];
    }
    else if ([methodName isEqualToString:@"hasApp"]) {
        NSString *appId = (NSString*)[parameters objectForKey:@"appId"];
        [HasAppManager hasApp:appId];
    }
    else if ([methodName isEqualToString:@"openApp"]) {
        NSString *appId = (NSString*)[parameters objectForKey:@"appId"];
        [HasAppManager openApp:appId];
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