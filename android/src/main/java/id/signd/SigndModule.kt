package id.signd

import android.app.Activity
import android.content.Intent
import android.net.Uri
import android.util.Log
import android.os.Bundle
import com.facebook.react.bridge.*

import id.signd.core.feature.procesexecution.domain.VerificationResult
import id.signd.core.feature.signd.ProgressBarStyle
import id.signd.core.feature.signd.Signd
import id.signd.core.feature.signd.VerificationFinishedListener
import id.signd.core.feature.start.SigndActivity

class SigndModule(reactContext: ReactApplicationContext) : ReactContextBaseJavaModule(reactContext),
  VerificationFinishedListener {
  override fun getName() = "SigndModule"

  private var signdPromise: Promise? = null

  private val TAG = this.javaClass.simpleName
  private var verbose = false
  private var scheme: String = ""
  private var host: String = "session"
  private var url: String = ""

  private fun log(message: String = "") {
    if (verbose) {
      Log.v(TAG, message)
    }
  }

  private val onSigndActivityResult =
    object : BaseActivityEventListener() {
      override fun onActivityResult(
        activity: Activity?,
        requestCode: Int,
        resultCode: Int,
        intent: Intent?
      ) {
        if (requestCode == CALLBACK_NAME) {
          signdPromise?.let { promise ->
            when (resultCode) {
              Activity.RESULT_OK -> {
                val verificationResult: VerificationResult =
                  intent?.data?.getSerializableExtra(SigndActivity.VERIFICATION_RESULT) as VerificationResult
                promise.resolve(verificationResult.toJson())
              }
            }

            signdPromise = null
          }
        }
      }
    }

  init {
    reactContext.addActivityEventListener(onSigndActivityResult)
  }

  @ReactMethod
  fun initialize(readableMap: ReadableMap, promise: Promise) {
    this.scheme = readableMap.getString(ARG_SCHEME) ?: ""
    this.host = readableMap.getString(ARG_HOST) ?: ""
    this.url = readableMap.getString(ARG_API_URL) ?: ""

    if (this.scheme.isBlank() || this.host.isBlank() || this.url.isBlank()) {
      promise.reject("Arguments 'scheme', 'host', 'url' must not be null or empty!")
      return
    }

    Signd.setApiUrl(url)
      .setHost(host)
      .setScheme(scheme)
      .addPlugins(id.signd.scanid.ScanIdPlugin)
      .setVerificationFinishedListener(this)
      .withUiSettings {
        this.showFooter = readableMap.getBoolean(ARG_SHOW_FOOTER) ?: true
        this.showLastScreen = readableMap.getBoolean(ARG_SHOW_LAST_SCREEN) ?: true
        this.showStartScreen = readableMap.getBoolean(ARG_SHOW_START_SCREEN) ?: true
        this.showBackButton = readableMap.getBoolean(ARG_SHOW_BACK_BUTTON) ?: false
        this.showCloseButton = readableMap.getBoolean(ARG_SHOW_CLOSE_BUTTON) ?: false
        this.progressBarStyle = when (readableMap.getString(ARG_PROGRESS_BAR_STYLE) ?: "Default") {
          "Linear" -> ProgressBarStyle.Linear
          else -> ProgressBarStyle.Default
        }
      }

    promise.resolve(null)
  }

  @ReactMethod
  fun start(sessionToken: String, promise: Promise) {
    if (sessionToken.isBlank()) {
      promise.reject("sessionToken is null or blank!")
      return
    }

    startWithSession(promise, sessionToken)
  }

  private fun launchSignd(promise: Promise, uri: Uri) {
    val activity = currentActivity

    if (activity == null) {
      promise.reject(E_ACTIVITY_DOES_NOT_EXIST, "Activity doesn't exist")
      return
    }

    signdPromise = promise;

    activity.startActivityForResult(SigndActivity.createLaunchIntent(context, uri), CALLBACK_NAME)
  }

  private fun startWithSession(promise: Promise, sessionToken: String) {
    val uri = Uri.Builder()
      .scheme(scheme)
      .authority(host)
      .appendQueryParameter(SESSION_TOKEN, sessionToken)
      .build()

    launchSignd(promise, uri)
  }

  override fun onVerificationFinished(result: VerificationResult) {
    val savedCall = getBridge().getSavedCall(CALLBACK_ID)
    savedCall?.resolve(result.toJson())
  }

  override fun saveInstanceState(): Bundle {
    val superState: Bundle = super.saveInstanceState()
    superState.putString(CALLBACK_ID, callbackId)
    log("saveInstanceState callbackId: $callbackId")
    return superState
  }

  override fun restoreState(state: Bundle?) {
    super.restoreState(state)
    callbackId = state?.getString(CALLBACK_ID)
    log("restored callbackId: $callbackId")
  }

  companion object {
    private const val SESSION_TOKEN = "sessionToken"
    private const val CALLBACK_NAME = 1
    private const val CALLBACK_ID = "callbackId"

    private const val E_ACTIVITY_DOES_NOT_EXIST = "E_ACTIVITY_DOES_NOT_EXIST"

    private const val ARG_SCHEME = "scheme"
    private const val ARG_HOST = "host"
    private const val ARG_API_URL = "apiUrl"

    private const val ARG_SHOW_FOOTER = "showFooter"
    private const val ARG_SHOW_LAST_SCREEN = "showLastScreen"
    private const val ARG_SHOW_START_SCREEN = "showFirstScreen"
    private const val ARG_SHOW_BACK_BUTTON = "showBackButton"
    private const val ARG_SHOW_CLOSE_BUTTON = "showCloseButton"
    private const val ARG_PROGRESS_BAR_STYLE = "progressBarStyle"
  }
}
