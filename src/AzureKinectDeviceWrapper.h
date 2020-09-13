#include <napi.h>
#include "AzureKinectDevice.h"

class AzureKinectDeviceWrapper : public Napi::ObjectWrap<AzureKinectDeviceWrapper> {
 public:
   //Init function for setting the export key to JS
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
   //Constructor to initialise
  AzureKinectDeviceWrapper(const Napi::CallbackInfo& info);

 private:
  //reference to store the class definition that needs to be exported to JS
  static Napi::FunctionReference constructor;
  //Wrap all of our functions
  void setDeviceId(const Napi::CallbackInfo& info);
  void configureDevice(const Napi::CallbackInfo& info);
  Napi::Value openDevice(const Napi::CallbackInfo& info);
  void configureDepthMode(const Napi::CallbackInfo& info);
  void configureFPS(const Napi::CallbackInfo& info);
  void configureColorResolution(const Napi::CallbackInfo& info);
  void configureColorFormat(const Napi::CallbackInfo& info);
  Napi::Value startCameras(const Napi::CallbackInfo& info);
  void stopCameras(const Napi::CallbackInfo& info);
  Napi::Value getFrame(const Napi::CallbackInfo& info);
  Napi::Value getDepthData(const Napi::CallbackInfo& info);
  Napi::Value getColorData(const Napi::CallbackInfo& info);
  Napi::Value getIRData(const Napi::CallbackInfo& info);
  Napi::Value getPointCloudData(const Napi::CallbackInfo& info);
  Napi::Value getImageSpecs(const Napi::CallbackInfo& info);

  void setExposure(const Napi::CallbackInfo& info);
  void setISO(const Napi::CallbackInfo& info);
  void setTimestamp(const Napi::CallbackInfo& info);
  void setWhiteBalance(const Napi::CallbackInfo& info);
  void releaseImageAndCamera(const Napi::CallbackInfo& info);

  int combineInts(int a, int b);


  //internal instance of actualclass used to perform actual operations.
  AzureKinectDevice *azureKinectDevice;
};
