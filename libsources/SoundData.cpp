#pragma once
#include "SoundData.h"

namespace wavAgent
{
    SoundData::SoundData() : waves(),
                             metaData(0,
                                      0,
                                      SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_UNSIGNED_8_BIT,
                                      0),
                             isInitialized(false)
    {
    }

    template <class T, SampleFormatType FORMAT>
    WavAgentErrorCode SoundData::getWaveBody(T **ppWave, int channel)
    {
        if (!isInitialized)
        {
            return WavAgentErrorCode::WAV_AGENT_SOUND_DATA_IS_NOT_INITIALIZED;
        }

        SampleFormatType actualFormat;
        auto result = metaData.GetSampleFormat(actualFormat);

        if (!IsWavAgentActionSucceeded(result))
        {
            return result;
        }

        if (actualFormat != FORMAT)
        {
            return WavAgentErrorCode::WAV_AGENT_INVALID_FORMAT;
        }

        if (waves.size() <= channel)
        {
            return WavAgentErrorCode::WAV_AGENT_CHANNEL_OUT_OF_RANGE;
        }

        *ppWave = (T *)(waves[channel].data());
        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }

    WavAgentErrorCode SoundData::GetWave(
        SampleUnsigned8bit **ppWave,
        int channel)
    {
        return getWaveBody<SampleUnsigned8bit,
                           SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_UNSIGNED_8_BIT>(ppWave, channel);
    }

    WavAgentErrorCode SoundData::GetWave(
        SampleSigned16bit **ppWave,
        int channel)
    {
        return getWaveBody<SampleSigned16bit,
                           SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_16_BIT>(ppWave, channel);
    }

    WavAgentErrorCode SoundData::GetWave(
        SampleSigned24bit **ppWave,
        int channel)
    {
        return getWaveBody<SampleSigned24bit,
                           SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_24_BIT>(ppWave, channel);
    }

    WavAgentErrorCode SoundData::GetWave(
        SampleSigned32bit **ppWave,
        int channel)
    {
        return getWaveBody<SampleSigned32bit,
                           SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_32_BIT>(ppWave, channel);
    }

    WavAgentErrorCode SoundData::GetWave(
        SampleSigned32bitFloat **ppWave,
        int channel)
    {
        return getWaveBody<SampleSigned32bitFloat,
                           SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_32_BIT_FLOAT>(ppWave, channel);
    }

    WavAgentErrorCode SoundData::GetWave(
        void **ppWave,
        int channel)
    {
        SampleFormatType sampleFormatType;
        auto result = metaData.GetSampleFormat(sampleFormatType);

        if (!IsWavAgentActionSucceeded(result))
        {
            return result;
        }

        switch (sampleFormatType)
        {
        case SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_UNSIGNED_8_BIT:
            return getWaveBody<SampleUnsigned8bit,
                               SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_UNSIGNED_8_BIT>(
                (SampleUnsigned8bit **)ppWave,
                channel);
        case SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_16_BIT:
            return getWaveBody<SampleSigned16bit,
                               SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_16_BIT>(
                (SampleSigned16bit **)ppWave,
                channel);
        case SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_24_BIT:
            return getWaveBody<SampleSigned24bit,
                               SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_24_BIT>(
                (SampleSigned24bit **)ppWave,
                channel);
        case SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_32_BIT:
            return getWaveBody<SampleSigned32bit,
                               SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_32_BIT>(
                (SampleSigned32bit **)ppWave,
                channel);
        case SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_32_BIT_FLOAT:
            return getWaveBody<SampleSigned32bitFloat,
                               SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_32_BIT_FLOAT>(
                (SampleSigned32bitFloat **)ppWave,
                channel);

        default:
            return WavAgentErrorCode::WAV_AGENT_INVALID_FORMAT;
        }
    }

    WavAgentErrorCode SoundData::GetWaveSizeInByte(size_t *ret, int channel)
    {
        if (!isInitialized)
        {
            return WavAgentErrorCode::WAV_AGENT_SOUND_DATA_IS_NOT_INITIALIZED;
        }

        if (waves.size() <= channel)
        {
            return WavAgentErrorCode::WAV_AGENT_CHANNEL_OUT_OF_RANGE;
        }

        *ret = waves[channel].size();

        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }

    WavAgentErrorCode SoundData::GetMetaData(MetaData *pMetaData)
    {
        if (!isInitialized)
        {
            return WavAgentErrorCode::WAV_AGENT_SOUND_DATA_IS_NOT_INITIALIZED;
        }

        *pMetaData = metaData;

        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }
}