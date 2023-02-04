#pragma once
#include "SoundData.h"

namespace wavAgent
{
    SoundData::SoundData() : waves(),
                             metaData(0,
                                      0,
                                      SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_UNSIGNED_8_BIT,
                                      0)
    {
    }

    WavAgentErrorCode SoundData::GetWave(
        SampleUnsigned8bit **ppWave,
        int channel)
    {
        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }

    WavAgentErrorCode SoundData::GetWave(
        SampleSigned16bit **ppWave,
        int channel)
    {
        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }

    WavAgentErrorCode SoundData::GetWave(
        SampleSigned24bit **ppWave,
        int channel)
    {
        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }

    WavAgentErrorCode SoundData::GetWave(
        SampleSigned32bit **ppWave,
        int channel)
    {
        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }

    WavAgentErrorCode SoundData::GetWave(
        SampleSigned32bitFloat **ppWave,
        int channel)
    {
        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }

    WavAgentErrorCode SoundData::GetMetaData(MetaData *pMetaData)
    {
        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }
}