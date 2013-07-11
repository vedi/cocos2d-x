//
// Created by Fedor Shubin on 7/1/13.
//

#import <Foundation/Foundation.h>

@interface HasAppManager : NSObject
+ (void)init: (NSDictionary *)initParams;
+ (void)hasApp:(NSString *)appId;

+ (void)openApp:(NSString *)appId;
@end