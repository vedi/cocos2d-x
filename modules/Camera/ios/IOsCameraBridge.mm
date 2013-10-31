//
// Created by Alexandr on 30.10.13.
//


#import "IOsCameraBridge.h"
#import "IOSNDKHelper.h"
#import "RootViewController.h"
#import "AppController.h"
#import "CameraViewController.h"

@implementation IOsCameraBridge {

}

+ (NSObject *)dispatchNDKCall:(NSDictionary *)parameters {
    NSString *methodName = [parameters objectForKey:@"method"];

    NSMutableDictionary *retParameters = [NSMutableDictionary dictionary];
    if ([methodName isEqualToString:@"getPhoto"]) {
        NSString *imagesPath = (NSString*)[parameters objectForKey:@"imagesPath"];
        if ([UIImagePickerController isSourceTypeAvailable:
             UIImagePickerControllerSourceTypeCamera])
        {
            UIImagePickerController *imagePicker = [[UIImagePickerController alloc] init];
            
            imagePicker.sourceType =
            UIImagePickerControllerSourceTypeCamera;
            imagePicker.allowsEditing = NO;
            CameraViewController *controller = [[CameraViewController alloc] init];
            //[controller setImagesPath:imagesPath];
            controller.imagesPath = imagesPath;
            RootViewController *rooViewController = ((AppController *)[UIApplication sharedApplication].delegate).viewController;
            imagePicker.delegate = controller;
            [rooViewController presentViewController:imagePicker animated:YES completion:nil];
            //[self presentModalViewController:imagePicker animated:YES];
            imagePicker = nil;
        }
        CCLOG("Camera work");
        //TODO implement camera work here
    }
    else if ([methodName isEqualToString:@"getPhotoFromGallery"]) {
        NSString *imagesPath = (NSString*)[parameters objectForKey:@"imagesPath"];
        
        UIImagePickerController *picker = [[UIImagePickerController alloc] init];
        picker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
        CameraViewController *controller = [[CameraViewController alloc] init];
        //[controller setImagesPath:imagesPath];
        controller.imagesPath = imagesPath;
        picker.delegate = controller;
        picker.allowsEditing = YES;
        RootViewController *rooViewController = ((AppController *)[UIApplication sharedApplication].delegate).viewController;
        [rooViewController presentModalViewController:picker animated:YES];
        //TODO implement gallery work here
        CCLOG("Gallery work");
       // NSString *key = [NSString stringWithUTF8String:"onPhotoWasTaken"];
       // NSDictionary *params = [NSDictionary ]  // only one parameter for dict string with key "photoFileName"
        //[IOsCameraBridge dispatchNDKCallback:key withParameters:params];
    }
    else {
        NSLog(@"Unsupported method %@", methodName);
    }
    return retParameters;
}

+ (void)dispatchNDKCallback:(NSString *)key withParameters:(NSDictionary *)parameters {
    [IOSNDKHelper sendMessage:key withParameters:parameters];
}


@end