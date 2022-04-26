#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "IncludeZoomVideoSdk.h"
#include "MyListeners.h"
#include "ZoomSDKManager.h"
#include "Windows.h"
#include <stdio.h>
#include <process.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "comdlg32.lib")

#define BT_JOIN_EVENT                   1
#define BT_REFRESH_AUD_INPUT_EVENT      2
#define BT_SET_CAMERA_EVENT             3
#define BT_GET_CAM_LIST_EVENT           4
#define BT_GET_USERS_EVENT              5
#define BT_QUIT_SESSION_EVENT           6
#define BT_TERMINATE_SESSION_EVENT      7
#define BT_SET_VIDEO_PIPE_EVENT         8
#define BT_STOP_REC_EVENT               9
#define BT_SET_VIDEO_FILE_EVENT         10
#define BT_SET_AUDIO_FILE_EVENT         11
#define BT_START_REC_EVENT              12
#define BT_REFRESH_AUD_OUTPUT_EVENT     13
#define BT_SET_AUD_INPUT_EVENT          14
#define BT_SET_AUD_OUTPUT_EVENT         15
#define BT_MUTE_AUDIO_USER_EVENT        16
#define BT_ENABLE_VIRTUAL_MIC_EVENT     17
#define BT_ENABLE_VIRTUAL_SPEAKER_EVENT 18
#define BT_STOP_SENDING_R_AUDIO_EVENT   19
#define BT_ENABLE_VIRTUAL_CAM_EVENT     20

using namespace std;
using namespace ZOOM_VIDEO_SDK_NAMESPACE;

/*Prototypes*/
LRESULT CALLBACK mWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
bool InitSDK();
bool JoinOrCreateSession();
bool AddControls(HWND hwnd);
bool RegisterMyWindowClass(CString className);
HWND CreateMyMainWindow(CString className);
void RefreshMyCameraDevices(HWND hwnd);
void RefreshMyMicsDevices(HWND hwnd);
void RefreshMySpeakersDevices(HWND hwnd);
bool SetMyCameraDevice(HWND hwnd);
bool GetUsers(HWND hwnd);
bool SubscribePipe();
bool StopRecording();
bool SetMyMicDevice(HWND hwnd);
bool SetMySpeakerDevice(HWND hwnd);
bool MuteOrUnmuteUser(HWND hwnd);
bool EnableVirtualMic();
bool EnableVirtualSpeaker();
void VirtualCamInitialized();
bool EnableVirtualCam();


/*Threads*/
void WaitConnection(void* pMyID);
void WaitDisconnection(void* pMyID);
void SendMyAudio(void* pMyID);
void SendMyRawVideo(void* pMyID);

/*Callbacks*/
void UserListHasChanged();
void NewVideoFrameArrived(YUVRawDataI420* data_);
void NewMixedAudioFrameReceived(AudioRawData* data_);
void VirtualMicWasInitialized();
void FinishedSendingAudioPacket();
void BeginToSendRawAudio();

/*Types*/

typedef struct
{    
    ZoomSDKManager* mySdkManager;       //Instance from Library            
    
    int currentPipe;                    //Pipe (user) that we are recording video
    ZoomVideoSDKResolution resolution;  //Resolution from that pipe

    IVideoSDKVector<IZoomVideoSDKCameraDevice*>* myCameraDevices;
    IVideoSDKVector<IZoomVideoSDKMicDevice*>* myMicDevices;
    IVideoSDKVector<IZoomVideoSDKSpeakerDevice*>* mySpeakerDevices;

    ZoomVideoSDKSessionContext sessionContext;    
    
    ofstream* vWf; //Raw Video Write Stream file
    ofstream* aWf; //Raw Audio write Stream file
    ifstream* vRf; //Raw Video Reading Stream file
    ifstream* aRf; //Raw Audio Reading Stram file
    
    bool record;

    bool virtualMicInitialized;
    bool virtualCamInitialized;
}MyAppState_t;