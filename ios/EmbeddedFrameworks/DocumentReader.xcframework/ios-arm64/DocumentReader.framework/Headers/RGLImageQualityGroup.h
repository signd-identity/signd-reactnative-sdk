#import <Foundation/Foundation.h>
#import "RGLDocumentReaderResults.h"

@class RGLImageQuality;

typedef NS_ENUM(NSInteger, RGLImageQualityCheckType) {
    /**
     Glares presence check
     */
    RGLEImageQualityCheckTypeImageGlares       = 0,
    /**
     Focus quality check
     */
    RGLEImageQualityCheckTypeImageFocus        = 1,
    /**
     Image resolution check
     */
    RGLEImageQualityCheckTypeImageResolution   = 2,
    /**
     Image colorness check
     */
    RGLEImageQualityCheckTypeImageColorness    = 3,
    /**
     Image perspective check, i.e. the deviation of the corners of the document from the value of 90 degrees is checked
     */
    RGLEImageQualityCheckTypeImagePerspective  = 4,
    /**
     Image quality check if the whole document page is completely within the image
     */
    RGLEImageQualityCheckTypeImageBounds       = 5,
    /**
     Image moire check
     */
    RGLEImageQualityCheckTypeScreenCapture       = 6,
    /**
     Portrait image check
     */
    RGLEImageQualityCheckTypePortrait       = 7
} NS_SWIFT_NAME(ImageQualityCheckType);

NS_SWIFT_NAME(ImageQualityGroup)
@interface RGLImageQualityGroup : NSObject

/**
 Number of results
 */
@property(nonatomic, assign, readonly) NSInteger count;
/**
 Overall check result for document page, one of RGLCheckResult values
 */
@property(nonatomic, assign, readonly) RGLCheckResult result;
/**
 An array of single check result pointers
 */
@property(nonatomic, strong, readonly, nonnull) NSArray <RGLImageQuality *> *imageQualityList;

/**
 Index of the document page, whence the result is received
 */
@property(nonatomic, assign, readonly) NSInteger pageIndex;

- (instancetype _Nonnull)init NS_UNAVAILABLE;
- (RGLCheckResult)getQualityResultWithType:(RGLImageQualityCheckType)type;
- (instancetype _Nonnull)initWithJSON:(NSDictionary *_Nonnull)json;
+ (instancetype _Nonnull)initWithJSON:(NSDictionary * _Nonnull)json;
- (NSDictionary *_Nonnull)jsonDictionary;

@end

