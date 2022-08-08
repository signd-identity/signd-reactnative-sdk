#import <Foundation/Foundation.h>
#import "RGLDocumentReaderResults.h"

@class RGLDocumentReaderTextField;

NS_SWIFT_NAME(DocumentReaderTextResult)
@interface RGLDocumentReaderTextResult : NSObject

/**
 An array of textual results
 */
@property(nonatomic, strong, readonly, nonnull) NSArray <RGLDocumentReaderTextField *> *fields;
/**
 Textual fields check result, one of RGLCheckResult values
 */
@property(nonatomic, assign, readonly) RGLCheckResult status;

- (instancetype _Nonnull)init NS_UNAVAILABLE;
- (instancetype _Nonnull)initWithJSON:(NSDictionary *_Nonnull)json;
+ (instancetype _Nonnull)initWithJSON:(NSDictionary * _Nonnull)json;
- (NSDictionary *_Nonnull)jsonDictionary;
- (void)sortByFieldType:(BOOL)desc;

@end
