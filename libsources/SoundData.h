#pragma once
#include <vector>
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
        std::vector<std::vector<unsigned char>> waves;

        // サンプリング周波数などのメタ情報
        MetaData metaData;

    public:
        SoundData();

        // 特定のチャンネルの波形のポインタを返す
        WavAgentErrorCode GetWave(SampleUnsigned8bit **ppWave,
                                  int channel);

        // 特定のチャンネルの波形のポインタを返す
        WavAgentErrorCode GetWave(SampleSigned16bit **ppWave,
                                  int channel);

        // 特定のチャンネルの波形のポインタを返す
        WavAgentErrorCode GetWave(SampleSigned24bit **ppWave,
                                  int channel);

        // 特定のチャンネルの波形のポインタを返す
        WavAgentErrorCode GetWave(SampleSigned32bit **ppWave,
                                  int channel);

        // 特定のチャンネルの波形のポインタを返す
        WavAgentErrorCode GetWave(SampleSigned32bitFloat **ppWave,
                                  int channel);

        // 音声データに含まれるメタデータを保持したオブジェクトへのポインタを返す
        WavAgentErrorCode GetMetaData(MetaData **ppMetaData);

        // Load関数からはメンバに直接アクセスできるようにする
        friend WavAgentErrorCode Load(
            const std::string &path,
            SoundData *pSoundData);
    };
}