//
// Created by Fedor Shubin on 8/8/13.
//


#import <Foundation/Foundation.h>


@interface AddThisManager : NSObject

+ (void)init:(NSDictionary *)initParams;
+ (void)shareText:(NSString *)text toService:(NSString *)serviceName;
+ (void)shareUrl:(NSString *)urlStr withTitle:(NSString *)title toService:(NSString *)serviceName;
+ (void)shareImage:(NSString *)imageStr withTitle:(NSString *)title toService:(NSString *)serviceName;
+ (void)shareWithTitle:(NSString *)title withText:(NSString *)text withUrl:(NSString *)urlStr withImage:(NSString *)imageStr toService:(NSString *)serviceName;
@end