/*!
* \file zoom_video_sdk_def.h
* \brief Zoom Video SDK Common Definition File.
*
*/

#ifndef _ZOOM_VIDEO_SDK_DEF_H_
#define _ZOOM_VIDEO_SDK_DEF_H_
#include <iostream>
#include "zoom_video_sdk_platform.h"
#include "zoom_sdk_raw_data_def.h"

#define ZOOM_VIDEO_SDK_NAMESPACE ZOOMVIDEOSDK
#define BEGIN_ZOOM_VIDEO_SDK_NAMESPACE namespace ZOOM_VIDEO_SDK_NAMESPACE {
#define END_ZOOM_VIDEO_SDK_NAMESPACE };
#define USING_ZOOM_VIDEO_SDK_NAMESPACE using namespace ZOOM_VIDEO_SDK_NAMESPACE;

BEGIN_ZOOM_VIDEO_SDK_NAMESPACE
typedef enum
{ 
	ZoomVideoSDKErrors_Success = 0,///<Success.
	ZoomVideoSDKErrors_Wrong_Usage,
	ZoomVideoSDKErrors_Internal_Error,
	ZoomVideoSDKErrors_Uninitialize,
	ZoomVideoSDKErrors_Memory_Error,
	ZoomVideoSDKErrors_Load_Module_Error,
	ZoomVideoSDKErrors_UnLoad_Module_Error,
	ZoomVideoSDKErrors_Invalid_Parameter,
	ZoomVideoSDKErrors_Call_Too_Frequently,
	ZoomVideoSDKErrors_Unknown,
	ZoomVideoSDKErrors_Auth_Error = 1001,
	ZoomVideoSDKErrors_Auth_Empty_Key_or_Secret,
	ZoomVideoSDKErrors_Auth_Wrong_Key_or_Secret,
	ZoomVideoSDKErrors_Auth_DoesNot_Support_SDK,
	ZoomVideoSDKErrors_Auth_Disable_SDK,
	ZoomVideoSDKErrors_JoinSession_NoSessionName = 1500,
	ZoomVideoSDKErrors_JoinSession_NoSessionToken,
	ZoomVideoSDKErrors_JoinSession_NoUserName,
	ZoomVideoSDKErrors_JoinSession_Invalid_SessionName,
	ZoomVideoSDKErrors_JoinSession_Invalid_Password,
	ZoomVideoSDKErrors_JoinSession_Invalid_SessionToken,
	ZoomVideoSDKErrors_JoinSession_SessionName_TooLong,
	ZoomVideoSDKErrors_JoinSession_Token_MismatchedSessionName,
	ZoomVideoSDKErrors_JoinSession_Token_NoSessionName,
	ZoomVideoSDKErrors_JoinSession_Token_RoleType_EmptyOrWrong,
	ZoomVideoSDKErrors_JoinSession_Token_UserIdentity_TooLong,
	ZoomVideoSDKErrors_MeetingModule_Not_Found = 2001,
	ZoomVideoSDKErrors_MeetingService_Invaild,
	ZoomVideoSDKErrors_Meeting_Join_Failed,
	ZoomVideoSDKErrors_Meeting_No_Rights,
	ZoomVideoSDKErrors_Meeting_Already_In_Progress,
	ZoomVideoSDKErrors_Meeting_Dont_Support_MeetingType,
	ZoomVideoSDKErrors_Meeting_Reconnecting,
	ZoomVideoSDKErrors_Meeting_Disconnecting,
	ZoomVideoSDKErrors_Meeting_Not_Started,
	ZoomVideoSDKErrors_Meeting_Need_Password,
	ZoomVideoSDKErrors_Meeting_Password_Wrong,
	ZoomVideoSDKErrors_Meeting_Remote_DB_Error,
	ZoomVideoSDKErrors_Meeting_Invalid_Param,
	ZoomVideoSDKErrors_Meeting_Dont_Support_Feature,
	ZoomVideoSDKErrors_Meeting_Audio_Error = 3000,
	ZoomVideoSDKErrors_Meeting_Audio_No_Microphone,
	ZoomVideoSDKErrors_Meeting_Video_Error = 4000,
	ZoomVideoSDKErrors_Meeting_Video_Device_Error,
	ZoomVideoSDKErrors_Meeting_Live_Stream_Error = 5000,
	ZoomVideoSDKErrors_Meeting_Phone_Error = 5500,

	ZoomVideoSDKErrors_RAWDATA_MALLOC_FAILED = 6001,
	ZoomVideoSDKErrors_RAWDATA_NOT_IN_Session,
	ZoomVideoSDKErrors_RAWDATA_NO_LICENSE,
	ZoomVideoSDKErrors_RAWDATA_VIDEO_MODULE_NOT_READY,
	ZoomVideoSDKErrors_RAWDATA_VIDEO_MODULE_ERROR,
	ZoomVideoSDKErrors_RAWDATA_VIDEO_DEVICE_ERROR,
	ZoomVideoSDKErrors_RAWDATA_NO_VIDEO_DATA,
	ZoomVideoSDKErrors_RAWDATA_SHARE_MODULE_NOT_READY,
	ZoomVideoSDKErrors_RAWDATA_SHARE_MODULE_ERROR,
	ZoomVideoSDKErrors_RAWDATA_NO_SHARE_DATA,
	ZoomVideoSDKErrors_RAWDATA_AUDIO_MODULE_NOT_READY,
	ZoomVideoSDKErrors_RAWDATA_AUDIO_MODULE_ERROR,
	ZoomVideoSDKErrors_RAWDATA_NO_AUDIO_DATA,
	ZoomVideoSDKErrors_RAWDATA_PREPROCESS_RAWDATA_ERROR,
	ZoomVideoSDKErrors_RAWDATA_NO_DEVICE_RUNNING,
	ZoomVideoSDKErrors_RAWDATA_INIT_DEVICE,
	ZoomVideoSDKErrors_RAWDATA_VIRTUAL_DEVICE,
	ZoomVideoSDKErrors_RAWDATA_CANNOT_CHANGE_VIRTUAL_DEVICE_IN_PREVIEW,
	ZoomVideoSDKErrors_RAWDATA_INTERNAL_ERROR,
	ZoomVideoSDKErrors_RAWDATA_SEND_TOO_MUCH_DATA_IN_SINGLE_TIME,
	ZoomVideoSDKErrors_RAWDATA_SEND_TOO_FREQUENTLY,
	ZoomVideoSDKErrors_RAWDATA_VIRTUAL_MIC_IS_TERMINATE,

	ZoomVideoSDKErrors_Meeting_Share_Error = 7001,
	ZoomVideoSDKErrors_Meeting_Share_Module_Not_Ready,
	ZoomVideoSDKErrors_Meeting_Share_You_Are_Not_Sharing,
	ZoomVideoSDKErrors_Meeting_Share_Type_Is_Not_Support,
	ZoomVideoSDKErrors_Meeting_Share_Internal_Error,

}ZoomVideoSDKErrors;

typedef enum 
{
	ZoomVideoSDKShareStatus_None,
	ZoomVideoSDKShareStatus_Start,
	ZoomVideoSDKShareStatus_Pause,
	ZoomVideoSDKShareStatus_Resume,
	ZoomVideoSDKShareStatus_Stop,
}ZoomVideoSDKShareStatus;

typedef enum
{
	ZoomVideoSDKLiveStreamStatus_None,
	ZoomVideoSDKLiveStreamStatus_InProgress,
	ZoomVideoSDKLiveStreamStatus_Connecting,
	ZoomVideoSDKLiveStreamStatus_FailedTimeout,
	ZoomVideoSDKLiveStreamStatus_StartFailed,
	ZoomVideoSDKLiveStreamStatus_Ended,
}ZoomVideoSDKLiveStreamStatus;

typedef enum
{
	ZoomVideoSDKRawDataMemoryModeStack = 0,
	ZoomVideoSDKRawDataMemoryModeHeap,
}ZoomVideoSDKRawDataMemoryMode;

typedef enum
{
	RAW_DATA_TYPE_VIDEO = 0,
	RAW_DATA_TYPE_SHARE,
}ZoomVideoSDKRawDataType;


typedef enum
{
	ZoomVideoSDKCameraControlRequestType_RequestControl = 0,
	ZoomVideoSDKCameraControlRequestType_GiveUpControl
	
}ZoomVideoSDKCameraControlRequestType;

/*! \enum RecordingStatus
	\brief  An enum representing the status of the recording status.
*/
enum RecordingStatus
{
	/// \brief The recording has started or resumed.
	Recording_Start,
	/// \brief The recording has stopped.
	Recording_Stop,
	/// \brief Recording is unsuccessful due to not having enough storage space.
	///	Please try to:
	///		Free up space
	///		Purchase more space
	Recording_DiskFull,
	/// \brief The recording has paused.
	Recording_Pause,
};

/*! \struct ZoomVideoSDKInitParams
	\brief Initialization parameters.
*/
struct ZoomVideoSDKInitParams
{
	const zchar_t* domain; /// \brief Web domain, required.
	const zchar_t* logFilePrefix; /// \brief Prefix for log file name, optional.
	bool  enableLog; /// \brief Enable log or not, optional.
	bool  enableIndirectRawdata; /// \brief Enable indirect rawdata or not, optional.
	ZoomVideoSDKRawDataMemoryMode audioRawDataMemoryMode; /// \brief Store audio raw data buffer in heap or stack, optional.
	ZoomVideoSDKRawDataMemoryMode videoRawDataMemoryMode; /// \brief Store video raw data buffer in heap or stack, optional.
	ZoomVideoSDKRawDataMemoryMode shareRawDataMemoryMode; /// \brief Store share raw data buffer in heap or stack, optional.

	ZoomVideoSDKInitParams()
	{
		domain = NULL;
		logFilePrefix = NULL;
		enableLog = false;
#if (defined __IOS__) || (defined CMM_MAC)
		enableIndirectRawdata = true;
#else
		enableIndirectRawdata = false;
#endif
		audioRawDataMemoryMode = ZoomVideoSDKRawDataMemoryModeStack;
		videoRawDataMemoryMode = ZoomVideoSDKRawDataMemoryModeStack;
		shareRawDataMemoryMode = ZoomVideoSDKRawDataMemoryModeStack;
	}
};

/*! \struct ZoomVideoSDKVideoOption
	\brief Video option used by ZoomVideoSDKSessionContext.
*/
struct ZoomVideoSDKVideoOption 
{
    bool localVideoOn; /// \brief Turn local video on or off.
	ZoomVideoSDKVideoOption()
	{
		localVideoOn = true;
	}
};
/*! \struct ZoomVideoSDKAudioOption
	\brief Audio options used by ZoomVideoSDKSessionContext.
*/
struct ZoomVideoSDKAudioOption 
{
    bool connect; /// \brief Connect local audio or not.
    bool mute;    /// \brief Mute audio or not.

	ZoomVideoSDKAudioOption()
	{
		connect = true;
		mute = false;
	}
};

class IZoomVideoSDKVideoSourcePreProcessor;
class IZoomVideoSDKVideoSource;
class IZoomVideoSDKVirtualAudioMic;
class IZoomVideoSDKVirtualAudioSpeaker;

/*! \struct ZoomVideoSDKSessionContext
	\brief Session context information.
*/
struct ZoomVideoSDKSessionContext
{
    const zchar_t* sessionName;		///<Session name, required.
    const zchar_t* sessionPassword; ///<Meeting password, optional.
    const zchar_t* userName;        ///<Display name in meeting, required.
    const zchar_t* token;			///<JWT token to join session, required.
    ZoomVideoSDKVideoOption videoOption; ///<Video option, optional.
    ZoomVideoSDKAudioOption audioOption; ///<Audio option, optional.
	IZoomVideoSDKVideoSourcePreProcessor* preProcessor; ///<Camera data preprocessor object pointer, optional.
	IZoomVideoSDKVideoSource* externalVideoSource; ///<Virtual camera object pointer, optional.
	IZoomVideoSDKVirtualAudioMic* virtualAudioMic; ///<Virtual mic object pointer, optional.
	IZoomVideoSDKVirtualAudioSpeaker* virtualAudioSpeaker; ///<Virtual speaker object pointer, optional.
	unsigned int sessionIdleTimeoutMins; ///<The amount of time in minutes after which an idle session will end. If the value is 0, the session will stay alive indefinitely.

	ZoomVideoSDKSessionContext()
	{
		sessionName = NULL;
		sessionPassword = NULL;
		userName = NULL;
		token = NULL;
		preProcessor = NULL;
		externalVideoSource = NULL;
		virtualAudioMic = NULL;
		virtualAudioSpeaker = NULL;
		sessionIdleTimeoutMins = 40;
	}
};
END_ZOOM_VIDEO_SDK_NAMESPACE
#endif