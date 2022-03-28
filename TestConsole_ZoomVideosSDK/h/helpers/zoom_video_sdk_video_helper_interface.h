/*!
* \file zoom_video_sdk_video_helper_interface.h
* \brief video helper
*
*/

#ifndef _ZOOM_VIDEO_SDK_VIDEO_HELPER_INTERFACE_H_
#define _ZOOM_VIDEO_SDK_VIDEO_HELPER_INTERFACE_H_
#include "zoom_video_sdk_def.h"
#include "zoom_video_sdk_vector_interface.h"

BEGIN_ZOOM_VIDEO_SDK_NAMESPACE
typedef enum
{
	VideoRotation_0,
	VideoRotation_90,
	VideoRotation_180,
	VideoRotation_270,
}VideoRotation;

/// \brief Camera device interface.
///
class IZoomVideoSDKCameraDevice
{
public:
	virtual ~IZoomVideoSDKCameraDevice(){}
	virtual const zchar_t* getDeviceId() = 0;
	virtual const zchar_t* getDeviceName() = 0;
	virtual bool isSelectedDevice() = 0;
};
/// \brief Video helper interface.
///
class IZoomVideoSDKVideoHelper
{
public:
	virtual ~IZoomVideoSDKVideoHelper(){}

	/// \brief Start send local video data.(open camera).
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
    virtual ZoomVideoSDKErrors startVideo() = 0;

	/// \brief Stop send local video data. (close camera).
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
    virtual ZoomVideoSDKErrors stopVideo() = 0;

	/// \brief Rotate my video.
	/// \return True if success. Otherwise returns false.
    virtual bool rotateMyVideo(VideoRotation rotation) = 0;

	/// \brief Switch to next camera.
	/// \return True if success. Otherwise returns false.
    virtual bool switchCamera() = 0;

	/// \brief Select camera with cameraDeviceID.
	/// \return True if success. Otherwise returns false.
	virtual bool selectCamera(const zchar_t* cameraDeviceID) = 0;

	/// \brief Get camera number of the device.
	/// \return The count of cameras.
    virtual uint32_t getNumberOfCameras() = 0;

	/// \brief Get camera device list.
	/// \return Camera devices list.
    virtual IVideoSDKVector<IZoomVideoSDKCameraDevice*>* getCameraList() = 0;

	/// \brief Check whether the current user has permission to control the camera.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors canControlCamera(bool& bCan) = 0;

	/// \brief Turn the camera to the left.
	/// \param range: Rotation range, 10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors turnCameraLeft(unsigned int range = 50) = 0;

	/// \brief Turn the camera to the right.
	/// \param range: Rotation range, 10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors turnCameraRight(unsigned int range = 50) = 0;

	/// \brief Turn the camera up.
	/// \param range: Rotation range, 10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors turnCameraUp(unsigned int range = 50) = 0;

	/// \brief Turn the camera down.
	/// \param range: Rotation range, 10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors turnCameraDown(unsigned int range = 50) = 0;

	/// \brief Zoom the camera in.
	/// \param range: Zoom range, 10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors zoomCameraIn(unsigned int range = 50) = 0;

	/// \brief Zoom the camera out.
	/// \param range: Zoom range, 10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors zoomCameraOut(unsigned int range = 50) = 0;

};
END_ZOOM_VIDEO_SDK_NAMESPACE
#endif