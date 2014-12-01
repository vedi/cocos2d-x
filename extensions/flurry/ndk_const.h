//
// Created by Alexandr on 14.10.14.
//

#define EASY_NDK_METHOD flurry_easyNDK


#define NDK_BRIDGE(METHOD_NAME, BRIDGE_NAME) - (NSObject *)METHOD_NAME:(NSObject *)params {\
NSLog(@"METHOD_NAME call"); \
NSDictionary *parameters = (NSDictionary*) params; \
NSLog(@"Passed params are : %@", parameters); \
return [BRIDGE_NAME dispatchNDKCall:parameters]; \
}