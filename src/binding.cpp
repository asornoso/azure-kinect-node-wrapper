#include <node_api.h>
#include "AzureKinectDeviceWrapper.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return AzureKinectDeviceWrapper::Init(env, exports);
}

NODE_API_MODULE(addon, InitAll)
