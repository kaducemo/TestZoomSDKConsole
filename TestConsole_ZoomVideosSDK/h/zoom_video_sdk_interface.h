/*!
* \file zoom_video_sdk_interface.h
* \brief zoom video sdk interface.
*
*/

#ifndef _ZOOM_VIDEO_SDK_INTERFACE_H_
#define _ZOOM_VIDEO_SDK_INTERFACE_H_
#include "zoom_video_sdk_def.h"

BEGIN_ZOOM_VIDEO_SDK_NAMESPACE
class IZoomVideoSDKSession;
class IZoomVideoSDKDelegate;
class IZoomVideoSDKAudioHelper;
class IZoomVideoSDKVideoHelper;
class IZoomVideoSDKUserHelper;
class IZoomVideoSDKShareHelper;
class IZoomVideoSDKRecordingHelper;
class IZoomVideoSDKLiveStreamHelper;
class IZoomVideoSDKChatHelper;
class IZoomVideoSDKCmdChannel;
class IZoomVideoSDKPhoneHelper;
/// \brief API manager interface.
///
class IZoomVideoSDK
{
public:
	virtual ~IZoomVideoSDK(){}

	/// \brief Init Zoom Video SDK.
	/// \param params Parameters for init zoom video sdk. For more details, see \link ZoomVideoSDKInitParams \endlink structure.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
    virtual ZoomVideoSDKErrors initialize(ZoomVideoSDKInitParams& params) = 0;
	
	/// \brief Clean up ZOOM Video SDK.
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors cleanup() = 0;
	
	/// \brief Add session callback event handler.
	/// \param listener A pointer to the IZoomVideoSDKDelegate that receives the session callback event.
	virtual void addListener(IZoomVideoSDKDelegate* listener) = 0;
	
	/// \brief Remove session callback event handler.
	/// \param listener A pointer to the IZoomVideoSDKDelegate that receives the session callback event.
	virtual void removeListener(IZoomVideoSDKDelegate* listener) = 0;
	
	/// \brief Join the session.
	/// \param params The parameter is used to join session. For more details, see \link ZoomVideoSDKSessionContext \endlink structure. 
	/// \return If the function succeeds, the return value is the pointer to IZoomVideoSDKSession object.
	///Otherwise NULL. To get extended error information, see \link IZoomVideoSDKSession \endlink enum.
	virtual IZoomVideoSDKSession* joinSession(ZoomVideoSDKSessionContext& params) = 0;
	
	/// \brief Leave session.
	/// \param end TRUE indicates to end session. FALSE indicates to leave session. 
	/// \return If the function succeeds, the return value is ZoomVideoSDKErrors_Success.
	///Otherwise failed. To get extended error information, see \link ZoomVideoSDKErrors \endlink enum.
	virtual ZoomVideoSDKErrors leaveSession(bool end) = 0;
	
	/// \brief Get session information object.
	/// \return If the function succeeds, the return value is the pointer to IZoomVideoSDKSession object.
	///Otherwise NULL.
	virtual IZoomVideoSDKSession* getSessionInfo() = 0;
	
	/// \brief Determine if is in session.
	/// \return True indicates is in session, otherwise return false.
	virtual bool isInSession() = 0;
	
	/// \brief Get the sdk version
	/// \return If the function succeeds, the return value is sdk version. Otherwise returns NULL.
	virtual const zchar_t* getSDKVersion() = 0;
	
	/// \brief Get audio helper object.
	/// \return If the function succeeds, the return value is the audio helper object. Otherwise returns NULL. For more details, see \link IZoomVideoSDKAudioHelper \endlink.
	virtual IZoomVideoSDKAudioHelper* getAudioHelper() = 0;
	
	/// \brief Get video helper object.
	/// \return If the function succeeds, the return value is the video helper object. Otherwise returns NULL. For more details, see \link IZoomVideoSDKVideoHelper \endlink.
	virtual IZoomVideoSDKVideoHelper* getVideoHelper() = 0;
	
	/// \brief Get recording helper object.
	/// \return If the function succeeds, the return value is the recording helper object. Otherwise returns NULL. For more details, see \link IZoomVideoSDKVideoHelper \endlink.
	virtual IZoomVideoSDKRecordingHelper* getRecordingHelper() = 0;

	/// \brief Get user helper object.
	/// \return If the function succeeds, the return value is the user helper object. Otherwise returns NULL. For more details, see \link IZoomVideoSDKUserHelper \endlink.
	virtual IZoomVideoSDKUserHelper*  getUserHelper() = 0;
	
	/// \brief Get share helper object.
	/// \return If the function succeeds, the return value is the share helper object. Otherwise returns NULL. For more details, see \link IZoomVideoSDKShareHelper \endlink.
	virtual IZoomVideoSDKShareHelper* getShareHelper() = 0;
	
	/// \brief Get live stream helper object.
	/// \return If the function succeeds, the return value is the live stream helper object. Otherwise returns NULL. For more details, see \link IZoomVideoSDKLiveStreamHelper \endlink.
	virtual IZoomVideoSDKLiveStreamHelper* getLiveStreamHelper() = 0;


	/// \brief Get phone helper object.
	/// \return If the function succeeds, the return value is the phone helper object. Otherwise returns NULL. For more details, see \link IZoomVideoSDKPhoneHelper \endlink.
	virtual IZoomVideoSDKPhoneHelper* getPhoneHelper() = 0;
	
	/// \brief Get chat helper object.
	/// \return If the function succeeds, the return value is the chat helper object. Otherwise returns NULL. For more details, see \link IZoomVideoSDKChatHelper \endlink.
	virtual IZoomVideoSDKChatHelper* getChatHelper() = 0;
	
	/// \brief Get an instance to access the command channel.
	/// \return If the function succeeds, the return value is the command channel object. Otherwise returns NULL. For more details, see \link IZoomVideoSDKCmdChannel \endlink.
	virtual IZoomVideoSDKCmdChannel* getCmdChannel() = 0;
};
END_ZOOM_VIDEO_SDK_NAMESPACE
#endif
