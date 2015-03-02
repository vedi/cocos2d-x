//
// Created by Fedor Shubin on 7/1/13.
//


#import "HasAppManager.h"

#include "CCDirector.h"
#import "iHasApp.h"
#import "HasAppBridge.h"

static iHasApp *detectionObject = nil;
static NSDictionary *idDict = nil;

@implementation HasAppManager {
}

+ (void)init: (NSDictionary *)initParams {
    detectionObject = [[iHasApp alloc] init];
    if ([initParams objectForKey:@"schemesDictName"]) {
        detectionObject.appSchemesDictionaryName = [initParams objectForKey:@"schemesDictName"];
    }
    idDict = [initParams objectForKey:@"idDict"];
    if (idDict) {
        [idDict retain];
    }
}

+ (void)hasApp:(NSString *)appId {

    NSString *realId = [self getRealId:appId];

    [detectionObject detectAppIdsWithIncremental:^(NSArray *appIds) {
        // NOTHING DO
    } withSuccess:^(NSArray *appIds) {
        bool exists = ([appIds indexOfObject:realId] != NSNotFound);
        NSDictionary *params = [NSDictionary
                dictionaryWithObjects:[NSArray arrayWithObjects:@"hasApp", appId, [NSNumber numberWithBool:exists] , nil]
                        forKeys:[NSArray arrayWithObjects: @"method", @"appId", @"result", nil]];
        [HasAppBridge dispatchNDKCallback:@"HasApp_callback" withParameters:params];
    } withFailure:^(NSError *error) {
        NSLog(@"Failure: %@", error.localizedDescription);
        NSDictionary *params = [NSDictionary
            dictionaryWithObjects:[NSArray arrayWithObjects:@"hasApp", error.localizedDescription, nil]
            forKeys:[NSArray arrayWithObjects: @"method", @"error", nil]];
        [HasAppBridge dispatchNDKCallback:@"HasApp_callback" withParameters:params];
    }];
}

+ (void)openApp:(NSString *)appId {
    NSString *realId = [self getRealId:appId];

    [detectionObject getAppSchemeWithAppId: realId
                               withSuccess:^(NSArray *schemes)
    {
        if ([schemes count] == 1) {
            [schemes objectAtIndex:0];
            NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"%@://", [schemes objectAtIndex:0]]];
            [[UIApplication sharedApplication] openURL:url];
        } else {
            NSString *errMsg = [NSString stringWithFormat:@"wrong schemes number %d, expected 1", [schemes count]];
            NSLog(@"Failure: %@", errMsg);
            NSDictionary *params = [NSDictionary
                    dictionaryWithObjects:[NSArray arrayWithObjects:@"openApp", errMsg, nil]
                                  forKeys:[NSArray arrayWithObjects: @"method", @"error", nil]];
            [HasAppBridge dispatchNDKCallback:@"HasApp_callback" withParameters:params];

        }
    } withFailure:^(NSError *error) {
        NSLog(@"Failure: %@", error.localizedDescription);
        NSDictionary *params = [NSDictionary
                dictionaryWithObjects:[NSArray arrayWithObjects:@"openApp", error.localizedDescription, nil]
                              forKeys:[NSArray arrayWithObjects: @"method", @"error", nil]];
        [HasAppBridge dispatchNDKCallback:@"HasApp_callback" withParameters:params];
    }];
}

+ (NSString *)getRealId:(NSString *)appId {
    NSString *realId;
    if (idDict) {
        realId = [idDict objectForKey:appId];
    } else {
        realId = appId;
    }
    return realId;
}

@end