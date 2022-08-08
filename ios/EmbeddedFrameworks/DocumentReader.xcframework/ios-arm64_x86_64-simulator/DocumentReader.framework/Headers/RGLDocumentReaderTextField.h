#import <Foundation/Foundation.h>
#import "RGLDocumentReaderResults.h"

@class RGLDocumentReaderValue;

NS_SWIFT_NAME(DocumentReaderTextField)
@interface RGLDocumentReaderTextField : NSObject

/**
 Textual field logical type, one of RGLFieldType values
 */
@property(nonatomic, assign, readonly) RGLFieldType fieldType;
/**
 Textual field symbolic name
 */
@property(nonatomic, strong, readonly, nonnull) NSString *fieldName;
/**
 ID of language-culture to differentiate one field of the same type from another (for example Belarus Passport Page # 31 – Belarusian and Russian fields of the same type), one of RGLLCID values
 */
@property(nonatomic, assign, readonly) RGLLCID lcid;
/**
 An array of values
 */
@property(nonatomic, strong, readonly, nonnull) NSArray <RGLDocumentReaderValue *> *values;
/**
 Textual field check result, one of RGLCheckResult values
 */
@property(nonatomic, assign, readonly) RGLCheckResult status;

- (RGLDocumentReaderValue *_Nullable)getValue;

- (instancetype _Nonnull)init NS_UNAVAILABLE;
- (instancetype _Nonnull)initWithFieldType:(RGLFieldType)fieldType;
- (instancetype _Nonnull)initWithFieldType:(RGLFieldType)fieldType lcid:(RGLLCID)lcid;
- (instancetype _Nonnull)initWithJSON:(NSDictionary *_Nonnull)json;
+ (instancetype _Nonnull)initWithJSON:(NSDictionary * _Nonnull)json;
- (NSDictionary *_Nonnull)jsonDictionary;

+ (NSString *_Nonnull)fieldTypeName:(RGLFieldType) fieldType;
+ (NSString *_Nonnull)lcidName:(RGLLCID) lcid;

@end
