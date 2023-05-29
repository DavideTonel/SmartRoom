package com.example.smartroom

import android.Manifest
import android.annotation.SuppressLint
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothManager
import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.content.IntentFilter
import android.os.Build
import android.os.Bundle
import android.util.Log
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.compose.setContent
import androidx.activity.result.contract.ActivityResultContracts
import androidx.activity.viewModels
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.Button
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import com.example.smartroom.bluetooth.BluetoothController
import com.example.smartroom.model.SmartRoomViewModel
import com.example.smartroom.ui.screen.PreviewDashboardScreen
import com.example.smartroom.ui.screen.SmartRoomScreen
import com.example.smartroom.ui.theme.SmartRoomTheme
import com.example.smartroom.util.askPermissions
import com.example.smartroom.util.askSinglePermission
import com.example.smartroom.util.enableLocation
import com.example.smartroom.util.isLocationEnabled

const val MY_TAG = "GG"

class MainActivity : ComponentActivity() {
    lateinit var bluetoothAdapter: BluetoothAdapter
    lateinit var bluetoothManager: BluetoothManager
    lateinit var bluetoothController: BluetoothController

    val viewModel: SmartRoomViewModel by viewModels()
    private val mReceiver = object : BroadcastReceiver() {
        @SuppressLint("MissingPermission")
        override fun onReceive(context: Context, intent: Intent) {
            when (intent.action) {
                BluetoothDevice.ACTION_FOUND -> {
                    val device =
                        intent.getParcelableExtra<BluetoothDevice>(BluetoothDevice.EXTRA_DEVICE)
                    if (device != null && device.name != null) {
                        Log.d(MY_TAG, "device name is " + device.name.toString())
                        if (viewModel.isTargetDevice(device)) {
                            viewModel.connectToRoom(device)
                        }

                    }
                }

                BluetoothAdapter.ACTION_DISCOVERY_FINISHED -> {
                    Log.i(MY_TAG, "ACTION_DISCOVERY_FINISHED")
                    if (!viewModel.isConnected()) {
                        Toast.makeText(
                            applicationContext,
                            "Target device not found",
                            Toast.LENGTH_SHORT
                        ).show()
                    } else {
                        Toast.makeText(applicationContext, "Target device found!", Toast.LENGTH_SHORT)
                            .show()
                    }
                }

                BluetoothAdapter.ACTION_STATE_CHANGED -> {
                    // Since app needs bluetooth to work correctly don't let the user turn it off
                    if (bluetoothAdapter.state == BluetoothAdapter.STATE_OFF
                    ) {
                        enableBluetooth()
                    }
                }
            }
        }
    }

    private val enableBluetoothResultLauncher = registerForActivityResult(
        ActivityResultContracts.StartActivityForResult()
    ) { result ->
        if (result.resultCode == RESULT_OK) {
            Toast.makeText(this, "Bluetooth Enabled!", Toast.LENGTH_SHORT).show()
        } else {
            Toast.makeText(this, "Bluetooth is required for this app to run", Toast.LENGTH_SHORT)
                .show()
            this.finish()
        }
    }

    /**
     * Pop-up activation for enabling Bluetooth
     *
     */
    private fun enableBluetooth() {
        val enableBtIntent = Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE)
        enableBluetoothResultLauncher.launch(enableBtIntent)
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        bluetoothManager = getSystemService(Context.BLUETOOTH_SERVICE) as BluetoothManager
        bluetoothAdapter = bluetoothManager.adapter

        if (!bluetoothAdapter.isEnabled) {
            enableBluetooth()
        }

        // This specific action is required since my personal mobile needs GPS enabled to discover devices
        // (not written in any official documentation but needed nonetheless)
        if (!isLocationEnabled(this) && Build.VERSION.SDK_INT <= 30) {
            Toast.makeText(
                this,
                "Location should be enabled since Location services are needed on some devices for correctly locating other Bluetooth devices",
                Toast.LENGTH_SHORT
            ).show()
            enableLocation(this)
        }

        // Register for broadcasts when a device is discovered
        val filter = IntentFilter()
        // register a broadcast receiver to check if the user disables his Bluetooth (or it has it already disabled)
        filter.addAction(BluetoothAdapter.ACTION_STATE_CHANGED)
        // receivers for device discovering
        filter.addAction(BluetoothDevice.ACTION_FOUND)
        filter.addAction(BluetoothAdapter.ACTION_DISCOVERY_FINISHED)
        registerReceiver(mReceiver, filter)

        bluetoothController =  BluetoothController(
            bluetoothAdapter
        )
        viewModel.setBluetoothController(bluetoothController)




        super.onCreate(savedInstanceState)
        setContent {
            SmartRoomTheme {
                // A surface container using the 'background' color from the theme
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    SmartRoomScreen(
                        roomViewModel = viewModel
                    )
                }
            }
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        viewModel.disconnect()
    }
}
