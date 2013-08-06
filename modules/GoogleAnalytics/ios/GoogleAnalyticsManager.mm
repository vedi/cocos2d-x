//
// Created by Fedor Shubin on 8/6/13.
//


#import "GoogleAnalyticsManager.h"

#import "GAITracker.h"
#import "GAI.h"

static id<GAITracker> tracker = nil;

@implementation GoogleAnalyticsManager {
}

+ (void)init: (NSDictionary *)params {

    id obj;

    obj = [params objectForKey:@"trackUncaughtExceptions"];
    if (obj != nil) {
        [GAI sharedInstance].trackUncaughtExceptions = [obj boolValue];
    }

    obj = [params objectForKey:@"dispatchInterval"];
    if (obj != nil) {
        [GAI sharedInstance].dispatchInterval = [obj integerValue];
    }

    obj = [params objectForKey:@"debug"];
    if (obj != nil) {
        [GAI sharedInstance].debug = [obj boolValue];
    }

    obj = [params objectForKey:@"trackingId"];
    if (obj != nil) {
        tracker = [[GAI sharedInstance] trackerWithTrackingId: [obj stringValue]];
    } else {
        [NSException raise:@"GoogleAnalytics" format:@"Tracking ID is not defined"];
    }
}

+ (void)sendEventWithCategory:(NSString *)category withAction:(NSString *)action withLabel:(NSString *)label withValue:(NSNumber *)value {
    [tracker sendEventWithCategory:category withAction:action withLabel:label withValue:value];
}

+ (void)sendView:(NSString*)viewName {
    [tracker sendView:viewName];
}

@end