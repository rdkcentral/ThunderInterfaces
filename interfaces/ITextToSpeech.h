#ifndef __ITEXTTOSPEECH_H
#define __ITEXTTOSPEECH_H

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

    struct EXTERNAL ITextToSpeech : virtual public Core::IUnknown {
        enum { ID = ID_TEXT_TO_SPEECH };

        struct Configuration {
            std::string ttsEndPoint;
            std::string ttsEndPointSecured;
            std::string language;
            std::string voice;
            std::string speechRate;
            uint8_t volume;
            uint8_t rate;
        };

        enum SpeechState: uint8_t {
            SPEECH_PENDING = 0,
            SPEECH_IN_PROGRESS,
            SPEECH_PAUSED,
            SPEECH_NOT_FOUND
        };

        enum TTSErrorDetail: uint8_t {
            TTS_OK = 0,
            TTS_FAIL,
            TTS_NOT_ENABLED,
            TTS_INVALID_CONFIGURATION,
            TTS_NO_ACCESS
        };


        struct INotification : virtual public Core::IUnknown {
            enum { ID = ID_TEXT_TO_SPEECH_NOTIFICATION };

            ~INotification() override = default;

            // Signal changes on the subscribed namespace
            // @brief Notify TTS enabled/disabled
            // @param state enabled/disabled
            virtual void Enabled(const bool state) = 0;

            // @brief Notify change in voice used for speaking
            // @param voice voice changed 
            virtual void VoiceChanged(const string voice) = 0;

            // @brief Notify speechid based on the speech state(eg: start,pause,..etc)
            // @param speechid id of the text
            virtual void WillSpeak(const uint32_t speechid) = 0;
            virtual void SpeechStart(const uint32_t speechid) = 0;
            virtual void SpeechPause(const uint32_t speechid) = 0;
            virtual void SpeechResume(const uint32_t speechid) = 0;
            virtual void SpeechInterrupted(const uint32_t speechid) = 0;
            virtual void NetworkError(const uint32_t speechid) = 0;
            virtual void PlaybackError(const uint32_t speechid) = 0;
            virtual void SpeechComplete(const uint32_t speechid) = 0;
        };

        ~ITextToSpeech() override = default;

        virtual void Register(ITextToSpeech::INotification* sink) = 0;
        virtual void Unregister(ITextToSpeech::INotification* sink) = 0;
        
        // @property
        // @brief Query the status/enable tts
        // @param enable status/enable
        virtual uint32_t Enable(const bool enable) = 0;
        virtual uint32_t Enable(bool &enable /* @out */) const = 0;

        // @brief Set the tts configuration attributes
        // @param config tts configuration
        // @param status return status
        virtual uint32_t SetConfiguration(const Configuration &config,TTSErrorDetail &status/* @out */) = 0;

        virtual uint32_t SetFallbackText(const string scenario,const string value) = 0;
        virtual uint32_t SetAPIKey(const string apikey) = 0;
        virtual uint32_t SetPrimaryVolDuck(const uint8_t prim) = 0;

        // @brief Retrieve tts configuration attributes 
        // @param config tts configuration
        virtual uint32_t GetConfiguration(Configuration &config/* @out */) const = 0;
        
        // @brief List voices available 
        // @param language input
        // @param voices list of voices
        virtual uint32_t ListVoices(const string language,RPC::IStringIterator*& voices/* @out */) const = 0;
        
        // @brief Speaks text provided
        // @param text for conversion
        // @param speechid returns id for the text 
        // @param status return status
        virtual uint32_t Speak(const string text,uint32_t &speechid/* @out */,TTSErrorDetail &status/* @out */) = 0;
        
        // @brief Cancel the speech
        // @param speechid id of text to be cancelled
        virtual uint32_t Cancel(const uint32_t speechid) = 0;
        
        // @brief Pause the speech
        // @param speechid id of text to be paused
        // @param status return status
        virtual uint32_t Pause(const uint32_t speechid,TTSErrorDetail &status /* @out */) = 0;
        
        // @brief Resume the speech
        // @param speechid id of text to be resumed
        // @param status return status
        virtual uint32_t Resume(const uint32_t speechid,TTSErrorDetail &status /* @out */) = 0;
        
        // @brief Get speech status
        // @param speechid id of text to get status
        // @param state speech state
        virtual uint32_t GetSpeechState(const uint32_t speechid,SpeechState &state/* @out */) = 0;
    };

} // Exchange
} // WPEFramework

#endif //__ITEXTTOSPEECH_H
