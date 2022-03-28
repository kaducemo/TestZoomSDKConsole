#include <iostream>
#include <memory>
#include "IncludeZoomVideoSdk.h"
#include "MyListeners.h"
#include "Windows.h"

using namespace std;
using namespace ZOOM_VIDEO_SDK_NAMESPACE;

/*Globals*/
IZoomVideoSDK* m_pVideoSDK;
MyListeners myListeners;
IZoomVideoSDKSession* pSession;
ZoomVideoSDKSessionContext sessionContext;
ZoomVideoSDKInitParams initParams;

int main()
{    

    m_pVideoSDK = CreateZoomVideoSDKObj();    
       
    initParams.domain = L"https://zoom.us";    
    initParams.audioRawDataMemoryMode = ZoomVideoSDKRawDataMemoryModeStack;
    initParams.videoRawDataMemoryMode = ZoomVideoSDKRawDataMemoryModeStack;
    initParams.shareRawDataMemoryMode = ZoomVideoSDKRawDataMemoryModeStack;    
    initParams.enableIndirectRawdata = false;    
    initParams.enableLog = true;    
    initParams.logFilePrefix = L"prefix";

    ZoomVideoSDKErrors returnVal = m_pVideoSDK->initialize(initParams);
    if (returnVal != ZoomVideoSDKErrors_Success) //Error...   
        return returnVal;  

    cout << "SDK Instance created...\n";

    myListeners = MyListeners(m_pVideoSDK);

    cout << "Listeners created and passed to SDK instance...\n"; //Listeners Criadados e passados para a SDK

    //Session Context configuration
    sessionContext.sessionName = L"Sessao";    
    sessionContext.userName = L"Kadu";
    // JWT for this session.
    sessionContext.token = L"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhcHBfa2V5IjoianlGMDlRZkxHNW83N2N6Zm9HTU4xbmxtTzQyYVRqN0xTNkFuIiwidmVyc2lvbiI6MSwicm9sZV90eXBlIjoxLCJ1c2VyX2lkZW50aXR5IjoiS2FkdSIsInNlc3Npb25fa2V5IjoiU2Vzc2FvIiwiaWF0IjoxNjQ4NDc0MDI4LCJleHAiOjE2NDg2NDY4MjgsInRwYyI6IlNlc3NhbyJ9.XUc9otCgOsBXjwZJbSrTphD_n36lwMcWg-O9iDJmpOg";
    // Video and audio options.
    sessionContext.videoOption.localVideoOn = true;
    sessionContext.audioOption.connect = true;
    sessionContext.audioOption.mute = false;

    pSession = m_pVideoSDK->joinSession(sessionContext);

    if (!pSession)
    {
        CString cstrInfo;
        cstrInfo.Format(_T("Failed to join session"));
    }

    else
    {
        CString cstrInfo;
        cstrInfo.Format(_T("Joined session successfully."));
    }

    //Message Loop...
    bool bRet = false;
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







