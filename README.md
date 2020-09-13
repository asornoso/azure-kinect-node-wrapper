# azure-kinect-node-wrapper
A wrapper for the Azure Kinect SDK < br /> Will only work on Node/Electron Projects.  
Note: Web based projects cannot utilize Native Addons. Electron or similar must be used.

## Getting Started
This package allows developers to access the raw image data from Microsoft's Azure Kinect Device. To get started you need:
-Windows 10
-Azure Kinect Device


## Installing
```
npm i --save node_kinect
```

## Example:
Steps:
-Require package
-Create device
-Open device
-Configure Mode(Color, IR, Depth)
-Configure FPS(5, 15, 30)
-Start Camera
--Get Frame
--Process Frame Data
--Release Image & Camera
-Stop Camera

```javascript
const kinect = require('node_kinect')

//Pass in deviceID and TTL
let myDevice = new kinect.AzureKinectDeviceWrapper(1, 1000)

let status = myDevice.openDevice()

if(status != 0 ) 
  process.exit()


//Configure device
myDevice.configureDepthMode(1)
myDevice.configureFPS(15)

console.log(`Start Cameras Code: ${myDevice.startCameras()}`)
console.log(`GetFrame Code: ${myDevice.getFrame()}`)

let depthData = myDevice.getDepthData()

//get specs for the depth image (mode  = 1)
let specs = myDevice.getImageSpecs(1)

console.log(`Height: ${specs.height} | Width: ${specs.width} | Stride: ${specs.stride} | ISO: ${specs.iso} | timestamp: ${specs.timestamp} | whitebalance: ${specs.whitebalance}`)

myDevice.releaseImageAndCamera()
myDevice.stopCameras()
```

## Functions:
### Create Device Reference:
```javascript
let myDevice = new kinect.AzureKinectDeviceWrapper(1)
```
### Open Device: Returns status code. 
0 == successful.
```javascript
myDevice.openDevice()
```
### Configure Depth Mode:
0 = K4A_DEPTH_MODE_OFF
1 = K4A_DEPTH_MODE_NFOV_2X2BINNED
2 = K4A_DEPTH_MODE_NFOV_UNBINNED
3 = K4A_DEPTH_MODE_WFOV_2X2BINNED
4 = K4A_DEPTH_MODE_WFOV_UNBINNED
5 = K4A_DEPTH_MODE_PASSIVE_IR
```javascript
myDevice.configureDepthMode(1)
```
### Configure Color Mode:
0 = K4A_IMAGE_FORMAT_COLOR_MJPG
1 = K4A_IMAGE_FORMAT_COLOR_NV12
2 = K4A_IMAGE_FORMAT_COLOR_YUY2
3 = K4A_IMAGE_FORMAT_COLOR_BGRA32
4 = K4A_IMAGE_FORMAT_DEPTH16
5 = K4A_IMAGE_FORMAT_IR16
```javascript
myDevice.configureColorFormat(3)
```
### Configure Color Resolution:
0 = K4A_COLOR_RESOLUTION_OFF
1 = K4A_COLOR_RESOLUTION_720P
2 = K4A_COLOR_RESOLUTION_1080P
3 = K4A_COLOR_RESOLUTION_1440P
4 = K4A_COLOR_RESOLUTION_1536P
5 = K4A_COLOR_RESOLUTION_2160P
6 = K4A_COLOR_RESOLUTION_3072P
```javascript
myDevice.configureColorResolution(1)
```
### Configure FPS:
5 = K4A_FRAMES_PER_SECOND_5
15 = K4A_FRAMES_PER_SECOND_15
30 = K4A_FRAMES_PER_SECOND_30
```javascript
myDevice.configureFPS(15)
```
### Start Cameras:
```javascript
myDevice.startCameras()
```
### Get Frame: assigns frame to private frame variable of device.
```javascript
myDevice.getFrame()
```
### Get Depth Data Array:
```javascript
myDevice.getDepthData()
```
### Get Color Data Array:
```javascript
myDevice.getColorData()
```
### Get IR Data Array:
```javascript
myDevice.getIRData()
```
### Get Point Cloud Data Array:
```javascript
myDevice.getPointCloudData()
```
### Get Object of Width/Height/ISO/StrideBytes/Timestamp/Whitebalance of Image:
1 = Specifications for Depth Image
2 = Specifications for Color Image
3 = Specifications for IR Image
4 = Specifications for Point Cloud Image
```javascript
myDevice.getImageSpecs(int mode)
```
### Release All Images(Color, Depth, IR, Point Cloud) and Camera References:
```javascript
myDevice.releaseImageAndCamera()
```
### Stop all Cameras:
```javascript
myDevice.stopCameras()
```
