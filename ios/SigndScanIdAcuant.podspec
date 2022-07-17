Pod::Spec.new do |s|

s.platform = :ios
s.ios.deployment_target = '11.0'
s.name         = "SigndScanIdAcuant"
s.version      = "0.15.0"
s.summary      = "Summary"
s.description  = "Description"
s.homepage     = "https://signd.com"
s.author       = { "Signd Inc" => "office@signd.id" }
s.vendored_frameworks = "EmbeddedFrameworks/SigndScanIdAcuant.xcframework"
s.resource_bundles = {
   'SigndScanIdAcuant' => ['EmbeddedFrameworks/SigndScanIdAcuant.xcframework/ios-arm64/SigndScanIdAcuant.framework/*.{storyboard,xib,xcassets,mp4,otf,ttf}']
 }
s.source = { :git => '' }
s.dependency 'SigndCore', '= 0.15.0'
s.dependency 'SigndScanId', '= 0.15.0'
s.dependency 'AcuantiOSSDKV11/AcuantImagePreparation', '= 11.5.1'
s.dependency 'AcuantiOSSDKV11/AcuantFaceCapture', '= 11.5.1'
s.dependency 'AcuantiOSSDKV11/AcuantHGLiveness', '= 11.5.1'
s.dependency 'AcuantiOSSDKV11/AcuantIPLiveness', '= 11.5.1'
s.dependency 'AcuantiOSSDKV11/AcuantDocumentProcessing', '= 11.5.1'
s.dependency 'AcuantiOSSDKV11/AcuantPassiveLiveness', '= 11.5.1'
end
