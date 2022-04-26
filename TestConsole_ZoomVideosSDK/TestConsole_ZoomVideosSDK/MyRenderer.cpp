#include "MyRenderer.h"

ZoomVideoSDKErrors MyRenderer::Subscribe(IZoomVideoSDKUser* pUser, ZoomVideoSDKRawDataType dataType, int size)
{
    ZoomVideoSDKErrors err;

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


void MyRenderer::onRawDataFrameReceived(YUVRawDataI420* data_)
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

void MyRenderer::onRawDataStatusChanged(RawDataStatus status)
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
