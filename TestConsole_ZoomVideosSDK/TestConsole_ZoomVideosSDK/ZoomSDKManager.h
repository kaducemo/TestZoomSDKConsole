#pragma once

#include "IncludeZoomVideoSdk.h"
#include <atlstr.h>

using namespace ZOOM_VIDEO_SDK_NAMESPACE;
using std::vector;

class ZoomSDKManager:
	public ZOOM_VIDEO_SDK_NAMESPACE::IZoomVideoSDKDelegate,
	public ZOOM_VIDEO_SDK_NAMESPACE::IZoomVideoSDKRawDataPipeDelegate,
	public ZOOM_VIDEO_SDK_NAMESPACE::IZoomVideoSDKVirtualAudioMic, 
	public ZOOM_VIDEO_SDK_NAMESPACE::IZoomVideoSDKVirtualAudioSpeaker,
	public ZOOM_VIDEO_SDK_NAMESPACE::IZoomVideoSDKVideoSource
{
	typedef void (*MyCallback)(); //Used to sign a User List Change/ VirtualMicInitialized
	typedef void (*MyCallback2)(YUVRawDataI420*); //Used to receive video from a user subcribed pipe
	typedef void (*MyCallback3)(AudioRawData*); //Used to receive audio from all users
	typedef void (*MyCallback4)(AudioRawData*, IZoomVideoSDKUser*); //Used to receive audio from a user subcribed pipe	

private:
	/*SDK instance pointer*/
	IZoomVideoSDK* m_pVideoSDK = nullptr;	
	IZoomVideoSDKAudioSender* virtual_audio_sender_ = nullptr;
	IZoomVideoSDKVideoSender* video_sender_ = nullptr;

public:		
	/*Constructor*/
	ZoomSDKManager	() {};
	ZoomSDKManager	(ZoomVideoSDKInitParams initParams);
	
	/*Destructor*/
	~ZoomSDKManager() {};

	/*Other Methods*/
	IZoomVideoSDK* GetSdkInstance();	
	bool InitSession(ZoomVideoSDKSessionContext sessionContext);
	void LeaveSession();
	static void MyZoomMessageLoop();
	void TerminateSession();
	ZoomVideoSDKErrors Subscribe(IZoomVideoSDKUser* pUser, ZoomVideoSDKResolution resolution);
	void Unsubscribe(IZoomVideoSDKUser* pUser);
	vector<IZoomVideoSDKUser*> GetAllUsers();
	int GetUserCountInSession();
	void SendRawAudio(char* data, unsigned int data_length, int sample_rate);
	void SendRawVideo(char* frameBuffer, int width, int height, int frameLength, int rotation);
	

	//Properties
	bool IsConnected = false;

	//Callbacks
	MyCallback UsersListChanged = nullptr;

	MyCallback VirtualMicInitialized = nullptr;
	MyCallback RawAudioStoppedSend = nullptr;
	MyCallback StartToSendRawAudio = nullptr;

	MyCallback VirtualCamInitialized = nullptr;
	MyCallback StartToSendRawVideo = nullptr;
	MyCallback StopSendingRawVideo = nullptr;

	MyCallback2 RawVideoReceived = nullptr;

	MyCallback3 RawMixedAudioReceived = nullptr;
	MyCallback4 RawSingleUserAudioReceived = nullptr;

private:	
	// Herdado por meio de IZoomVideoSDKDelegate	
	virtual void onSessionJoin() override;
	virtual void onSessionLeave() override;
	virtual void onError(ZoomVideoSDKErrors errorCode, int detailErrorCode) override;
	virtual void onUserJoin(IZoomVideoSDKUserHelper* pUserHelper, IVideoSDKVector<IZoomVideoSDKUser*>* userList) override;
	virtual void onUserLeave(IZoomVideoSDKUserHelper* pUserHelper, IVideoSDKVector<IZoomVideoSDKUser*>* userList) override;
	virtual void onUserVideoStatusChanged(IZoomVideoSDKVideoHelper* pVideoHelper, IVideoSDKVector<IZoomVideoSDKUser*>* userList) override;
	virtual void onUserAudioStatusChanged(IZoomVideoSDKAudioHelper* pAudioHelper, IVideoSDKVector<IZoomVideoSDKUser*>* userList) override;
	virtual void onUserShareStatusChanged(IZoomVideoSDKShareHelper* pShareHelper, IZoomVideoSDKUser* pUser, ZoomVideoSDKShareStatus status) override;
	virtual void onLiveStreamStatusChanged(IZoomVideoSDKLiveStreamHelper* pLiveStreamHelper, ZoomVideoSDKLiveStreamStatus status) override;
	virtual void onChatNewMessageNotify(IZoomVideoSDKChatHelper* pChatHelper, IZoomVideoSDKChatMessage* messageItem) override;
	virtual void onUserHostChanged(IZoomVideoSDKUserHelper* pUserHelper, IZoomVideoSDKUser* pUser) override;
	virtual void onUserActiveAudioChanged(IZoomVideoSDKAudioHelper* pAudioHelper, IVideoSDKVector<IZoomVideoSDKUser*>* list) override;
	virtual void onSessionNeedPassword(IZoomVideoSDKPasswordHandler* handler) override;
	virtual void onSessionPasswordWrong(IZoomVideoSDKPasswordHandler* handler) override;
	virtual void onMixedAudioRawDataReceived(AudioRawData* data_) override;
	virtual void onOneWayAudioRawDataReceived(AudioRawData* data_, IZoomVideoSDKUser* pUser) override;
	virtual void onSharedAudioRawDataReceived(AudioRawData* data_) override;
	virtual void onUserManagerChanged(IZoomVideoSDKUser* pUser) override;
	virtual void onUserNameChanged(IZoomVideoSDKUser* pUser) override;
	virtual void onCameraControlRequestResult(IZoomVideoSDKUser* pUser, bool isApproved) override;
	virtual void onCameraControlRequestReceived(IZoomVideoSDKUser* pUser, ZoomVideoSDKCameraControlRequestType requestType, IZoomVideoSDKCameraControlRequestHandler* pCameraControlRequestHandler) override;
	virtual void onCommandReceived(IZoomVideoSDKUser* sender, const zchar_t* strCmd) override;
	virtual void onCommandChannelConnectResult(bool isSuccess) override;
	virtual void onInviteByPhoneStatus(PhoneStatus status, PhoneFailedReason reason) override;
	virtual void onCloudRecordingStatus(RecordingStatus status) override;
	virtual void onHostAskUnmute() override;

	// Herdado por meio de IZoomVideoSDKRawDataPipeDelegate
	virtual void onRawDataFrameReceived(YUVRawDataI420* data_) override;
	virtual void onRawDataStatusChanged(RawDataStatus status) override;

	//// Herdado por meio de IZoomVideoSDKVirtualAudioMic
	virtual void onMicInitialize(ZOOM_VIDEO_SDK_NAMESPACE::IZoomVideoSDKAudioSender* rawdata_sender) override;
	virtual void onMicStartSend() override;
	virtual void onMicStopSend() override;
	virtual void onMicUninitialized() override;

	////IZoomVideoSDKVirtualAudioSpeaker
	virtual void onVirtualSpeakerMixedAudioReceived(AudioRawData* data_) override;
	virtual void onVirtualSpeakerOneWayAudioReceived(AudioRawData* data_, ZOOM_VIDEO_SDK_NAMESPACE::IZoomVideoSDKUser* pUser) override;
	virtual void onVirtualSpeakerSharedAudioReceived(AudioRawData* data_) override;

	////IZoomVideoSDKVideoSource 
	virtual void onInitialize(IZoomVideoSDKVideoSender* sender, IVideoSDKVector< VideoSourceCapability >* support_cap_list, VideoSourceCapability& suggest_cap) override;
	virtual void onPropertyChange(IVideoSDKVector< VideoSourceCapability >* support_cap_list, VideoSourceCapability suggest_cap) override;
	virtual void onStartSend() override;
	virtual void onStopSend() override;
	virtual void onUninitialized() override;
};

