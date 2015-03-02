//
// Created by Fedor Shubin on 7/1/13.
//


#import <Foundation/Foundation.h>

@protocol NativeViewProtocol <NSObject>
- (void)sendMessageToView:(NSString *)message;
- (void)close;
@end