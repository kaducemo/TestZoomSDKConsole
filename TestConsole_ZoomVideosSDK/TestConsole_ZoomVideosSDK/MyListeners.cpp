#include "MyListeners.h"

void MyListeners::onSessionJoin()
{    
    std::cout << "User is Logged in...";
    // You have successfully joined the session.
}

void MyListeners::onSessionLeave()
{    
    std::cout << "User is Logged out";
    // You have successfully joined the session.
}

void MyListeners::onError(ZoomVideoSDKErrors errorCode, int detailErrorCode)
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

void MyListeners::onUserJoin(IZoomVideoSDKUserHelper* pUserHelper, IVideoSDKVector<IZoomVideoSDKUser*>* userList)
{
    CString strInfo;
    IZoomVideoSDKUser* pUser;
    int count = userList->GetCount();

    for (int i = 0; i < count; i++)
    {
        pUser = userList->GetItem(i);
        if (!pUser) continue;

        strInfo.Format(_T("A user joined the session: name=%s"), pUser->getUserName());
    }
}

void MyListeners::onUserLeave(IZoomVideoSDKUserHelper* pUserHelper, IVideoSDKVector<IZoomVideoSDKUser*>* userList)
{
    CString strInfo;
    IZoomVideoSDKUser* pUser;
    int count = userList->GetCount();
    
    for (int i = 0; i < count; i++)
    {
        pUser = userList->GetItem(i);
        if (!pUser) continue;
    
        strInfo.Format(_T("A user left the session: name=%s"), pUser->getUserName());
    }
}

void MyListeners::onUserVideoStatusChanged(IZoomVideoSDKVideoHelper* pVideoHelper, IVideoSDKVector<IZoomVideoSDKUser*>* userList)
{
	CString strInfo;
    IZoomVideoSDKUser* pUser;
    int count = userList->GetCount();

	for (int i = 0; i < count; i++)
	{
		pUser = userList->GetItem(i);
		strInfo.Format(_T("A user's video status changed: userid=%s, name=%s, status=%s"), pUser->getUserName(), pUser->getVideoStatus());
	}
}

void MyListeners::onUserAudioStatusChanged(IZoomVideoSDKAudioHelper* pAudioHelper, IVideoSDKVector<IZoomVideoSDKUser*>* userList)
{
	    CString strInfo;
    IZoomVideoSDKUser* pUser;
    int count = userList->GetCount();

	for (int i = 0; i < count; i++)
	{
		pUser = userList->GetItem(i);
		strInfo.Format(_T("A user's audio status changed: name=%s, status=%s"), pUser->getUserName(), pUser->getAudioStatus());
	}
}

void MyListeners::onUserShareStatusChanged(IZoomVideoSDKShareHelper* pShareHelper, IZoomVideoSDKUser* pUser, ZoomVideoSDKShareStatus status)
{
	CString strInfo;
    switch (status)
    {
    case ZoomVideoSDKShareStatus_None:
        strInfo.Format(_T("User's share status changed to None: name=%s"), pUser->getUserName());
        break;
    case ZoomVideoSDKShareStatus_Pause:
        strInfo.Format(_T("User paused sharing: name=%s"), pUser->getUserName());
        break;
    case ZoomVideoSDKShareStatus_Resume:
        strInfo.Format(_T("User resumed sharing: name=%s"), pUser->getUserName());
        break;
    case ZoomVideoSDKShareStatus_Start:
        strInfo.Format(_T("User began sharing: name=%s"), pUser->getUserName());
        break;
    case ZoomVideoSDKShareStatus_Stop:
        strInfo.Format(_T("User stopped sharing: name=%s"), pUser->getUserName());
        break;
    }
}

void MyListeners::onLiveStreamStatusChanged(IZoomVideoSDKLiveStreamHelper* pLiveStreamHelper, ZoomVideoSDKLiveStreamStatus status)
{
	CString strInfo;
    switch (status)
    {
    case ZoomVideoSDKLiveStreamStatus_Connecting:
        strInfo = _T("Live stream is connecting.");
        break;
    case ZoomVideoSDKLiveStreamStatus_Ended:
        strInfo = _T("Live stream has ended.");
        break;
    case ZoomVideoSDKLiveStreamStatus_FailedTimeout:
        strInfo = _T("Live stream failed: Timeout.");
        break;
    case ZoomVideoSDKLiveStreamStatus_InProgress:
        strInfo = _T("Live stream is in progress.");
        break;
    case ZoomVideoSDKLiveStreamStatus_StartFailed:
        strInfo = _T("Live stream failed to start.");
        break;
    case ZoomVideoSDKLiveStreamStatus_None:
        strInfo = _T("Live stream status changed to none.");
        break;
    }
}

void MyListeners::onChatNewMessageNotify(IZoomVideoSDKChatHelper* pChatHelper, IZoomVideoSDKChatMessage* messageItem)
{
    //    if (!messageItem)
    //    return;

    //CString strInfo;
    //const zchar_t* szMessageContent = messageItem->getContent();
    //IZoomVideoSDKUser* pRecievingUser = messageItem->getReceiveUser();
    //IZoomVideoSDKUser* pSendingUser = messageItem->getSendUser();

    //// Check if this is a public message. If false, this is a private message.
    //bool bIsChatToAll = messageItem->isChatToAll();
    //// Check if this message was sent from the local user.
    //bool bIsSelfSend = messageItem->isSelfSend();

    //time_t time = messageItem->getTimeStamp();

    //if (!pSendUser)
    //    return;

    //strInfo.Format(_T("New message from %s to %s  %s"), pSendUser->getUserName(), pRcvUser->getUserName(), szContent);
}

void MyListeners::onUserHostChanged(IZoomVideoSDKUserHelper* pUserHelper, IZoomVideoSDKUser* pUser)
{
}

void MyListeners::onUserActiveAudioChanged(IZoomVideoSDKAudioHelper* pAudioHelper, IVideoSDKVector<IZoomVideoSDKUser*>* list)
{
    CString strInfo;
    IZoomVideoSDKUser* pUser;
    int count = list->GetCount();

    for (int i = 0; i < count; i++)
    {
        pUser = list->GetItem(i);
        strInfo.Format(_T("User's audio activity changed: name=%s"), pUser->getUserName());
    }
}

void MyListeners::onSessionNeedPassword(IZoomVideoSDKPasswordHandler* handler)
{
    //    // Store password handler.
    //    IZoomVideoSDKPasswordHandler* m_pPasswordHandler = handler;
    //
    //    // When ready, call inputSesstionPassword on the handler.
    //    if (m_pPasswordHandler)
    //    {
    //        CString strPassword;
    //        //m_pPswHandler->inputSessionPassword(strPassword.GetBuffer());
    //    }
    //
    //    // Or ignore the password request and leave the session with leaveSessionIgnorePassword.
    //   /* if (m_pPasswordHandler)
    //    {
    //        m_pPasswordHandler->leaveSessionIgnorePassword();
    //    }*/
}

void MyListeners::onSessionPasswordWrong(IZoomVideoSDKPasswordHandler* handler)
{
    //    // Store password handler.
//    //m_pPasswordHandler = handler;
//
//    //// When ready, call inputSesstionPassword on the handler.
//    //if (m_pPasswordHandler)
//    //{
//    //    CString strPassword;
//    //    m_pPswHandler->inputSessionPassword(strPassword.GetBuffer());
//    //}
//
//    // Or ignore the password request and leave the session with leaveSessionIgnorePassword.
//   /* if (m_pPasswordHandler)
//    {
//        m_pPasswordHandler->leaveSessionIgnorePassword();
//    }*/
}

void MyListeners::onMixedAudioRawDataReceived(AudioRawData* data_)
{
}

void MyListeners::onOneWayAudioRawDataReceived(AudioRawData* data_, IZoomVideoSDKUser* pUser)
{
}

void MyListeners::onSharedAudioRawDataReceived(AudioRawData* data_)
{
}

void MyListeners::onUserManagerChanged(IZoomVideoSDKUser* pUser)
{
}

void MyListeners::onUserNameChanged(IZoomVideoSDKUser* pUser)
{
}

void MyListeners::onCameraControlRequestResult(IZoomVideoSDKUser* pUser, bool isApproved)
{
}

void MyListeners::onCameraControlRequestReceived(IZoomVideoSDKUser* pUser, ZoomVideoSDKCameraControlRequestType requestType, IZoomVideoSDKCameraControlRequestHandler* pCameraControlRequestHandler)
{
}

void MyListeners::onCommandReceived(IZoomVideoSDKUser* sender, const zchar_t* strCmd)
{
}

void MyListeners::onCommandChannelConnectResult(bool isSuccess)
{
}

void MyListeners::onInviteByPhoneStatus(PhoneStatus status, PhoneFailedReason reason)
{
}

void MyListeners::onCloudRecordingStatus(RecordingStatus status)
{
}

void MyListeners::onHostAskUnmute()
{
}
