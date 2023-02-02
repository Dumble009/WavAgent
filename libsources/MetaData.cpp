#include "MetaData.h"

namespace wavAgent
{
    MetaData::MetaData(
        int _channelCount,
        int _samplingFreqHz,
        SampleFormatType _sampleFormat,
        int _sampleCount)
    {
    }

    // 波形データに含まれるチャンネル数を返す
    WavAgentErrorCode GetChannelCount(int &ret)
    {
        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }

    // サンプリング周波数。単位はHz
    WavAgentErrorCode GetSamplingFreqHz(int &ret)
    {
        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }

    // サンプルのデータ形式
    WavAgentErrorCode GetSampleFormat(SampleFormatType &ret)
    {
        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }

    // 波形データの1チャンネルに含まれるサンプル数
    WavAgentErrorCode GetSampleCount(int &ret)
    {
        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }
}