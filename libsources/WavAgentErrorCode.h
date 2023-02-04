#pragma once
#include <iostream>
#include <string_view>

namespace wavAgent
{
    // WavAgent内における操作の実行結果
    enum class WavAgentErrorCode
    {
        WAV_AGENT_SUCCESS = 0,
        WAV_AGENT_FILE_NOT_EXIST = 1,
        WAV_AGENT_NOT_WAV_FILE = 2,
        WAV_AGENT_CHANNEL_OUT_OF_RANGE = 3,
        WAV_AGENT_INVALID_FORMAT = 4,
        WAV_AGENT_SOUND_DATA_IS_NOT_INITIALIZED = 5,
        WAV_AGENT_FILE_IS_BROKEN = 6,
    };

    std::ostream &operator<<(std::ostream &os, WavAgentErrorCode code);

    // エラーコードを、その名称の文字列に変換する
    std::string_view ConvertWavAgentErrorCodeToString(WavAgentErrorCode code);

    // エラーコードから、その原因を説明した文字列に変換する
    std::string_view GetDescriptionOfErrorCode(WavAgentErrorCode code);

    // WAvAgentErrorCodeを返す関数が正常に終了したかどうか判定する
    inline bool IsDataLibActionSucceeded(WavAgentErrorCode code)
    {
        // inline関数なのでヘッダに実装を記述する必要がある
        return code == WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }
}