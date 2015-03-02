//
// Created by Fedor Shubin on 7/1/13.
//


#import <Foundation/Foundation.h>

@protocol NativeViewProtocol;

@protocol NativeViewFactory <NSObject>
- (UIViewController *)createNativeViewWithParams:(NSDictionary *)viewParams viewData:(NSString *)viewData;
@end