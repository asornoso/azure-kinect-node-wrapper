#include <k4a/k4a.h>

class AzureKinectDevice {

  public:
    AzureKinectDevice(int id, int ttl);
    void setDeviceId(int id);
    void configureDevice();
    int openDevice();
    void configureDepthMode(int depth_mode);
    void configureColorResolution(int resMode);
    void configureColorFormat(int format);
    void configureFPS(int fps_mode);
    int startCameras();
    void stopCameras();
    int getFrame();
    k4a_image_t getIRImage();   //NEW
    k4a_image_t getDepthImage();  //NEW
    k4a_image_t getColorImage();  //NEW
    k4a_image_t getPointCloudImage(); //NEW
    uint8_t* getDepthData();
    uint8_t* getColorData();
    uint8_t* getIRData();
    uint8_t* getPointCloudData();
    int getBufferLength(int mode);
    void releaseImageAndCamera();

  private:
    int depthMode;
    int deviceId;
    k4a_device_t device;
    k4a_calibration_t calibration;
    k4a_device_configuration_t configuration;
    k4a_image_t IRImage;
    k4a_image_t colorImage; //NEW
    k4a_image_t depthImage; //NEW
    k4a_image_t pointCloudImage;

    k4a_capture_t capture;
    int timeout;
    int depth_buffer_length;
    int color_buffer_length;
    int ir_buffer_length;
    int point_cloud_buffer_length;
};
