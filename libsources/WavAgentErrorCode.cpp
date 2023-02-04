#include "WavAgentErrorCode.h"

namespace wavAgent
{
    std::ostream &operator<<(std::ostream &os, WavAgentErrorCode code)
    {
        return (os << ConvertWavAgentErrorCodeToString(code));
    }

    // WavAgentErrorCodeを文字列に変換した結果。
    // WavAgentErrorCodeをint型に変換した時の要素番号の位置に、対応する文字列を入れる
    constexpr std::string_view ERROR_CODE_NAMES[8] = {
        "WAV_AGENT_SUCCESS",
        "WAV_AGENT_FILE_NOT_EXIST",
        "WAV_AGENT_NOT_WAV_FILE",
        "WAV_AGENT_CHANNEL_OUT_OF_RANGE",
        "WAV_AGENT_INVALID_FORMAT",
        "WAV_AGENT_SOUND_DATA_IS_NOT_INITIALIZED",
        "WAV_AGENT_FILE_IS_BROKEN",
        "WAV_AGENT_NOT_SUPPORTED_FORMAT"};

    std::string_view ConvertWavAgentErrorCodeToString(WavAgentErrorCode code)
    {
        return ERROR_CODE_NAMES[(int)code];
    }

    constexpr std::string_view ERROR_DESCRIPTIONS[8] = {
        "WavAgent : Operation successfully completed.",
        "WavAgent : Loading a file failed. A file does not exist.",
        "WavAgent : Loading a file failed. A file is not a wav file.",
        "WavAgent : Invalid channel index was passed. Please check a channel count in a meta data.",
        "WavAgent : Claimed format does not match with a format of data. Please check a sample format in a meta data.",
        "WavAgent : A sound data was not initialized. Please initialize it using Load function before accessing its members.",
        "WavAgent : Passed wav file is broken. Metadata or payload has invalid values.",
        "WavAgent : Passed wav file has a format which is not supported by this library."};

    std::string_view GetDescriptionOfErrorCode(WavAgentErrorCode code)
    {
        return ERROR_DESCRIPTIONS[(int)code];
    }
}