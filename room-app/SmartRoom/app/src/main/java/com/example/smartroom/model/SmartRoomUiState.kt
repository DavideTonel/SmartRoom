package com.example.smartroom.model

data class SmartRoomUiState(
    val connected: Boolean = false,
    val lightOn: Boolean = false,
    val blindOpenPercentage: Int = 0,
    val controlMode: String = "AUTO"
)
