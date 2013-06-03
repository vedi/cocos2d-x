/*
 * Copyright (c) 2013 VedideV
 *
 */

#import "FlurryBridge.h"
#import "Flurry.h"

@implementation FlurryBridge {
}

+ (NSObject *)dispatchNDKCall:(NSDictionary *)parameters {
    NSString *methodName = [parameters objectForKey:@"method"];

    NSMutableDictionary *retParameters = [NSMutableDictionary dictionary];
    if ([methodName isEqualToString:@"setUserId"]) {
        NSString *userId = (NSString *) [parameters objectForKey:@"userId"];
        [Flurry setUserID:userId];
    }
    else if ([methodName isEqualToString:@"setAppVersion"]) {
        NSString *appVersion = (NSString *) [parameters objectForKey:@"appVersion"];
        [Flurry setAppVersion:appVersion];
    }
    else if ([methodName isEqualToString:@"init"]) {
        NSString *version = (NSString *) [parameters objectForKey:@"apiKey"];
        [Flurry startSession:version];
        [retParameters setObject:[NSNumber numberWithBool:YES] forKey:@"return"];
    }
    else if ([methodName isEqualToString:@"logEvent"]) {
        NSString *eventId = (NSString *) [parameters objectForKey:@"eventId"];
        NSDictionary *paramMap = (NSDictionary *) [parameters objectForKey:@"paramMap"];
        [Flurry logEvent:eventId withParameters:paramMap];
    }
    else if ([methodName isEqualToString:@"logTimedEventBegin"]) {
        NSString *eventId = (NSString *) [parameters objectForKey:@"eventId"];
        NSDictionary *paramMap = (NSDictionary *) [parameters objectForKey:@"paramMap"];
        [Flurry logEvent:eventId withParameters:paramMap timed: YES];
    }
    else if ([methodName isEqualToString:@"logTimedEventEnd"]) {
        NSString *eventId = (NSString *) [parameters objectForKey:@"eventId"];
        NSDictionary *paramMap = (NSDictionary *) [parameters objectForKey:@"paramMap"];
        [Flurry endTimedEvent: eventId withParameters:paramMap];
    }
    else {
        NSLog(@"Unsupported method %@", methodName);
    }
    return retParameters;
}

+ (void)dispatchNDKCallback:(NSNotification*)notification {
    NSLog(@"FlurryBridge::dispatchNDKCallback: Illegal state: unexpected callback call");
}

@end
