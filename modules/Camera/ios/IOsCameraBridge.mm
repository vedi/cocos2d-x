//
// Created by Alexandr on 30.10.13.
//


#import "IOsCameraBridge.h"
#import "IOSNDKHelper.h"


@implementation IOsCameraBridge {

}

+ (NSObject *)dispatchNDKCall:(NSDictionary *)parameters {
    NSString *methodName = [parameters objectForKey:@"method"];

    NSMutableDictionary *retParameters = [NSMutableDictionary dictionary];
    if ([methodName isEqualToString:@"getPhoto"]) {
        NSString *imagesPath = (NSString*)[parameters objectForKey:@"imagesPath"];
        CCLOG("Camera work");
        //TODO implement camera work here
    }
    else if ([methodName isEqualToString:@"getPhotoFromGallery"]) {
        NSString *imagesPath = (NSString*)[parameters objectForKey:@"imagesPath"];
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