#pragma once

#include "SampleFormatType.h"

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
        MetaData(
            int _channelCount,
            int _samplingFreqHz,
            int _sampleFormat,
            int _sampleCount);

        // 波形データに含まれるチャンネル数を返す
        int GetChannelCount();

        // サンプリング周波数。単位はHz
        int GetSamplingFreqHz();

        // サンプルのデータ形式
        SampleFormatType GetSampleFormat();

        // 波形データの1チャンネルに含まれるサンプル数
        int GetSampleCount();
    };
}