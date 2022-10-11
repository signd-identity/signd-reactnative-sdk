package id.signd.reactnative

import android.app.Activity
import android.content.Intent
import android.net.Uri
import android.util.Log
import com.facebook.react.bridge.*

import id.signd.core.feature.procesexecution.domain.VerificationResult
import id.signd.core.feature.signd.ProgressBarStyle
import id.signd.core.feature.signd.Signd
import id.signd.core.feature.signd.VerificationFinishedListener
import id.signd.core.feature.start.SigndActivity

class SigndReactnativeSdk(reactContext: ReactApplicationContext) : ReactContextBaseJavaModule(reactContext),
  VerificationFinishedListener {
  override fun getName() = "SigndReactnativeSdk"

  private var signdPromise: Promise? = null

  private var scheme: String = ""
  private var host: String = "session"
  private var url: String = ""


  private val onSigndActivityResult =
    object : BaseActivityEventListener() {
      override fun onActivityResult(
        activity: Activity?,
        requestCode: Int,
        resultCode: Int,
        data: Intent?
      ) {
        if (requestCode == REQUEST_CODE) {
          signdPromise?.let { promise ->
            when (resultCode) {
              Activity.RESULT_CANCELED -> {
                Log.v(this.javaClass.simpleName, "Result canceled")
                promise.reject(E_CANCELED, "Result canceled")
              }
              Activity.RESULT_OK -> {
                val result: VerificationResult =
                  data?.getSerializableExtra(SigndActivity.VERIFICATION_RESULT) as VerificationResult
                promise.resolve(result.toJson())
              }
              else -> Log.v(this.javaClass.simpleName, "Result: $resultCode")
            }
          }

          signdPromise = null
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
      return promise.reject(
        E_ARGUMENTS_NULL_EMPTY,
        "Arguments 'scheme', 'host', 'url' must not be null or empty!"
      )
    }

    Signd.setApiUrl(url)
      .setHost(host)
      .setScheme(scheme)
      .addPlugins(id.signd.scanid.ScanIdPlugin, id.signd.scanidregula.ScanIdRegulaPlugin)
      .setVerificationFinishedListener(this)
      .withUiSettings {
        this.showFooter = readableMap.getOptionalBoolean(ARG_SHOW_FOOTER, true)
        this.showLastScreen = readableMap.getOptionalBoolean(ARG_SHOW_LAST_SCREEN, true)
        this.showStartScreen = readableMap.getOptionalBoolean(ARG_SHOW_START_SCREEN, false)
        this.showBackButton = readableMap.getOptionalBoolean(ARG_SHOW_BACK_BUTTON, false)
        this.showCloseButton = readableMap.getOptionalBoolean(ARG_SHOW_CLOSE_BUTTON, false)
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
      promise.reject(E_SESSION_TOKEN_IS_NULL, "sessionToken is null or blank!")
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

    signdPromise = promise

    activity.startActivityForResult(
      SigndActivity.createLaunchIntent(
        reactApplicationContext.baseContext,
        uri
      ), REQUEST_CODE
    )
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
    signdPromise?.resolve(result.toJson())
  }

  companion object {
    private const val SESSION_TOKEN = "sessionToken"
    private const val REQUEST_CODE = 1

    private const val E_ACTIVITY_DOES_NOT_EXIST = "E_ACTIVITY_DOES_NOT_EXIST"
    private const val E_SESSION_TOKEN_IS_NULL = "E_SESSION_TOKEN_IS_NULL"
    private const val E_ARGUMENTS_NULL_EMPTY = "E_ARGUMENTS_NULL_EMPTY"
    private const val E_CANCELED = "E_CANCELED"

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

fun ReadableMap.getOptionalBoolean(key: String, default: Boolean): Boolean {
  return if (this.hasKey(key)) this.getBoolean(key) else default
}
