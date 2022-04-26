#include "MyListeners.h"
#include <format>
#include <iostream>

void MyListeners::onSessionJoin()
{
	std::cout << "\nLogin...";
}

void MyListeners::onSessionLeave()
{
	std::cout << "\nLogout...";    
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
    IZoomVideoSDKUser* pUser = nullptr;
    int count = userList->GetCount();

    for (int i = 0; i < count; i++)
    {
        pUser = userList->GetItem(i);
        if (!pUser) continue;

        strInfo.Format(_T("\nA user joined the session: name=%s"), pUser->getUserName());
        std::wcout << strInfo.GetString();        
    }
    if (pUser)
    {
        if (!Subscribe(pUser))
        {
            strInfo.Format(_T("\nCapturando Pipe de : name=%s"), pUser->getUserName());
            std::wcout << strInfo.GetString();
        }
        else
        {
            std::cout << "Falha ao cadastrar PIPE";
        }
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
        std::wcout << strInfo.GetString();
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
        //strInfo.Format(_T("A user's video status changed: userid=%s, name=%s, status=%s"), pUser->getUserName(), pUser->getVideoStatus());
    }
}

void MyListeners::onUserAudioStatusChanged(IZoomVideoSDKAudioHelper* pAudioHelper, IVideoSDKVector<IZoomVideoSDKUser*>* userList)
{

}

void MyListeners::onUserShareStatusChanged(IZoomVideoSDKShareHelper* pShareHelper, IZoomVideoSDKUser* pUser, ZoomVideoSDKShareStatus status)
{
}

void MyListeners::onLiveStreamStatusChanged(IZoomVideoSDKLiveStreamHelper* pLiveStreamHelper, ZoomVideoSDKLiveStreamStatus status)
{
}

void MyListeners::onChatNewMessageNotify(IZoomVideoSDKChatHelper* pChatHelper, IZoomVideoSDKChatMessage* messageItem)
{
}

void MyListeners::onUserHostChanged(IZoomVideoSDKUserHelper* pUserHelper, IZoomVideoSDKUser* pUser)
{
}

void MyListeners::onUserActiveAudioChanged(IZoomVideoSDKAudioHelper* pAudioHelper, IVideoSDKVector<IZoomVideoSDKUser*>* list)
{
}

void MyListeners::onSessionNeedPassword(IZoomVideoSDKPasswordHandler* handler)
{
}

void MyListeners::onSessionPasswordWrong(IZoomVideoSDKPasswordHandler* handler)
{
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

ZoomVideoSDKErrors MyListeners::Subscribe(IZoomVideoSDKUser* pUser)
{
    ZoomVideoSDKErrors err = ZoomVideoSDKErrors_Unknown;

    // Set the resolution.
    ZoomVideoSDKResolution resolution = ZoomVideoSDKResolution_360P;

    // Get the video pipe for the user.
    IZoomVideoSDKRawDataPipe* pPipe = NULL;
    pPipe = pUser->GetVideoPipe();
    if (!pPipe)
        return err;

    // Call subscribe.
    err = pPipe->subscribe(resolution, this);
    return err;
}

void MyListeners::onRawDataFrameReceived(YUVRawDataI420* data_)
{
    // Get frame data resolution.
    data_->GetStreamWidth();
    data_->GetStreamHeight();

    // Get frame buffer.
    data_->GetYBuffer();
    data_->GetUBuffer();
    data_->GetVBuffer();

    // Get frame rotation
    data_->GetRotation();
}

void MyListeners::onRawDataStatusChanged(RawDataStatus status)
{
    if (status == RawData_On)
    {
        // Now subscribed to user's data.
    }
    else
    {
        // No longer subscribed to user's data.
    }
}
