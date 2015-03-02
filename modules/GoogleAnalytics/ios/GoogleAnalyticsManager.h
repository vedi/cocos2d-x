//
// Created by Fedor Shubin on 7/1/13.
//

#import <Foundation/Foundation.h>

@interface GoogleAnalyticsManager : NSObject
+ (void)init: (NSDictionary *)params;
+ (void)sendEventWithCategory:(NSString *)category withAction:(NSString *)action withLabel:(NSString *)label withValue:(NSNumber *)value;
+ (void)sendView: (NSString*)viewName;
@end