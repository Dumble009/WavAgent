#include <gtest/gtest.h>
#include "WavAgent.h"

// ファイルの読み込みが出来るかどうか
TEST(WavAgentLoadTest, BasicAssertions)
{
    // 存在するファイルを読み込む
    wavAgent::SoundData soundData = wavAgent::SoundData();
    auto ret = wavAgent::Load("data/WAV-8000Hz-2ch-16bit-800Hz_square.wav",
                              &soundData);
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS);

    // float32のファイルは他とは違うフォーマットタイプを持っているが、正常に読み込めることを確認
    ret = wavAgent::Load("data/WAV-16000Hz-1ch-f32bit-16000Hz_square.wav",
                         &soundData);
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS);

    // 存在しないファイルを読み込み、エラーが返ってくることを確かめる
    ret = wavAgent::Load("not-exist-file", &soundData);
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_FILE_NOT_EXIST);

    // 存在するファイルだが、wavファイルでないファイルを読み込ませる
    // データを持っていない、拡張子がwavでないファイルを読み込もうとする
    ret = wavAgent::Load("data/dummy1.txt", &soundData);
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE);

    // データを持っている、拡張子がwavでないファイルを読み込もうとする
    ret = wavAgent::Load("data/dummy2.txt", &soundData);
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE);

    // データを持っていない、拡張子がwavだがwavファイルでないファイルを読み込もうとする
    ret = wavAgent::Load("data/dummy3.wav", &soundData);
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE);

    // データを持っている、拡張子がwavだがwavファイルでないファイルを読み込もうとする。
    ret = wavAgent::Load("data/dummy4.wav", &soundData);
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE);

    // RIFFチャンクのWAVEフォーマットが他の値になっているファイルを読み込もうとする
    // この場合は破損ではなく、wavファイルではないという判定を行う
    ret = wavAgent::Load("data/broken_invalid_WAVE_token.wav", &soundData);
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE);

    // fmt識別子が存在しないファイルを読み込もうとする。
    // この場合は破損ではなく、wavファイルではないという判定を行う
    ret = wavAgent::Load("data/broken_no_fmt_identifier.wav", &soundData);
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE);

    // data識別子が存在しないファイルを読み込もうとする。
    // この場合は破損ではなく、wavファイルではないという判定を行う
    ret = wavAgent::Load("data/broken_no_data_identifier.wav", &soundData);
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE);

    // 1サンプル当たりのビット数が不正な値のファイルを読み込もうとする。
    // この場合は、対応していないフォーマットであると判定する
    ret = wavAgent::Load("data/broken_invalid_bit_per_sample.wav", &soundData);
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_SUPPORTED_FORMAT);

    // 対応していないフォーマット(u-Lawやa-Law)などのファイルを読み込ませる。
    // この場合は、対応していないフォーマットであると判定する
    ret = wavAgent::Load("data/broken_u_law.wav", &soundData);
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_SUPPORTED_FORMAT);
    ret = wavAgent::Load("data/broken_a_law.wav", &soundData);
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_SUPPORTED_FORMAT);

    // 波形データのサイズが間違っているファイルを読み込もうとする
    // この場合は破損しているという判定が返って来ればOK
    ret = wavAgent::Load("data/broken_tail_wrond_data_size_larger.wav", &soundData);
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_FILE_IS_BROKEN);
    ret = wavAgent::Load("data/broken_tail_wrong_data_size_not_multiple.wav", &soundData);
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_FILE_IS_BROKEN);
}

template <class T>
void LoadAndCheckWaveData(const std::string &path,
                          T maxValue,
                          T minValue,
                          int channelCount,
                          int waveCount,
                          int byteSize)
{
    wavAgent::SoundData soundData = wavAgent::SoundData();
    auto ret = wavAgent::Load(path, &soundData);

    // ここでSUCCESSが返ってこなかったら後の操作は出来ないのでASSERTを使用する
    ASSERT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS);

    // 各チャンネルの波形を独立に調べる
    T *pWave = nullptr;
    for (int i = 0; i < channelCount; i++)
    {
        ret = soundData.GetWave(&pWave, i);

        ASSERT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS);
        // pWaveには波形データを指す有効なポインタが格納される
        ASSERT_TRUE(pWave != nullptr);

        // バイト数のチェック
        size_t actualByteSize = 0;
        ret = soundData.GetWaveSizeInByte(&actualByteSize, i);

        ASSERT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS);
        ASSERT_EQ(byteSize, actualByteSize);

        // サンプルの値を一つずつ調べていく。
        // 周期ごとに10個のサンプルが含まれ、前半5個が最大値、後半5個が最小値
        int sampleIdx = 0;
        for (int j = 0; j < waveCount; j++)
        {
            ASSERT_EQ(pWave[sampleIdx], maxValue) << ":" << path << ": channel = " << i << " : sampleIdx = " << sampleIdx << std::endl;
            ASSERT_EQ(pWave[sampleIdx + 1], maxValue) << ":" << path << ": channel = " << i << " : sampleIdx = " << sampleIdx << std::endl;
            ASSERT_EQ(pWave[sampleIdx + 2], maxValue) << ":" << path << ": channel = " << i << " : sampleIdx = " << sampleIdx << std::endl;
            ASSERT_EQ(pWave[sampleIdx + 3], maxValue) << ":" << path << ": channel = " << i << " : sampleIdx = " << sampleIdx << std::endl;
            ASSERT_EQ(pWave[sampleIdx + 4], maxValue) << ":" << path << ": channel = " << i << " : sampleIdx = " << sampleIdx << std::endl;

            ASSERT_EQ(pWave[sampleIdx + 5], minValue) << ":" << path << ": channel = " << i << " : sampleIdx = " << sampleIdx << std::endl;
            ASSERT_EQ(pWave[sampleIdx + 6], minValue) << ":" << path << ": channel = " << i << " : sampleIdx = " << sampleIdx << std::endl;
            ASSERT_EQ(pWave[sampleIdx + 7], minValue) << ":" << path << ": channel = " << i << " : sampleIdx = " << sampleIdx << std::endl;
            ASSERT_EQ(pWave[sampleIdx + 8], minValue) << ":" << path << ": channel = " << i << " : sampleIdx = " << sampleIdx << std::endl;
            ASSERT_EQ(pWave[sampleIdx + 9], minValue) << ":" << path << ": channel = " << i << " : sampleIdx = " << sampleIdx << std::endl;

            sampleIdx += 10;
        }
    }

    ASSERT_NE(pWave, nullptr); // 直前に読み込んだ波形を指している事を確認

    // 存在しないチャンネルの波形データを読み込もうとするとエラーが変えることを調べる。
    ret = soundData.GetWave(&pWave, channelCount + 1);

    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_CHANNEL_OUT_OF_RANGE);
}

const std::string PATH_u8_1ch_4410 = "data/WAV-44100Hz-1ch-u8bit-4410Hz_square.wav";
const std::string PATH_16_2ch_800 = "data/WAV-8000Hz-2ch-16bit-800Hz_square.wav";
const std::string PATH_u8_1ch_38400 = "data/WAV-384000Hz-1ch-u8bit-38400Hz_square.wav";
const std::string PATH_16_1ch_4410 = "data/WAV-44100Hz-1ch-16bit-4410Hz_square.txt";
const std::string PATH_24_1ch_1600 = "data/WAV-16000Hz-1ch-24bit-1600Hz_square.wav";
const std::string PATH_32_1ch_1600 = "data/WAV-16000Hz-1ch-32bit-1600Hz_square.wav";
const std::string PATH_f32_1ch_1600 = "data/WAV-16000Hz-1ch-f32bit-16000Hz_square.wav";

// 読み込んだ波形データが正しいかどうか
TEST(WavAgentWavDataTest, BasicAssertions)
{
    LoadAndCheckWaveData(PATH_u8_1ch_4410,
                         (wavAgent::SampleUnsigned8bit)0xFF,
                         (wavAgent::SampleUnsigned8bit)0x00,
                         1,
                         4410,
                         4410);

    LoadAndCheckWaveData(PATH_16_2ch_800,
                         (wavAgent::SampleSigned16bit)0x7FFF,
                         (wavAgent::SampleSigned16bit)0x8000,
                         2,
                         800,
                         1600);

    LoadAndCheckWaveData(PATH_u8_1ch_38400,
                         (wavAgent::SampleUnsigned8bit)0xC0,
                         (wavAgent::SampleUnsigned8bit)0x40,
                         1,
                         38400,
                         38400);

    // SampleSigned24bitでは、int型からの変換の際に、24bit目を無視し、32bit目を符号ビットとして認識する
    // そのため、0x800000は、24bit目が無視され0になってしまう。
    // なので、0の24bit目を1にする操作を行うことで最小値を作る
    wavAgent::SampleSigned24bit maxValue24 = (wavAgent::SampleSigned24bit)0x7FFFFF;
    wavAgent::SampleSigned24bit minValue24 = 0;
    minValue24 = minValue24 | (1 << 23); // 符号ビットを1にする

    LoadAndCheckWaveData(PATH_24_1ch_1600,
                         maxValue24,
                         minValue24,
                         1,
                         1600,
                         4800);

    LoadAndCheckWaveData(PATH_32_1ch_1600,
                         (wavAgent::SampleSigned32bit)0x7FFFFFFF,
                         (wavAgent::SampleSigned32bit)0x80000000,
                         1,
                         1600,
                         6400);

    int maxValueInt = 0x3F800000; // floatの最大値の16進数表記
    int minValueInt = 0xBF800000; // floatの最小値の16進数表記

    // 浮動小数点に16進数表記をそのまま代入する事は出来ないので、
    // 一度intに代入してから、ビット配列はそのままにfloatとして読み替える
    wavAgent::SampleSigned32bitFloat maxValueFloat = *((wavAgent::SampleSigned32bitFloat *)&maxValueInt);
    wavAgent::SampleSigned32bitFloat minValueFloat = *((wavAgent::SampleSigned32bitFloat *)&minValueInt);

    LoadAndCheckWaveData(PATH_f32_1ch_1600,
                         maxValueFloat,
                         minValueFloat,
                         1,
                         1600,
                         6400);

    // 不適切なフォーマットで読み込みをかけるとエラーコードが返されることを調べる
    wavAgent::SampleSigned32bit dummyValue = 0;
    wavAgent::SampleSigned32bit *pWave = &dummyValue;

    wavAgent::SoundData soundData{};
    auto ret = wavAgent::Load(PATH_u8_1ch_4410, &soundData);
    ASSERT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS);

    ret = soundData.GetWave(&pWave, 0);
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_INVALID_FORMAT);

    // Load関数でロードされていないSoundDataに対してGetWave関数を実行したらエラーコードが返されることを調べる。
    soundData = wavAgent::SoundData();
    pWave = &dummyValue;
    ret = soundData.GetWave(&pWave, 0);
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_SOUND_DATA_IS_NOT_INITIALIZED);
}

void LoadAndCheckMetaData(const std::string &path,
                          int expectedChannelCount,
                          int expectedSamplengFreqHz,
                          wavAgent::SampleFormatType expectedSampleFormat,
                          int expectedSampleCount)
{
    // サウンドデータの読み込み
    wavAgent::SoundData soundData{};
    auto ret = wavAgent::Load(path, &soundData);
    ASSERT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS);

    // サウンドデータからメタデータを読み込み
    wavAgent::MetaData metaData{};
    ret = soundData.GetMetaData(&metaData);
    ASSERT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS);

    // メタデータから各値を読み込み
    int actualChannelCount, actualSamplingFreqHz, actualSampleCount;
    wavAgent::SampleFormatType actualSampleFormatType;
    EXPECT_EQ(wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS,
              metaData.GetChannelCount(actualChannelCount));
    EXPECT_EQ(wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS,
              metaData.GetSamplingFreqHz(actualSamplingFreqHz));
    EXPECT_EQ(wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS,
              metaData.GetSampleFormat(actualSampleFormatType));
    EXPECT_EQ(wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS,
              metaData.GetSampleCount(actualSampleCount));

    // 比較
    EXPECT_EQ(expectedChannelCount, actualChannelCount);
    EXPECT_EQ(expectedSamplengFreqHz, actualSamplingFreqHz);
    EXPECT_EQ(expectedSampleFormat, actualSampleFormatType);
    EXPECT_EQ(expectedSampleCount, actualSampleCount);
}

// 読み込んだメタデータが正しいか調べる
TEST(LoadMetaDataTest, BasicAssertions)
{
    LoadAndCheckMetaData(PATH_u8_1ch_4410,
                         1,
                         44100,
                         wavAgent::SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_UNSIGNED_8_BIT,
                         44100);

    LoadAndCheckMetaData(PATH_16_2ch_800,
                         2,
                         8000,
                         wavAgent::SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_16_BIT,
                         8000);

    LoadAndCheckMetaData(PATH_u8_1ch_38400,
                         1,
                         384000,
                         wavAgent::SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_UNSIGNED_8_BIT,
                         384000);

    LoadAndCheckMetaData(PATH_16_1ch_4410,
                         1,
                         44100,
                         wavAgent::SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_16_BIT,
                         44100);

    LoadAndCheckMetaData(PATH_24_1ch_1600,
                         1,
                         16000,
                         wavAgent::SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_24_BIT,
                         16000);

    LoadAndCheckMetaData(PATH_32_1ch_1600,
                         1,
                         16000,
                         wavAgent::SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_32_BIT,
                         16000);

    LoadAndCheckMetaData(PATH_f32_1ch_1600,
                         1,
                         16000,
                         wavAgent::SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_32_BIT_FLOAT,
                         16000);

    // 初期化できていないSoundDataからメタデータに読み込みをかけた時に
    // エラーコードを返ってくる事を調べる
    wavAgent::SoundData soundData{};
    wavAgent::MetaData metaData{};
    auto ret = soundData.GetMetaData(&metaData);

    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_SOUND_DATA_IS_NOT_INITIALIZED);
}