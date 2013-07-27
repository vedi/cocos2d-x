//
//  iHasApp.m
//  iHasApp
//
//  Created by Daniel Amitay on 10/21/12.
//  Copyright (c) 2012 Daniel Amitay. All rights reserved.
//

#import "iHasApp.h"

@implementation iHasApp

@synthesize country = _country;
@synthesize appSchemesDictionaryName = _appSchemesDictionaryName;
@synthesize appSchemesDictionaryUrl = _appSchemesDictionaryUrl;

#pragma mark - Public methods

- (void)detectAppIdsWithIncremental:(void (^)(NSArray *appIds))incrementalBlock
                        withSuccess:(void (^)(NSArray *appIds))successBlock
                        withFailure:(void (^)(NSError *error))failureBlock {
    dispatch_queue_t detection_thread = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    dispatch_async(detection_thread, ^{
        
        [self retrieveSchemeAppsDictionaryWithSuccess:^(NSDictionary *schemeAppsDictionary) {
            NSMutableArray *schemeDictionaries = [[[NSMutableArray alloc] init] autorelease];
            for (NSString *scheme in schemeAppsDictionary.allKeys) {
                NSArray *appIds = [schemeAppsDictionary objectForKey:scheme];
                NSDictionary *schemeDictionary = @{@"scheme" : scheme, @"ids" : appIds};
                [schemeDictionaries addObject:schemeDictionary];
            }
            
            __block BOOL successBlockExecuted = FALSE;
            NSMutableSet *successfulAppIds = [[NSMutableSet alloc] init];
            NSOperationQueue *operationQueue = [[NSOperationQueue alloc] init];
            NSArray *arrayOfArrays =  [self subarraysOfArray:schemeDictionaries withCount:1000];
            for (NSArray *schemeDictionariesArray in arrayOfArrays) {
                [operationQueue addOperationWithBlock: ^{
                    NSMutableSet *incrementalAppIds = [[NSMutableSet alloc] init];
                    for (NSDictionary *schemeDictionary in schemeDictionariesArray) {
                        NSString *scheme = [schemeDictionary objectForKey:@"scheme"];
                        NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"%@://", scheme]];
                        if([[UIApplication sharedApplication] canOpenURL:url]) {
                            NSArray *appIds = [schemeDictionary objectForKey:@"ids"];
                            for (NSString *appId in appIds) {
                                if (![successfulAppIds containsObject:appId]) {
                                    [successfulAppIds addObject:appId];
                                    [incrementalAppIds addObject:appId];
                                }
                            }
                        }
                    }
                    if (incrementalBlock && incrementalAppIds.count) {
                        dispatch_sync(dispatch_get_main_queue(), ^{
                            incrementalBlock(incrementalAppIds.allObjects);
                        });
                    }
                    /* Unhappy with this implementation */
                    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.1f * NSEC_PER_SEC),
                                   dispatch_get_main_queue(), ^{
                                       if (operationQueue.operationCount == 0 && successBlock && !successBlockExecuted) {
                                           successBlockExecuted = TRUE;
                                           successBlock(successfulAppIds.allObjects);
                                       }
                                   });
                }];
            }
        } failure:failureBlock];
        
    });
}

- (void)getAppSchemeWithAppId:(NSString *)appId
                  withSuccess:(void (^)(NSArray *))successBlock
                  withFailure:(void (^)(NSError *))failureBlock {
    dispatch_queue_t detection_thread = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    dispatch_async(detection_thread, ^{

        [self retrieveSchemeAppsDictionaryWithSuccess:^(NSDictionary *schemeAppsDictionary) {
            NSMutableArray *schemes = [[[NSMutableArray alloc] init] autorelease];
            for (NSString *scheme in schemeAppsDictionary.allKeys) {
                NSArray *appIds = [schemeAppsDictionary objectForKey:scheme];
                if ([appIds indexOfObject: appId] != NSNotFound) {
                    [schemes addObject:scheme];
                }
            }

            successBlock(schemes);
        } failure:failureBlock];

    });
}

- (void)detectAppDictionariesWithIncremental:(void (^)(NSArray *appDictionaries))incrementalBlock
                                 withSuccess:(void (^)(NSArray *appDictionaries))successBlock
                                 withFailure:(void (^)(NSError *error))failureBlock {
    __block BOOL successBlockExecuted = FALSE;
    __block BOOL appIdDetectionComplete = FALSE;
    __block NSInteger netAppIncrements = 0;
    NSMutableArray *successfulAppDictionaries = [[NSMutableArray alloc] init];
    [self detectAppIdsWithIncremental:^(NSArray *appIds) {
        netAppIncrements += 1;
        [self retrieveAppDictionariesForAppIds:appIds
                                   withSuccess:^(NSArray *appDictionaries) {
                                       [successfulAppDictionaries addObjectsFromArray:appDictionaries];
                                       incrementalBlock(appDictionaries);
                                       netAppIncrements -= 1;
                                       /* Unhappy with this implementation */
                                       dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.1f * NSEC_PER_SEC),
                                                      dispatch_get_main_queue(), ^{
                                                          if (appIdDetectionComplete &&
                                                              !netAppIncrements &&
                                                              successBlock &&
                                                              !successBlockExecuted) {
                                                              successBlockExecuted = TRUE;
                                                              successBlock(successfulAppDictionaries);
                                                          }
                                                      });
                                   } withFailure:^(NSError *error) {
                                       netAppIncrements -= 1;
                                       /* Unhappy with this implementation */
                                       dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.1f * NSEC_PER_SEC),
                                                      dispatch_get_main_queue(), ^{
                                                          if (appIdDetectionComplete &&
                                                              !netAppIncrements &&
                                                              successBlock &&
                                                              !successBlockExecuted) {
                                                              successBlockExecuted = TRUE;
                                                              successBlock(successfulAppDictionaries);
                                                          }
                                                      });
                                   }];
    } withSuccess:^(NSArray *appIds) {
        appIdDetectionComplete = TRUE;
    } withFailure:failureBlock];
}

- (void)retrieveAppDictionariesForAppIds:(NSArray *)appIds
                             withSuccess:(void (^)(NSArray *appDictionaries))successBlock
                             withFailure:(void (^)(NSError *error))failureBlock {
    dispatch_queue_t retrieval_thread = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    dispatch_async(retrieval_thread, ^{
        
        NSString *appString = [appIds componentsJoinedByString:@","];
        NSMutableString *requestUrlString = [[NSMutableString alloc] init];
        [requestUrlString appendFormat:@"http://itunes.apple.com/lookup"];
        [requestUrlString appendFormat:@"?id=%@", appString];
        if (self.country) {
            [requestUrlString appendFormat:@"&country=%@", self.country];
        }
        
        NSURLResponse *response = nil;
        NSError *connectionError = nil;
        NSMutableURLRequest *request = [[NSMutableURLRequest alloc] init];
        [request setURL:[NSURL URLWithString:requestUrlString]];
        [request setTimeoutInterval:20.0f];
        [request setCachePolicy:NSURLRequestReturnCacheDataElseLoad];
        NSData *result = [NSURLConnection sendSynchronousRequest:request
                                               returningResponse:&response
                                                           error:&connectionError];
        if (connectionError) {
            if (failureBlock) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    failureBlock(connectionError);
                });
            }
        } else {
            NSError *jsonError = nil;
            NSDictionary *jsonDictionary = [NSJSONSerialization JSONObjectWithData:result
                                                                           options:NSJSONReadingMutableLeaves
                                                                             error:&jsonError];
            if (jsonError) {
                if (failureBlock) {
                    dispatch_async(dispatch_get_main_queue(), ^{
                        failureBlock(jsonError);
                    });
                }
            } else {
                if (successBlock) {
                    NSArray *results = [jsonDictionary objectForKey:@"results"];
                    dispatch_async(dispatch_get_main_queue(), ^{
                        successBlock(results);
                    });
                }
            }
        }
    });
}

#pragma mark - Internal methods

- (void)retrieveSchemeAppsDictionaryWithSuccess:(void (^)(NSDictionary *schemeAppsDictionary))successBlock
                                        failure:(void (^)(NSError *error))failureBlock {
    [self retrieveSchemeAppsDictionaryFromLocalWithSuccess:successBlock failure:^(NSError *error) {
        [self retrieveSchemeAppsDictionaryFromWebWithSuccess:successBlock failure:failureBlock];
    }];
}

- (void)retrieveSchemeAppsDictionaryFromLocalWithSuccess:(void (^)(NSDictionary *schemeAppsDictionary))successBlock
                                                 failure:(void (^)(NSError *error))failureBlock {
    dispatch_queue_t retrieval_thread = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    dispatch_async(retrieval_thread, ^{
        
        NSBundle *selfBundle = [NSBundle bundleForClass:[self class]];
        NSString *appSchemesDictionaryPath = [selfBundle pathForResource: self.appSchemesDictionaryName ofType:@"json"];
        if (!appSchemesDictionaryPath) {
            if (failureBlock) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    failureBlock(nil);
                });
            }
        } else {
            NSError *dataError = nil;
            NSData *schemeAppsData = [NSData dataWithContentsOfFile:appSchemesDictionaryPath
                                                            options:NSDataReadingMappedIfSafe
                                                              error:&dataError];
            if (dataError) {
                if (failureBlock) {
                    dispatch_async(dispatch_get_main_queue(), ^{
                        failureBlock(dataError);
                    });
                }
            } else {
                NSError *jsonError = nil;
                NSDictionary *schemeAppsDictionary = [NSJSONSerialization JSONObjectWithData:schemeAppsData
                                                                                     options:NSJSONReadingMutableLeaves
                                                                                       error:&jsonError];
                if (jsonError) {
                    if (failureBlock) {
                        dispatch_async(dispatch_get_main_queue(), ^{
                            failureBlock(jsonError);
                        });
                    }
                } else {
                    if (successBlock) {
                        dispatch_async(dispatch_get_main_queue(), ^{
                            successBlock(schemeAppsDictionary);
                        });
                    }
                }
            }
        }
    });
}

- (void)retrieveSchemeAppsDictionaryFromWebWithSuccess:(void (^)(NSDictionary *schemeAppsDictionary))successBlock
                                               failure:(void (^)(NSError *error))failureBlock {
    dispatch_queue_t retrieval_thread = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    dispatch_async(retrieval_thread, ^{
        
        NSURLResponse *response = nil;
        NSError *connectionError = nil;
        NSMutableURLRequest *request = [[NSMutableURLRequest alloc] init];
        [[NSURLCache sharedURLCache] setMemoryCapacity:1024*1024*2];
        [request setCachePolicy:NSURLRequestReturnCacheDataElseLoad];
        [request setURL:[NSURL URLWithString: self.appSchemesDictionaryUrl]];
        [request setTimeoutInterval:30.0f];
        NSData *result = [NSURLConnection sendSynchronousRequest:request
                                               returningResponse:&response
                                                           error:&connectionError];
        if (connectionError) {
            if (failureBlock) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    failureBlock(connectionError);
                });
            }
        } else {
            NSError *jsonError = nil;
            NSDictionary *schemeAppsDictionary = [NSJSONSerialization JSONObjectWithData:result
                                                                                 options:NSJSONReadingMutableLeaves
                                                                                   error:&jsonError];
            if (jsonError) {
                if (failureBlock) {
                    dispatch_async(dispatch_get_main_queue(), ^{
                        failureBlock(jsonError);
                    });
                }
            } else {
                if (successBlock) {
                    dispatch_async(dispatch_get_main_queue(), ^{
                        successBlock(schemeAppsDictionary);
                    });
                }
            }
        }
    });
}


#pragma mark - Helper methods

- (NSArray *)subarraysOfArray:(NSArray *)array withCount:(NSInteger)subarraySize {
    NSInteger rangeLocation = 0;
    NSInteger arrayCount = [array count];
    NSInteger itemsRemaining = [array count];
    NSMutableArray *arrayOfArrays = [[NSMutableArray alloc] init];
    while(rangeLocation < arrayCount) {
        NSInteger rangeLength = MIN(subarraySize, itemsRemaining);
        NSRange range = NSMakeRange(rangeLocation, rangeLength);
        NSArray *subarray = [array subarrayWithRange:range];
        [arrayOfArrays addObject:subarray];
        itemsRemaining -= rangeLength;
        rangeLocation += rangeLength;
    }
    return arrayOfArrays;
}

#pragma mark - Property methods

- (NSString *)country {
    if (!_country) {
        NSLocale *currentLocale = [NSLocale currentLocale];
        _country = [currentLocale objectForKey:NSLocaleCountryCode];
    }
    return _country;
}

- (NSString *)appSchemesDictionaryName {
    if (!_appSchemesDictionaryName) {
        _appSchemesDictionaryName = @"schemeApps";
    }
    return _appSchemesDictionaryName;
}

- (NSString *)appSchemesDictionaryUrl {
    if (!_appSchemesDictionaryUrl) {
        _appSchemesDictionaryUrl = @"https://ihasapp.herokuapp.com/api/schemeApps.json";
    }
    return _appSchemesDictionaryUrl;
}

- (void)dealloc {
    [_country release];
    [_appSchemesDictionaryName release];
    [_appSchemesDictionaryUrl release];
    [super dealloc];
}

@end
