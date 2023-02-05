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

    // fmtチャンク内の、音声フォーマットのリニアPCMを示す値
    constexpr int16_t FORMAT_LINEAR_PCM = 1;

    // fmtチャンク内の、音声フォーマットのfloat32を示す値
    constexpr int16_t FORMAT_FLOAT32 = 3;

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

// loadMetaData関数内で、各パラメターを読み込む処理
#define LOAD_FORMAT_DATA(data)              \
    result = getWord(ifs, &data);           \
    if (!IsWavAgentActionSucceeded(result)) \
    {                                       \
        return result;                      \
    }

    // ifstreamからメタデータを読み込んで、各ポインタが指す先に格納する
    // ifsは、fmt識別子を読み終わった直後のバイトを指している事
    WavAgentErrorCode loadMetaData(
        std::ifstream &ifs,
        int *pChannelCount,
        int *pSamplingFreqHz,
        SampleFormatType *pSampleFormat)
    {
        auto result = WavAgentErrorCode::WAV_AGENT_SUCCESS;

        int32_t fmtChunkByteSize;
        LOAD_FORMAT_DATA(fmtChunkByteSize)

        int16_t soundFormat;
        LOAD_FORMAT_DATA(soundFormat)

        int16_t channelCount;
        LOAD_FORMAT_DATA(channelCount)

        int32_t samplingFreqHz;
        LOAD_FORMAT_DATA(samplingFreqHz)

        int32_t averageBytesPerSecond;
        LOAD_FORMAT_DATA(averageBytesPerSecond)

        int16_t blockSize;
        LOAD_FORMAT_DATA(blockSize)

        int16_t bitPerSample;
        LOAD_FORMAT_DATA(bitPerSample)

        // フォーマットチャンク全体のサイズから、読み込んだ各データのバイト数を引いた残りサイズ
        int remainingBytes = fmtChunkByteSize - 16;
        ifs.seekg(remainingBytes, ifs.cur); // 残りのデータは使用しないので、現在の位置からその分だけ読み込み位置をシークする
        if (ifs.fail())
        {
            return WavAgentErrorCode::WAV_AGENT_FILE_IS_BROKEN;
        }

        // 1サンプル当たりのビット数をSampleFormatTypeEnumに変換する
        SampleFormatType formatType;
        if (soundFormat == FORMAT_FLOAT32)
        {
            formatType = SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_32_BIT_FLOAT;
        }
        else if (soundFormat == FORMAT_LINEAR_PCM)
        {
            // リニアPCMの場合は1サンプル当たりのビット数でフォーマットが決まる
            switch (bitPerSample)
            {
            case 8:
                formatType = SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_UNSIGNED_8_BIT;
                break;
            case 16:
                formatType = SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_16_BIT;
                break;
            case 24:
                formatType = SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_24_BIT;
                break;
            case 32:
                formatType = SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_32_BIT;
                break;
            default:
                return WavAgentErrorCode::WAV_AGENT_NOT_SUPPORTED_FORMAT;
            }
        }
        else
        {
            return WavAgentErrorCode::WAV_AGENT_NOT_SUPPORTED_FORMAT;
        }

        *pChannelCount = channelCount;
        *pSamplingFreqHz = samplingFreqHz;
        *pSampleFormat = formatType;

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

        // fmtチャンクを読み込んでメタデータを読み込む
        result = findFmt(ifs);
        if (!IsWavAgentActionSucceeded(result))
        {
            return result;
        }

        int channelCount;
        int samplingFreqHz;
        SampleFormatType sampleFormat;
        result = loadMetaData(ifs, &channelCount, &samplingFreqHz, &sampleFormat);
        if (!IsWavAgentActionSucceeded(result))
        {
            return result;
        }

        return WavAgentErrorCode::WAV_AGENT_SUCCESS;
    }
}