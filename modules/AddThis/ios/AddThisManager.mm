//
// Created by Fedor Shubin on 8/8/13.
//


#import "AddThisManager.h"
#import "AppController.h"
#import "RootViewController.h"
#import "AddThis.h"


@implementation AddThisManager {

}

+ (AppController *) getAppController {
    id sth = [[UIApplication sharedApplication] delegate];
    if ([sth isKindOfClass:[AppController class]]) {
        return  (AppController *)sth;
    } else {
        [NSException raise:@"AddThisManager" format:@"Cannot get controller. Stopping."];
    }
}

+ (void)init:(NSDictionary *)initParams {
    NSDictionary *facebookParams = [initParams objectForKey: @"facebook"];
    if (facebookParams != nil) {
        if ([facebookParams objectForKey: @"appId"] != nil) {
            [AddThisSDK setFacebookAuthenticationMode:ATFacebookAuthenticationTypeFBConnect];
            [AddThisSDK setFacebookAPIKey:[facebookParams objectForKey: @"appId"]];
        }
    }
    NSDictionary *addThisParams = [initParams objectForKey: @"addThis"];
    if (addThisParams != nil) {
        if ([addThisParams objectForKey: @"publisherId"] != nil) {
            [AddThisSDK setAddThisPubId: [addThisParams objectForKey: @"publisherId"]];
        }
    }
}

+ (void)shareText:(NSString *)text toService:(NSString *)serviceName {
    if (serviceName) {
        [AddThisSDK shareURL:@"" withService: serviceName title:@"" description:text];
    } else {
        [AddThisSDK presentAddThisMenuForURL:@"" withTitle:@"" description:text];
    }
}

+ (void)shareUrl:(NSString *)urlStr withTitle:(NSString *)title toService:(NSString *)serviceName {
    if (serviceName) {
        [AddThisSDK shareURL:urlStr withService: serviceName title:title description:@""];
    } else {
        [AddThisSDK presentAddThisMenuForURL:urlStr withTitle:title description:@""];
    }
}

+ (void)shareImage:(NSString *)imageStr withTitle:(NSString *)title toService:(NSString *)serviceName {
    UIImage *image = [UIImage imageWithContentsOfFile: imageStr];
    if (serviceName) {
        [AddThisSDK shareImage:image withService: serviceName title:title description:@""];
    } else {
        [AddThisSDK presentAddThisMenuForImage:image withTitle:title description:@""];
    }
}

+ (void)shareWithTitle:(NSString *)title withText:(NSString *)text withUrl:(NSString *)urlStr withImage:(NSString *)imageStr toService:(NSString *)serviceName {
    UIImage *image = nil;
    if (imageStr != nil) {
        image = [UIImage imageWithContentsOfFile: imageStr];
    }

    if (imageStr != nil) {
        if (serviceName) {
            [AddThisSDK shareImage:image withService: serviceName title:title description:text];
        } else {
            [AddThisSDK presentAddThisMenuForImage:image withTitle:title description:text];
        }
    } else if (urlStr != nil) {
        if (serviceName) {
            [AddThisSDK shareURL:urlStr withService: serviceName title:title description:text];
        } else {
            [AddThisSDK presentAddThisMenuForURL:urlStr withTitle:title description:text];
        }
    } else if (text != nil) {
        if (serviceName) {
            [AddThisSDK shareURL:@"" withService: serviceName title:title description:text];
        } else {
            [AddThisSDK presentAddThisMenuForURL:@"" withTitle:title description:text];
        }
    } else {
        [NSException raise:@"AddThisManager" format:@"Cannot create sharing without any item defined"];
    }
}



@end