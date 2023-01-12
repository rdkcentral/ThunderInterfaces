/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2022 RDK Management
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

namespace WPEFramework {
namespace Exchange {

   struct EXTERNAL IDTV : virtual public Core::IUnknown
   {
      enum { ID = ID_DTV };

      enum TunerType : uint8_t
      {
         NONE = 0,
         DVBS = 1,
         DVBT = 2,
         DVBC = 3
      };

      enum ServiceSearchType : uint8_t
      {
         FREQUENCY = 0,
         NETWORK = 1
      };

      struct EXTERNAL ICountry : virtual public Core::IUnknown
      {
         enum { ID = ID_DTV_COUNTRY };

         struct EXTERNAL IIterator : virtual public Core::IUnknown
         {
            enum { ID = ID_DTV_COUNTRY_ITERATOR };

            virtual uint32_t Current(IDTV::ICountry*& country /* @out */) const = 0;
            virtual uint32_t Next() = 0;
            virtual uint32_t Reset() = 0;
         };

         virtual uint32_t Name(string& name /* @out */) const = 0;
         virtual uint32_t Code(uint32_t& code /* @out */) const = 0;
      };

      struct EXTERNAL IService : virtual public Core::IUnknown
      {
         enum { ID = ID_DTV_SERVICE };

         struct EXTERNAL IIterator : virtual public Core::IUnknown
         {
            enum { ID = ID_DTV_SERVICE_ITERATOR };

            virtual uint32_t Current(IDTV::IService*& service /* @out */) const = 0;
            virtual uint32_t Next() = 0;
            virtual uint32_t Reset() = 0;
         };

         enum ServiceType : uint16_t
         {
            TV = 1,
            RADIO = 2,
            TELETEXT = 3,
            NVOD = 4,
            NVOD_TIMESHIFT = 5,
            MOSAIC = 6,
            AVC_RADIO = 10,
            AVC_MOSAIC = 11,
            DATA = 12,
            MPEG2_HD = 17,
            AVC_SD_TV = 22,
            AVC_SD_NVOD_TIMESHIFT = 23,
            AVC_SD_NVOD = 24,
            HD_TV = 25,
            AVC_HD_NVOD_TIMESHIFT = 26,
            AVC_HD_NVOD = 27,
            UHD_TV = 31,
            ANALOG = 256,
            DSD = 257,
            VIRTUAL = 258,
            UNKNOWN = 512
         };

         enum RunState : uint8_t
         {
            RUN_STATE_UNDEFINED = 0,
            RUN_STATE_NOT_RUNNING = 1,
            RUN_STATE_STARTS_SOON = 2,
            RUN_STATE_PAUSING = 3,
            RUN_STATE_RUNNING = 4,
            RUN_STATE_OFF_AIR = 5
         };

         virtual uint32_t Fullname(string& fullname /* @out */) const = 0;
         virtual uint32_t Shortname(string& shortname /* @out */) const = 0;
         virtual uint32_t Dvburi(string& dvburi /* @out */) const = 0;
         virtual uint32_t Type(ServiceType& type /* @out */) const = 0;
         virtual uint32_t Lcn(uint16_t& lcn /* @out */) const = 0;
         virtual uint32_t Scrambled(bool& scrambled /* @out */) const = 0;
         virtual uint32_t HasCaDescriptor(bool& has_ca_desc /* @out */) const = 0;
         virtual uint32_t Hidden(bool& hidden /* @out */) const = 0;
         virtual uint32_t Selectable(bool& selectable /* @out */) const = 0;
         virtual uint32_t RunningStatus(RunState& run_state /* @out */) const = 0;
      };

      struct EXTERNAL IDvbcTuningParams : virtual public Core::IUnknown
      {
         enum { ID = ID_DTV_DVBCTUNINGPARAMS };

         enum ModulationType : uint8_t
         {
            MOD_AUTO = 0,
            MOD_4QAM,
            MOD_8QAM,
            MOD_16QAM,
            MOD_32QAM,
            MOD_64QAM,
            MOD_128QAM,
            MOD_256QAM
         };

         virtual uint32_t Frequency(uint32_t& freq_hz /* @out */) const = 0;
         virtual uint32_t SymbolRate(uint16_t& sym_rate /* @out */) const = 0;
         virtual uint32_t Modulation(ModulationType& modulation /* @out */) const = 0;
      };

      struct EXTERNAL IDvbsTuningParams : virtual public Core::IUnknown
      {
         enum { ID = ID_DTV_DVBSTUNINGPARAMS };

         enum PolarityType : uint8_t
         {
            HORIZONTAL = 0,
            VERTICAL = 1,
            LEFT = 2,
            RIGHT = 3
         };

         enum FecType : uint8_t
         {
            FEC_AUTO = 0,
            FEC1_2,
            FEC2_3,
            FEC3_4,
            FEC5_6,
            FEC7_8,
            FEC1_4,
            FEC1_3,
            FEC2_5,
            FEC8_9,
            FEC9_10,
            FEC3_5,
            FEC4_5
         };

         enum ModulationType: uint8_t
         {
            MOD_AUTO = 0,
            MOD_QPSK,
            MOD_8PSK,
            MOD_16QAM
         };

         virtual uint32_t Satellite(string& sat_name /* @out */) const = 0;
         virtual uint32_t Frequency(uint32_t& freq_khz /* @out */) const = 0;
         virtual uint32_t Polarity(PolarityType& polarity /* @out */) const = 0;
         virtual uint32_t SymbolRate(uint16_t& sym_rate /* @out */) const = 0;
         virtual uint32_t Fec(FecType& fec /* @out */) const = 0;
         virtual uint32_t Modulation(ModulationType& modulation /* @out */) const = 0;
         virtual uint32_t DvbS2(bool& dvbs2 /* @out */) const = 0;
      };

      struct EXTERNAL IDvbtTuningParams : virtual public Core::IUnknown
      {
         enum { ID = ID_DTV_DVBTTUNINGPARAMS };

         enum BandwidthType : uint8_t
         {
            BW_UNDEFINED = 0,
            BW_5MHZ,
            BW_6MHZ,
            BW_7MHZ,
            BW_8MHZ,
            BW_10MHZ
         };

         enum OfdmModeType : uint8_t
         {
            OFDM_UNDEFINED = 0,
            OFDM_1K,
            OFDM_2K,
            OFDM_4K,
            OFDM_8K,
            OFDM_16K,
            OFDM_32K
         };

         virtual uint32_t Frequency(uint32_t& freq_hz /* @out */) const = 0;
         virtual uint32_t Bandwidth(BandwidthType& bandwidth /* @out */) const = 0;
         virtual uint32_t OfdmMode(OfdmModeType& mode /* @out */) const = 0;
         virtual uint32_t DvbT2(bool& dvbt2 /* @out */) const = 0;
         virtual uint32_t PlpId(uint8_t& plp_id /* @out */) const = 0;
      };

      struct EXTERNAL ILnb : virtual public Core::IUnknown
      {
         enum { ID = ID_DTV_LNB };

         struct EXTERNAL IIterator : virtual public Core::IUnknown
         {
            enum { ID = ID_DTV_LNB_ITERATOR };

            virtual uint32_t Current(IDTV::ILnb*& lnb /* @out */) const = 0;
            virtual uint32_t Next() = 0;
            virtual uint32_t Reset() = 0;
         };

         enum LnbType : uint8_t
         {
            SINGLE = 0,
            UNIVERSAL,
            UNICABLE,
            USERDEFINED
         };

         enum LnbPower : uint8_t
         {
            POWER_OFF = 0,
            POWER_ON,
            POWER_AUTO
         };

         enum DiseqcTone : uint8_t
         {
            TONE_OFF = 0,
            TONE_A,
            TONE_B
         };

         enum DiseqcCSwitch : uint8_t
         {
            CS_OFF = 0,
            CS_A,
            CS_B,
            CS_C,
            CS_D
         };

         virtual uint32_t Name(string& name /* @out */) const = 0;
         virtual uint32_t Type(LnbType& type /* @out */) const = 0;
         virtual uint32_t Power(LnbPower& power /* @out */) const = 0;
         virtual uint32_t Tone(DiseqcTone& tone /* @out */) const = 0;
         virtual uint32_t CSwitch(DiseqcCSwitch& cswitch /* @out */) const = 0;
         virtual uint32_t Is22kHz(bool& is_22khz /* @out */) const = 0;
         virtual uint32_t Is12V(bool& is_12v /* @out */) const = 0;
         virtual uint32_t IsPulsePosition(bool& is_pulse_pos /* @out */) const = 0;
         virtual uint32_t IsDiseqcPosition(bool& is_diseqc_pos /* @out */) const = 0;
         virtual uint32_t IsSmatv(bool& is_smatv /* @out */) const = 0;
         virtual uint32_t DiseqcRepeats(uint8_t& repeats /* @out */) const = 0;
         virtual uint32_t USwitch(uint8_t& u_switch /* @out */) const = 0;
         virtual uint32_t UnicableChannel(uint8_t& channel /* @out */) const = 0;
         virtual uint32_t UnicableFreq(uint32_t& freq /* @out */) const = 0;
      };

      struct EXTERNAL ISatellite : virtual public Core::IUnknown
      {
         enum { ID = ID_DTV_SATELLITE };

         struct EXTERNAL IIterator : virtual public Core::IUnknown
         {
            enum { ID = ID_DTV_SATELLITE_ITERATOR };

            virtual uint32_t Current(IDTV::ISatellite*& sat /* @out */) const = 0;
            virtual uint32_t Next() = 0;
            virtual uint32_t Reset() = 0;
         };

         virtual uint32_t Name(string& name /* @out */) const = 0;
         virtual uint32_t Longitude(int16_t& longitude /* @out */) const = 0;
         virtual uint32_t Lnb(string& lnb_name /* @out */) const = 0;
      };

      struct EXTERNAL IStatus : virtual public Core::IUnknown
      {
         enum { ID = ID_DTV_STATUS };

         virtual uint32_t Tuner(uint8_t& tuner /* @out */) const = 0;
         virtual uint32_t Demux(uint8_t& demux /* @out */) const = 0;
         virtual uint32_t PmtPid(uint16_t& pid /* @out */) const = 0;
         virtual uint32_t Dvburi(string& dvburi /* @out */) const = 0;
         virtual uint32_t Lcn(uint16_t& lcn /* @out */) const = 0;
      };

      struct EXTERNAL IEitEvent : virtual public Core::IUnknown
      {
         enum { ID = ID_DTV_EIT_EVENT };

         struct EXTERNAL IIterator : virtual public Core::IUnknown
         {
            enum { ID = ID_DTV_EIT_EVENT_ITERATOR };

            virtual uint32_t Current(IDTV::IEitEvent*& eit_event /* @out */) const = 0;
            virtual uint32_t Next() = 0;
            virtual uint32_t Reset() = 0;
         };

         struct EXTERNAL IContentData : virtual public Core::IUnknown
         {
            enum { ID = ID_DTV_CONTENTDATA };

            struct EXTERNAL IIterator : virtual public Core::IUnknown
            {
               enum { ID = ID_DTV_CONTENTDATA_ITERATOR };

               virtual uint32_t Current(IDTV::IEitEvent::IContentData*& content_data /* @out */) const = 0;
               virtual uint32_t Next() = 0;
               virtual uint32_t Reset() = 0;
            };

            virtual uint32_t Value(uint8_t& value /* @out */) const = 0;
         };

         virtual uint32_t Name(string& name /* @out */) const = 0;
         virtual uint32_t StartTime(uint32_t& start_time /* @out */) const = 0;
         virtual uint32_t Duration(uint32_t& duration /* @out */) const = 0;
         virtual uint32_t EventId(uint16_t& event_id /* @out */) const = 0;
         virtual uint32_t ShortDescription(string& description /* @out */) const = 0;
         virtual uint32_t HasSubtitles(bool& has_subs /* @out */) const = 0;
         virtual uint32_t HasAudioDescription(bool& has_ad /* @out */) const = 0;
         virtual uint32_t ParentalRating(uint8_t& rating /* @out */) const = 0;
         virtual uint32_t ContentData(IContentData::IIterator*& content_data /* @out */) const = 0;
         virtual uint32_t HasExtendedInfo(bool& extended_info /* @out */) const = 0;
      };

      struct EXTERNAL IEitExtendedEvent : virtual public Core::IUnknown
      {
         enum { ID = ID_DTV_EIT_EXTENDEDEVENT };

         struct EXTERNAL IEitExtendedEventItem : virtual public Core::IUnknown
         {
            enum { ID = ID_DTV_EIT_EXTENDEDEVENTITEM };

            struct EXTERNAL IIterator : virtual public Core::IUnknown
            {
               enum { ID = ID_DTV_EIT_EXTENDEDEVENTITEM_ITERATOR };

               virtual uint32_t Current(IDTV::IEitExtendedEvent::IEitExtendedEventItem*& event_item /* @out */) const = 0;
               virtual uint32_t Next() = 0;
               virtual uint32_t Reset() = 0;
            };

            virtual uint32_t Description(string& desc /* @out */) const = 0;
            virtual uint32_t Item(string& item /* @out */) const = 0;
         };

         virtual uint32_t Description(string& desc /* @out */) const = 0;
         virtual uint32_t Items(IEitExtendedEventItem::IIterator*& items /* @out */) const = 0;
      };

      struct EXTERNAL ISignalInfo : virtual public Core::IUnknown
      {
         enum { ID = ID_DTV_SIGNALINFO };

         virtual uint32_t Locked(bool& locked /* @out */) const = 0;
         virtual uint32_t Strength(uint8_t& strength /* @out */) const = 0;
         virtual uint32_t Quality(uint8_t& quality /* @out */) const = 0;
      };

      struct EXTERNAL IComponent : virtual public Core::IUnknown
      {
         enum { ID = ID_DTV_COMPONENT };

         struct EXTERNAL IIterator : virtual public Core::IUnknown
         {
            enum { ID = ID_DTV_COMPONENT_ITERATOR };

            virtual uint32_t Current(IDTV::IComponent*& comp /* @out */) const = 0;
            virtual uint32_t Next() = 0;
            virtual uint32_t Reset() = 0;
         };

         struct EXTERNAL ITag : virtual public Core::IUnknown
         {
            enum { ID = ID_DTV_COMPONENT_TAG };

            struct EXTERNAL IIterator : virtual public Core::IUnknown
            {
               enum { ID = ID_DTV_COMPONENT_TAG_ITERATOR };

               virtual uint32_t Current(IDTV::IComponent::ITag*& tag /* @out */) const = 0;
               virtual uint32_t Next() = 0;
               virtual uint32_t Reset() = 0;
            };

            virtual uint32_t Tag(uint8_t& value /* @out */) const = 0;
         };

         enum ComponentType : uint8_t
         {
            VIDEO,
            AUDIO,
            SUBTITLES,
            TELETEXT,
            DATA
         };

         enum CodecType : uint8_t
         {
            MPEG2,
            H264,
            H265,
            AVS,
            MPEG1,
            AAC,
            HEAAC,
            HEAACV2,
            AC3,
            EAC3
         };

         enum AudType : uint8_t
         {
            AUDIOTYPE_UNDEFINED,
            AUDIOTYPE_CLEAN,
            AUDIOTYPE_HEARINGIMPAIRED,
            AUDIOTYPE_VISUALLYIMPAIRED,
            AUDIOTYPE_UNKNOWN
         };

         enum AudMode : uint8_t
         {
            AUDIOMODE_MONO,
            AUDIOMODE_LEFT,
            AUDIOMODE_RIGHT,
            AUDIOMODE_STEREO,
            AUDIOMODE_MULTICHANNEL,
            AUDIOMODE_UNDEFINED
         };

         enum SubFormat : uint8_t
         {
            FORMAT_DEFAULT,
            FORMAT_4_3,
            FORMAT_16_9,
            FORMAT_221_1,
            FORMAT_HD,
            FORMAT_HARDOFHEARING,
            FORMAT_HARDOFHEARING4_3,
            FORMAT_HARDOFHEARING16_9,
            FORMAT_HARDOFHEARING221_1,
            FORMAT_HARDOFHEARINGHD
         };

         virtual uint32_t Type(ComponentType& type /* @out */) const = 0;
         virtual uint32_t Tags(ITag::IIterator*& tags /* @out */) const = 0;
         virtual uint32_t Pid(uint16_t& pid /* @out */) const = 0;
         virtual uint32_t Codec(CodecType& codec /* @out */) const = 0;
         virtual uint32_t Language(string& lang /* @out */) const = 0;
         virtual uint32_t AudioType(AudType& type /* @out */) const = 0;
         virtual uint32_t AudioMode(AudMode& mode /* @out */) const = 0;
         virtual uint32_t SubtitleFormat(SubFormat& format /* @out */) const = 0;
         virtual uint32_t CompositionPage(uint16_t& page /* @out */) const = 0;
         virtual uint32_t AncillaryPage(uint16_t& page /* @out */) const = 0;
         virtual uint32_t TeletextType(uint8_t& type /* @out */) const = 0;
         virtual uint32_t TeletextMagazine(uint8_t& magazine /* @out */) const = 0;
         virtual uint32_t TeletextPage(uint8_t& page /* @out */) const = 0;
      };

      struct EXTERNAL ITransport : virtual public Core::IUnknown
      {
         enum { ID = ID_DTV_TRANSPORT };

         virtual uint32_t Tuner(TunerType& type /* @out */) const = 0;
         virtual uint32_t OriginalNetworkId(uint16_t& onet_id /* @out */) const = 0;
         virtual uint32_t TransportId(uint16_t& trans_id /* @out */) const = 0;
         virtual uint32_t SignalStrength(uint8_t& strength /* @out */) const = 0;
         virtual uint32_t SignalQuality(uint8_t& quality /* @out */) const = 0;
         virtual uint32_t TuningParamsDvbc(IDvbcTuningParams*& params /* @out */) const = 0;
         virtual uint32_t TuningParamsDvbs(IDvbsTuningParams*& params /* @out */) const = 0;
         virtual uint32_t TuningParamsDvbt(IDvbtTuningParams*& params /* @out */) const = 0;
      };

      struct EXTERNAL INotification : virtual public Core::IUnknown
      {
         enum { ID = ID_DTV_NOTIFICATION };

         enum ServiceEventType : uint8_t
         {
            SERVICE_UPDATED,
            SERVICE_ADDED,
            SERVICE_DELETED,
            VIDEO_CHANGED,
            AUDIO_CHANGED,
            SUBTITLES_CHANGED,
            NOW_EVENT_CHANGED
         };

         virtual void SearchEvent(const uint8_t handle, const bool finished, const uint8_t progress) = 0;
         virtual void ServiceEvent(const ServiceEventType event_type, const IDTV::IService *service,
            const IEitEvent *eit_event = nullptr) = 0;
      };

      /* @brief Allow the plugin to initialize and read its configuration data */
      virtual uint32_t Initialize(PluginHost::IShell* framework) = 0;

      /* @brief Register for notifications from the plugin */
      virtual uint32_t Register(IDTV::INotification* notification) = 0;

      /* @brief Unregister for notifications from the plugin */
      virtual uint32_t Unregister(IDTV::INotification* notification) = 0;

      virtual uint32_t GetNumberOfCountries(uint8_t& count /* @out */) const = 0;
      virtual uint32_t GetCountryList(ICountry::IIterator*& countries /* @out */) const = 0;
      virtual uint32_t GetCountry(uint32_t& code /* @out */) const = 0;
      virtual uint32_t SetCountry(const uint32_t code) = 0;

      virtual uint32_t GetLnbList(ILnb::IIterator*& lnbs /* @out */) const = 0;
      virtual uint32_t GetSatelliteList(ISatellite::IIterator*& satellites /* @out */) const = 0;

      virtual uint32_t GetNumberOfServices(uint16_t& count /* @out */) const = 0;
      virtual uint32_t GetServiceList(IService::IIterator*& services /* @out */) const = 0;
      virtual uint32_t GetServiceList(const TunerType tuner_type, IService::IIterator*& services /* @out */) const = 0;
      virtual uint32_t GetServiceList(const uint16_t onet_id, const uint16_t trans_id,
         IService::IIterator*& services /* @out */) const = 0;

      virtual uint32_t GetNowNextEvents(const uint16_t onet_id, const uint16_t trans_id, const uint16_t serv_id,
         IEitEvent*& now_event /* @out */, IEitEvent*& next_event /* @out */) const = 0;
      virtual uint32_t GetScheduleEvents(const uint16_t onet_id, const uint16_t trans_id, const uint16_t serv_id,
         const uint32_t start_utc, const uint32_t end_utc, IEitEvent::IIterator*& events /* @out */) const = 0;

      virtual uint32_t GetStatus(const int32_t handle, IStatus*& status /* @out */) const = 0;

      virtual uint32_t GetServiceInfo(const uint16_t onet_id, const uint16_t trans_id, const uint16_t serv_id,
         IService*& service_info /* @out */) const = 0;
      virtual uint32_t GetServiceComponents(const uint16_t onet_id, const uint16_t trans_id, const uint16_t serv_id,
         IComponent::IIterator*& components /* @out */) const = 0;
      virtual uint32_t GetTransportInfo(const uint16_t onet_id, const uint16_t trans_id,
         ITransport*& transport_info /* @out */) const = 0;
      virtual uint32_t GetExtendedEventInfo(const uint16_t onet_id, const uint16_t trans_id, const uint16_t serv_id,
         const uint16_t event_id, IEitExtendedEvent*& info /* @out */) const = 0;
      virtual uint32_t GetSignalInfo(const int32_t handle, ISignalInfo*& info /* @out */) const = 0;

      virtual uint32_t AddLnb(const string lnb_name, const ILnb::LnbType type, const ILnb::LnbPower power,
         const ILnb::DiseqcTone tone, const ILnb::DiseqcCSwitch cswitch, const bool is22khz, const bool is12v,
         const bool is_pulse_pos, const bool is_diseqc_pos, const bool is_smatv, const uint8_t diseqc_repeats,
         const uint8_t uswitch, const uint8_t unicable_channel, const uint32_t unicable_freq) = 0;
      virtual uint32_t AddSatellite(const string sat_name, const int16_t longitude, const string lnb_name) = 0;

      virtual uint32_t StartServiceSearch(const TunerType tuner_type, const ServiceSearchType search_type,
         const bool retune) = 0;
      virtual uint32_t StartServiceSearch(const ServiceSearchType search_type, const bool retune,
         const IDvbcTuningParams* tuning_params) = 0;
      virtual uint32_t StartServiceSearch(const ServiceSearchType search_type, const bool retune,
         const IDvbsTuningParams* tuning_params) = 0;
      virtual uint32_t StartServiceSearch(const ServiceSearchType search_type, const bool retune,
         const IDvbtTuningParams* tuning_params) = 0;
      virtual uint32_t FinishServiceSearch(const TunerType tuner_type, const bool save_changes) = 0;

      virtual uint32_t StartPlaying(const string dvburi, const bool monitor_only, int32_t& play_handle /* @out */) = 0;
      virtual uint32_t StartPlaying(const uint16_t lcn, const bool monitor_only, int32_t& play_handle /* @out */) = 0;
      virtual uint32_t StopPlaying(const int32_t play_handle) = 0;

      virtual uint32_t DvbcTuningParams(const uint32_t freq_hz, const uint16_t symbol_rate,
         const IDvbcTuningParams::ModulationType modulation, IDvbcTuningParams*& params /* @out */) = 0;

      virtual uint32_t DvbsTuningParams(const string sat_name, const uint32_t freq_khz,
         const IDvbsTuningParams::PolarityType polarity, const uint16_t symbol_rate,
         const IDvbsTuningParams::FecType fec, const IDvbsTuningParams::ModulationType modulation,
         const bool dvbs2, IDvbsTuningParams*& params /* @out */) = 0;

      virtual uint32_t DvbtTuningParams(const uint32_t freq_hz, const IDvbtTuningParams::BandwidthType bandwidth,
         const IDvbtTuningParams::OfdmModeType mode, const bool dvbt2, const uint8_t plp_id,
         IDvbtTuningParams*& params /* @out */) = 0;

   };
}
}

