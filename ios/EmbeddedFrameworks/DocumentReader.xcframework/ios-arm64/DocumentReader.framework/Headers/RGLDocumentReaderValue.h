#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "RGLDocumentReaderResults.h"

NS_SWIFT_NAME(DocumentReaderValue)
@interface RGLDocumentReaderValue : NSObject

/**
 Identifies zone whence data is extracted, one of RGLResultType values
 */
@property(nonatomic, assign, readonly) RGLResultType sourceType;
/**
 A value
 */
@property(nonatomic, strong, readonly, nonnull) NSString *value;
/**
 An original value
 */
@property(nonatomic, strong, readonly, nonnull) NSString *originalValue;
/**
 Field rectangular area coordinates on the image
 */
@property(nonatomic, assign, readonly) CGRect boundRect;
/**
 Verification result, one of RGLFieldVerificationResult values
 */
@property(nonatomic, assign, readonly) RGLFieldVerificationResult validity;
/**
 A comparison result of a textual field values where the key is one of RGLResultType values and the value is one of RGLFieldVerificationResult values
 */
@property(nonatomic, strong, readonly, nonnull) NSDictionary <NSNumber *, NSNumber *> *comparison;
/**
 An index of the document page whence the textual field is extracted
 */
@property(nonatomic, assign, readonly) NSInteger pageIndex;
/**
 Textual field recognition probability (0 - 100, %)
 */
@property(nonatomic, assign, readonly) NSInteger probability;

- (instancetype _Nonnull)init NS_UNAVAILABLE;
- (instancetype _Nonnull)initWithJSON:(NSDictionary *_Nonnull)json;
+ (instancetype _Nonnull)initWithJSON:(NSDictionary * _Nonnull)json;
- (NSDictionary *_Nonnull)jsonDictionary;

@end
