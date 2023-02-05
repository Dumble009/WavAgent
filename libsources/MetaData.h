#pragma once

#include "SampleFormatType.h"
#include "WavAgentErrorCode.h"

namespace wavAgent
{
    // 音声データのメタ情報。サンプリング周波数、ビット深度など
    class MetaData
    {
    private:
        // チャンネル数
        int channelCount;

        // サンプリング周波数。単位はHz
        int samplingFreqHz;

        // サンプルのデータ形式
        SampleFormatType sampleFormat;

        // 波形データの1チャンネルに含まれるサンプル数
        int sampleCount;

    public:
        MetaData();
        MetaData(
            int _channelCount,
            int _samplingFreqHz,
            SampleFormatType _sampleFormat,
            int _sampleCount);

        // 波形データに含まれるチャンネル数を返す
        WavAgentErrorCode GetChannelCount(int &ret);

        // サンプリング周波数。単位はHz
        WavAgentErrorCode GetSamplingFreqHz(int &ret);

        // サンプルのデータ形式
        WavAgentErrorCode GetSampleFormat(SampleFormatType &ret);

        // 波形データの1チャンネルに含まれるサンプル数
        WavAgentErrorCode GetSampleCount(int &ret);
    };
}