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

    // ifstreamからT型のバイト分のデータを読み込んで、pRetValの先に代入する
    template <class T>
    WavAgentErrorCode getWord(
        std::ifstream &ifs,
        T *pRetVal)
    {
        ifs.read((char *)pRetVal, sizeof(T)); // readはchar*しか受け取れないので、char*にキャストする必要がある

        // readに何か失敗が起こった場合はfailがtrueになるので、正常に読み込むことが出来たか確認する
        if (ifs.fail())
        {
            return WavAgentErrorCode::WAV_AGENT_FILE_IS_BROKEN;
        }

        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }

    // ifsを読み込み、identifierが見つかればtrue、見つからなければfalseを返す
    // 関数から帰った後のifsは、identifierを読み終わった直後の状態になっている
    template <class T>
    bool findIdentifier(
        std::ifstream &ifs,
        T identifier)
    {
        T buffer{}; // ここにifsから読み込んだ最新のsizeof(T)バイトのデータを読み込む

        bool isIdentifierFound = false;
        while (!ifs.eof())
        {
            // bufferを1バイト分下にずらし、上のバイトにifsの先頭のバイトを読み込む
            // 上のバイトに最新の値を入れるのは、変数はメモリ上でリトルエンディアンになっているので、
            // ファイルの先頭にあるバイトがbufferの先頭のバイトに来るようにするため
            buffer >>= 8;
            ifs.read((char *)&buffer + (sizeof(T) - 1), 1);

            if (buffer == identifier)
            {
                isIdentifierFound = true;
                break;
            }
        }

        return isIdentifierFound;
    }

    // ifsが保持するストリームが正しいwavファイルの物かを調べる。
    WavAgentErrorCode checkWavFile(std::ifstream &ifs)
    {
        int32_t buffer32 = 0; // 32bit分のバッファ。ここにifsの先頭4バイトを貯めていく

        // RIFFFタグを探す
        if (!findIdentifier(ifs, RIFF))
        {
            return WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE;
        }

        // RFIFチャンクのフォーマットがWAVEである事を調べる。
        getWord(ifs, &buffer32); // RFIFチャンクの識別子の次の4バイトはチャンクサイズ
        getWord(ifs, &buffer32); // チャンクサイズの次の4バイトがフォーマット

        // RFIFチャンクは必ず8バイトのデータを含んでいるはずなので、
        // そうでなかったらファイルは破損している
        if (ifs.fail())
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

    // fmt識別子を探し、ifsをfmt識別子を読み終わった状態にする
    WavAgentErrorCode findFmt(std::ifstream &ifs)
    {
        // fmt識別子を探す。見つからなければ、それはwavファイルではない。
        if (!findIdentifier(ifs, FMT_))
        {
            return WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE;
        }
        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }

    // ifstreamからメタデータを読み込んで、pMetaDataの先にメタデータオブジェクトを代入する
    // ifsは、fmt識別子を読み終わった直後のバイトを指している事
    WavAgentErrorCode loadMetaData(
        std::ifstream &ifs,
        MetaData *pMetaData)
    {

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

        // fmtチャンクを読み込んでメタデータを作成する
        result = findFmt(ifs);
        if (!IsWavAgentActionSucceeded(result))
        {
            return result;
        }

        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }
}