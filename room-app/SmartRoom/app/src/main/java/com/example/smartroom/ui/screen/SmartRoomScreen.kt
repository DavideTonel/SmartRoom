package com.example.smartroom.ui.screen

import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.ui.Modifier
import com.example.smartroom.model.SmartRoomViewModel

@Composable
fun SmartRoomScreen(
    roomViewModel: SmartRoomViewModel,
    modifier: Modifier = Modifier
) {
    val uiState by roomViewModel.state.collectAsState()
    if (!uiState.connected) {
        WelcomeScreen(
            onConnect = roomViewModel::startSearchRoom,
            modifier = modifier
        )
    } else {
        DashboardScreen(
            uiState = uiState,
            onSwitchModePress = roomViewModel::switchMode,
            onSwitchLightPress = roomViewModel::switchLight,
            onRollerblindSliderChangeFinished = roomViewModel::changeBlindOpenPercentage,
            modifier = modifier
        )
    }
}