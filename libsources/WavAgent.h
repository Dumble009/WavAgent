#pragma once
#include <string_view>
#include "WavAgentErrorCode.h"
#include "SoundData.h"

namespace wavAgent
{
    // pathが指すwavファイルを読み込んで、pSoundDataが指す先に格納する
    WavAgentErrorCode Load(
        std::string_view path,
        SoundData *pSoundData);
}