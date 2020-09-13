const kinect = require('./build/Release/AzureKinectDevice.node')

module.exports = kinect;

//EXAMPLE:

let myDevice = new kinect.AzureKinectDeviceWrapper(1, 1000)

myDevice.configureDevice()

console.log(`Open Device Code: ${myDevice.openDevice()}`)

myDevice.configureDepthMode(1)
myDevice.configureFPS(15)

console.log(`Start Cameras Code: ${myDevice.startCameras()}`)
console.log(`GetFrame Code: ${myDevice.getFrame()}`)

let depthData = myDevice.getDepthData()

//get specs for the depth image (mode  = 1)
let specs = myDevice.getImageSpecs(1)

console.log(`Height: ${specs.height} | Width: ${specs.width} | Stride: ${specs.stride} `+
  `| ISO: ${specs.iso} | timestamp: ${specs.timestamp} | whitebalance: ${specs.whitebalance}`)

myDevice.releaseImageAndCamera()
myDevice.stopCameras()
