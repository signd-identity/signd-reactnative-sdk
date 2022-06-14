// SigndReactnativeSdkViewManager.m
#import <React/RCTBridgeModule.h>

@interface RCT_EXTERN_MODULE(SigndReactnativeSdkViewManager, NSObject)

RCT_EXTERN_METHOD(initialize:(NSDictionary)*data
                resolver:(RCTPromiseResolveBlock)resolve
                rejecter:(RCTPromiseRejectBlock)reject)
RCT_EXTERN_METHOD(start:(NSString *)sessionToken
                resolver:(RCTPromiseResolveBlock)resolve
                rejecter:(RCTPromiseRejectBlock)reject)

@end