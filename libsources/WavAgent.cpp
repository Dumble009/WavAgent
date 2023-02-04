#include "WavAgent.h"

namespace wavAgent
{
    /// RIFF識別子。リトルエンディアンなので、Rが下のバイトに来る
    constexpr int RIFF = 0x46464952;

    // WAVE識別子。リトルエンディアンなので、Wが下のバイトに来る
    constexpr int WAVE = 0x45564157;

    // fmt識別子。リトルエンディアンなので、半角スペースが下のバイトに来る
    constexpr int FMT_ = 0x20746D66;

    // サブチャンク識別子(data)。リトルエンディアンなのでdが下のバイトに来る
    constexpr int DATA = 0x61746164;

    WavAgentErrorCode Load(
        std::string_view path,
        SoundData *pSoundData)
    {

        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }
}