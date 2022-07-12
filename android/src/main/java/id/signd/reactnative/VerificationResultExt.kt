package id.signd.reactnative

import id.signd.core.feature.procesexecution.domain.*
import com.facebook.react.bridge.*

internal fun VerificationResult.toJson(): WritableMap {
  val resultData = WritableNativeMap()

  val result = when (this) {
    is ProcessCanceled -> "ProcessCanceled"
    is ProcessFailed -> "ProcessFailed"
    is ProcessFinished -> "ProcessFinished"
    is ProcessInProgress -> "ProcessInProgress"
  }

  resultData.putString("sessionToken", this.sessionToken);
  resultData.putString("result", result);
  return resultData
}
