#include <stdio.h>
#include <vector>
#include <k4a/k4a.h>
#include "AzureKinectDevice.h"

AzureKinectDevice::AzureKinectDevice(int id, int ttl){
  this->deviceId = id;
  this->timeout = ttl;
}

void AzureKinectDevice::setDeviceId(int id){
  this->deviceId = id;
}

void AzureKinectDevice::configureDevice(){
  int returnValue = 0;
  this->configuration = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
}

int AzureKinectDevice::openDevice(){
  if (K4A_RESULT_SUCCEEDED != k4a_device_open(K4A_DEVICE_DEFAULT, &device))
  {
    printf("Failed to open device\n");
    return -1;
  }
  else
    return  0;
}

void AzureKinectDevice::configureDepthMode(int depth_mode){
 //0 = K4A_DEPTH_MODE_OFF
 //1 = K4A_DEPTH_MODE_NFOV_2X2BINNED
 //2 = K4A_DEPTH_MODE_NFOV_UNBINNED
 //3 = K4A_DEPTH_MODE_WFOV_2X2BINNED
 //4 = K4A_DEPTH_MODE_WFOV_UNBINNED
 //5 = K4A_DEPTH_MODE_PASSIVE_IR
   switch(depth_mode){
     case 0:
      this->configuration.depth_mode = K4A_DEPTH_MODE_OFF;
      break;
     case 1:
      this->configuration.depth_mode = K4A_DEPTH_MODE_NFOV_2X2BINNED;
      break;
     case 2:
      this->configuration.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
      break;
     case 3:
      this->configuration.depth_mode = K4A_DEPTH_MODE_WFOV_2X2BINNED;
      break;
     case 4:
      this->configuration.depth_mode = K4A_DEPTH_MODE_WFOV_UNBINNED;
      break;
     case 5:
      this->configuration.depth_mode = K4A_DEPTH_MODE_PASSIVE_IR;
      break;
     default:
      this->configuration.depth_mode = K4A_DEPTH_MODE_NFOV_2X2BINNED;
  }

}

void AzureKinectDevice::configureColorResolution(int resMode){
/*
    0 = K4A_COLOR_RESOLUTION_OFF
    1 = K4A_COLOR_RESOLUTION_720P
    2 = K4A_COLOR_RESOLUTION_1080P
    3 = K4A_COLOR_RESOLUTION_1440P
    4 = K4A_COLOR_RESOLUTION_1536P
    5 = K4A_COLOR_RESOLUTION_2160P
    6 = K4A_COLOR_RESOLUTION_3072P
*/
  switch(resMode){
    case 0:
      this->configuration.color_resolution = K4A_COLOR_RESOLUTION_OFF;
      break;
    case 1:
      this->configuration.color_resolution = K4A_COLOR_RESOLUTION_720P;
      break;
    case 2:
      this->configuration.color_resolution = K4A_COLOR_RESOLUTION_1080P;
      break;
    case 3:
      this->configuration.color_resolution = K4A_COLOR_RESOLUTION_1440P;
      break;
    case 4:
      this->configuration.color_resolution = K4A_COLOR_RESOLUTION_1536P;
      break;
    case 5:
      this->configuration.color_resolution = K4A_COLOR_RESOLUTION_2160P;
      break;
    case 6:
      this->configuration.color_resolution = K4A_COLOR_RESOLUTION_3072P;
      break;
    default:
      this->configuration.color_resolution = K4A_COLOR_RESOLUTION_OFF;
  }
}

void AzureKinectDevice::configureColorFormat(int format){
  /*
    0 = K4A_IMAGE_FORMAT_COLOR_MJPG
    1 = K4A_IMAGE_FORMAT_COLOR_NV12
    2 = K4A_IMAGE_FORMAT_COLOR_YUY2
    3 = K4A_IMAGE_FORMAT_COLOR_BGRA32
    4 = K4A_IMAGE_FORMAT_DEPTH16
    5 = K4A_IMAGE_FORMAT_IR16
  */
  switch(format){
    case 0:
      this->configuration.color_format = K4A_IMAGE_FORMAT_COLOR_MJPG;
      break;
    case 1:
      this->configuration.color_format = K4A_IMAGE_FORMAT_COLOR_NV12;
      break;
    case 2:
      this->configuration.color_format = K4A_IMAGE_FORMAT_COLOR_YUY2;
      break;
    case 3:
      this->configuration.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
      break;
    case 4:
      this->configuration.color_format = K4A_IMAGE_FORMAT_DEPTH16;
      break;
    case 5:
      this->configuration.color_format = K4A_IMAGE_FORMAT_IR16;
      break;
    default:
      this->configuration.color_format = K4A_IMAGE_FORMAT_COLOR_MJPG;
  }
}


void AzureKinectDevice::configureFPS(int fps_mode){

      switch(fps_mode){
        case 5:
         this->configuration.camera_fps = K4A_FRAMES_PER_SECOND_5 ;
         break;
        case 15:
         this->configuration.camera_fps = K4A_FRAMES_PER_SECOND_15 ;
         break;
        case 30:
         this->configuration.camera_fps = K4A_FRAMES_PER_SECOND_30 ;
         break;
        default:
         this->configuration.camera_fps = K4A_FRAMES_PER_SECOND_15 ;
     }
}

int AzureKinectDevice::startCameras(){

  if (K4A_RESULT_SUCCEEDED != k4a_device_start_cameras(this->device, &configuration)){
    printf("Failed to start device\n");
    return -1;
  }
  else
    return 0;
}

void AzureKinectDevice::stopCameras(){
  k4a_device_stop_cameras(this->device);
  //k4a_device_close(this->device);

}

int AzureKinectDevice::getFrame(){
  // Get a depth frame
	switch (k4a_device_get_capture(this->device, &capture, this->timeout)){
  	case K4A_WAIT_RESULT_SUCCEEDED:
  		break;

  	case K4A_WAIT_RESULT_TIMEOUT:
  		printf("ERROR FROM CPP: Timed out waiting for a capture\n");
  		break;

  	case K4A_WAIT_RESULT_FAILED:
  		printf("ERROR FROM CPP: Failed to read a capture\n");
      return -1;
	}

  return 0;
}

k4a_image_t AzureKinectDevice::getIRImage(){
  return this->IRImage;
}
k4a_image_t AzureKinectDevice::getColorImage(){
  return this->colorImage;
}
k4a_image_t AzureKinectDevice::getDepthImage(){
  return this->depthImage;
}
k4a_image_t AzureKinectDevice::getPointCloudImage(){
  return this->pointCloudImage;
}

uint8_t* AzureKinectDevice::getColorData(){
  this->colorImage = k4a_capture_get_color_image(this->capture);
  uint8_t* buffer_data =   k4a_image_get_buffer(this->colorImage);
  this->color_buffer_length = k4a_image_get_size(this->colorImage);

  return buffer_data;
}

uint8_t* AzureKinectDevice::getDepthData(){
  this->depthImage = k4a_capture_get_depth_image(this->capture);
  uint8_t* buffer_data =   k4a_image_get_buffer(this->depthImage);
  this->depth_buffer_length = k4a_image_get_size(this->depthImage);

  return buffer_data;
}

uint8_t* AzureKinectDevice::getIRData(){
  this->IRImage = k4a_capture_get_ir_image(this->capture);
  uint8_t* buffer_data =   k4a_image_get_buffer(this->IRImage);
  this->ir_buffer_length = k4a_image_get_size(this->IRImage);

  return buffer_data;
}

uint8_t* AzureKinectDevice::getPointCloudData(){
  this->depthImage = k4a_capture_get_depth_image(this->capture);
  uint8_t* buffered_data;
  //Create a custom image format
  if(k4a_image_create(K4A_IMAGE_FORMAT_CUSTOM, k4a_image_get_width_pixels(this->depthImage), k4a_image_get_height_pixels(this->depthImage), k4a_image_get_width_pixels(this->depthImage) * 6, &pointCloudImage) == K4A_RESULT_SUCCEEDED  )
  {
    printf("Created custom image\n");
    //Set the calibration for the device using this device, the current depth and resolution, and the calibration handle.
    k4a_device_get_calibration(this->device,   this->configuration.depth_mode,  this->configuration.color_resolution, &calibration);

    //Create a transformation handle of depth type
    k4a_transformation_t transformer = k4a_transformation_create( &calibration );

    //Transform the depth image to a cloud point using the transformer, this depth image, the depth calibration, and this point cloud handle
    if( k4a_transformation_depth_image_to_point_cloud	(transformer, this->depthImage, K4A_CALIBRATION_TYPE_DEPTH, this->pointCloudImage) == K4A_RESULT_SUCCEEDED )
    {
      buffered_data = k4a_image_get_buffer(this->pointCloudImage);
      this->point_cloud_buffer_length = k4a_image_get_size(this->pointCloudImage);
      k4a_transformation_destroy(transformer);
      printf("Transformed data\n");
    }
  }
  else{
    printf("Failed to create custom image!!!\n");
  }
  return buffered_data;

}

void AzureKinectDevice::releaseImageAndCamera(){
  if(this->depthImage && this->depth_buffer_length)
    k4a_image_release(this->depthImage);
  if(this->colorImage && this-> color_buffer_length)
    k4a_image_release(this->colorImage);
  if(this->IRImage && this->ir_buffer_length )
    k4a_image_release(this->IRImage);
  if(this->capture)
    k4a_capture_release(this->capture);
}

int AzureKinectDevice::getBufferLength(int mode){
  switch(mode){
    case 1:
      return this->depth_buffer_length;
    case 2:
      return this->color_buffer_length;
    case 3:
      return this->ir_buffer_length;
    case 4:
      return this->point_cloud_buffer_length;
    default:
      return -1;
  }
}
