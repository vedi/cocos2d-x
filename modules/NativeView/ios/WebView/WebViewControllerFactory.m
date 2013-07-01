//
// Created by Fedor Shubin on 7/1/13.
//


#import "WebViewControllerFactory.h"
#import "WebViewController.h"


@implementation WebViewControllerFactory {

}

- (id) init {
    if (self = [super init]) {
        return self;
    } else {
        return nil;
    }
}

- (UIViewController *)createNativeView:(NSString *)viewData {
    WebViewController *viewController = [[WebViewController alloc]
            initWithNibName:@"WebViewController" bundle:nil];

    viewController.data = viewData;

    return viewController;
}

@end