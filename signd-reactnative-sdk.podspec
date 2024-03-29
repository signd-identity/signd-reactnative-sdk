require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))
folly_version = '2021.06.28.00-v2'
folly_compiler_flags = '-DFOLLY_NO_CONFIG -DFOLLY_MOBILE=1 -DFOLLY_USE_LIBCPP=1 -Wno-comma -Wno-shorten-64-to-32'

Pod::Spec.new do |s|
  s.name         = "signd-reactnative-sdk"
  s.version      = package["version"]
  s.summary      = package["description"]
  s.homepage     = package["homepage"]
  s.license      = package["license"]
  s.authors      = package["author"]
  s.source       = { :git => "https://github.com/signd-identity/signd-reactnative-sdk.git", :tag => "#{s.version}" }
  s.vendored_frameworks = 'ios/EmbeddedFrameworks/**'
  s.source_files = "ios/*.{swift,h,m,c,cc,mm,cpp}"
  s.ios.deployment_target  = '13.0'
  
  s.dependency "React-Core"
  s.dependency 'FaceSDK', '= 3.2.1078'
  s.dependency 'DocumentReaderFull', '= 6.2.6012'
  s.dependency 'DocumentReader', '= 6.2.2441'
  s.dependency 'AcuantiOSSDKV11/AcuantImagePreparation', '= 11.5.7'
  s.dependency 'AcuantiOSSDKV11/AcuantFaceMatch', '= 11.5.7'
  s.dependency 'AcuantiOSSDKV11/AcuantHGLiveness', '= 11.5.7'
  s.dependency 'AcuantiOSSDKV11/AcuantDocumentProcessing', '= 11.5.7'
  s.dependency 'AcuantiOSSDKV11/AcuantPassiveLiveness', '= 11.5.7'
end
