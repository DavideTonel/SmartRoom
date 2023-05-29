package com.example.smartroom.ui.screen

import androidx.compose.foundation.BorderStroke
import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Slider
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import com.example.smartroom.model.SmartRoomUiState
import kotlin.math.round

@Composable
fun DashboardScreen(
    uiState: SmartRoomUiState,
    onSwitchModePress: () -> Unit,
    onSwitchLightPress: () -> Unit,
    onRollerblindSliderChangeFinished: (Int) -> Unit,
    modifier: Modifier = Modifier
) {
    var sliderPosition by remember {
        mutableStateOf(uiState.blindOpenPercentage.toFloat())
    }


    Column(
        modifier = modifier
            .fillMaxSize()
    ) {
        // Title
        Row(
            modifier = modifier
                .fillMaxWidth()
                .background(MaterialTheme.colorScheme.primary)
        ) {
            Text(
                text = "SmartRoom",
                style = MaterialTheme.typography.headlineSmall,
                color = MaterialTheme.colorScheme.inverseOnSurface,
                modifier = modifier
                    .padding(horizontal = 10.dp, vertical = 5.dp)
            )
        }

        Spacer(
            modifier = modifier
                .height(80.dp)
        )

        // Room data
        Column(
            modifier = modifier
                .fillMaxWidth()
                .fillMaxHeight(0.4f)
                .padding(horizontal = 10.dp, vertical = 0.dp),
        ) {
            Row(
                modifier = modifier
            ) {
                Text(
                    text = "Room Data",
                    style = MaterialTheme.typography.titleLarge,
                    color = MaterialTheme.colorScheme.onSecondaryContainer,
                    modifier = modifier
                )
            }

            Column(
                modifier = modifier
                    .fillMaxHeight(0.8f)
                    .fillMaxWidth(),
                verticalArrangement = Arrangement.SpaceEvenly
            ) {
                Text(
                    text = "Light: ${if (uiState.lightOn) "ON" else "OFF" }",
                    style = MaterialTheme.typography.bodyLarge,
                    color = MaterialTheme.colorScheme.onSecondaryContainer
                )
                Text(
                    text = "Blind (open %): ${uiState.blindOpenPercentage}",
                    style = MaterialTheme.typography.bodyLarge,
                    color = MaterialTheme.colorScheme.onSecondaryContainer
                )
                Text(
                    text = "Control Mode: ${uiState.controlMode}",
                    style = MaterialTheme.typography.bodyLarge,
                    color = MaterialTheme.colorScheme.onSecondaryContainer
                )
            }
        }

        // Room control
        Column(
            modifier = modifier
                .fillMaxWidth()
                .fillMaxHeight(0.6f)
                .padding(horizontal = 10.dp, vertical = 0.dp),
            verticalArrangement = Arrangement.SpaceEvenly
        ) {
            Row(
                modifier = modifier
                    .fillMaxWidth(),
                horizontalArrangement = Arrangement.SpaceBetween,
                verticalAlignment = Alignment.CenterVertically

            ) {
                Text(
                    text = "Room Control",
                    style = MaterialTheme.typography.titleLarge,
                    color = MaterialTheme.colorScheme.onSecondaryContainer,
                    modifier = modifier
                )

                Button(
                    onClick = { onSwitchModePress() },
                    enabled = uiState.controlMode != "MANUAL_SERIAL",
                ) {
                    Text(text = "${if (uiState.controlMode != "MANUAL_BT") "Start" else "Stop"} Manual Mode")
                }
            }

            Row(
                modifier = modifier
                    .fillMaxWidth(),
                horizontalArrangement = Arrangement.SpaceBetween,
                verticalAlignment = Alignment.CenterVertically
            ) {
                Text(
                    text = "Light System",
                    style = MaterialTheme.typography.bodyLarge,
                    color = MaterialTheme.colorScheme.onSecondaryContainer
                )
                Button(
                    onClick = { onSwitchLightPress() },
                    enabled = uiState.controlMode == "MANUAL_BT"
                ) {
                    Text(text = "Switch ${if (uiState.lightOn) "OFF" else "ON"} Light")
                }
            }

            Row(
                modifier = modifier
                    .fillMaxWidth(),
                horizontalArrangement = Arrangement.SpaceBetween,
                verticalAlignment = Alignment.CenterVertically
            ) {
                Text(
                    text = "Roller blinds opening:",
                    style = MaterialTheme.typography.bodyLarge,
                    color = MaterialTheme.colorScheme.onSecondaryContainer
                )

                Slider(
                    value = sliderPosition,
                    valueRange = 0f..100f,
                    steps = 19,
                    onValueChange = { sliderPosition = it },
                    onValueChangeFinished = { onRollerblindSliderChangeFinished(round(sliderPosition).toInt()) },
                    enabled = uiState.controlMode == "MANUAL_BT"
                )
            }
        }
    }
}

@Preview
@Composable
fun PreviewDashboardScreen() {
    DashboardScreen(
        uiState = SmartRoomUiState(
            connected = true,
            lightOn = false,
            blindOpenPercentage = 50,
            controlMode = "AUTO"
        ),
        onSwitchModePress = {},
        onSwitchLightPress = {},
        onRollerblindSliderChangeFinished = {}
    )
}
