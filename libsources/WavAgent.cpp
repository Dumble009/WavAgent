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

    // ifstreamから4バイト分のデータを読み込んで、retValに代入する
    WavAgentErrorCode get32bitWord(
        std::ifstream &ifs,
        int32_t *retVal)
    {

        ifs.read((char *)retVal, 4); // readはchar*しか受け取れないので、キャストする必要がある

        // readで何か失敗が起こった場合はbadがtrueになるので、正常に読み込むことが出来たか確認する
        if (ifs.bad())
        {
            return WavAgentErrorCode::WAV_AGENT_FILE_IS_BROKEN;
        }

        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }

    // ifsが保持するストリームが正しいwavファイルの物かを調べる。
    WavAgentErrorCode checkWavFile(std::ifstream &ifs)
    {
        int32_t buffer32 = 0; // 32bit分のバッファ。ここにifsの先頭4バイトを貯めていく

        // RIFFFタグを探す
        bool isRFIFFound = false;
        while (!ifs.eof())
        {
            // buffer32を1バイト分下にずらし、上のバイトにifsの先頭のバイトを読み込む
            // 上のバイトを先頭にしているのは、ファイルの先頭のバイトがbuffer32の先頭のバイトに来るようにするため
            buffer32 >>= 8;
            ifs.read(((char *)&buffer32 + 3), 1);

            if (buffer32 == RIFF)
            {
                isRFIFFound = true;
                break;
            }
        }

        // RFIFチャンクを持っていなかったら、そのファイルはwavファイルではない
        if (!isRFIFFound)
        {
            return WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE;
        }

        // RFIFチャンクのフォーマットがWAVEである事を調べる。
        ifs.read((char *)&buffer32, 4); // RFIFチャンクの識別子の次の4バイトはチャンクサイズ
        ifs.read((char *)&buffer32, 4); // チャンクサイズの次の4バイトがフォーマット

        // RFIFチャンクは必ず8バイトのデータを含んでいるはずなので、
        // そうでなかったらファイルは破損している
        if (ifs.bad())
        {
            return WavAgentErrorCode::WAV_AGENT_FILE_IS_BROKEN;
        }

        // フォーマットがWAVEで無かったら、そのファイルはwavファイルではない。
        if (buffer32 != WAVE)
        {
            return WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE;
        }

        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }

    WavAgentErrorCode Load(
        std::string_view path,
        SoundData *pSoundData)
    {
        // ファイルを読み込み、正常に読めるかどうか確認
        std::ifstream ifs(path.data(), std::ios::in | std::ios::binary);
        if (ifs.fail())
        {
            return WavAgentErrorCode::WAV_AGENT_FILE_NOT_EXIST;
        }

        // 読み込んだファイルがwavファイルかどうかチェック
        auto result = checkWavFile(ifs);
        if (!IsWavAgentActionSucceeded(result))
        {
            return result;
        }

        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }
}