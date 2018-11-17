
//
//  main.cpp
//  cameraSettingsLibUVC
//
//  Created by Margaret Peterson on 11/3/18.
//  Copyright © 2018 Margaret Peterson. All rights reserved.
//

#include <iostream>
#include"libuvc.h"
#include <stdio.h>
#include <unistd.h>
#include "OpenVideo.h"
using namespace cv;


/* This callback function runs once per frame. Use it to perform any
 * quick processing you need, or have it put the frame into your application's
 * input queue. If this function takes too long, you'll start losing frames. */

int main(int argc, char **argv) {
    
   /* SAMPLE CODE
    // opens camera and returns one frame
    
    OpenVideo myCamera(1); //OpenVideo objects takes in int CameraIndex
    imshow("Frame", myCamera.getImage());
    waitKey(0);
    */

    //opens camera continuously until user presses q
    OpenVideo myCamera(1); //OpenVideo objects takes in int CameraIndex
    char keyboard = 0;
    while (keyboard != 'q'){ // press q to stop stream
        imshow("Frame", myCamera.getImage());
        keyboard = (char)waitKey( 30 );
    }
    cvDestroyWindow("Frame");
    
    return 0;
}
