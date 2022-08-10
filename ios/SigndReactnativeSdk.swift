// SigndReactnativeSdk.swift
import Foundation

import SigndCore
import SigndScanId
import SigndScanIdRegula
import SigndScanIdRegulaNative

@objc(SigndReactnativeSdk)
class SigndReactnativeSdk: NSObject, SigndDelegate {

    var resolve: RCTPromiseResolveBlock?
    var reject: RCTPromiseRejectBlock?
    
    var sessionToken: String?
    var result: String?

    @objc(initialize:resolver:rejecter:)
    func initialize(_ config:[String: String],
                resolver: @escaping (RCTPromiseResolveBlock),
                rejecter: @escaping (RCTPromiseRejectBlock)) {
        guard let scheme = config["scheme"] else {
            rejecter("Initialize failed", "No scheme", nil)
            return
        }

        Signd.shared.delegate = self

        var style:SGDStyle?

        let primaryColor = config["primaryColor"]
        let secondaryColor = config["secondaryColor"]
        let textPrimary = config["textPrimary"]
        let textSecondary = config["textSecondary"]
        let textHint = config["textHint"]
        let primaryBackgroundColor = config["primaryBackgroundColor"]
        let secondaryBackgroundColor = config["secondaryBackgroundColor"]

        if let primaryColor = primaryColor,
            let secondaryColor = secondaryColor,
            let textPrimary = textPrimary,
            let textSecondary = textSecondary,
            let textHint = textHint,
            let primaryBackgroundColor = primaryBackgroundColor,
            let secondaryBackgroundColor = secondaryBackgroundColor
        {
            style = SGDStyle(
                primaryColor: UIColor.hexStringToUIColor(hex: primaryColor),
                secondaryColor: UIColor.hexStringToUIColor(hex: secondaryColor),
                textPrimary: UIColor.hexStringToUIColor(hex: textPrimary),
                textSecondary: UIColor.hexStringToUIColor(hex: textSecondary),
                textHint: UIColor.hexStringToUIColor(hex: textHint),
                primaryBackgroundColor: UIColor.hexStringToUIColor(hex: primaryBackgroundColor),
                secondaryBackgroundColor: UIColor.hexStringToUIColor(hex: secondaryBackgroundColor)
            )
        }

        let regularFontFileName = config["regularFontFileName"]
        let boldFontFileName = config["boldFontFileName"]

        var fonts:SGDFontPack?

        if let regularFontFileName = regularFontFileName,
            let regularName = regularFontFileName.components(separatedBy: ".").first,
            let boldFontFileName = boldFontFileName,
            let boldName = boldFontFileName.components(separatedBy: ".").first
        {
            fonts = SGDFontPack(primaryRegular: SGDFont(name: regularName,
                                                            fileName: regularFontFileName,
                                                            bundle: Bundle.main),
                                    primarySemiBold: SGDFont(name: boldName,
                                                            fileName: boldFontFileName,
                                                            bundle: Bundle.main),
                                    secondaryRegular: SGDFont(name: regularName,
                                                            fileName: regularFontFileName,
                                                            bundle: Bundle.main),
                                    secondaryBold: SGDFont(name: boldName,
                                                            fileName: boldFontFileName,
                                                            bundle: Bundle.main))
        }

        let showLastScreen = config["showLastScreen"] == "true"
        let showFirstScreen = config["showFirstScreen"] == "true"
        let showBackButton = config["showBackButton"] == "true"
        let showCloseButton = config["showCloseButton"] == "true"
        let showFooter = config["showFooter"] == "true"
        let progressBarStyle = config["progressBarStyle"] ?? "Default"
        let actionButtonStyle = config["actionButtonStyle"] ?? "Round"

        let scanExampleAnimationFileName = config["scanExampleAnimationFileName"]
        var scanExampleAnimationUrl:URL?
        if let scanExampleAnimationName = scanExampleAnimationFileName?.components(separatedBy: ".").first,
            let scanExampleAnimationExtension = scanExampleAnimationFileName?.components(separatedBy: ".").last
        {
            scanExampleAnimationUrl = Bundle.main.url(forResource: scanExampleAnimationName, withExtension: scanExampleAnimationExtension)
        }

        let doneAnimationFileName = config["doneAnimationFileName"]
        var doneAnimationUrl:URL?
        if let doneAnimationName = doneAnimationFileName?.components(separatedBy: ".").first,
            let doneAnimationExtension = doneAnimationFileName?.components(separatedBy: ".").last
        {
            doneAnimationUrl = Bundle.main.url(forResource: doneAnimationName, withExtension: doneAnimationExtension)
        }
        
        let buttonImageName = config["buttonImage"] ?? ""
        let buttonUIImage = UIImage(named: buttonImageName)

        let options =  SGDOptions(
            style: style,
            fontPack: fonts,
            showBackButton: showBackButton,
            hideLastScreen: !showLastScreen,
            hideFirstScreen: !showFirstScreen,
            hideCloseButton: !showCloseButton,
            hideFooter: !showFooter,
            buttonImage: buttonUIImage,
            progressBarStyle: progressBarStyle == "Default" ? .dots : .linear,
            actionButtonStyle: actionButtonStyle == "Round" ? .round : .rounded,
            scanExampleAnimationUrl: scanExampleAnimationUrl,
            doneAnimationUrl: doneAnimationUrl
        )

        DispatchQueue.main.async {
            Signd.shared.initialize(
                processes: [
                    SigndScanIdProccess(processes: [RegulaNativeProccess()])
                ],
                options:options
            )
            Signd.shared.setScheme(scheme: scheme)

            if let apiUrl = config["apiUrl"] {
                print(apiUrl)
                Signd.shared.setApiUrl(url: apiUrl)
            }

            resolver(nil)
        }
    }
    @objc(start:resolver:rejecter:)
    func start(_ sessionToken: String,
                resolver: @escaping (RCTPromiseResolveBlock),
                rejecter: @escaping (RCTPromiseRejectBlock)) {
        if sessionToken.isEmpty {
            rejecter("Start failed", "No sessionToken", nil)
            return
        }
        self.resolve = resolver
        self.reject = rejecter
        self.result = nil

        DispatchQueue.main.async {
            Signd.shared.start(sessionToken: sessionToken)
        }
    }

    public func onEvent(event: SGDEvent) {
        switch event {
        case .processAborted:
            resolve?([
                "result": "ProcessCanceled",
                "sessionToken": self.sessionToken ?? "undefined"
            ])
        case .processEnded:
            resolve?([
                "result": self.result ?? "undefined" ,
                "sessionToken": self.sessionToken ?? "undefined"
            ])
        default:
            break
        }
    }

    public func onDone(results: [SGDPluginResultData], responseCode: ExecutionResponseCode?) {
        guard let responseCode = responseCode else {
            return
        }
        if responseCode == .EXECUTION_LOCKED {
            self.result = "ProcessInProgress"
        }
        if responseCode == .EXECUTION_LOCKED_WAIT {
            self.result = "ProcessInProgress"
        }
        if responseCode == .EXECUTION_LOCKED_WAIT_AND_LISTEN {
            self.result = "ProcessInProgress"
        }
        if responseCode == .PROCESS_DONE {
            self.result = "ProcessFinished"
        }
        if responseCode == .PROCESS_DONE_ON_DEVICE {
            self.result = "ProcessInProgress"
        }
        if responseCode == .PROCESS_DONE_ON_DEVICE_REDIRECT{
            self.result = "ProcessInProgress"
        }
        if responseCode == .REDIRECT_TO_DEVICE {
            self.result = "ProcessInProgress"
        }
        if responseCode == .PROCESS_FAILED {
            self.result = "ProcessFailed"
        }
    }

    public func onError(text: String, domain: String?, sessionToken: String?) {
        reject?(text, domain, nil)
    }

    public func onAuthFailed() {
        reject?("Auth failed", "auth failed", nil)
    }

    public func onSessionTokenChange(sessionToken: String?) {}

    public func onAuthSuccess(response: SGDLoginResponse?, sessionToken: String?) {}
    
    @objc
    static func requiresMainQueueSetup() -> Bool {
        return true
    }
}
