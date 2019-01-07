//
//  OpenVideo.h
//  cameraSettingsLibUVC
//
//  Created by Margaret Peterson on 11/10/18.
//  Copyright © 2018 Margaret Peterson. All rights reserved.
//

#ifndef OpenVideo_h
#define OpenVideo_h
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"


#include "imgcodecs.hpp"
#include "imgproc.hpp"
#include "videoio.hpp"
#include "highgui.hpp"
#include "video.hpp"

#include <iostream>
#include"libuvc.h"
#include <stdio.h>
#include <unistd.h>

//C++
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;

#endif /* OpenVideo_h */

class OpenVideo {
    
public:
    OpenVideo(int camNum);
    static void cb(uvc_frame_t *frame, void *ptr);
    Mat getImage();
    
private:
    void ChangeExposure();
    int webCamIndex;
    VideoCapture *capture;
};


