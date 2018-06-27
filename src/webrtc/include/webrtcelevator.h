#ifndef WEBRTCELEVATOR_WEBRTCELEVATOR_H
#define WEBRTCELEVATOR_WEBRTCELEVATOR_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    size_t width;
    size_t height;
    const uint8_t* y;
    const uint8_t* u;
    const uint8_t* v;
} webrtc_elevator_video_frame;

typedef void (*webrtc_elevator_video_frame_callback)(void* obj, const webrtc_elevator_video_frame* const);

void start_webrtc_elevator(void* obj, webrtc_elevator_video_frame_callback callback);

#ifdef __cplusplus
}
#endif

#endif
