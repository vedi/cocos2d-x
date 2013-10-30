//
// Created by Alexandr on 30.10.13.
//


#import <Foundation/Foundation.h>


@interface IOsCameraBridge : NSObject
+ (NSObject *)dispatchNDKCall:(NSDictionary *)parameters;
+ (void)dispatchNDKCallback:(NSString *)string withParameters:(NSDictionary *)parameters;
@end