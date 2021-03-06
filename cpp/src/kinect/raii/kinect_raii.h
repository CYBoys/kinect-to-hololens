#pragma once

#include <Kinect.h>
#include <memory>
#include <vector>

namespace kh
{
namespace kinect
{
// The RAII classes wrapping the official Kinect API.
namespace raii
{
class KinectColorCameraSettings
{
public:
    KinectColorCameraSettings(IColorCameraSettings* color_camera_settings);
    ~KinectColorCameraSettings();
    KinectColorCameraSettings(const KinectColorCameraSettings& other) = delete;
    KinectColorCameraSettings& operator=(const KinectColorCameraSettings& other) = delete;
    int64_t getFrameInterval();

private:
    IColorCameraSettings* color_camera_settings_;
};

class KinectColorFrame
{
public:
    KinectColorFrame(IColorFrame* color_frame);
    ~KinectColorFrame();
    KinectColorFrame(const KinectColorFrame& other) = delete;
    KinectColorFrame& operator=(const KinectColorFrame& other) = delete;
    std::unique_ptr<KinectColorCameraSettings> getColorCameraSettings();
    BYTE* getRawUnderlyingBuffer();

private:
    IColorFrame* color_frame_;
};

class KinectDepthFrame
{
public:
    KinectDepthFrame(IDepthFrame* depth_frame);
    ~KinectDepthFrame();
    KinectDepthFrame(const KinectDepthFrame& other) = delete;
    KinectDepthFrame& operator=(const KinectDepthFrame& other) = delete;
    UINT16* getUnderlyingBuffer();

private:
    IDepthFrame* depth_frame_;
};

class KinectMultiSourceFrame
{
public:
    KinectMultiSourceFrame(IMultiSourceFrame* multi_source_frame);
    ~KinectMultiSourceFrame();
    KinectMultiSourceFrame(const KinectMultiSourceFrame& other) = delete;
    KinectMultiSourceFrame& operator=(const KinectMultiSourceFrame& other) = delete;
    std::unique_ptr<KinectColorFrame> getColorFrame();
    std::unique_ptr<KinectDepthFrame> getDepthFrame();

private:
    IMultiSourceFrame* multi_source_frame_;
};

class KinectMultiSourceFrameReader
{
public:
    KinectMultiSourceFrameReader(IMultiSourceFrameReader* multi_source_frame_reader);
    ~KinectMultiSourceFrameReader();
    KinectMultiSourceFrameReader(const KinectMultiSourceFrameReader& other) = delete;
    KinectMultiSourceFrameReader& operator=(const KinectMultiSourceFrameReader& other) = delete;
    std::unique_ptr<KinectMultiSourceFrame> getMultiSourceFrame();

private:
    IMultiSourceFrameReader* multi_source_frame_reader_;
};

class KinectSensor
{
public:
    KinectSensor(IKinectSensor* kinect_sensor);
    ~KinectSensor();
    KinectSensor(const KinectSensor& other) = delete;
    KinectSensor& operator=(const KinectSensor& other) = delete;
    static std::unique_ptr<KinectSensor> create();
    bool isAvailable();
    std::unique_ptr<KinectMultiSourceFrameReader> getMultiSourceFrameReader();

private:
    IKinectSensor* kinect_sensor_;
};
}
}
}