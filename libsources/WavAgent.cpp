#include "WavAgent.h"
#include <fstream>

namespace wavAgent
{
    /// RIFF識別子。リトルエンディアンなので、Rが下のバイトに来る
    constexpr int32_t RIFF = 0x46464952;

    // WAVE識別子。リトルエンディアンなので、Wが下のバイトに来る
    constexpr int32_t WAVE = 0x45564157;

    // fmt識別子。リトルエンディアンなので、半角スペースが下のバイトに来る
    constexpr int32_t FMT_ = 0x20746D66;

    // サブチャンク識別子(data)。リトルエンディアンなのでdが下のバイトに来る
    constexpr int32_t DATA = 0x61746164;

    // ifstreamから4バイト分のデータを読み込んで、int32_tとして返す
    int32_t get32bitWord(
        std::ifstream &ifs)
    {
        int32_t retVal = 0;

        ifs.read((char *)&retVal, 4); // readはchar*しか受け取れないので、キャストする必要がある

        return retVal;
    }

    WavAgentErrorCode Load(
        std::string_view path,
        SoundData *pSoundData)
    {
        std::ifstream ifs(path.data(), std::ios::in | std::ios::binary);
        if (!ifs.is_open())
        {
            return WavAgentErrorCode::WAV_AGENT_FILE_NOT_EXIST;
        }

        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }
}