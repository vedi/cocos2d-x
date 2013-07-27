//
// Created by Fedor Shubin on 7/1/13.
//

#import <Foundation/Foundation.h>

#import "NativeViewFactory.h"

#define WEB_VIEW_KEY @"WEB_VIEW_KEY"

@interface NativeViewManager : NSObject
+ (void)init;
+ (void)addFactory:(id <NativeViewFactory>)factory forKey:(NSString *)viewKey;
+ (void)setViewController:(UIViewController *)viewController;

+ (void)createAndShowNativeWithKey:(NSString *)key viewParams:(NSDictionary *)viewParams viewData:(NSString *)viewData x:(NSNumber *)x y:(NSNumber *)y w:(NSNumber *)w h:(NSNumber *)h;
+ (void)nativeSendMessage:(NSString *)key messageData:(NSString *)messageData;
+ (void)closeNative:(NSString *)key;
@end