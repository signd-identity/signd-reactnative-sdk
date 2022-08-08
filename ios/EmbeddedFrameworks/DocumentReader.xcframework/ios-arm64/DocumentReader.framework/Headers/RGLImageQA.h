//
//  RGLImageQA.h
//  DocumentReader
//
//  Created by Pavel Kondrashkov on 8/27/21.
//  Copyright © 2021 Regula. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RGLImageQA : NSObject

/// This parameter sets threshold for Image QA check of the presented document physical dpi.
/// If actual document dpi is below this threshold, check will fail.
/// Type: Integer.
@property (nonatomic, strong, nullable) NSNumber *dpiThreshold;

/// This parameter sets threshold for Image QA check of the presented document perspective angle in degrees.
/// If actual document perspective angle is above this threshold, check will fail.
/// Type: Integer.
@property (nonatomic, strong, nullable) NSNumber *angleThreshold;

/// This option disabled focus check during performing image quality validation.
/// Type: Bool.
@property (nonatomic, strong, nullable) NSNumber *focusCheck;

/// This option disabled glares check during performing image quality validation.
/// Type: Bool.
@property (nonatomic, strong, nullable) NSNumber *glaresCheck;

/// This option disabled colorness check during performing image quality validation.
/// Type: Bool.
@property (nonatomic, strong, nullable) NSNumber *colornessCheck;

/// This option disabled moire patterns check during performing image quality validation.
/// Type: Bool.
@property (nonatomic, strong, nullable) NSNumber *moireCheck;

@end

NS_ASSUME_NONNULL_END
