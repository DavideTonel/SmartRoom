const express = require('express')
const mqtt = require('mqtt')
const {SerialPort} = require('serialport')
const {ReadlineParser} = require('@serialport/parser-readline')

const app = express()
app.use(express.static('public'))
app.use(express.json())
const serverPort = 3000


sensorBoard = {
    presenceDetected: 0,
    lightLevel: 0,
    hour: 0,
}

room = {
    blindOpenPercentage: 0,
    lightOn: 0,
    controlMode: 'AUTO'
}


// HTTP service
app.listen(serverPort, () => console.log("listening at " + serverPort))

app.post('/switchSerialMode', (req, res) => {
    if (room.controlMode == 'AUTO') {
        serialPort.write('chmod MANUAL_SERIAL' + '\n')

    } else if (room.controlMode == 'MANUAL_SERIAL') {
        serialPort.write('chmod AUTO' + '\n')
    }
    res.json(true)
})

app.post('/setBlindOpenPercentage', (req, res) => {
    if (room.controlMode == 'MANUAL_SERIAL') {
        let data = req.body

        clientInput = data
        let json = JSON.stringify(clientInput)
        //console.log(json)
        serialPort.write(json + '\n')
    }
    res.json(true)
})

app.post('/switchLight', (req, res) => {
    if (room.controlMode == 'MANUAL_SERIAL') {
        clientInput = {}
        if (room.lightOn == 1) {
            clientInput.remoteLightOn = 0
        } else {
            clientInput.remoteLightOn = 1
        }
        let json = JSON.stringify(clientInput)
        //console.log(json)
        serialPort.write(json + '\n')
    }
    res.json(true)
})

app.post('/getUpdate', (req, res) => {
    let data = {...room, ...sensorBoard}
    res.json(data)
})


// Serial service
const serialPort = new SerialPort({
    path: 'COM8',
    baudRate: 9600
})
serialPort.setEncoding('utf8')
const parser = serialPort.pipe(new ReadlineParser({ delimiter: '\n'}))

serialPort.on('open', () => {
    console.log('serial port open')
})

parser.on('data', (data) => {
    //console.log('msg received:\t' + data)
    try {
        room = JSON.parse(data)
    } catch (error) {
        console.log(error.message)
    }
})

setInterval(() => {
    //sensorBoard.hour = new Date().getHours()
    let json = JSON.stringify(sensorBoard)
    serialPort.write(json + '\n')
}, 1000)


//TODO: delete this
setInterval(() => {
    sensorBoard.hour += 1
    if (sensorBoard.hour >= 24) {
        sensorBoard.hour = 0
    }
}, 2000)


// MQTT service
const client = mqtt.connect("mqtt://broker.mqtt-dashboard.com")

client.on('connect', () => {
    console.log("Client connected")
    client.subscribe('sensorBoard/lightLevel')
    client.subscribe('sensorBoard/presenceDetected')
})

client.on('message', (topic, message, payload) => {
    //console.log(topic + ': ' + message)
    
    switch (topic) {
        case 'sensorBoard/lightLevel':
            sensorBoard.lightLevel = parseFloat(message)
            break
        case 'sensorBoard/presenceDetected':
            sensorBoard.presenceDetected = parseInt(message)
            break
        default:
    }
})

client.on('offline', () => {
    console.log('client offline')
})

client.on('reconnect', () => {
    console.log('client reconnect event')
})
