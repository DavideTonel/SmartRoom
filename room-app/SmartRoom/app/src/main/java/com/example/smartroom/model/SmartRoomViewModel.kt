package com.example.smartroom.model

import android.annotation.SuppressLint
import android.bluetooth.BluetoothDevice
import android.util.Log
import androidx.lifecycle.ViewModel
import com.example.smartroom.MY_TAG
import com.example.smartroom.bluetooth.BluetoothController
import kotlinx.coroutines.delay
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import org.json.JSONException
import org.json.JSONObject


const val TARGET_DEVICE_NAME = "room_controller"

class SmartRoomViewModel(): ViewModel() {
    private val _state = MutableStateFlow(SmartRoomUiState())
    val state: StateFlow<SmartRoomUiState> = _state.asStateFlow()

    private lateinit var bluetoothController: BluetoothController

    private var receivingThread: Thread? = null
    private var isReceiving = false



    fun setBluetoothController(bluetoothController: BluetoothController) {
        this.bluetoothController = bluetoothController
    }


    @SuppressLint("MissingPermission")
    fun isTargetDevice(device: BluetoothDevice): Boolean {
        if (device.name == TARGET_DEVICE_NAME) {
            return true
        }
        return false
    }

    fun isConnected(): Boolean {
        return bluetoothController.isConnected()
    }

    fun startSearchRoom() {
        bluetoothController.startDiscovery()
    }

    fun stopSearchRoom() {
        if (bluetoothController.isConnecting()) {
            bluetoothController.cancelDiscovery()
        }
    }

    fun connectToRoom(device: BluetoothDevice) {
        bluetoothController.connectToDevice(device)
        _state.update {
            it.copy(
                connected = bluetoothController.isConnected()
            )
        }
        if (isConnected()) {
            startListenForIncomingData()
        }
    }

    private fun startListenForIncomingData() {
        Log.d(MY_TAG, "start listen")
        receivingThread = Thread {
            isReceiving = true
            while (isReceiving) {
                if (isConnected()) {
                    updateRoomData()
                }
            }
        }
        receivingThread?.start()
    }

    fun stopListenForIncomingData() {
        if (isReceiving) {
            isReceiving = false
            try {
                receivingThread?.join()
            } catch (e: InterruptedException) {
                e.printStackTrace()
            }
        }
    }

    private fun updateRoomData() {
        val bytes = bluetoothController.receiveData()
        if (bytes != null) {

            // backup values
            var lightOn = _state.value.lightOn
            var blindOpenPercentage = _state.value.blindOpenPercentage
            var controlMode = _state.value.controlMode

            try {
                val json = JSONObject(String(bytes))

                if (json.has("lightOn")) {
                    lightOn = json.getInt("lightOn") == 1
                }
                if (json.has("blindOpenPercentage")) {
                    blindOpenPercentage = json.getInt("blindOpenPercentage")
                }
                if (json.has("controlMode")) {
                    controlMode = json.getString("controlMode")
                }

                _state.update {
                    it.copy(
                        lightOn = lightOn,
                        blindOpenPercentage = blindOpenPercentage,
                        controlMode = controlMode,
                    )
                }
            } catch (e:JSONException) {
                Log.d(MY_TAG, e.toString())
                e.printStackTrace()
            }
        }
    }

    fun switchMode() {
        Log.d(MY_TAG, "Toggle in viewModel")
        if (_state.value.controlMode == "AUTO") {
            bluetoothController.sendMessage("chmod MANUAL_BT\n")
        } else if (_state.value.controlMode == "MANUAL_BT") {
            bluetoothController.sendMessage("chmod AUTO\n")
        }
    }

    fun switchLight() {
        val json = JSONObject(
            "{ \"remoteLightOn\": ${if (_state.value.lightOn) 0 else 1} }"
        )
        var jsonString: String = json.toString()
        jsonString += "\n"
        bluetoothController.sendMessage(jsonString)
    }

    fun changeBlindOpenPercentage(openPercentage: Int) {
        val json = JSONObject(
            "{ \"remoteBlindOpenPercentage\": $openPercentage }"
        )
        var jsonString: String = json.toString()
        jsonString += "\n"
        bluetoothController.sendMessage(jsonString)
    }

    fun disconnect() {
        stopListenForIncomingData()
        stopSearchRoom()
        bluetoothController.disconnect()
    }
}
