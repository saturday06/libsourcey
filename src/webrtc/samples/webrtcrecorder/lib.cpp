///
//
// LibSourcey
// Copyright (c) 2005, Sourcey <https://sourcey.com>
//
// SPDX-License-Identifier:	LGPL-2.1+
//
///

#include "webrtcelevator.h"
#include "scy/idler.h"
#include "scy/logger.h"
#include "signaler.h"

#include "rtc_base/ssladapter.h"
#include "rtc_base/thread.h"

#include <thread>
#include <sys/epoll.h>
#include <sys/timerfd.h>

using std::endl;
using namespace scy;


// Test this demo with the code in the `client` directory
/*
void encoder_loop(Signaler& app) {
    struct itimerspec interval = {
      { // Interval for periodic timer
        1, // sec
        0 // nsec
      },
      { // Initial expiration
        1, // sec
        0 // nsec
      }
    };

    int timerfd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (timerfd == -1) {
        fprintf(stderr, "timerfd_create() failed: errno=%d\n", errno);
        abort();
    }

    int r = timerfd_settime(timerfd, 0, &interval, NULL);
    if (r < 0) {
        fprintf(stderr, "timerfd_settime() failed: errno=%d\n", errno);
        abort();
    }

    int epollfd = epoll_create(1);
    if (epollfd < 0) {
        fprintf(stderr, "epoll_create() failed: errno=%d\n", errno);
        abort();
    }

    struct epoll_event ev = {0};
    ev.events = EPOLLIN;

    r = epoll_ctl(epollfd, EPOLL_CTL_ADD, timerfd, &ev);
    if (r < 0) {
        fprintf(stderr, "epoll_ctl(ADD) failed: errno=%d\n", errno);
        abort();
    }

    while (true) {
        struct epoll_event event = {0};
        int n = epoll_wait(epollfd, &event, 1, -1);
        if (n == 1) {
            uint64_t tick = 0;
            r = read(timerfd, &tick, sizeof(tick));
            if (r < 0) {
                fprintf(stderr, "read failed: errno=%d\n", errno);
                abort();
            }
            printf("read(): %d, tick=%d\n", r, tick);

            for (int i = 0; i < tick; i++) {

            }
        }
    }
}
*/

void start_webrtc_elevator(webrtc_elevator_video_frame_callback callback)
{
    Logger::instance().add(new ConsoleChannel("debug", Level::Debug)); // LTrace

    wrtc::video_frame_callback = callback;

#if USE_SSL
    net::SSLManager::initNoVerifyClient();
#endif

    // Setup WebRTC environment
    rtc::LogMessage::LogToDebug(rtc::LERROR);
    rtc::LogMessage::LogTimestamps();
    rtc::LogMessage::LogThreads();

    rtc::InitializeSSL();

    {
        smpl::Client::Options options;
        options.host = SERVER_HOST;
        options.port = SERVER_PORT;
        options.name = "Video Recorder";
        options.user = "videorecorder";

        // NOTE: The server must enable anonymous authentication for this demo.
        // options.token = ""; token based authentication

        Signaler app(options);
        //std::thread encoder_thread([&] { encoder_loop(app); });
        // Process WebRTC threads on the main loop.
        auto rtcthread = rtc::Thread::Current();
        Idler rtc([=]() {
            rtcthread->ProcessMessages(1);
        });

        app.waitForShutdown();
        exit(0); // ...
    }

#if USE_SSL
    net::SSLManager::destroy();
#endif
    rtc::CleanupSSL();
    Logger::destroy();
}
