//
// Created by Fedor Shubin on 7/1/13.
//

#import "GoogleAnalyticsBridge.h"
#import "GoogleAnalyticsManager.h"
#import "IOSNDKHelper.h"

@implementation GoogleAnalyticsBridge {
}

+ (NSObject *)dispatchNDKCall:(NSDictionary *)parameters {
    NSString *methodName = [parameters objectForKey:@"method"];

    NSMutableDictionary *retParameters = [NSMutableDictionary dictionary];
    if ([methodName isEqualToString:@"init"]) {
        NSDictionary *initParams = [parameters objectForKey:@"initParams"];
        [GoogleAnalyticsManager init:initParams];
    }
    else if ([methodName isEqualToString:@"sendEventWithCategory"]) {
        NSString *category = [parameters objectForKey:@"category"];
        NSString *action = [parameters objectForKey:@"action"];
        NSString *label = [parameters objectForKey:@"label"];
        NSNumber *value = [parameters objectForKey:@"value"];
        [GoogleAnalyticsManager sendEventWithCategory:category withAction:action withLabel:label withValue:value];
    }
    else if ([methodName isEqualToString:@"sendView"]) {
        NSDictionary *viewName = [parameters objectForKey:@"appId"];
        [GoogleAnalyticsManager sendView:viewName];
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