//
// Created by Alexandr on 29.07.13.
//


#import "AddThisBridge.h"
#import "AddThisManager.h"


@implementation AddThisBridge {

}

+ (NSObject *)dispatchNDKCall:(NSDictionary *)parameters {
    NSString *methodName = [parameters objectForKey:@"method"];

    NSMutableDictionary *retParameters = [NSMutableDictionary dictionary];

    if ([methodName isEqualToString:@"init"]) {
        NSDictionary *initParams = [parameters objectForKey:@"initParams"];
        [AddThisManager init:initParams];
    }
    else if ([methodName isEqualToString:@"setFacebookKeys"]) {
        NSString *key = (NSString *) [parameters objectForKey:@"key"];
        NSString *secret = (NSString *) [parameters objectForKey:@"secret"];

    }
    else if ([methodName isEqualToString:@"shareText"]) {
        NSString *text = (NSString *) [parameters objectForKey:@"text"];
        NSString *serviceName = (NSString *) [parameters objectForKey:@"serviceName"];
        [AddThisManager shareText:text toService:serviceName];
    }
    else if ([methodName isEqualToString:@"shareUrl"]) {
        NSString *urlStr = [parameters objectForKey:@"urlStr"];
        NSString *title = [parameters objectForKey:@"title"];
        NSString *serviceName = (NSString *) [parameters objectForKey:@"serviceName"];
        [AddThisManager shareUrl:urlStr withTitle:title toService:serviceName];
    }
    else if ([methodName isEqualToString:@"shareImage"]) {
        NSString *imagePath = [parameters objectForKey:@"imagePath"];
        NSString *title = [parameters objectForKey:@"title"];
        NSString *serviceName = (NSString *) [parameters objectForKey:@"serviceName"];
        [AddThisManager shareImage:imagePath withTitle:title toService:serviceName];
    }
    else if ([methodName isEqualToString:@"share"]) {
        NSString *text = [parameters objectForKey:@"text"];
        NSString *urlStr = [parameters objectForKey:@"urlStr"];
        NSString *imagePath = [parameters objectForKey:@"imagePath"];
        NSString *title = [parameters objectForKey:@"title"];
        NSString *serviceName = (NSString *) [parameters objectForKey:@"serviceName"];
        [AddThisManager shareWithTitle:title withText:text withUrl:urlStr withImage:imagePath toService:serviceName];
    }
    else {
        NSLog(@"Unsupported method %@", methodName);
    }

    return retParameters;
}

+ (void)dispatchNDKCallback:(NSNotification *)notification {
    NSLog(@"ParseBridge::dispatchNDKCallback: Illegal state: unexpected callback call");
}

@end