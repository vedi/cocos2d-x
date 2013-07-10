//
//  WebViewController.m
//  jumper
//
//  Created by Fedor Shubin on 12/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "WebViewController.h"

#import "NativeViewBridge.h"

@implementation WebViewController {
}
@synthesize data = _data;


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];

    NSString *urlAddress = [[NSString stringWithUTF8String:[_data UTF8String]]
            stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];

    NSURL *url = [NSURL URLWithString:urlAddress];

    NSURLRequest *requestObj = [NSURLRequest requestWithURL:url];

    [[_webView scrollView] setBounces:NO];
    //Load the request in the UIWebView.
    [_webView loadRequest:requestObj];
    [_webView setDelegate:self];
}

- (void)viewDidUnload
{
    [self setWebView:nil];
    [self setCloseButton:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType {
    // Intercept custom location change, URL begins with "js-call:"
    NSString *requestString = [[request URL] absoluteString];
    if ([requestString hasPrefix:@"js-call:"]) {
        // Extract the selector name from the URL
        NSArray *components = [requestString componentsSeparatedByString:@":"];
        NSString *data = [components objectAtIndex:1];
        // Call the given selector
        [self jsCallBack: data];
        // Cancel the location change
        return NO;
    } else {
        return YES;
    }
}

- (void)webViewDidStartLoad:(UIWebView *)webView {

}

- (void)webViewDidFinishLoad:(UIWebView *)webView {

}

- (void)setParams:(NSDictionary *)params {
    _params = params;
    if ([params objectForKey:@"backgroundColor"]) {
        NSString *colorStr = [params objectForKey:@"backgroundColor"];
        NSArray *colorArr = [colorStr componentsSeparatedByString:@","];
        _webView.backgroundColor = [UIColor
                colorWithRed:[[colorArr objectAtIndex:0] floatValue]
                       green:[[colorArr objectAtIndex:1] floatValue]
                        blue:[[colorArr objectAtIndex:2] floatValue]
                       alpha:[[colorArr objectAtIndex:3] floatValue]];
    } else {
//        _webView.backgroundColor = [UIColor clearColor];
    }
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error {
    NSLog(@"Cannot load webview with error: %@", error);
}

- (void)jsCallBack:(NSString *)data {
    NSString *normalizedData = [data stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    NSLog(@"call from JS in iOS: %@", normalizedData);
    NSError *error = nil;
    NSDictionary *dict = [NSJSONSerialization
            JSONObjectWithData:[normalizedData
                    dataUsingEncoding:NSUTF8StringEncoding]
            options:NSJSONReadingMutableContainers
            error:&error];

    if (error != nil)
        return;

    [NativeViewBridge dispatchNDKCallback:WEB_VIEW_KEY withParameters:dict];
}


- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}


- (IBAction)close:(id)sender {

    [[self view] removeFromSuperview];

    [NativeViewBridge dispatchNDKCallback:WEB_VIEW_KEY withParameters:nil];

    [self release];
//    [self dismissViewControllerAnimated:NO completion:nil];
}

- (void)sendMessageToView:(NSString *)message {
    NSLog(@"Try to pass message to JS: %@", message);

    NSData *jsonData = [message dataUsingEncoding:NSUTF8StringEncoding];
    //parse out the json data
    NSError* error = nil;
    NSDictionary* json = [NSJSONSerialization
            JSONObjectWithData:jsonData
                       options:kNilOptions
                         error:&error];
    if (!error) {
        NSString *event = [json objectForKey:@"event"];
        if (event) {
            if([event isEqualToString:@"onSettings"] || [event isEqualToString:@"onBuy"]) {
                [[self view] setHidden:YES];
            }
            else if([event isEqualToString:@"onCloseSettings"] || [event isEqualToString:@"onCloseBuy"]) {
                [[self view] setHidden:NO];
            }
            else if([event isEqualToString:@"onSettingsChanged"]) {
                NSNumber *notificationsOn = (NSNumber *) [json objectForKey:@"notificationsOn"];
                if (notificationsOn != nil) {
                    if (notificationsOn.boolValue == YES) {
                        [[UIApplication sharedApplication] registerForRemoteNotificationTypes: UIRemoteNotificationTypeBadge |
                                UIRemoteNotificationTypeAlert |
                                UIRemoteNotificationTypeSound];
                    } else {
                        [[UIApplication sharedApplication] unregisterForRemoteNotifications];
                    }
                }
            }
        }
    } else {
        NSLog(@"Error happened: %@", error);
    }
    NSString *jsCode = [NSString stringWithFormat:@"nativeCallBack(JSON.parse('%@'))", message];
    [_webView stringByEvaluatingJavaScriptFromString:jsCode];
}

- (void)close {
    [self close:nil];
}


- (void)dealloc {
    [_data release];
    [_webView release];
    [_closeButton release];
    [super dealloc];
}

@end
