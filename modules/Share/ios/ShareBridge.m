//
// Created by Alexandr on 29.07.13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#import "ShareBridge.h"
#import "AppController.h"
#import "RootViewController.h"
#import "SHK.h"


@implementation ShareBridge {

}

+ (NSObject *)dispatchNDKCall:(NSDictionary *)parameters {
    NSString *methodName = [parameters objectForKey:@"method"];

    NSMutableDictionary *retParameters = [NSMutableDictionary dictionary];

    if ([methodName isEqualToString:@"shareText"]) {
        NSString *textForShare = (NSString *) [parameters objectForKey:@"text"];
        [ShareBridge shareText:textForShare];
    }
    else if ([methodName isEqualToString:@"init"]) {
        NSString *applicationName = (NSString *) [parameters objectForKey:@"applicationName"];
        NSString *applicationURL = (NSString *) [parameters objectForKey:@"applicationURL"];

    }
    else if ([methodName isEqualToString:@"setFacebookKeys"]) {
        NSString *key = (NSString *) [parameters objectForKey:@"key"];
        NSString *secret = (NSString *) [parameters objectForKey:@"secret"];

    }
    else {
        NSLog(@"Unsupported method %@", methodName);
    }

    return retParameters;
}

+ (void)dispatchNDKCallback:(NSNotification *)notification {
    NSLog(@"ParseBridge::dispatchNDKCallback: Illegal state: unexpected callback call");
}

+ (void)shareText:(NSString *)textForShare {
    id sth = [[UIApplication sharedApplication] delegate];
    if ([sth isKindOfClass:[AppController class]]) {
        AppController *controller = (AppController *)sth;

// Wrap the NSString within the SHKItem Class
        SHKItem *item = [SHKItem text:textForShare];
// Create a ShareKit ActionSheet and Assign the Sheet an SHKItem
        SHKActionSheet *actionSheet = [SHKActionSheet actionSheetForItem:item];
// Display the ActionSheet in the current UIView
        [actionSheet showInView:controller.viewController.view];
    }
}

@end