#pragma once

#include "IncludeZoomVideoSdk.h"
#include <atlstr.h>

using namespace ZOOM_VIDEO_SDK_NAMESPACE;

class MyListeners:
    public ZOOM_VIDEO_SDK_NAMESPACE::IZoomVideoSDKDelegate
{
private:
    /*SDK instance pointer*/
    //IZoomVideoSDK* m_pVideoSDK;

public:
    /*Constructor*/
    MyListeners(){}
    //MyListeners(ZOOM_VIDEO_SDK_NAMESPACE::IZoomVideoSDK* val)
    //    :m_pVideoSDK{ val }
    //{
    //    //Adiciona este objeto como listener da instância da SDK
    //    m_pVideoSDK->addListener(this);
    //}
    ~MyListeners() {}
    

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

};
