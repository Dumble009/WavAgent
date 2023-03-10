#pragma once
#include <vector>
#include <cstdint>
#include "MetaData.h"
#include "SampleDataTypeDefinitions.h"
#include "WavAgentErrorCode.h"

namespace wavAgent
{
    // 音声ファイルから読み込まれたデータを保持するクラス。
    class SoundData
    {
    private:
        // 波形データ。各配列が各チャンネルの波形を表す
        std::vector<std::vector<uint8_t>> waves;

        // サンプリング周波数などのメタ情報
        MetaData metaData;

        // Load関数によって初期化されたかどうか
        bool isInitialized;

        template <class T, SampleFormatType FORMAT>
        WavAgentErrorCode getWaveBody(T **ppWave, int channel) const;

    public:
        SoundData();

        // 特定のチャンネルの波形のポインタを返す
        WavAgentErrorCode GetWave(SampleUnsigned8bit **ppWave,
                                  int channel) const;

        WavAgentErrorCode GetWave(SampleSigned16bit **ppWave,
                                  int channel) const;

        WavAgentErrorCode GetWave(SampleSigned24bit **ppWave,
                                  int channel) const;

        WavAgentErrorCode GetWave(SampleSigned32bit **ppWave,
                                  int channel) const;

        WavAgentErrorCode GetWave(SampleSigned32bitFloat **ppWave,
                                  int channel) const;

        WavAgentErrorCode GetWave(void **ppWave,
                                  int channel) const;

        // 特定のチャンネルのサイズをバイトで返す
        WavAgentErrorCode GetWaveSizeInByte(size_t *ret, int channel) const;

        // 音声データに含まれるメタデータを保持したオブジェクトへのポインタを返す
        WavAgentErrorCode GetMetaData(MetaData *pMetaData) const;

        // Load関数からはメンバに直接アクセスできるようにする
        friend WavAgentErrorCode Load(
            std::string_view path,
            SoundData *pSoundData);
    };
}