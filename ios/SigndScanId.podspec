Pod::Spec.new do |s|

s.platform = :ios
s.ios.deployment_target = '11.0'
s.name         = "SigndScanId"
s.version      = "0.15.0"
s.summary      = "Summary"
s.description  = "Description"
s.homepage     = "https://signd.com"
s.author       = { "Signd Inc" => "office@signd.id" }
s.vendored_frameworks = "EmbeddedFrameworks/SigndScanId.xcframework"
s.resource_bundles = {
   'SigndScanId' => ['EmbeddedFrameworks/SigndScanId.xcframework/ios-arm64/SigndScanId.framework/*.{storyboard,xib,xcassets,mp4,otf,ttf}']
 }
s.source = { :git => '' }
s.dependency 'SigndCore', '= 0.15.0'
end
