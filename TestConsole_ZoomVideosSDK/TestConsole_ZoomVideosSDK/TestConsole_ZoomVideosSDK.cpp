#include "TestConsole_ZoomVideoSDK.h"

/*Globals*/

MyAppState_t appState =
{
    nullptr, //Zoom SDK Instance Cleared

    0, //No pipe record
    ZoomVideoSDKResolution_NoUse, //No Resolution Set

    nullptr,    //No camera devices
    nullptr,    //No mic devices
    nullptr,    //No speaker devices
    
    {},         //Init Session Context to nothing

    nullptr,
    nullptr,
    nullptr,
    nullptr,


    false,      //Record is disabled
    
    false,      //Vitual Mic is disabled
    false       //Virtual Cam is disabled
};

//Controls
HWND tbJWT, tbUsers, tbOutput, tbCameras, tbParam1, tbParam2, tbVideoFileOuptut, tbAudioFileOutput, tbMics, tbSpks;
HBRUSH hbrBkgnd = NULL; //Fills Static Controls

int main()
{  
    CString myClassName = "MyWindow";
    if (!RegisterMyWindowClass(myClassName))
        return -1; //Error

    HWND hMyMainWindow = CreateMyMainWindow(myClassName);    

    /*Init Zoom SDK*/
    InitSDK();    
    appState.mySdkManager->MyZoomMessageLoop();

    return 0;
}

LRESULT CALLBACK mWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    wchar_t fileName[30] = { 0 };
    wchar_t afileName[30] = { 0 };
    switch (message)
    {
    case WM_COMMAND:
        switch (wparam)
        {
        case BT_JOIN_EVENT:
            JoinOrCreateSession();            
            break;
        case BT_SET_CAMERA_EVENT:
            SetMyCameraDevice(tbParam1);
            break;
        case BT_REFRESH_AUD_INPUT_EVENT:
            RefreshMyMicsDevices(tbMics);            
            break;
        case BT_GET_CAM_LIST_EVENT:   
            RefreshMyCameraDevices(tbCameras);            
            break;
        case BT_GET_USERS_EVENT:
            GetUsers(tbUsers);
            break;
        case BT_TERMINATE_SESSION_EVENT:
            appState.mySdkManager->TerminateSession();
            break;
        case BT_QUIT_SESSION_EVENT:
            appState.mySdkManager->LeaveSession();
            break;
        case BT_SET_VIDEO_PIPE_EVENT:            
            SubscribePipe();
            break;
        case BT_STOP_REC_EVENT:
            StopRecording();
            break;
        case BT_SET_VIDEO_FILE_EVENT:            
            GetWindowText(tbVideoFileOuptut, fileName, 30);
            appState.vWf = new ofstream(fileName, ios::out | ios::binary);
            if (appState.vWf)
            {
                SetWindowText(tbOutput, L"Video Stream Opened!");
            }
            else
            {
                MessageBox(NULL, L"Cannot open file!", L"ERROR", MB_OK);                
                return 1;
            }
            break;
        case BT_SET_AUDIO_FILE_EVENT:            
            GetWindowText(tbAudioFileOutput, afileName, 30);            
            appState.aWf = new ofstream(afileName, ios::out | ios::binary);
            if(appState.aWf)
                SetWindowText(tbOutput, L"Audio Stream Opened!");
            else
            {                
                return 1;
            }
            break;
        case BT_START_REC_EVENT:            
            if(!appState.vWf && !appState.aWf)
            {
                MessageBox(NULL, L"Set Output Files First", L"ERROR", MB_OK);
            }                
            else if (appState.vWf && !appState.aWf)
            { 
                appState.record = true;
                SetWindowText(tbOutput, L"Recording video only...");
            }
                
            else if (!appState.vWf && appState.aWf)
            {
                appState.record = true;
                SetWindowText(tbOutput, L"Recording audio only...");
            }
                
            else if (appState.vWf && appState.aWf)
            {
                appState.record = true;
                SetWindowText(tbOutput, L"Recording Video and Audio...");
            }
        case BT_REFRESH_AUD_OUTPUT_EVENT:
            RefreshMySpeakersDevices(tbSpks);
            break;
        case BT_SET_AUD_INPUT_EVENT:
            SetMyMicDevice(tbParam1);
            break;
        case BT_SET_AUD_OUTPUT_EVENT:
            SetMySpeakerDevice(tbParam1);
            break;
        case BT_MUTE_AUDIO_USER_EVENT:
            MuteOrUnmuteUser(tbOutput);
            break;
        case BT_ENABLE_VIRTUAL_MIC_EVENT:
            EnableVirtualMic();
            break;
        case BT_ENABLE_VIRTUAL_SPEAKER_EVENT:
            EnableVirtualSpeaker();
            break;
        case BT_ENABLE_VIRTUAL_CAM_EVENT:
            EnableVirtualCam();
            break;
        }
    break;

    case WM_CREATE:
        AddControls(hwnd);
        break;

    case WM_CHAR: //this is just for a program exit besides window's borders/task bar

        if (wparam == VK_ESCAPE)
        {
            PostQuitMessage(0);
            //DestroyWindow(hwnd);
        }
        if (wparam == 'a' || wparam == 'A')
        {
            
        }
        if (wparam == 'q' || wparam == 'Q')
        {
            
        }
        if (wparam == 't' || wparam == 'T')
        {
            
        }
        break;

    case WM_DESTROY:
        if(appState.vWf)
            appState.vWf->close();
        if (appState.aWf)
            appState.aWf->close();
        PostQuitMessage(0);
        break;

    case WM_CTLCOLORSTATIC:        
        SetBkMode((HDC)wparam, TRANSPARENT);
        if (hbrBkgnd == NULL)
            hbrBkgnd = (HBRUSH)GetStockObject(NULL_BRUSH);
        return (INT_PTR)hbrBkgnd;
        break;
    
    default:
        return DefWindowProc(hwnd, message, wparam, lparam);
    }
    return 0;
}

bool AddControls(HWND hwnd)
{   
    int aux = 10;
    tbJWT = CreateWindowW(L"edit", L""          , WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 50, aux, 850, 60, hwnd, NULL, NULL, NULL);
    CreateWindowW(L"static", L"JWT: "   , WS_VISIBLE | WS_CHILD , 10, aux+6, 30, 20, hwnd, NULL, NULL, NULL);
    
    aux += (60 + 20);
    CreateWindowW(L"static", L"Video output file: ", WS_VISIBLE | WS_CHILD, 10, aux, 150, 20, hwnd, NULL, NULL, NULL);
    tbVideoFileOuptut = CreateWindowW(L"edit", L"video.yuv", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 125, aux-7, 200, 30, hwnd, NULL, NULL, NULL);
    CreateWindowW(L"button", L"Set Video File ", WS_VISIBLE | WS_CHILD, 355, aux-10, 150, 33, hwnd, (HMENU)BT_SET_VIDEO_FILE_EVENT, NULL, NULL);

    aux += (20 + 20);
    CreateWindowW(L"static", L"Audio output file: ", WS_VISIBLE | WS_CHILD, 10, aux, 150, 20, hwnd, NULL, NULL, NULL);
    tbAudioFileOutput = CreateWindowW(L"edit", L"audio.raw", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 125, aux - 7, 200, 30, hwnd, NULL, NULL, NULL);
    CreateWindowW(L"button", L"Set Audio File ", WS_VISIBLE | WS_CHILD, 355, aux-10, 150, 33, hwnd, (HMENU)BT_SET_AUDIO_FILE_EVENT, NULL, NULL);

    aux += (20+20);
    CreateWindowW(L"static", L"Cameras: ", WS_VISIBLE | WS_CHILD, 10, aux, 80, 20, hwnd, NULL, NULL, NULL);    
    CreateWindowW(L"static", L"Output: " , WS_VISIBLE | WS_CHILD , 250, aux, 50, 20, hwnd, NULL, NULL, NULL);
    
    aux += (20 + 10);
    tbCameras = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 10, aux, 230, 70, hwnd, NULL, NULL, NULL);    
    tbOutput = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 250, aux, 900-250, 70, hwnd, NULL, NULL, NULL);    aux += (70 + 10);
    CreateWindowW(L"static", L"Users: ", WS_VISIBLE | WS_CHILD, 10, aux, 50, 20, hwnd, NULL, NULL, NULL);
    CreateWindowW(L"static", L"Commands: ", WS_VISIBLE | WS_CHILD, 250, aux, 80, 20, hwnd, NULL, NULL, NULL);
    CreateWindowW(L"static", L"Parameters: ", WS_VISIBLE | WS_CHILD, 250 + 30 + 160, aux, 80, 20, hwnd, NULL, NULL, NULL);
    tbParam1 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 250 + 30 + 160 + 100, aux-5, 30, 30, hwnd, NULL, NULL, NULL);
    tbParam2 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 250 + 30 + 160 + 100+ 10 + 30, aux-5, 30, 30, hwnd, NULL, NULL, NULL);
    
    aux += (20 + 10);
    tbUsers = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 10, aux, 230, 70, hwnd, NULL, NULL, NULL);
    CreateWindowW(L"button", L"Set Camera", WS_VISIBLE | WS_CHILD, 250, aux, 160, 30, hwnd, (HMENU)BT_SET_CAMERA_EVENT, NULL, NULL);
    CreateWindowW(L"button", L"Start Recording", WS_VISIBLE | WS_CHILD, 250 + 160 + 20, aux, 160, 30, hwnd, (HMENU)BT_START_REC_EVENT, NULL, NULL);
    CreateWindowW(L"button", L"Virtual Cam", WS_VISIBLE | WS_CHILD, 250 + 340 + 20, aux, 160, 30, hwnd, (HMENU)BT_ENABLE_VIRTUAL_CAM_EVENT, NULL, NULL);
    CreateWindowW(L"button", L"Stop Recording", WS_VISIBLE | WS_CHILD, 250 + 160 + 20, aux + 10 + 30, 160, 30, hwnd, (HMENU)BT_STOP_REC_EVENT, NULL, NULL);
    CreateWindowW(L"button", L"Refresh Audio Inputs", WS_VISIBLE | WS_CHILD, 250, aux+10+30, 160, 30, hwnd, (HMENU)BT_REFRESH_AUD_INPUT_EVENT, NULL, NULL);        
    CreateWindowW(L"button", L"Refresh Cam List", WS_VISIBLE | WS_CHILD, 250, aux+20+60, 160, 30, hwnd, (HMENU)(BT_GET_CAM_LIST_EVENT), NULL, NULL);    
    CreateWindowW(L"button", L"Refresh Audio Outputs", WS_VISIBLE | WS_CHILD, 250 + 160 + 20, aux + 20 + 60, 160, 30, hwnd, (HMENU)BT_REFRESH_AUD_OUTPUT_EVENT, NULL, NULL);
    CreateWindowW(L"static", L"Mics: ", WS_VISIBLE | WS_CHILD, 10, aux + 20 + 60 + 5, 80, 20, hwnd, NULL, NULL, NULL);
    

    aux += (30 + 10);
    CreateWindowW(L"button", L"Get Users", WS_VISIBLE | WS_CHILD, 250, aux + 20 + 60, 160, 30, hwnd, (HMENU)(BT_GET_USERS_EVENT), NULL, NULL);
    CreateWindowW(L"button", L"Set Audio Input", WS_VISIBLE | WS_CHILD, 250 + 160 + 20, aux + 20 + 60, 160, 30, hwnd, (HMENU)BT_SET_AUD_INPUT_EVENT, NULL, NULL);
    tbMics = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 10, aux + 20 + 60, 230, 70, hwnd, NULL, NULL, NULL);
    
    aux += (30 + 10);
    CreateWindowW(L"button", L"Quit Session", WS_VISIBLE | WS_CHILD, 250, aux + 20 + 60, 160, 30, hwnd, (HMENU)(BT_QUIT_SESSION_EVENT), NULL, NULL);
    CreateWindowW(L"button", L"Set Audio Output", WS_VISIBLE | WS_CHILD, 250 + 160 + 20, aux + 20 + 60, 160, 30, hwnd, (HMENU)BT_SET_AUD_OUTPUT_EVENT, NULL, NULL);
    
    aux += (30 + 10);
    CreateWindowW(L"button", L"Terminate Session", WS_VISIBLE | WS_CHILD, 250, aux + 20 + 60, 160, 30, hwnd, (HMENU)(BT_TERMINATE_SESSION_EVENT), NULL, NULL);
    CreateWindowW(L"button", L"Mute/Unmute User", WS_VISIBLE | WS_CHILD, 250 + 160 + 20, aux + 20 + 60, 160, 30, hwnd, (HMENU)BT_MUTE_AUDIO_USER_EVENT, NULL, NULL);
    CreateWindowW(L"static", L"Audio Outputs: ", WS_VISIBLE | WS_CHILD, 10, aux + 20 + 60+5, 160, 20, hwnd, NULL, NULL, NULL);

    aux += (110 + 10);    
    CreateWindowW(L"button", L"Create / Join Session", WS_VISIBLE | WS_CHILD, 250, aux, 160, 30, hwnd, (HMENU)(BT_JOIN_EVENT), NULL, NULL);
    CreateWindowW(L"button", L"Virtual Speaker", WS_VISIBLE | WS_CHILD, 250 + 160 + 20, aux, 160, 30, hwnd, (HMENU)(BT_ENABLE_VIRTUAL_SPEAKER_EVENT), NULL, NULL);
    tbSpks = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 10, aux, 230, 70, hwnd, NULL, NULL, NULL);

    aux += (30 + 10);
    CreateWindowW(L"button", L"Subscribe User Pipe", WS_VISIBLE | WS_CHILD, 250, aux, 160, 30, hwnd, (HMENU)BT_SET_VIDEO_PIPE_EVENT, NULL, NULL);
    CreateWindowW(L"button", L"Virtual Mic", WS_VISIBLE | WS_CHILD, 250 + 160 + 20, aux, 160, 30, hwnd, (HMENU)BT_ENABLE_VIRTUAL_MIC_EVENT, NULL, NULL);

    return true;
}

bool InitSDK()
{    
    ZoomVideoSDKInitParams initParams;

    initParams.domain = L"https://zoom.us";
    initParams.audioRawDataMemoryMode = ZoomVideoSDKRawDataMemoryModeStack;
    initParams.videoRawDataMemoryMode = ZoomVideoSDKRawDataMemoryModeStack;
    initParams.shareRawDataMemoryMode = ZoomVideoSDKRawDataMemoryModeStack;
    initParams.enableIndirectRawdata = false;
    //initParams.enableLog = true;
    //initParams.logFilePrefix = L"prefix";
    appState.mySdkManager = new ZoomSDKManager(initParams);

    appState.mySdkManager->UsersListChanged = UserListHasChanged;
    appState.mySdkManager->RawVideoReceived = NewVideoFrameArrived;  
    appState.mySdkManager->RawMixedAudioReceived = NewMixedAudioFrameReceived;    
    appState.mySdkManager->VirtualMicInitialized = VirtualMicWasInitialized;
    appState.mySdkManager->StartToSendRawAudio = BeginToSendRawAudio;
    appState.mySdkManager->RawAudioStoppedSend = FinishedSendingAudioPacket;
    appState.mySdkManager->VirtualCamInitialized = VirtualCamInitialized;
    

    CString out = "SDK Initialized...";    
    SetWindowTextW(tbOutput, out);
    SetWindowTextW(tbJWT, L"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhcHBfa2V5IjoianlGMDlRZkxHNW83N2N6Zm9HTU4xbmxtTzQyYVRqN0xTNkFuIiwidmVyc2lvbiI6MSwicm9sZV90eXBlIjoxLCJpYXQiOjE2NTA4OTA2NTEsImV4cCI6MTY1MTA2MzQ1MSwidHBjIjoiU2Vzc2FvIn0.wQ7VngPIXTnqME0W3o-c-9oe24sMbOBZOl9wTT3g1rw");
    return true;
}

bool JoinOrCreateSession()
{
    //Session Context configuration
    appState.sessionContext.sessionName = L"sessao";
    appState.sessionContext.userName = L"Kadu";
    
    // JWT for this session.
    wchar_t jwt[350] = { 0 };
    GetWindowText(tbJWT, jwt, 350);    
    appState.sessionContext.token = jwt;

    // Video and audio options.    
    appState.sessionContext.videoOption.localVideoOn = true;
    appState.sessionContext.audioOption.connect = true;
    appState.sessionContext.audioOption.mute = false;     

    if (!appState.mySdkManager->InitSession(appState.sessionContext))
    {
        CString out = "Error Creating Session";
        SetWindowTextW(tbOutput, out);
    }  
    
    int i = 1;
    _beginthread(WaitConnection, 0, &i);

    return true;
}

bool RegisterMyWindowClass(CString className)
{
    WNDCLASS windowClass = { 0 };

    windowClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hInstance = NULL;
    windowClass.lpfnWndProc = mWndProc;
    windowClass.lpszClassName = className;
    windowClass.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&windowClass))
    {        
        MessageBox(NULL, L"Coundn´t register the class", L"Error", MB_OK);
        return false;
    }
    return true;
}

HWND CreateMyMainWindow(CString className)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = mWndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = NULL;
    wcex.lpszClassName = className;
    RegisterClassExW(&wcex);

    HWND hWnd = CreateWindowW(className, L"Test Zoom SDK", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 945, 730, nullptr, nullptr, nullptr, nullptr);

    ShowWindow(hWnd, SW_RESTORE);
    SetFocus(hWnd);

    return hWnd;
}

void RefreshMyCameraDevices(HWND hwnd)
{ 
    ////    /*Helper to manipulate video stuff*/
    IZoomVideoSDKVideoHelper* videoHelper = appState.mySdkManager->GetSdkInstance()->getVideoHelper();
    appState.myCameraDevices = videoHelper->getCameraList(); 

    if (appState.myCameraDevices->GetCount())
    {
        CString s = ""; 
        CString out = "";
        
        for (int i = 0; i < appState.myCameraDevices->GetCount(); i++) // access by reference to avoid copying
        {    
            IZoomVideoSDKCameraDevice* pCameraDevice = appState.myCameraDevices->GetItem(i);            
            s.Format(_T("[%d] %s\r\n"), i+1, pCameraDevice->getDeviceName());            
            out.Append(s);            
        }
        SetWindowTextW(hwnd, out);
    }    
}

void RefreshMyMicsDevices(HWND hwnd)
{
    IZoomVideoSDKAudioHelper* audio_helper = appState.mySdkManager->GetSdkInstance()->getAudioHelper();

    if(audio_helper)
        appState.myMicDevices = audio_helper->getMicList();    

    if (appState.myMicDevices->GetCount())
    {
        CString s = "";
        CString out = "";

        for (int i = 0; i < appState.myMicDevices->GetCount(); i++) // access by reference to avoid copying
        {
            IZoomVideoSDKMicDevice* pMicDevice = appState.myMicDevices->GetItem(i);
            s.Format(_T("[%d] %s\r\n"), i + 1, pMicDevice->getDeviceName());
            out.Append(s);
        }
        SetWindowTextW(hwnd, out);
    }
}

void RefreshMySpeakersDevices(HWND hwnd)
{
    IZoomVideoSDKAudioHelper* audio_helper = appState.mySdkManager->GetSdkInstance()->getAudioHelper();

    if (audio_helper)
        appState.mySpeakerDevices = audio_helper->getSpeakerList();

    if (appState.mySpeakerDevices->GetCount())
    {
        CString s = "";
        CString out = "";

        for (int i = 0; i < appState.mySpeakerDevices->GetCount(); i++) // access by reference to avoid copying
        {
            IZoomVideoSDKSpeakerDevice* pSpeakerDevice = appState.mySpeakerDevices->GetItem(i);
            s.Format(_T("[%d] %s\r\n"), i + 1, pSpeakerDevice->getDeviceName());
            out.Append(s);
        }
        SetWindowTextW(hwnd, out);
    }
}

bool SetMyCameraDevice(HWND hwnd)
{
    char param[20];  
    try
    {
        GetWindowText(hwnd, (LPWSTR)param, 10);
        int num = stoi(param);
        /*Helper to manipulate video stuff*/
        IZoomVideoSDKVideoHelper* videoHelper = appState.mySdkManager->GetSdkInstance()->getVideoHelper();
        appState.myCameraDevices = videoHelper->getCameraList();

        if (num > 0 && num <= appState.myCameraDevices->GetCount())
        {
            IZoomVideoSDKCameraDevice* pCameraDeviceSelected = appState.myCameraDevices->GetItem(num - 1);
            
            std::wcout << pCameraDeviceSelected->getDeviceName() << endl;
            if (!pCameraDeviceSelected->isSelectedDevice())
            {
                videoHelper->selectCamera(pCameraDeviceSelected->getDeviceId());
            }
            CString out = "Camera OK";
            SetWindowTextW(tbOutput, out);
            return true;
        }
    }
    catch(exception e)
    {
        CString out = "Invalid Camera";
        SetWindowTextW(tbOutput, out);
    }

    
    return false;
}

bool SetMyMicDevice(HWND hwnd)
{
    char param[20];
    try
    {
        GetWindowText(hwnd, (LPWSTR)param, 10);
        int num = stoi(param);
        ////    /*Helper to manipulate audio stuff*/
        IZoomVideoSDKAudioHelper* audioHelper = appState.mySdkManager->GetSdkInstance()->getAudioHelper();
        appState.myMicDevices = audioHelper->getMicList(); 

        if (num > 0 && num <= appState.myMicDevices->GetCount())
        {
            IZoomVideoSDKMicDevice* pMicDeviceSelected = appState.myMicDevices->GetItem(num - 1);            
            if (!pMicDeviceSelected->isSelectedDevice())
            {
                audioHelper->selectMic(pMicDeviceSelected->getDeviceId(), pMicDeviceSelected->getDeviceName());
            }
            CString out = "Audio Input OK";
            SetWindowTextW(tbOutput, out);
            return true;
        }
    }
    catch (exception e)
    {
        CString out = "Invalid Audio Input";
        SetWindowTextW(tbOutput, out);
    }
    return false;
}

bool SetMySpeakerDevice(HWND hwnd)
{
    char param[20];
    try
    {
        GetWindowText(hwnd, (LPWSTR)param, 10);
        int num = stoi(param);
        ////    /*Helper to manipulate audio stuff*/
        IZoomVideoSDKAudioHelper* audioHelper = appState.mySdkManager->GetSdkInstance()->getAudioHelper();
        appState.mySpeakerDevices = audioHelper->getSpeakerList();

        if (num > 0 && num <= appState.mySpeakerDevices->GetCount())
        {
            IZoomVideoSDKSpeakerDevice* pSpeakerDeviceSelected = appState.mySpeakerDevices->GetItem(num - 1);
            if (!pSpeakerDeviceSelected->isSelectedDevice())
            {
                audioHelper->selectMic(pSpeakerDeviceSelected->getDeviceId(), pSpeakerDeviceSelected->getDeviceName());
            }
            CString out = "Audio Output OK";
            SetWindowTextW(tbOutput, out);
            return true;
        }
    }
    catch (exception e)
    {
        CString out = "Invalid Audio Input";
        SetWindowTextW(tbOutput, out);
    }
    return false;
}

bool GetUsers(HWND hwnd)
{
    IZoomVideoSDKSession* session = appState.mySdkManager->GetSdkInstance()->getSessionInfo();
    
    if (session)
    {
        vector<IZoomVideoSDKUser*> userList = appState.mySdkManager->GetAllUsers();
        CString aux = "", out = "";
        int i = 1;
        for (auto& user : userList)
        {

            aux.Format(_T("[%d] %s\r\n"), i++ ,user->getUserName());
            out.Append(aux);
        }
        SetWindowTextW(hwnd, out);
        return true;
    }
    else
    {
        return false;
    }    
}

void WaitConnection(void* pMyID)
{
    while (!appState.mySdkManager->IsConnected);
    CString out = "Logged IN";
    SetWindowTextW(tbOutput, out);
    int i = 1;
    _beginthread(WaitDisconnection, 0, &i);
}

void WaitDisconnection(void* pMyID)
{
    while (appState.mySdkManager->IsConnected);
    CString out = "Logged OUT";
    SetWindowTextW(tbOutput, out);    
}

void SendMyAudio(void* pMyID)
{
    char* myRawAudioData = new char[32000]{ 0 };

    /* for (int i = 0; i < 32000; i++)
         myRawAudioData[i] = i;*/

    int i = 0;
    while (true)
    {
        for (i = 0; i < 32000; i += 2)
        {
            appState.aRf->read(&myRawAudioData[i], 2);
            if (appState.aRf->eof())
            {
                appState.aRf->clear();
                appState.aRf->seekg(0, ios::beg);
                break;
            }
            else
            {
                int a = 0;
                a++;
            }

        }

        appState.mySdkManager->SendRawAudio(myRawAudioData, 32000, i);
        Sleep(500);
    }
    delete[] myRawAudioData;
}

void SendMyRawVideo(void* pMyID)
{
    
    /* for (int i = 0; i < 32000; i++)
         myRawAudioData[i] = i;*/

    int w = 1280;
    int h = 720;
    int nFrameLength = (w * h) + (w * h) / 4 + (w * h) / 4;

    char* myRawVideoData = new char[nFrameLength]{ 0 };
    
    unsigned int size = appState.vRf->tellg();
    unsigned int times = size / nFrameLength;
    appState.vRf->clear();
    appState.vRf->seekg(0, ios::beg);
    
    int i = 0;
    while (true)
    {
        appState.vRf->read(myRawVideoData, nFrameLength);
        appState.mySdkManager->SendRawVideo(myRawVideoData, w, h, nFrameLength, 0);
        i++;
        if (i == times)
        {
            appState.vRf->clear();
            appState.vRf->seekg(0, ios::beg);
            i = 0;
        }        
        Sleep(40);
    }

    delete[] myRawVideoData;
}

bool SubscribePipe()
{
    wchar_t aux[10] = { 0 };
    wchar_t aux2[10] = { 0 };
    GetWindowText(tbParam1,aux,10);
    GetWindowText(tbParam2, aux2, 10);
    try
    {
        int num = stoi(aux);
        int num2 = stoi(aux2);
        vector<IZoomVideoSDKUser*> userList = appState.mySdkManager->GetAllUsers();
        IZoomVideoSDKUser* myUser = userList.at(num-1);         
        
        ZoomVideoSDKResolution resolution = (ZoomVideoSDKResolution)num2;
        
        if (!appState.mySdkManager->Subscribe(myUser, resolution))
        {
            
            switch (resolution)
            {
            case ZoomVideoSDKResolution_90P:
                SetWindowText(tbOutput, L"User Subcribed with 90P frame resolution");
                break;
            case ZoomVideoSDKResolution_180P:
                SetWindowText(tbOutput, L"User Subcribed with 180P frame resolution");
                break;
            case ZoomVideoSDKResolution_360P:
                SetWindowText(tbOutput, L"User Subcribed with 360P frame resolution");
                break;
            case ZoomVideoSDKResolution_720P:
                SetWindowText(tbOutput, L"User Subcribed with 720P frame resolution");
                break;
            case ZoomVideoSDKResolution_1080P:
                SetWindowText(tbOutput, L"User Subcribed with 1080P frame resolution");
                break;
            default:
                SetWindowText(tbOutput, L"Error setting resolution...");
                break;
            }
            appState.currentPipe = num;
            appState.resolution = resolution;
            return true;
        }            
        else
            SetWindowText(tbOutput, L"Error subscribing user");
    }
    catch (exception e)
    {
        SetWindowText(tbOutput, L"User cannot be Subcribed");
    }
    return false;
}

bool StopRecording()
{
    wchar_t aux[10] = { 0 };
    GetWindowText(tbParam1, aux, 10);
    try
    {
        int num = stoi(aux);
        vector<IZoomVideoSDKUser*> userList = appState.mySdkManager->GetAllUsers();
        IZoomVideoSDKUser* myUser = userList.at(num - 1);
        appState.mySdkManager->Unsubscribe(myUser);
        SetWindowText(tbOutput, L"User Unsubscribed");
        appState.record = false;        
        return true;
    }
    catch (exception e)
    {
        SetWindowText(tbOutput, L"User cannot be Subscribed");
    }
    return false;
}

bool MuteOrUnmuteUser(HWND hwnd)
{
    wchar_t aux1[10] = { 0 };
    GetWindowText(tbParam1, aux1, 10); //Get User Index from tbParam1
    wchar_t aux2[10] = { 0 };
    GetWindowText(tbParam2, aux2, 10); //Get Mute or Unmute from tbParam2
    try
    {
        int num = stoi(aux1);
        int num2 = stoi(aux2);

        vector<IZoomVideoSDKUser*> userList = appState.mySdkManager->GetAllUsers();
        IZoomVideoSDKUser* myUser = userList.at(num - 1);//Get user from the list

        ZoomVideoSDKAudioStatus audioStatus = myUser->getAudioStatus();
        ZoomVideoSDKAudioType audioType = audioStatus.audioType; //Check if user audio is enabled
        
        if (audioType == ZoomVideoSDKAudioType_None) //User hasn´t an audio channel enabled
        {
            SetWindowText(hwnd, L"User do not have audio enabled!");
            return false;
        }

        IZoomVideoSDKAudioHelper* pAudioHelper = appState.mySdkManager->GetSdkInstance()->getAudioHelper();
        
        if (num2) //Values diff from 0 mute audio user
        {            
            pAudioHelper->muteAudio(myUser);            
            SetWindowText(hwnd, L"User is Muted");            
        }
        else
        {
            pAudioHelper->unMuteAudio(myUser);
            SetWindowText(hwnd, L"User is Unmuted");
        }
        return true;
    }
    catch (...)
    {
        SetWindowText(hwnd, L"Invalid Parameters...");
    }   
    return false;
}

bool EnableVirtualMic()
{      
    appState.sessionContext.virtualAudioMic = appState.mySdkManager;
    SetWindowText(tbOutput, L"Virtual Microphone Enabled");
    return true;
}

bool EnableVirtualSpeaker()
{
    appState.sessionContext.virtualAudioSpeaker = appState.mySdkManager;    
    SetWindowText(tbOutput, L"Virtual Espeaker Enabled");
    return true;
}

bool EnableVirtualCam()
{
    appState.sessionContext.externalVideoSource = appState.mySdkManager;
    SetWindowText(tbOutput, L"Virtual Camera Enabled");
    return true;
}

/*Callbacks*/
void UserListHasChanged()
{
    GetUsers(tbUsers);
}

void NewVideoFrameArrived(YUVRawDataI420* data_)
{
    int frameSize1 = 0, frameSize2 = 0;   
    int frameSize = data_->GetBufferLen();
    int width = data_->GetStreamWidth();
    int height = data_->GetStreamHeight();

    switch (appState.resolution)
    {
    case ZoomVideoSDKResolution_90P: //160x90P
        frameSize1 = 14400; 
        frameSize2 = 3600;
        break;
    case ZoomVideoSDKResolution_180P: //320x180P
        frameSize1 = 57600;
        frameSize2 = 14400;
        break;
    case ZoomVideoSDKResolution_360P: //640x360P
        frameSize1 = 230400;
        frameSize2 = 57600;
        break;
    case ZoomVideoSDKResolution_720P: //1280x720P 
        frameSize1 = 921600;
        frameSize2 = 230400;
        break;
    case ZoomVideoSDKResolution_1080P: //1920x1080P
        frameSize1 = 2073600;
        frameSize2 = 518400;
        break;
    default:
        break;
    }
    if (appState.vWf && appState.record)
    {
        if (frameSize > 0)
        {
            appState.vWf->write(data_->GetYBuffer(), frameSize1);
            appState.vWf->write(data_->GetUBuffer(), frameSize2);
            appState.vWf->write(data_->GetVBuffer(), frameSize2);
        }
        else
        //Invalid data
        {
            while (true);
        }        
    }    
}

void NewMixedAudioFrameReceived(AudioRawData* data_)
{
    int fs = data_->GetSampleRate();
    int size = data_->GetBufferLen();
    int nChannel = data_->GetChannelNum();
    if (appState.aWf && appState.record)
    {        
        appState.aWf->write(data_->GetBuffer(),size);
    }
}

void VirtualMicWasInitialized()
{    
    appState.virtualMicInitialized = true;
}

void FinishedSendingAudioPacket()
{  
    int a = 0;
    a++;
}

void BeginToSendRawAudio()
{    
    char fileName[20] = "audioSend.raw\0";
    appState.aRf = new ifstream(fileName, ios::in | ios::binary);
    if (!appState.aRf)
        cout << "Cannot open file!" << endl;
    int i = 1;
    _beginthread(SendMyAudio, 0, &i);     
}

void VirtualCamInitialized()
{
    appState.virtualCamInitialized = true;

    char fileName[20] = "videoSend.yuv\0";
    appState.vRf = new ifstream(fileName, ios::in | ios::binary | ios::ate);
    if (!appState.vRf)
        cout << "Cannot open file!" << endl;
    int i = 1;
    _beginthread(SendMyRawVideo, 0, &i);
}

