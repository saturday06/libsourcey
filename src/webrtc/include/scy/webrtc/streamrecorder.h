///
//
// LibSourcey
// Copyright (c) 2005, Sourcey <https://sourcey.com>
//
// SPDX-License-Identifier:	LGPL-2.1+
//
/// @addtogroup webrtc
/// @{


#ifndef SCY_WebRTC_StreamRecorder_H
#define SCY_WebRTC_StreamRecorder_H


#include "scy/base.h"
#include "webrtcelevator.h"
#include "api/peerconnectioninterface.h"

#include <vector>
#include <mutex>

namespace scy {
namespace wrtc {

extern void* video_frame_callback_obj;
extern webrtc_elevator_video_frame_callback video_frame_callback;

class StreamRecorder : public rtc::VideoSinkInterface<webrtc::VideoFrame>,
                       public webrtc::AudioTrackSinkInterface
{
public:
    StreamRecorder();
    ~StreamRecorder();

    void setVideoTrack(webrtc::VideoTrackInterface* track);
    void setAudioTrack(webrtc::AudioTrackInterface* track);

    /// VideoSinkInterface implementation
    void OnFrame(const webrtc::VideoFrame& frame) override;

    /// AudioTrackSinkInterface implementation
    void OnData(const void* audio_data, int bits_per_sample, int sample_rate,
                size_t number_of_channels, size_t number_of_frames) override;

    std::mutex buf_mutex;
    std::vector<uint8_t> buf_y;
    std::vector<uint8_t> buf_u;
    std::vector<uint8_t> buf_v;
protected:
    rtc::scoped_refptr<webrtc::VideoTrackInterface> _videoTrack;
    rtc::scoped_refptr<webrtc::AudioTrackInterface> _audioTrack;
    bool _awaitingVideo = false;
    bool _awaitingAudio = false;
    bool _shouldInit = true;
};


} } // namespace scy::wrtc

#endif


/// @\}
