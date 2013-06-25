//
//  ParseIOS.m
//  ParseIOS
//
//  Created by Alexandr on 06/24/13.
//  Copyright (c) 2013 VedideV. All rights reserved.
//

#import <Parse/Parse.h>
#import "ParseIOS.h"

@implementation ParseIOS

+ (NSObject *)dispatchNDKCall:(NSDictionary *)parameters {
    NSString *methodName = [parameters objectForKey:@"method"];

    NSMutableDictionary *retParameters = [NSMutableDictionary dictionary];

    if ([methodName isEqualToString:@"setKeys"]) {
        NSString *applicationID = (NSString *) [parameters objectForKey:@"applicationID"];
        NSString *clientKey = (NSString *) [parameters objectForKey:@"clientKey"];
        [Parse setApplicationId:applicationID clientKey:clientKey];
    }
    else if ([methodName isEqualToString:@"initParsePush"]) {
        NSNumber *notificationsOn = (NSNumber*)[parameters objectForKey:@"notificationsOn"];
        if (notificationsOn) {
            [[UIApplication sharedApplication] registerForRemoteNotificationTypes: UIRemoteNotificationTypeBadge |
                    UIRemoteNotificationTypeAlert |
                    UIRemoteNotificationTypeSound];
        }
    }
    else if ([methodName isEqualToString:@"sendParseObject"]) {
        NSString *objectName = (NSString *) [parameters objectForKey:@"objectName"];
        PFObject *pa = [PFObject objectWithClassName:objectName];
        [pa saveEventually];
    }
    else {
        NSLog(@"Unsupported method %@", methodName);
    }

    return retParameters;
}

+ (void)dispatchNDKCallback:(NSNotification *)notification {
    NSLog(@"ParseIOS::dispatchNDKCallback: Illegal state: unexpected callback call");
}

+ (void)registerForRemoteNotifications:(NSData *)deviceToken {
    // Store the deviceToken in the current installation and save it to Parse.
    // PFInstallation *currentInstallation = [PFInstallation currentInstallation];
    // [currentInstallation setDeviceTokenFromData:newDeviceToken];
    // [currentInstallation saveInBackground];

    //from native Daniel
    // Tell Parse about the device token.
    [PFPush storeDeviceToken:deviceToken];
    // Subscribe to the global broadcast channel.
    [PFPush subscribeToChannelInBackground:@""];
}

+ (void)receiveRemoteNotification:(NSDictionary *)userInfo {
    [PFPush handlePush:userInfo];
}

@end
