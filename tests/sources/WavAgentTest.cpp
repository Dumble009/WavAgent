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

    // 存在しないファイルを読み込み、エラーが返ってくることを確かめる
    ret = wavAgent::Load("not-exist-file", &soundData);
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_FILE_NOT_EXIST);

    // 存在するファイルだが、wavファイルでないファイルを読み込ませる
    ret = wavAgent::Load("dummy1.txt", &soundData); // データを持っていない、拡張子がwavでないファイルを読み込もうとする
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE);

    ret = wavAgent::Load("dummy2.txt", &soundData); // データを持っている、拡張子がwavでないファイルを読み込もうとする
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE);

    ret = wavAgent::Load("dummy3.wav", &soundData); // データを持っていない、拡張子がwavだがwavファイルでないファイルを読み込もうとする
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE);

    ret = wavAgent::Load("dummy4.wav", &soundData); // データを持っている、拡張子がwavだがwavファイルでないファイルを読み込もうとする。
    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE);
}

template <class T>
void LoadAndCheckWaveData(const std::string &path,
                          T maxValue,
                          T minValue,
                          int channelCount,
                          int waveCount)
{
    wavAgent::SoundData soundData = wavAgent::SoundData();
    auto ret = wavAgent::Load(path, &soundData);

    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS);

    // 各チャンネルの波形を独立に調べる
    T *pWave = nullptr;
    for (int i = 0; i < channelCount; i++)
    {
        ret = soundData.GetWave(&pWave, i);

        EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS);
        EXPECT_NE(pWave, nullptr); // pWaveには波形データを指す有効なポインタが格納される

        // サンプルの値を一つずつ調べていく。
        // 周期ごとに10個のサンプルが含まれ、前半5個が最大値、後半5個が最小値
        int sampleIdx = 0;
        for (int j = 0; j < waveCount; j++)
        {
            EXPECT_EQ(pWave[sampleIdx], maxValue);
            EXPECT_EQ(pWave[sampleIdx + 1], maxValue);
            EXPECT_EQ(pWave[sampleIdx + 2], maxValue);
            EXPECT_EQ(pWave[sampleIdx + 3], maxValue);
            EXPECT_EQ(pWave[sampleIdx + 4], maxValue);

            EXPECT_EQ(pWave[sampleIdx + 5], minValue);
            EXPECT_EQ(pWave[sampleIdx + 6], minValue);
            EXPECT_EQ(pWave[sampleIdx + 7], minValue);
            EXPECT_EQ(pWave[sampleIdx + 8], minValue);
            EXPECT_EQ(pWave[sampleIdx + 9], minValue);

            sampleIdx += 10;
        }
    }

    EXPECT_NE(pWave, nullptr) // 直前に読み込んだ波形を指している事を確認

    // 存在しないチャンネルの波形データを読み込もうとするとエラーが変えることを調べる。
    ret = soundData.GetWave(&pWave, channelCount + 1);

    EXPECT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_CHANNEL_OUT_OF_RANGE);
    EXPECT_EQ(pWave, nullptr); // 上でnullptrで無いことを確認したものがnullptrになっている事を確認
}

const std::string PATH_u8_1ch_4410 = "WAV-44100Hz-1ch-u8bit-4410Hz_square.wav";
const std::string PATH_16_2ch_800 = "WAV-8000Hz-2ch-16bit-800Hz_square.wav";
const std::string PATH_u8_1ch_38400 = "WAV-384000Hz-1ch-u8bit-38400Hz_square.wav";
const std::string PATH_16_1ch_1600 = "WAV-44100Hz-1ch-16bit-4410Hz_square.wav";
const std::string PATH_24_1ch_1600 = "WAV-16000Hz-1ch-24bit-1600Hz_square.wav";
const std::string PATH_32_1ch_1600 = "WAV-16000Hz-1ch-32bit-1600Hz_square.wav";
const std::string PATH_f32_1ch_1600 = "WAV-16000Hz-1ch-f32bit-16000Hz_square.wav";

// 読み込んだ波形データが正しいかどうか
TEST(WavAgentWavDataTest, BasicAssertions)
{
    LoadAndCheckWaveData(PATH_u8_1ch_4410,
                         (wavAgent::SampleUnsigned8bit)0xFF,
                         (wavAgent::SampleUnsigned8bit)0x00,
                         1,
                         4410);

    LoadAndCheckWaveData(PATH_16_2ch_800,
                         (wavAgent::SampleSigned16bit)0x7FFF,
                         (wavAgent::SampleSigned16bit)0x8000,
                         2,
                         800);

    LoadAndCheckWaveData(PATH_u8_1ch_38400,
                         (wavAgent::SampleUnsigned8bit)0xFF,
                         (wavAgent::SampleUnsigned8bit)0x00,
                         1,
                         38400);

    LoadAndCheckWaveData(PATH_24_1ch_1600,
                         (wavAgent::SampleSigned24bit)0x7FFFFF,
                         (wavAgent::SampleSigned24bit)0x800000,
                         1,
                         1600);

    LoadAndCheckWaveData(PATH_32_1ch_1600,
                         (wavAgent::SampleSigned32bit)0x7FFFFFFF,
                         (wavAgent::SampleSigned32bit)0x80000000,
                         1,
                         1600);

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
                         1600);
}