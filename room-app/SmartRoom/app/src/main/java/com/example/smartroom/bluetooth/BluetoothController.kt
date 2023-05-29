package com.example.smartroom.bluetooth

import android.annotation.SuppressLint
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothManager
import android.util.Log
import com.example.smartroom.MY_TAG
import com.example.smartroom.model.TARGET_DEVICE_NAME
import org.json.JSONException
import org.json.JSONObject
import java.nio.charset.Charset


class BluetoothController(
    private var bluetoothAdapter: BluetoothAdapter
) {
    private lateinit var connectionManager: BluetoothConnectionManager


    @SuppressLint("MissingPermission")
    fun startDiscovery() {
        bluetoothAdapter.startDiscovery()
    }

    @SuppressLint("MissingPermission")
    fun cancelDiscovery() {
        if (bluetoothAdapter.isDiscovering) {
            bluetoothAdapter.cancelDiscovery()
        }
    }

    fun connectToDevice(device: BluetoothDevice) {
        connectionManager = BluetoothConnectionManager(device, bluetoothAdapter)
        connectionManager.connect()
    }

    fun isConnected(): Boolean {
        return connectionManager.isConnected()
    }

    @SuppressLint("MissingPermission")
    fun isConnecting(): Boolean {
        return bluetoothAdapter.isDiscovering
    }

    fun sendMessage(message: String) {
        connectionManager.sendData(message.toByteArray())
    }

    fun receiveData(): ByteArray? {
        return connectionManager.receiveData()
    }

    fun disconnect() {
        connectionManager.disconnect()
    }
}
