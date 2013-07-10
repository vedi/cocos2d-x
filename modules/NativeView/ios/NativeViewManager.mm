//
// Created by Fedor Shubin on 7/1/13.
//


#import "NativeViewManager.h"

#include "CCDirector.h"

UIViewController *sViewController = nil;
NSMutableDictionary *sViewControllers = nil;
NSMutableDictionary *sViewControllerFactories = [[NSMutableDictionary alloc] init];

@implementation NativeViewManager {
}

+ (void)setViewController:(UIViewController *)viewController {
    sViewController = viewController;
}

+ (void)init {
    sViewControllers = [[NSMutableDictionary alloc] init];
}

+ (void)addFactory:(id<NativeViewFactory>)factory forKey:(NSString *)viewKey {
    [sViewControllerFactories setValue:factory forKey:viewKey];
}

+ (void)createAndShowNativeWithKey:(NSString *)key viewParams:(NSDictionary *)viewParams viewData:(NSString *)viewData x:(NSNumber *)x y:(NSNumber *)y w:(NSNumber *)w h:(NSNumber *)h {
    float scale = 1 / sViewController.view.contentScaleFactor;

    y = [NSNumber numberWithFloat: cocos2d::CCDirector::sharedDirector()->getWinSize().height - y.floatValue];

    // cleanup if there is any
    [sViewControllers setValue:nil forKey:key];

    id<NativeViewFactory>nativeViewFactory = [sViewControllerFactories objectForKey:key];

    if (nativeViewFactory != nil) {
        UIViewController *viewController = [nativeViewFactory createNativeViewWithParams:viewParams viewData:viewData];

        [viewController.view setContentScaleFactor:2];

        [viewController.view setBounds:CGRectMake(0.f, 0, scale * w.floatValue, scale * h.floatValue)];
        [viewController.view setCenter:CGPointMake(scale * x.floatValue, scale * y.floatValue)];

        [sViewController.view addSubview: viewController.view];
        [sViewControllers setObject:viewController forKey:key];
    } else {
        NSLog(@"Cannot find factory for key: %@", key);
    }
}

+ (void)nativeSendMessage:(NSString *)key messageData:(NSString *)messageData {
    id<NativeViewProtocol> nativeView = [sViewControllers objectForKey:key];

    if (nativeView != nil) {
        [nativeView sendMessageToView:messageData];
    } else {
        NSLog(@"There is no view with key: %@", key);
    }
}

+ (void)closeNative:(NSString *)key {
    id<NativeViewProtocol> nativeView = [sViewControllers objectForKey:key];

    if (nativeView != nil) {
        [nativeView close];
        [sViewControllers setValue:nil forKey:key];
    } else {
        NSLog(@"There is no view with key: %@", key);
    }
}

@end