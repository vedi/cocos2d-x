//
//  WebViewController.h
//  jumper
//
//  Created by Fedor Shubin on 12/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "NativeViewProtocol.h"

#define WEB_VIEW_KEY @"WEB_VIEW_KEY"

@interface WebViewController : UIViewController<NativeViewProtocol, UIWebViewDelegate>

- (void)sendMessageToView:(NSString *)message;
- (void)close;

- (IBAction)close:(id)sender;

@property (retain, nonatomic) IBOutlet UIWebView *webView;

@property (retain, nonatomic) IBOutlet UIButton *closeButton;

@property(nonatomic, copy) NSString *data;

@property(nonatomic, assign) NSDictionary *params;
@end
