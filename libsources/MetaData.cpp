#include "MetaData.h"

namespace wavAgent
{
    MetaData::MetaData() {}
    MetaData::MetaData(
        int _channelCount,
        int _samplingFreqHz,
        SampleFormatType _sampleFormat,
        int _sampleCount)
        : channelCount(_channelCount),
          samplingFreqHz(_samplingFreqHz),
          sampleFormat(_sampleFormat),
          sampleCount(_sampleCount)
    {
    }

    // 波形データに含まれるチャンネル数を返す
    WavAgentErrorCode MetaData::GetChannelCount(int &ret)
    {
        ret = channelCount;
        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }

    // サンプリング周波数。単位はHz
    WavAgentErrorCode MetaData::GetSamplingFreqHz(int &ret)
    {
        ret = samplingFreqHz;
        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }

    // サンプルのデータ形式
    WavAgentErrorCode MetaData::GetSampleFormat(SampleFormatType &ret)
    {
        ret = sampleFormat;
        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }

    // 波形データの1チャンネルに含まれるサンプル数
    WavAgentErrorCode MetaData::GetSampleCount(int &ret)
    {
        ret = sampleCount;
        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }
}