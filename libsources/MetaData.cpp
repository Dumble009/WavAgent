#include "MetaData.h"

namespace wavAgent
{
    MetaData::MetaData() {}
    MetaData::MetaData(
        int _channelCount,
        int _samplingFreqHz,
        SampleFormatType _sampleFormat,
        int _sampleCount)
    {
    }

    // 波形データに含まれるチャンネル数を返す
    WavAgentErrorCode MetaData::GetChannelCount(int &ret)
    {
        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }

    // サンプリング周波数。単位はHz
    WavAgentErrorCode MetaData::GetSamplingFreqHz(int &ret)
    {
        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }

    // サンプルのデータ形式
    WavAgentErrorCode MetaData::GetSampleFormat(SampleFormatType &ret)
    {
        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }

    // 波形データの1チャンネルに含まれるサンプル数
    WavAgentErrorCode MetaData::GetSampleCount(int &ret)
    {
        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }
}