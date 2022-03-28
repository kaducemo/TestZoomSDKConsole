/*!
* \file zoom_video_sdk_user_helper_interface.h
* \brief user helper
*
*/

#ifndef _ZOOM_VIDEO_SDK_USER_HELPER_INTERFACE_H_
#define _ZOOM_VIDEO_SDK_USER_HELPER_INTERFACE_H_
#include "zoom_video_sdk_def.h"
#include "zoom_video_sdk_vector_interface.h"

BEGIN_ZOOM_VIDEO_SDK_NAMESPACE
/*! \struct ZoomVideoSDKVideoStatus
	\brief Video status information.
*/
typedef struct
{
	bool isHasVideoDevice;
	bool isOn;
}ZoomVideoSDKVideoStatus;

/*! \struct ZoomVideoSDKAudioType
	\brief Audio type information.
*/
typedef enum {
	ZoomVideoSDKAudioType_VOIP,
	ZoomVideoSDKAudioType_None,
}ZoomVideoSDKAudioType;

/*! \struct ZoomVideoSDKAudioStatus
	\brief Audio status information.
*/
typedef struct
{
	ZoomVideoSDKAudioType audioType;
	bool isMuted;
	bool isTalking;
}ZoomVideoSDKAudioStatus;

/*! \struct ZoomVideoSDKVideoStatisticInfo
	\brief Video statistic information.
*/
typedef struct
{
	int width;
	int height;
	int fps;
	int bpf;
}ZoomVideoSDKVideoStatisticInfo;

/*! \struct ZoomVideoSDKShareStatisticInfo
	\brief Share statistic information.
*/
typedef struct
{
	int width;
	int height;
	int fps;
	int bpf;
}ZoomVideoSDKShareStatisticInfo;

typedef enum
{
	ZoomVideoSDKResolution_90P = 0,
	ZoomVideoSDKResolution_180P,
	ZoomVideoSDKResolution_360P,
	ZoomVideoSDKResolution_720P,
#if (defined _WIN32) || (defined __MACOS__)
	ZoomVideoSDKResolution_1080P,
#endif
	ZoomVideoSDKResolution_NoUse = 100,
}ZoomVideoSDKResolution;

typedef enum 
{
	RawData_On,
	RawData_Off,
}RawDataStatus;

/// \brief Video/share raw data sink interface.
///
class IZoomVideoSDKRawDataPipeDelegate
{
public:
	/// \brief Call when subscribed data received.
	/// \param data_, data object.
	virtual void onRawDataFrameReceived(YUVRawDataI420* data_) = 0;

	/// \brief Call when subscribed data status changed.
	/// \param status, current data status.
	virtual void onRawDataStatusChanged(RawDataStatus status) = 0;

	virtual ~IZoomVideoSDKRawDataPipeDelegate() {};
};

/// \brief Video/share raw data pipe interface.
///
class IZoomVideoSDKRawDataPipe
{
public:
	/// \brief Subscribe video/share.
	/// \param resolution, subscribe size.
	/// \param listener, callback sink object.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors subscribe(ZoomVideoSDKResolution resolution, IZoomVideoSDKRawDataPipeDelegate* listener) = 0;
	
	/// \brief Unsubscribe video/share.
	/// \param listener, the callback sink object.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors unSubscribe(IZoomVideoSDKRawDataPipeDelegate* listener) = 0;
};


/// \brief Camera control interface.
///
class IZoomVideoSDKCameraControlRequestHandler
{
public:
	virtual ~IZoomVideoSDKCameraControlRequestHandler() {}

	/// \brief Approve the remote camera control request.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	virtual ZoomVideoSDKErrors approve() = 0;

	/// \brief Decline the remote camera control request.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	virtual ZoomVideoSDKErrors decline() = 0;
};

class IZoomVideoSDKRemoteCameraControlHelper
{
public:
	virtual ~IZoomVideoSDKRemoteCameraControlHelper() {}

	/// \brief Request to control remote camera.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	virtual ZoomVideoSDKErrors requestControlRemoteCamera() = 0;

	/// \brief Give up control of the remote camera.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	virtual ZoomVideoSDKErrors giveUpControlRemoteCamera() = 0;

	/// \brief Turn the camera to the left.
	/// \param range: Rotation range,  10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	virtual ZoomVideoSDKErrors turnLeft(unsigned int range = 50) = 0;

	/// \brief Turn the camera to the right.
	/// \param range: Rotation range,  10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	virtual ZoomVideoSDKErrors turnRight(unsigned int range = 50) = 0;

	/// \brief Turn the camera up.
	/// \param range: Rotation range,  10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	virtual ZoomVideoSDKErrors turnUp(unsigned int range = 50) = 0;

	/// \brief Turn the camera down.
	/// \param range: Rotation range,  10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	virtual ZoomVideoSDKErrors turnDown(unsigned int range = 50) = 0;

	/// \brief Zoom the camera in.
	/// \param range: Zoom range,  10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	virtual ZoomVideoSDKErrors zoomIn(unsigned int range = 50) = 0;

	/// \brief Zoom the camera out.
	/// \param range: Zoom range,  10 <= range <= 100.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	virtual ZoomVideoSDKErrors zoomOut(unsigned int range = 50) = 0;
};


/// \brief User object interface.
///
class IZoomVideoSDKUser
{
public:
	virtual ~IZoomVideoSDKUser(){}
	
	/// \brief Get custom id.
	/// \return The Custom id of the user object.
	virtual const zchar_t* getCustomIdentity() = 0;

	/// \brief Get user name.
	/// \return The name of the user object.
	virtual const zchar_t* getUserName() = 0;

	/// \brief Get user id of the user.
	/// \return The user id of the user object.
	virtual const zchar_t* getUserID() = 0;

	/// \brief Get video status.
	/// \return Video status of the user object.
	virtual ZoomVideoSDKVideoStatus getVideoStatus() = 0;

	/// \brief Get audio status.
	/// \return Audio status of the user object.
	virtual ZoomVideoSDKAudioStatus getAudioStatus() = 0;
	
	/// \brief Get share status.
	/// \return Share status of the user object.
	virtual ZoomVideoSDKShareStatus getShareStatus() = 0;
	
	/// \brief Determine if the user is session host.
	/// \return True if current user is host. Otherwise returns false.
	virtual bool isHost() = 0;

	/// \brief Determine if the user is session manager(coHost).
	/// \return True if current user is session manager(coHost). Otherwise returns false.
	virtual bool isManager() = 0;
	
	/// \brief Get video statistic information of the user.
	/// \return Statistic information.
	virtual ZoomVideoSDKVideoStatisticInfo getVideoStatisticInfo() = 0;

	/// \brief Get share statistic information of the user.
	/// \return Statistic information.
	virtual ZoomVideoSDKShareStatisticInfo getShareStatisticInfo() = 0;
	
	/// \brief Get video raw data pipe.
	/// \return Pipe object.
	virtual IZoomVideoSDKRawDataPipe* GetVideoPipe() = 0;

	/// \brief Get share raw data pipe.
	/// \return Pipe object.
	virtual IZoomVideoSDKRawDataPipe* GetSharePipe() = 0;

	/// \brief Get the helper class instance to access the remote camera control.
	/// \return If the function succeeds, the return value is the remote camera control helper object.
	///Otherwise returns NULL. For more details, see \link IZoomVideoSDKRemoteCameraControlHelper \endlink.
	virtual IZoomVideoSDKRemoteCameraControlHelper* getRemoteCameraControlHelper() = 0;
};

/// \brief User helper interface.
///
class IZoomVideoSDKUserHelper
{
public:
	/// \brief Change name of user object.
	/// \param name, the new name of the user object.
	/// \return True if success. Otherwise returns false.
	virtual bool changeName(const zchar_t* name, IZoomVideoSDKUser* pUser) = 0;

	/// \brief Make some user as session host.
	/// \param pUser, the user object.
	/// \return True if success. Otherwise returns false.
	virtual bool makeHost(IZoomVideoSDKUser* pUser) = 0;

	/// \brief Make some user as session manager(coHost).
	/// \param pUser, the user object.
	/// \return True if success. Otherwise returns false.
	virtual bool makeManager(IZoomVideoSDKUser* pUser) = 0;

	/// \brief Revoke some user's manager right.
	/// \param pUser, the user object.
	/// \return True if success. Otherwise returns false.
	virtual bool revokeManager(IZoomVideoSDKUser* pUser) = 0;

	/// \brief Remove some user from current session.
	/// \param pUser, the user object.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors removeUser(IZoomVideoSDKUser* pUser) = 0;
};
END_ZOOM_VIDEO_SDK_NAMESPACE
#endif