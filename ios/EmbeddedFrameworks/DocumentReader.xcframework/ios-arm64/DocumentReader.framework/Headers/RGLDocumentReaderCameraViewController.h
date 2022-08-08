#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "RGLScenario.h"
#import "RGLProcessParams.h"
#import "RGLCornerView.h"
#import "RGLPreviewView.h"
#import "RGLMaskView.h"
#import "RGLActivityIndicator.h"
#import "RGLDocumentView.h"
#import "RGLDocumentReaderResults.h"
#import "RGLImageQualityGroup.h"
#import "RGLDocumentPosition.h"
#import "RGLFunctionality.h"
#import "RGLCustomization.h"

#import <CoreMotion/CoreMotion.h>

typedef NS_ENUM(NSInteger, RGLCameraScanMode) {
    RGLCameraScanModeContinues,
    RGLCameraScanModeCapture
} NS_SWIFT_NAME(CameraScanMode);

typedef NS_ENUM(NSInteger, RGLTorchModeDevice) {
    RGLTorchModeDeviceClearScreen = 0,
    RGLTorchModeDeviceWhiteScreen  = 1
} NS_SWIFT_NAME(TorchModeDevice);

@class RGLDocumentReaderCameraViewController, RGLDocumentReaderResults;

typedef NS_ENUM(NSInteger, RGLCameraViewControllerAction) {
    RGLCameraViewControllerActionDone,
    RGLCameraViewControllerActionProcess,
    RGLCameraViewControllerActionCancel,
    RGLCameraViewControllerActionMorePagesAvailable,
    RGLCameraViewControllerBadLicense,
    RGLCameraViewControllerActionProcessWhiteFlashLight
} NS_SWIFT_NAME(CameraViewControllerAction);

typedef void (^RGLCameraViewControllerHandler)(RGLDocumentReaderCameraViewController * _Nullable controller,
                                            RGLCameraViewControllerAction action,
                                            RGLDocumentReaderResults * _Nullable results) NS_SWIFT_NAME(CameraViewControllerHandler);

@protocol RGLDocumentReaderCameraViewControllerDelegate <NSObject>

- (BOOL)didMotionControlEnabledInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (BOOL)didSkipFocusingFramesInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (BOOL)showCaptureButtonInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (BOOL)showChangeFrameSizeButtonInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (BOOL)showSwapCameraButtonInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (BOOL)showTorchButtonInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (BOOL)showCloseButtonInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (AVCaptureSessionPreset _Nullable)videoSessionPresetInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (BOOL)showLogoInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (BOOL)showHelpAnimationInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (BOOL)multipageProcessingInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (UIInterfaceOrientationMask)supportedOrientationsInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (void)startNewPageInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (BOOL)showStatusMessagesInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (BOOL)showResultMessagesInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (UIColor *_Nonnull)tintColorInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (UIColor *_Nonnull)resultStatusTextColorInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (UIFont *_Nullable)resultStatusTextFontInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (UIColor *_Nullable)resultStatusBackgroundColorInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (UIColor *_Nonnull)cameraFrameDefaultColorInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (UIColor *_Nonnull)cameraFrameActiveColorInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (CGFloat)cameraFrameBorderWidthInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (CGFloat)cameraFrameWidthOfssetInCameraController:(RGLDocumentReaderCameraViewController * _Nonnull)controller;
- (BOOL)cameraFrameHideInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (UIColor *_Nonnull)statusTextColorInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (UIFont *_Nullable)statusTextFontInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (UIColor *_Nonnull)statusBackgroundColorInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (UIColor *_Nullable)activityIndicatorViewColorInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (UIColor *_Nullable)skipMultipageButtonBackgroundColorInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (RGLCameraFrameShapeType)cameraFrameShapeTypeInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (CGFloat)cornerViewLineLengthInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (BOOL)showNextPageAnimationInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (BOOL)showMaskViewInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (RGLDocReaderFrame)cameraFrameSizeInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (RGLDocReaderFrame)defaultCameraFrameSizeInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (NSArray <NSNumber *> * _Nullable)barcodeTypesInCameraController:(RGLDocumentReaderCameraViewController * _Nonnull)controller;
- (AVCaptureDevicePosition)cameraPositionInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (BOOL)showSkipNextPageButtonInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (UIImage *_Nullable)helpAnimationImageInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (UIImage *_Nullable)multipageAnimationFrontImageInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (UIImage *_Nullable)multipageAnimationBackImageInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (CGFloat)statusPositionMultiplierInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (CGFloat)resultStatusPositionMultiplierInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (UIImage *_Nullable)borderBackgroundImageInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (BOOL)isUseAuthenticatorInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (NSString *_Nullable)btDeviceNameInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (NSString *_Nullable)cameraStatusInCameraController:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (CGFloat)cameraFrameVerticalPositionMultiplier:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (CGFloat)cameraFrameCornerRadius:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (CGFloat)cameraBorderAspectRatioPortrait:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (CGFloat)cameraBorderAspectRatioLandscape:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (BOOL)isShowCaptureButton:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (NSTimeInterval)showCaptureButtonDelayFromDetect:(RGLDocumentReaderCameraViewController *_Nonnull)controller;
- (NSTimeInterval)showCaptureButtonDelayFromStart:(RGLDocumentReaderCameraViewController *_Nonnull)controller;

@end

@class RGLDocumentReaderCameraViewControllerDelegate;

NS_SWIFT_NAME(DocumentReaderCameraViewController)
@interface RGLDocumentReaderCameraViewController : UIViewController

@property(nonatomic, assign) BOOL resultStatusLocked;

@property(readonly, nonatomic, assign) AVCaptureDevicePosition cameraPosition;
@property(nonatomic, assign) BOOL showHelpPopup;
@property(nonatomic, assign) BOOL helpAnimationShowed;
@property(nonatomic, assign) BOOL showResultMessages;
@property(nonatomic, assign) BOOL showStatusMessages;
@property(nonatomic, assign) BOOL recognizeWasInterrupted;
@property(nonatomic, assign) BOOL skipNextPageRecognition;
@property(nonatomic, assign) double motionRate;
@property(nonatomic, strong, nullable) NSString *cameraStatusString;

@property(nonatomic, strong, nullable) RGLDocumentReaderResults *latestResult;

@property (nonatomic, getter=isCameraControllerPresentedModally) BOOL cameraControllerPresentedModally;

@property(nonatomic, strong, nullable) RGLPreviewView *previewView;
@property(nonatomic, strong, nullable) UIButton *closeButton;
@property(nonatomic, strong, nullable) UIButton *flashButton;
@property(nonatomic, strong, nullable) UIButton *swapCameraButton;
@property(nonatomic, strong, nullable) UIButton *bleButton;
@property(nonatomic, strong, nullable) UIButton *batteryButton;
@property(nonatomic, strong, nullable) UILabel *statusLabel;
@property(nonatomic, strong, nullable) UIView *statusView;
@property(nonatomic, strong, nullable) UIButton *captureButton;
@property(nonatomic, strong, nullable) UIButton *skipMultipageButton;
@property(nonatomic, strong, nullable) UILabel *resultStatus;
@property(nonatomic, strong, nullable) UILabel *metadataLabel;
@property(nonatomic, strong, nullable) UIView *resultStatusView;
@property(nonatomic, strong, nullable) UIButton *frameSizeButton;
@property(nonatomic, strong, nullable) RGLMaskView *maskView;
@property(nonatomic, strong, nullable) UILabel *logoLabel;
@property(nonatomic, strong, nullable) UIImageView *logoImage;
@property(nonatomic, strong, nullable) RGLCornerView *borderView;
@property(nonatomic, strong, nullable) UIView *focusView;
@property(nonatomic, strong, nullable) UILabel *cameraUnavailableLabel;
@property(nonatomic, strong, nullable) RGLActivityIndicator *activityIndicator;
@property(nonatomic, strong, nullable) RGLDocumentView *multipageScaningView;
@property(nonatomic, strong, nullable) RGLDocumentView *helpAnimationView;
@property(nonatomic, strong, nullable) RGLDocumentView *hologramAnimationView;
@property(nonatomic, strong, nullable) UIImageView *borderPlaceholderImage;
@property(nonatomic, assign) BOOL barcodeEnabled;
@property(nonatomic, assign) BOOL faceEnabled;
@property(nonatomic, assign) RGLCameraScanMode cameraScanMode;
@property(nonatomic, strong, nullable) UILabel *customLabel;

@property(nonatomic, weak, nullable) id<RGLDocumentReaderCameraViewControllerDelegate> cameraViewControllerDelegate;
@property(nonatomic, strong, nullable) RGLCameraViewControllerHandler cameraViewControllerHandler;
@property(nonatomic, assign) BOOL recognitionIsActive;

@property(nonatomic, assign) BOOL showChangeFrameButton;

@property(nonatomic, assign) RGLDocReaderFrame currentCameraFrame;

- (void)closeTapped:(UIButton *_Nonnull)button;
- (void)flashTapped:(UIButton *_Nullable)button;
- (void)swapTapped:(UIButton *_Nonnull)button;
- (void)captureButtonTapped:(UIButton *_Nonnull)button;
- (void)skipMultipageTapped:(UIButton *_Nonnull)button;
- (void)changeFrameTapped:(UIButton *_Nonnull)button;
- (void)processParamChanged;
- (void)setHiddenForFlashButton:(BOOL)isHidden;
- (void)setHiddenForCloseButton:(BOOL)isHidden;
- (void)setHiddenForCaptureButton:(BOOL)isHidden;
- (void)setHiddenForSwapCameraButton:(BOOL)isHidden;
- (void)setVideoSessionPreset:(AVCaptureSessionPreset _Nonnull)sessionPreset;
- (void)setVideoZoomFactor:(CGFloat)videoZoomFactor;
- (void)setAVCaptureDevicePosition:(AVCaptureDevicePosition)cameraPosition;

- (void)notifyTintColorChanged;
- (void)notifyResultStatusTextColorChanged;
- (void)notifyResultStatusTextFontChanged;
- (void)notifyCameraFrameDefaultColorChanged;
- (void)notifyCameraFrameActiveColorChanged;
- (void)notifyStatusTextColorChanged;
- (void)notifyStatusTextFontChanged;
- (void)notifyStatusBackgroundColorChanged;
- (void)notifyShowStatusMessagesChanged;
- (void)notifyShowResultStatusMessagesChanged;
- (void)notifyCameraStatusChanged;
- (void)notifyCameraResultStatusChanged;
- (void)notifyCameraFrameShapeTypeChanged;
- (void)notifyMultipageButtonBackgroundColorChanged;
- (void)notifyCameraFrameBorderWidthChanged;
- (void)notifyActivityIndicatorColorChanged;
- (void)notifyResultStatusBackgroundColorChanged;
- (void)notifyCameraFrameLineLengthChanged;
- (void)notifyCameraFrameOffsetWidthChanged;
- (void)notifyShowBackgroundMaskChanged;
- (void)notifyBorderBackgroundImageChanged;
- (void)notifyBackgroundMaskAlphaChanged;
- (void)notifyMultipageAnimationFrontImageContentModeChanged;
- (void)notifyMultipageAnimationBackImageContentModeChanged;
- (void)notifyBorderBackgroundImageContentModeChanged;
- (void)notifyMultipageAnimationFrontImageChanged;
- (void)notifyMultipageAnimationBackImageChanged;
- (void)notifyCustomLabelStatusChanged;

- (void)closeCameraViewController:(void(^_Nullable)(void))completion;
    
@end
