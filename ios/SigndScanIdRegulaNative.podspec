Pod::Spec.new do |s|

s.platform = :ios
s.ios.deployment_target = '11.0'
s.name         = "SigndScanIdRegulaNative"
s.version      = "0.15.0"
s.summary      = "Summary"
s.description  = "Description"
s.homepage     = "https://signd.com"
s.author       = { "Signd Inc" => "office@signd.id" }
s.vendored_frameworks = "EmbeddedFrameworks/SigndScanIdRegulaNative.xcframework"
s.resource_bundles = {
   'SigndScanIdRegulaNative' => ['EmbeddedFrameworks/SigndScanIdRegulaNative.xcframework/ios-arm64/SigndScanIdRegulaNative.framework/*.{storyboard,xib,xcassets,mp4,otf,ttf}']
 }
s.source = { :git => '' }
s.dependency 'SigndCore', '= 0.15.0'
s.dependency 'SigndScanId', '= 0.15.0'
s.dependency 'FaceSDK', '= 3.2.1078'
s.dependency 'DocumentReaderFull', '= 6.2.6012'
s.dependency 'DocumentReader', '= 6.2.2441'
end
