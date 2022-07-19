// SigndReactnativeSdk.m
#import <React/RCTBridgeModule.h>

@interface RCT_EXTERN_MODULE(SigndReactnativeSdk, NSObject)

RCT_EXTERN_METHOD(initialize:(NSDictionary)*data
                resolver:(RCTPromiseResolveBlock)resolver
                rejecter:(RCTPromiseRejectBlock)rejecter)

RCT_EXTERN_METHOD(start:(NSString *)sessionToken
                resolver:(RCTPromiseResolveBlock)resolver
                rejecter:(RCTPromiseRejectBlock)rejecter)

@end
