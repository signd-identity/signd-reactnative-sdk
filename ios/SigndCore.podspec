Pod::Spec.new do |s|

s.platform = :ios
s.ios.deployment_target = '11.0'
s.name         = "SigndCore"
s.version      = "0.15.0"
s.summary      = "Summary"
s.description  = "Description"
s.homepage     = "https://signd.com"
s.author       = { "Signd Inc" => "office@signd.id" }
s.vendored_frameworks = "EmbeddedFrameworks/SigndCore.xcframework"
s.resource_bundles = {
   'SigndCore' => ['EmbeddedFrameworks/SigndCore.xcframework/ios-arm64/SigndCore.framework/*.{storyboard,xib,xcassets,mp4,otf,ttf}']
 }
s.source = { :git => '' }
end
