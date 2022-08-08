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

  s.platforms    = { :ios => "14.0" }
  s.source       = { :git => "https://github.com/signd-identity/signd-reactnative-sdk.git", :tag => "#{s.version}" }
  s.vendored_frameworks = 'ios/EmbeddedFrameworks/**'
  s.source_files = "ios/*.{swift,h,m,c,cc,mm,cpp}"
  
  s.dependency "React-Core"
  s.dependency 'FaceSDK', '= 3.2.1078'
end
