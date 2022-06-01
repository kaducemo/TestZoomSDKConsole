#include "ZoomSDKManager.h"

ZoomSDKManager::ZoomSDKManager(ZoomVideoSDKInitParams initParams)
{
	if (m_pVideoSDK == nullptr)
	{
		m_pVideoSDK = CreateZoomVideoSDKObj();

		/*Initialize SDK Instance*/
		ZoomVideoSDKErrors returnVal = m_pVideoSDK->initialize(initParams);
		Sleep(500);
		if (returnVal != ZoomVideoSDKErrors_Success) //Error...   
		{
			m_pVideoSDK = nullptr;
			return;
		}	
		else
		{
			m_pVideoSDK->addListener(this);			
		}
	}		
}

void ZoomSDKManager::onSessionJoin()
{
	IsConnected = true;
	std::cout << "\nLogged IN...\n";	
}

void ZoomSDKManager::onSessionLeave()
{	
	IsConnected = false;
	std::cout << "\nLogged OUT...\n";
}

void ZoomSDKManager::onError(ZoomVideoSDKErrors errorCode, int detailErrorCode)
{
	CString info;

	switch (errorCode)
	{
	case ZoomVideoSDKErrors_Meeting_Disconnecting:
		info.Format(_T("onError(): Disconnecting from session, Error:%d DetailCode: %d"), errorCode, detailErrorCode);
		break;
	case ZoomVideoSDKErrors_Meeting_Reconnecting:
		info.Format(_T("onError(): Reconnecting to session, Error:%d DetailCode: %d"), errorCode, detailErrorCode);
		break;
	case ZoomVideoSDKErrors_Meeting_Join_Failed:
		info.Format(_T("onError(): Failed to join session, Error:%d DetailCode: %d"), errorCode, detailErrorCode);
		break;
	default:
		info.Format(_T("onError(): Error:%d DetailCode: %d"), errorCode, detailErrorCode);
		break;
	}
}

void ZoomSDKManager::onUserJoin(IZoomVideoSDKUserHelper* pUserHelper, IVideoSDKVector<IZoomVideoSDKUser*>* userList)
{
	UsersListChanged();	
	int a = 1;
}

void ZoomSDKManager::onUserLeave(IZoomVideoSDKUserHelper* pUserHelper, IVideoSDKVector<IZoomVideoSDKUser*>* userList)
{
	UsersListChanged();	
	int a = 0;
}

void ZoomSDKManager::onUserVideoStatusChanged(IZoomVideoSDKVideoHelper* pVideoHelper, IVideoSDKVector<IZoomVideoSDKUser*>* userList)
{
}

void ZoomSDKManager::onUserAudioStatusChanged(IZoomVideoSDKAudioHelper* pAudioHelper, IVideoSDKVector<IZoomVideoSDKUser*>* userList)
{
	std::cout << "Audio Changed\n";
}

void ZoomSDKManager::onUserShareStatusChanged(IZoomVideoSDKShareHelper* pShareHelper, IZoomVideoSDKUser* pUser, ZoomVideoSDKShareStatus status)
{
}

void ZoomSDKManager::onLiveStreamStatusChanged(IZoomVideoSDKLiveStreamHelper* pLiveStreamHelper, ZoomVideoSDKLiveStreamStatus status)
{
}

void ZoomSDKManager::onChatNewMessageNotify(IZoomVideoSDKChatHelper* pChatHelper, IZoomVideoSDKChatMessage* messageItem)
{
}

void ZoomSDKManager::onUserHostChanged(IZoomVideoSDKUserHelper* pUserHelper, IZoomVideoSDKUser* pUser)
{
}

void ZoomSDKManager::onUserActiveAudioChanged(IZoomVideoSDKAudioHelper* pAudioHelper, IVideoSDKVector<IZoomVideoSDKUser*>* list)
{
}

void ZoomSDKManager::onSessionNeedPassword(IZoomVideoSDKPasswordHandler* handler)
{
}

void ZoomSDKManager::onSessionPasswordWrong(IZoomVideoSDKPasswordHandler* handler)
{
}

void ZoomSDKManager::onMixedAudioRawDataReceived(AudioRawData* data_)
{
	RawMixedAudioReceived(data_);
}

void ZoomSDKManager::onOneWayAudioRawDataReceived(AudioRawData* data_, IZoomVideoSDKUser* pUser)
{
	RawMixedAudioReceived(data_);
}

void ZoomSDKManager::onSharedAudioRawDataReceived(AudioRawData* data_)
{
	RawMixedAudioReceived(data_);
}

void ZoomSDKManager::onUserManagerChanged(IZoomVideoSDKUser* pUser)
{
}

void ZoomSDKManager::onUserNameChanged(IZoomVideoSDKUser* pUser)
{
}

void ZoomSDKManager::onCameraControlRequestResult(IZoomVideoSDKUser* pUser, bool isApproved)
{
}

void ZoomSDKManager::onCameraControlRequestReceived(IZoomVideoSDKUser* pUser, ZoomVideoSDKCameraControlRequestType requestType, IZoomVideoSDKCameraControlRequestHandler* pCameraControlRequestHandler)
{
}

void ZoomSDKManager::onCommandReceived(IZoomVideoSDKUser* sender, const zchar_t* strCmd)
{
}

void ZoomSDKManager::onCommandChannelConnectResult(bool isSuccess)
{
}

void ZoomSDKManager::onInviteByPhoneStatus(PhoneStatus status, PhoneFailedReason reason)
{
}

void ZoomSDKManager::onCloudRecordingStatus(RecordingStatus status)
{
}

void ZoomSDKManager::onHostAskUnmute()
{
}

void ZoomSDKManager::onRawDataFrameReceived(YUVRawDataI420* data_)
{	
	if (RawVideoReceived)
		RawVideoReceived(data_);
	else
		return;
}

ZoomVideoSDKErrors ZoomSDKManager::Subscribe(IZoomVideoSDKUser* pUser, ZoomVideoSDKResolution resolution)
{
	ZoomVideoSDKErrors err = ZoomVideoSDKErrors_Unknown;	

	// Get the video pipe for the user.
	IZoomVideoSDKRawDataPipe* pPipe = NULL;	
	pPipe = pUser->GetVideoPipe();	
	if (!pPipe)
		return err;

	// Call subscribe.	
	//err = pPipe->subscribe(ZoomVideoSDKResolution_180P, this);
	err = pPipe->subscribe(resolution, this);
	return err;
}

void ZoomSDKManager::Unsubscribe(IZoomVideoSDKUser* pUser)
{
	if (pUser->GetVideoPipe())
		pUser->GetVideoPipe()->unSubscribe(this);
	ZoomVideoSDKErrors err = ZoomVideoSDKErrors_Unknown;	
}

vector<IZoomVideoSDKUser*> ZoomSDKManager::GetAllUsers()
{
	vector<IZoomVideoSDKUser*> vect_all_user;

	if (m_pVideoSDK)
	{
		IZoomVideoSDKSession* session = m_pVideoSDK->getSessionInfo();
		if (session)
		{			
			IZoomVideoSDKUser* my_self = session->getMyself();
			if (my_self)
			{
				vect_all_user.push_back(my_self);
			}

			IVideoSDKVector<IZoomVideoSDKUser*>* remote_users = session->getRemoteUsers();

			if (remote_users)
			{
				for (int i = 0; i < remote_users->GetCount(); i++)
				{
					IZoomVideoSDKUser* user = remote_users->GetItem(i);
					if (!user) continue;
					vect_all_user.push_back(user);
				}
			}
		}
	}
	return vect_all_user;
}

int ZoomSDKManager::GetUserCountInSession()
{
	if (m_pVideoSDK)
	{
		return GetAllUsers().size();
	}
	return 0;
}

void ZoomSDKManager::onRawDataStatusChanged(RawDataStatus status)
{	
}

IZoomVideoSDK* ZoomSDKManager::GetSdkInstance()
{
	return m_pVideoSDK;
}

bool ZoomSDKManager::InitSession(ZoomVideoSDKSessionContext sessionContext)
{
	if (!m_pVideoSDK->joinSession(sessionContext))
	{
		CString cstrInfo;
		cstrInfo.Format(_T("Failed to join session"));
	}
	else
	{
		CString cstrInfo;
		cstrInfo.Format(_T("Joined session successfully."));
		int i = 1;		
		return true;
	}

	return false;
}

/*Dispaches Messages from OS*/
void ZoomSDKManager::MyZoomMessageLoop()
{
	BOOL bRet = false;
	MSG msg;
	while ((bRet = GetMessage(&msg, nullptr, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			// handle the error and possibly exit
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void ZoomSDKManager::LeaveSession()
{
	if (m_pVideoSDK)
	{
		m_pVideoSDK->leaveSession(false);
		std::cout << "\nUser LEFT the session...";
	}
}

void ZoomSDKManager::TerminateSession()
{
	if (m_pVideoSDK)
	{
		m_pVideoSDK->leaveSession(true);
		std::cout << "\nUser TERMINATED the session...";
	}	
}

void ZoomSDKManager::onMicInitialize(ZOOM_VIDEO_SDK_NAMESPACE::IZoomVideoSDKAudioSender* rawdata_sender)
{	
	if (rawdata_sender)
		virtual_audio_sender_ = rawdata_sender;
	else
		return;

	if ( VirtualMicInitialized && rawdata_sender)
		VirtualMicInitialized();	
}

void ZoomSDKManager::onMicStartSend()
{
	if(StartToSendRawAudio && virtual_audio_sender_)
		StartToSendRawAudio();			
}

void ZoomSDKManager::onMicStopSend()
{
	if (RawAudioStoppedSend && virtual_audio_sender_)
		RawAudioStoppedSend();
}

void ZoomSDKManager::onMicUninitialized()
{
	virtual_audio_sender_ = nullptr;
}

void ZoomSDKManager::onVirtualSpeakerMixedAudioReceived(AudioRawData* data_)
{	
	if(RawMixedAudioReceived)
		RawMixedAudioReceived(data_);
}

void ZoomSDKManager::onVirtualSpeakerOneWayAudioReceived(AudioRawData* data_, ZOOM_VIDEO_SDK_NAMESPACE::IZoomVideoSDKUser* pUser)
{	
	if (RawSingleUserAudioReceived)
		RawSingleUserAudioReceived(data_, pUser);
}

void ZoomSDKManager::onVirtualSpeakerSharedAudioReceived(AudioRawData* data_)
{

}

void ZoomSDKManager::SendRawAudio(char* data, unsigned int data_length, int sample_rate)
{
	if (!virtual_audio_sender_)
	{
		return;
	}	
	ZoomVideoSDKErrors err = virtual_audio_sender_->Send(data, data_length, sample_rate);
	if (err)
	{
		std::cout << "Error sending audio\n";
	}
}

void ZoomSDKManager::SendRawVideo(char* frameBuffer, int width, int height, int frameLength, int rotation)
{
	if (!video_sender_)
	{
		return;
	}	
	video_sender_->sendVideoFrame(frameBuffer, width, height, frameLength, rotation);	
}


void ZoomSDKManager::onInitialize(IZoomVideoSDKVideoSender* sender, IVideoSDKVector< VideoSourceCapability >* support_cap_list, VideoSourceCapability& suggest_cap)
{
	//when set virtual video source, go here!!!
	if (!sender) 
		return;	
		
	video_sender_ = sender;

	if (!VirtualCamInitialized)
		return;

	//capability
	if (!support_cap_list) 
		return;

	TCHAR szDbg[512] = { 0 };
	unsigned int nCount = support_cap_list->GetCount();
	CString s="";
	CString srec = "";
	for (unsigned int i = 0; i < nCount; i++)
	{		
		VideoSourceCapability cap_ = support_cap_list->GetItem(i);		
		s.Format(_T("onInitialize cap index:%d: frame=%d, Height=%d, width=%d \r\n"), i, cap_.frame, cap_.height, cap_.width);
		std::wcout << s.GetString();
	}

	srec.Format(_T("\r\nRecomended cap frame=%d, Height=%d, width=%d \r\n"), suggest_cap.frame, suggest_cap.height, suggest_cap.width);
	std::wcout << srec.GetString();
	VirtualCamInitialized();
}

void ZoomSDKManager::onPropertyChange(IVideoSDKVector< VideoSourceCapability >* support_cap_list, VideoSourceCapability suggest_cap)
{

}

void ZoomSDKManager::onStartSend()
{
	if (StartToSendRawVideo && video_sender_)
		StartToSendRawVideo();
}

void ZoomSDKManager::onStopSend() 
{

}

void ZoomSDKManager::onUninitialized() 
{

}