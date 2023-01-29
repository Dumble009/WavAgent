#pragma once
#include <string>
#include "WavAgentErrorCode.h"
#include "SoundData.h"

namespace wavAgent
{
    // wavファイルを読み込んで、波形データやメタデータを取り出す処理を行うクラス
    class WavAgent
    {
    public:
        // pathが指すwavファイルを読み込んで、pSoundDataが指す先に格納する
        WavAgentErrorCode Load(
            std::string path,
            SoundData *pSoundData);
    };
}