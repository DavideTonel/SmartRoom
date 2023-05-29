package com.example.smartroom.bluetooth

import android.annotation.SuppressLint
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothSocket
import android.util.Log
import com.example.smartroom.MY_TAG
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.coroutineScope
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import java.io.IOException
import java.io.InputStream
import java.io.OutputStream
import java.nio.charset.Charset
import java.util.UUID

class BluetoothConnectionManager(
    private val device: BluetoothDevice,
    private val bluetoothAdapter: BluetoothAdapter
) {
    private val uuid: UUID = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb")
    private var socket: BluetoothSocket? = null
    private var inputStream: InputStream? = null
    private var outputStream: OutputStream? = null


    private var connected: Boolean = false


    @SuppressLint("MissingPermission")
    fun connect() {
        socket = device.createRfcommSocketToServiceRecord(uuid)
        bluetoothAdapter.cancelDiscovery()

        Log.d("GG", "Socket connected: ${socket?.isConnected}")

        try {
            socket?.connect()
            inputStream = socket?.inputStream
            outputStream = socket?.outputStream
            connected = true

        } catch (e: IOException) {
            Log.e("GG", "FAILED CONNECTION")
            e.printStackTrace()
        }
    }

    fun disconnect() {
        try {
            inputStream?.close()
            outputStream?.close()
            socket?.close()
            connected = false
        } catch (e: IOException) {
            e.printStackTrace()
        }
    }

    fun isConnected(): Boolean {
        return connected
    }

    fun sendData(data: ByteArray) {
        Log.d(MY_TAG, "Send: ${data.toString()}")
        Thread {
            try {
                outputStream?.write(data)
                Log.d(MY_TAG, "message sent")
            } catch (e: IOException) {
                Log.d(MY_TAG, "Errore inviando")
                e.printStackTrace()
            }
        }.start()
    }

    fun receiveData(): ByteArray? {
        val bytes = ByteArray(1024)
        var index = 0

        var currentByte = inputStream?.read()?.toByte()
        if (currentByte != null) {
            bytes[index] = currentByte
            index++

            while (currentByte?.toInt()?.toChar() != '\n') {
                currentByte = inputStream?.read()?.toByte()
                if (currentByte != null) {
                    bytes[index] = currentByte
                    index++
                }
            }
            return bytes.copyOf(index)
        }
        return null
    }
}
