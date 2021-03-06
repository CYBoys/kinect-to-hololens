#pragma once

#include <optional>
#include "libfreenect2/libfreenect2.hpp"
#include "raii/kinect_raii.h"

namespace kh
{
namespace kinect
{
// The class for the Kinect frame.
class KinectFrame
{
public:
    KinectFrame(std::unique_ptr<raii::KinectColorFrame> color_frame,
        std::unique_ptr<raii::KinectDepthFrame> depth_frame)
        : color_frame_(std::move(color_frame))
        , depth_frame_(std::move(depth_frame))
    {
    }
    raii::KinectColorFrame* color_frame() { return color_frame_.get(); }
    raii::KinectDepthFrame* depth_frame() { return depth_frame_.get(); }

private:
    std::unique_ptr<raii::KinectColorFrame> color_frame_;
    std::unique_ptr<raii::KinectDepthFrame> depth_frame_;
};

// The class with APIs to access the Kinect.
class KinectDevice
{
public:
    KinectDevice(std::unique_ptr<raii::KinectSensor> sensor,
        std::unique_ptr<raii::KinectMultiSourceFrameReader> frame_reader);
    bool isAvailable();
    std::unique_ptr<KinectFrame> KinectDevice::acquireFrame();

private:
    std::unique_ptr<raii::KinectSensor> sensor_;
    std::unique_ptr<raii::KinectMultiSourceFrameReader> frame_reader_;
};

// The intrinsic parameters of the Kinect that can be obtained through Freenect2.
struct KinectIntrinsics
{
    libfreenect2::Freenect2Device::ColorCameraParams color_params;
    libfreenect2::Freenect2Device::IrCameraParams ir_params;
};

// Utility functions for creating a KinectDevice and a KinectIntrinsics.
std::unique_ptr<KinectDevice> obtainKinectDevice();
std::optional<KinectIntrinsics> obtainKinectIntrinsics();
}
}