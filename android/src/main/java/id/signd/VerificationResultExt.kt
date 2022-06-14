package id.signd

import id.signd.core.feature.procesexecution.domain.*
import org.json.JSONObject

internal fun VerificationResult.toJson(): JSONObject {
    val json = JSONObject()
    val result = when (this) {
        is ProcessCanceled -> "ProcessCanceled"
        is ProcessFailed -> "ProcessFailed"
        is ProcessFinished -> "ProcessFinished"
        is ProcessInProgress -> "ProcessInProgress"
    }
    json.put("sessionToken", this.sessionToken)
    json.put("result", result)
    return json
}