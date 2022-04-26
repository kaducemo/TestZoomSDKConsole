#pragma once

#include "IncludeZoomVideoSdk.h"

using namespace ZOOM_VIDEO_SDK_NAMESPACE;

class MyRenderer : public IZoomVideoSDKRawDataPipeDelegate
{

public:
	ZoomVideoSDKErrors Subscribe(IZoomVideoSDKUser* pUser, ZoomVideoSDKRawDataType dataType, int size);

private:
	// Herdado por meio de IZoomVideoSDKRawDataPipeDelegate
	virtual void onRawDataFrameReceived(YUVRawDataI420* data_) override;
	virtual void onRawDataStatusChanged(RawDataStatus status) override;
};

