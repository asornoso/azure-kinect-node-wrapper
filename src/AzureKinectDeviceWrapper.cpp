#include <napi.h>
#include <chrono>
#include "AzureKinectDeviceWrapper.h"
#include <bitset>
#include <string>


Napi::FunctionReference AzureKinectDeviceWrapper::constructor;

Napi::Object AzureKinectDeviceWrapper::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "AzureKinectDeviceWrapper", {
    //List all methods of class here....
    InstanceMethod("setDeviceId", &AzureKinectDeviceWrapper::setDeviceId),
    InstanceMethod("configureDevice", &AzureKinectDeviceWrapper::configureDevice),
    InstanceMethod("openDevice", &AzureKinectDeviceWrapper::openDevice),
    InstanceMethod("configureDepthMode", &AzureKinectDeviceWrapper::configureDepthMode),
    InstanceMethod("configureColorResolution", &AzureKinectDeviceWrapper::configureColorResolution),
    InstanceMethod("configureColorFormat", &AzureKinectDeviceWrapper::configureColorFormat),
    InstanceMethod("configureFPS", &AzureKinectDeviceWrapper::configureFPS),
    InstanceMethod("startCameras", &AzureKinectDeviceWrapper::startCameras),
    InstanceMethod("stopCameras", &AzureKinectDeviceWrapper::stopCameras),
    InstanceMethod("getFrame", &AzureKinectDeviceWrapper::getFrame),
    InstanceMethod("getDepthData", &AzureKinectDeviceWrapper::getDepthData),
    InstanceMethod("getColorData", &AzureKinectDeviceWrapper::getColorData),
    InstanceMethod("getIRData", &AzureKinectDeviceWrapper::getIRData),
    InstanceMethod("getPointCloudData", &AzureKinectDeviceWrapper::getPointCloudData),
    InstanceMethod("getImageSpecs", &AzureKinectDeviceWrapper::getImageSpecs),
    InstanceMethod("setExposure", &AzureKinectDeviceWrapper::setExposure),
    InstanceMethod("setISO", &AzureKinectDeviceWrapper::setISO),
    InstanceMethod("setTimestamp", &AzureKinectDeviceWrapper::setTimestamp),
    InstanceMethod("setWhiteBalance", &AzureKinectDeviceWrapper::setWhiteBalance),
    InstanceMethod("releaseImageAndCamera", &AzureKinectDeviceWrapper::releaseImageAndCamera),

  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("AzureKinectDeviceWrapper", func);
  return exports;
}

AzureKinectDeviceWrapper::AzureKinectDeviceWrapper(const Napi::CallbackInfo& info) : Napi::ObjectWrap<AzureKinectDeviceWrapper>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  int length = info.Length();
  if ( length != 2 || !info[0].IsNumber() || !info[1].IsNumber() ){
    Napi::TypeError::New(env, "DeviceID and TTL must be defined and must be integers").ThrowAsJavaScriptException();
  }
  this->azureKinectDevice = new AzureKinectDevice((int)info[0].As<Napi::Number>().DoubleValue(), (int)info[1].As<Napi::Number>().DoubleValue());
}

void AzureKinectDeviceWrapper::setDeviceId(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (  info.Length() != 1 ||  !info[0].IsNumber() ) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }

  this->azureKinectDevice->setDeviceId((int)info[0].As<Napi::Number>().DoubleValue());
}


void AzureKinectDeviceWrapper::configureDevice(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  this->azureKinectDevice->configureDevice();
}


Napi::Value AzureKinectDeviceWrapper::openDevice(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  int returnedValue = this->azureKinectDevice->openDevice();
  return Napi::Number::New(env, returnedValue);
}


void AzureKinectDeviceWrapper::configureDepthMode(const Napi::CallbackInfo& info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  int length = info.Length();
  if (length != 1 || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }

  this->azureKinectDevice->configureDepthMode((int)info[0].As<Napi::Number>().DoubleValue());
}


void AzureKinectDeviceWrapper::configureColorFormat(const Napi::CallbackInfo& info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  int length = info.Length();
  if (length != 1 || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }

  this->azureKinectDevice->configureColorFormat((int)info[0].As<Napi::Number>().DoubleValue());
}


void AzureKinectDeviceWrapper::configureColorResolution(const Napi::CallbackInfo& info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  int length = info.Length();
  if (length != 1 || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }

  this->azureKinectDevice->configureColorResolution((int)info[0].As<Napi::Number>().DoubleValue());
}


void AzureKinectDeviceWrapper::configureFPS(const Napi::CallbackInfo& info)   {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  int length = info.Length();
  if (length != 1 || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }

  this->azureKinectDevice->configureFPS((int)info[0].As<Napi::Number>().DoubleValue());
}


Napi::Value AzureKinectDeviceWrapper::startCameras(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  int returnedValue = this->azureKinectDevice->startCameras();
  return Napi::Number::New(env, returnedValue);
}

void AzureKinectDeviceWrapper::stopCameras(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  this->azureKinectDevice->stopCameras();
}


Napi::Value AzureKinectDeviceWrapper::getFrame(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  int returnedValue = this->azureKinectDevice->getFrame();
  return Napi::Number::New(env, returnedValue);
}


int AzureKinectDeviceWrapper::combineInts(int a, int b){
  int magnitude = 1;
  while( magnitude <= b){
    magnitude *= 10;
  }
  return (magnitude * a) + b;
}

Napi::Value AzureKinectDeviceWrapper::getDepthData(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  uint8_t* buffered_data = this->azureKinectDevice->getDepthData();
  int length = this->azureKinectDevice->getBufferLength(1);
  Napi::Array dataArray = Napi::Array::New(Env(), (length / 2));
  printf("length: %i\n", length);

  int j = 0;
  for(int i = 0; i < length; i+=2){

    std::string firstByte = std::bitset<8>(buffered_data[i+1]).to_string();
    std::string secondByte = std::bitset<8>(buffered_data[i]).to_string();
    std::string orderedData = firstByte + secondByte;


    int value = std::stoi(orderedData, nullptr, 2);
    dataArray[j] = value;
    j++;
  }

  return dataArray;
}

Napi::Value AzureKinectDeviceWrapper::getPointCloudData(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  int16_t * buffered_data = (int16_t *)(void *)this->azureKinectDevice->getPointCloudData();
  int length = this->azureKinectDevice->getBufferLength(4);

  Napi::Array dataArray = Napi::Array::New(Env(), length/2);
  printf("point cloud length: %i\n", length);

  for(int i = 0; i < length/2; i++){
    dataArray[i] = buffered_data[i];
  }

  return dataArray;
}


Napi::Value AzureKinectDeviceWrapper::getColorData(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  uint8_t* buffered_data = this->azureKinectDevice->getColorData();
  int length = this->azureKinectDevice->getBufferLength(2);
  Napi::Array dataArray = Napi::Array::New(Env(), (length));
  printf("length: %i\n", length);

  for(int i = 0; i < length; i+=2){
    dataArray[i] = buffered_data[i];
  }

  return dataArray;
}

Napi::Value AzureKinectDeviceWrapper::getIRData(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  uint8_t* buffered_data = this->azureKinectDevice->getIRData();
  int length = this->azureKinectDevice->getBufferLength(3);
  Napi::Array dataArray = Napi::Array::New(Env(), (length/2));
  printf("length: %i\n", length);

  int j = 0;
  for(int i = 0; i < length; i+=2){
    std::string firstByte = std::bitset<8>(buffered_data[i+1]).to_string();
    std::string secondByte = std::bitset<8>(buffered_data[i]).to_string();
    std::string orderedData = firstByte + secondByte;


    int value = std::stoi(orderedData, nullptr, 2);
    dataArray[j] = value;
    j++;
  }

  return dataArray;
}

void AzureKinectDeviceWrapper::releaseImageAndCamera(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  this->azureKinectDevice->releaseImageAndCamera();
}


Napi::Value AzureKinectDeviceWrapper::getImageSpecs(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() != 1 || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }

  Napi::Object obj = Napi::Object::New(env);

  switch((int)info[0].As<Napi::Number>().DoubleValue()){
    case 1:
      obj.Set("width", k4a_image_get_width_pixels(this->azureKinectDevice->getDepthImage()) );
      obj.Set("height", k4a_image_get_height_pixels(this->azureKinectDevice->getDepthImage()) );
      obj.Set("iso", k4a_image_get_iso_speed(this->azureKinectDevice->getDepthImage()) );
      obj.Set("strideBytes",  k4a_image_get_stride_bytes(this->azureKinectDevice->getDepthImage()) );
      obj.Set("timestamp",  k4a_image_get_device_timestamp_usec(this->azureKinectDevice->getDepthImage()) );
      obj.Set("whitebalance",  k4a_image_get_white_balance(this->azureKinectDevice->getDepthImage()) );
      break;

    case 2:
      obj.Set("width", k4a_image_get_width_pixels(this->azureKinectDevice->getColorImage()) );
      obj.Set("height", k4a_image_get_height_pixels(this->azureKinectDevice->getColorImage()) );
      obj.Set("iso", k4a_image_get_iso_speed(this->azureKinectDevice->getColorImage()) );
      obj.Set("strideBytes",  k4a_image_get_stride_bytes(this->azureKinectDevice->getColorImage()) );
      obj.Set("timestamp",  k4a_image_get_device_timestamp_usec(this->azureKinectDevice->getColorImage()) );
      obj.Set("whitebalance",  k4a_image_get_white_balance(this->azureKinectDevice->getColorImage()) );
      break;

    case 3:
      obj.Set("width", k4a_image_get_width_pixels(this->azureKinectDevice->getIRImage()) );
      obj.Set("height", k4a_image_get_height_pixels(this->azureKinectDevice->getIRImage()) );
      obj.Set("iso", k4a_image_get_iso_speed(this->azureKinectDevice->getIRImage()) );
      obj.Set("strideBytes",  k4a_image_get_stride_bytes(this->azureKinectDevice->getIRImage()) );
      obj.Set("timestamp",  k4a_image_get_device_timestamp_usec(this->azureKinectDevice->getIRImage()) );
      obj.Set("whitebalance",  k4a_image_get_white_balance(this->azureKinectDevice->getIRImage()) );
      break;

    case 4:
      obj.Set("width", k4a_image_get_width_pixels(this->azureKinectDevice->getPointCloudImage()) );
      obj.Set("height", k4a_image_get_height_pixels(this->azureKinectDevice->getPointCloudImage()) );
      obj.Set("iso", k4a_image_get_iso_speed(this->azureKinectDevice->getPointCloudImage()) );
      obj.Set("strideBytes",  k4a_image_get_stride_bytes(this->azureKinectDevice->getPointCloudImage()) );
      obj.Set("timestamp", k4a_image_get_device_timestamp_usec(this->azureKinectDevice->getPointCloudImage()) );
      obj.Set("whitebalance",  k4a_image_get_white_balance(this->azureKinectDevice->getPointCloudImage()) );
      break;

    default:
        obj.Set("width",  -1);
        obj.Set("height",  -1);
        obj.Set("iso", -1 );
        obj.Set("strideBytes", -1 );
        obj.Set("timestamp",  -1 );
        obj.Set("whitebalance",  -1 );
  }

  return  obj;
}


void AzureKinectDeviceWrapper::setExposure(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  int length = info.Length();
  if (length != 2 || !info[0].IsNumber() ||  !info[1].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }

  switch((int)info[0].As<Napi::Number>().DoubleValue()){
    case 1:
      k4a_image_set_exposure_usec(this->azureKinectDevice->getDepthImage(), (uint32_t)info[1].As<Napi::Number>().DoubleValue() );
    case 2:
      k4a_image_set_exposure_usec(this->azureKinectDevice->getColorImage(), (uint32_t)info[1].As<Napi::Number>().DoubleValue() );
    case 3:
      k4a_image_set_exposure_usec(this->azureKinectDevice->getIRImage(), (uint32_t)info[1].As<Napi::Number>().DoubleValue() );
    case 4:
      k4a_image_set_exposure_usec(this->azureKinectDevice->getPointCloudImage(), (uint32_t)info[1].As<Napi::Number>().DoubleValue() );
  }
}

void AzureKinectDeviceWrapper::setISO(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

    int length = info.Length();
    if (length != 2 || !info[0].IsNumber() ||  !info[1].IsNumber()) {
      Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    }

    switch((int)info[0].As<Napi::Number>().DoubleValue()){
      case 1:
        k4a_image_set_iso_speed(this->azureKinectDevice->getDepthImage(), (uint32_t)info[1].As<Napi::Number>().DoubleValue() );
      case 2:
        k4a_image_set_iso_speed(this->azureKinectDevice->getColorImage(), (uint32_t)info[1].As<Napi::Number>().DoubleValue() );
      case 3:
        k4a_image_set_iso_speed(this->azureKinectDevice->getIRImage(), (uint32_t)info[1].As<Napi::Number>().DoubleValue() );
      case 4:
        k4a_image_set_iso_speed(this->azureKinectDevice->getPointCloudImage(), (uint32_t)info[1].As<Napi::Number>().DoubleValue() );
    }
}

void AzureKinectDeviceWrapper::setTimestamp(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  int length = info.Length();
  if (length != 2 || !info[0].IsNumber() ||  !info[1].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }

  switch((int)info[0].As<Napi::Number>().DoubleValue()){
    case 1:
      k4a_image_set_device_timestamp_usec(this->azureKinectDevice->getDepthImage(), (uint64_t)info[1].As<Napi::Number>().DoubleValue() );
    case 2:
      k4a_image_set_device_timestamp_usec(this->azureKinectDevice->getColorImage(), (uint64_t)info[1].As<Napi::Number>().DoubleValue() );
    case 3:
      k4a_image_set_device_timestamp_usec(this->azureKinectDevice->getIRImage(), (uint64_t)info[1].As<Napi::Number>().DoubleValue() );
    case 4:
      k4a_image_set_device_timestamp_usec(this->azureKinectDevice->getPointCloudImage(), (uint64_t)info[1].As<Napi::Number>().DoubleValue() );
  }
}

void AzureKinectDeviceWrapper::setWhiteBalance(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  int length = info.Length();
  if (length != 2 || !info[0].IsNumber() ||  !info[1].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }

  switch((int)info[0].As<Napi::Number>().DoubleValue()){
    case 1:
      k4a_image_set_white_balance(this->azureKinectDevice->getDepthImage(), (uint32_t)info[1].As<Napi::Number>().DoubleValue() );
    case 2:
      k4a_image_set_white_balance(this->azureKinectDevice->getColorImage(), (uint32_t)info[1].As<Napi::Number>().DoubleValue() );
    case 3:
      k4a_image_set_white_balance(this->azureKinectDevice->getIRImage(), (uint32_t)info[1].As<Napi::Number>().DoubleValue() );
    case 4:
      k4a_image_set_white_balance(this->azureKinectDevice->getPointCloudImage(), (uint32_t)info[1].As<Napi::Number>().DoubleValue() );
  }

}
