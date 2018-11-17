//
//  OpenVideo.cpp
//  cameraSettingsLibUVC
//
//  Created by Margaret Peterson on 11/10/18.
//  Copyright © 2018 Margaret Peterson. All rights reserved.
//

#include <stdio.h>
#include "OpenVideo.h"
Mat frame; //current frame
char keyboard; //input from keyboard

/* This callback function runs once per frame. Use it to perform any
 * quick processing you need, or have it put the frame into your application's
 * input queue. If this function takes too long, you'll start losing frames. */



void OpenVideo::cb(uvc_frame_t *frame, void *ptr) {
    uvc_frame_t *bgr;
    uvc_error_t ret;
    /* We'll convert the image from YUV/JPEG to BGR, so allocate space */
    bgr = uvc_allocate_frame(frame->width * frame->height * 3);
    if (!bgr) {
        printf("unable to allocate bgr frame!");
        return;
    }
    /* Do the BGR conversion */
    ret = uvc_any2bgr(frame, bgr);
    if (ret) {
        uvc_perror(ret, "uvc_any2bgr");
        uvc_free_frame(bgr);
        return;
    }
    
    uvc_free_frame(bgr);
}

OpenVideo::OpenVideo(int camNum){
    this->webCamIndex = camNum;
    this->ChangeExposure();
    this->capture = new VideoCapture(this->webCamIndex);
    if(!this->capture->isOpened()){
        //error in opening the video input
        cerr << "Unable to open video file: " << webCamIndex << endl;
        exit(EXIT_FAILURE);
    }
}
void OpenVideo::ChangeExposure(void) {
    uvc_context_t *ctx;
    uvc_device_t *dev;
    uvc_device_handle_t *devh;
    uvc_stream_ctrl_t ctrl;
    uvc_error_t res;
    int mode = 1;
    /* Initialize a UVC service context. Libuvc will set up its own libusb
     * context. Replace NULL with a libusb_context pointer to run libuvc
     * from an existing libusb context. */
    res = uvc_init(&ctx, NULL);
    
    /* Locates the first attached UVC device, stores in dev */
    res = uvc_find_device(
                          ctx, &dev,
                          0, 0, NULL); /* filter devices: vendor_id, product_id, "serial_num" */
    if (res < 0) {
        uvc_perror(res, "uvc_find_device"); /* no devices found */
    } else {
        puts("Device found");
        /* Try to open the device: requires exclusive access */
        res = uvc_open(dev, &devh);
        if (res < 0) {
            uvc_perror(res, "uvc_open"); /* unable to open device */
        } else {
            puts("Device opened");
            /* Print out a message containing all the information that libuvc
             * knows about the device */
            uvc_print_diag(devh, stderr);
            /* Try to negotiate a 640x480 30 fps YUYV stream profile */
            res = uvc_get_stream_ctrl_format_size(
                                                  devh, &ctrl, /* result stored in ctrl */
                                                  UVC_FRAME_FORMAT_YUYV, /* YUV 422, aka YUV 4:2:2. try _COMPRESSED */
                                                  640, 480, 30 /* width, height, fps */
                                                  );
            /* Print out the result */
            uvc_print_stream_ctrl(&ctrl, stderr);
            if (res < 0) {
                uvc_perror(res, "get_mode"); /* device doesn't provide a matching stream */
            } else {
                /* Start the video stream. The library will call user function cb:
                 *   cb(frame, (void*) 12345)
                 */
                
                
                res = uvc_start_streaming(devh, &ctrl, OpenVideo::cb, (void *) 12345, 0);
                if (res < 0) {
                    uvc_perror(res, "start_streaming"); /* unable to start stream */
                } else {
                    puts("Streaming...");
                    //uvc_set_ae_mode(devh, 1); /* e.g., turn on auto exposure */
                    uvc_set_ae_mode(devh, mode);//sets exposure to manual
                    uvc_set_exposure_abs(devh, 10); //exposure
                    
                    sleep(1);
                    
                    /* End the stream. Blocks until last callback is serviced */
                    uvc_stop_streaming(devh);
                    puts("Done streaming.");
                }
            }
            /* Release our handle on the device */
            uvc_close(devh);
            puts("Device closed");
        }
        /* Release the device descriptor */
        uvc_unref_device(dev);
    }
    /* Close the UVC context. This closes and cleans up any existing device handles,
     * and it closes the libusb context if one was not provided. */
    uvc_exit(ctx);
    puts("UVC exited");
}

Mat OpenVideo::getImage(){
    static Mat image;
    this->capture->read(image);
    
    if(!this->capture->read(image)) {
        cerr << "Unable to read next frame." << endl;
        cerr << "Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
    return image;
}

