/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "Module.h"

// @stubgen:include <com/IRPCIterator.h>

namespace WPEFramework {
namespace Exchange {

    /* @json @extended */  // NOTE: extended format is deprecated!! Do not just copy this line!
    struct EXTERNAL IPlayerProperties : virtual public Core::IUnknown {
        enum { ID = ID_PLAYER_PROPERTIES };

         enum AudioCodec : uint8_t {
            AUDIO_UNDEFINED,
            AUDIO_AAC,
            AUDIO_AC3,
            AUDIO_AC3_PLUS,
            AUDIO_DTS,
            AUDIO_MPEG1,
            AUDIO_MPEG2,
            AUDIO_MPEG3,
            AUDIO_MPEG4,
            AUDIO_OPUS,
            AUDIO_VORBIS_OGG,
            AUDIO_WAV
        };

        enum VideoCodec : uint8_t {
            VIDEO_UNDEFINED,
            VIDEO_H263,
            VIDEO_H264,
            VIDEO_H265,
            VIDEO_H265_10,
            VIDEO_MPEG,
            VIDEO_MPEG2,
            VIDEO_MPEG4,
            VIDEO_VP8,
            VIDEO_VP9,
            VIDEO_VP10
        };

        typedef RPC::IIteratorType<AudioCodec, ID_PLAYER_PROPERTIES_AUDIO> IAudioCodecIterator;
        typedef RPC::IIteratorType<VideoCodec, ID_PLAYER_PROPERTIES_VIDEO> IVideoCodecIterator;

        virtual uint32_t AudioCodecs(IAudioCodecIterator*& codec /* @out */) const = 0;
        virtual uint32_t VideoCodecs(IVideoCodecIterator*& codec /* @out */) const = 0;

        enum PlaybackResolution : uint8_t {
            RESOLUTION_UNKNOWN,
            RESOLUTION_480I24,
            RESOLUTION_480I25,
            RESOLUTION_480I30,
            RESOLUTION_480I50,
            RESOLUTION_480I,
            RESOLUTION_480P24,
            RESOLUTION_480P25,
            RESOLUTION_480P30,
            RESOLUTION_480P50,
            RESOLUTION_480P,
            RESOLUTION_576I24,
            RESOLUTION_576I25,
            RESOLUTION_576I30,
            RESOLUTION_576I50,
            RESOLUTION_576I,
            RESOLUTION_576P24,
            RESOLUTION_576P25,
            RESOLUTION_576P30,
            RESOLUTION_576P50,
            RESOLUTION_576P,
            RESOLUTION_720P24,
            RESOLUTION_720P25,
            RESOLUTION_720P30,
            RESOLUTION_720P50,
            RESOLUTION_720P,
            RESOLUTION_1080I24,
            RESOLUTION_1080I25,
            RESOLUTION_1080I30,
            RESOLUTION_1080I50,
            RESOLUTION_1080I,
            RESOLUTION_1080P24,
            RESOLUTION_1080P25,
            RESOLUTION_1080P30,
            RESOLUTION_1080P50,
            RESOLUTION_1080P,
            RESOLUTION_2160P24,
            RESOLUTION_2160P25,
            RESOLUTION_2160P30,
            RESOLUTION_2160P50,
            RESOLUTION_2160P60,
            RESOLUTION_2160P,
            RESOLUTION_600P24,
            RESOLUTION_600P25,
            RESOLUTION_600P30,
            RESOLUTION_600P50,
            RESOLUTION_600P60,
            RESOLUTION_600P,
            RESOLUTION_768P24,
            RESOLUTION_768P25,
            RESOLUTION_768P30,
            RESOLUTION_768P50,
            RESOLUTION_768P60,
            RESOLUTION_768P,
            RESOLUTION_3840x1080P24,
            RESOLUTION_3840x1080P25,
            RESOLUTION_3840x1080P30,
            RESOLUTION_3840x1080P50,
            RESOLUTION_3840x1080P60,
            RESOLUTION_3840x1080P
        };

        // @property
        // @brief Current Video playback resolution
        // @param res: resolution
        virtual uint32_t Resolution(PlaybackResolution& res /* @out */) const = 0;

        // @property
        // @brief Checks Loudness Equivalence in platform
        // @param ae: enabled/disabled
        virtual uint32_t IsAudioEquivalenceEnabled(bool& ae /* @out */) const = 0;
    };
}
}
