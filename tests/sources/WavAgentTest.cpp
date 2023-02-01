﻿#include <gtest/gtest.h>
#include "WavAgent.h"

// ファイルの読み込みが出来るかどうか
TEST(WavAgentLoadTest, BasicAssertions)
{
    // 存在するファイルを読み込む
    wavAgent::SoundData soundData = wavAgent::SoundData();
    auto ret = wavAgent::Load("data/WAV-8000Hz-2ch-16bit-800Hz_square.wav",
                              &soundData);
    ASSERT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS);

    // 存在しないファイルを読み込み、エラーが返ってくることを確かめる
    ret = wavAgent::Load("not-exist-file", &soundData);
    ASSERT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_FILE_NOT_EXIST);

    // 存在するファイルだが、wavファイルでないファイルを読み込ませる
    ret = wavAgent::Load("dummy1.txt", &soundData); // データを持っていない、拡張子がwavでないファイルを読み込もうとする
    ASSERT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE);

    ret = wavAgent::Load("dummy2.txt", &soundData); // データを持っている、拡張子がwavでないファイルを読み込もうとする
    ASSERT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE);

    ret = wavAgent::Load("dummy3.wav", &soundData); // データを持っていない、拡張子がwavだがwavファイルでないファイルを読み込もうとする
    ASSERT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE);

    ret = wavAgent::Load("dummy4.wav", &soundData); // データを持っている、拡張子がwavだがwavファイルでないファイルを読み込もうとする。
    ASSERT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE);
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

    ASSERT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS);

    // 各チャンネルの波形を独立に調べる
    T *pWave = nullptr;
    for (int i = 0; i < channelCount; i++)
    {
        ret = soundData.GetWave(&pWave, i);

        ASSERT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS);
        ASSERT_NE(pWave, nullptr); // pWaveには波形データを指す有効なポインタが格納される

        // サンプルの値を一つずつ調べていく。
        // 周期ごとに10個のサンプルが含まれ、前半5個が最大値、後半5個が最小値
        int sampleIdx = 0;
        for (int j = 0; j < waveCount; j++)
        {
            ASSERT_EQ(pWave[sampleIdx], maxValue);
            ASSERT_EQ(pWave[sampleIdx + 1], maxValue);
            ASSERT_EQ(pWave[sampleIdx + 2], maxValue);
            ASSERT_EQ(pWave[sampleIdx + 3], maxValue);
            ASSERT_EQ(pWave[sampleIdx + 4], maxValue);

            ASSERT_EQ(pWave[sampleIdx + 5], minValue);
            ASSERT_EQ(pWave[sampleIdx + 6], minValue);
            ASSERT_EQ(pWave[sampleIdx + 7], minValue);
            ASSERT_EQ(pWave[sampleIdx + 8], minValue);
            ASSERT_EQ(pWave[sampleIdx + 9], minValue);

            sampleIdx += 10;
        }
    }

    ASSERT_NE(pWave, nullptr) // 直前に読み込んだ波形を指している事を確認

    // 存在しないチャンネルの波形データを読み込もうとするとエラーが変えることを調べる。
    ret = soundData.GetWave(&pWave, channelCount + 1);

    ASSERT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_CHANNEL_OUT_OF_RANGE);
    ASSERT_EQ(pWave, nullptr); // 上でnullptrで無いことを確認したものがnullptrになっている事を確認
}

const std::string PATH_u8_1ch_4410 = "WAV-44100Hz-1ch-u8bit-4410Hz_square.wav";
const std::string PATH_16_2ch_800 = "WAV-8000Hz-2ch-16bit-800Hz_square.wav";
const std::string PATH_u8_1ch_38400 = "WAV-384000Hz-1ch-u8bit-38400Hz_square.wav";
const std::string PATH_16_1ch_4410 = "WAV-44100Hz-1ch-16bit-4410Hz_square.wav";
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

    // 不適切なフォーマットで読み込みをかけるとエラーコードとnullptrが返されることを調べる
    wavAgent::SampleSigned32bit dummyValue = 0;
    wavAgent::SampleSigned32bit *pWave = &dummyValue; // pWaveがnullptrに上書きされることを調べたいので、適当な有効なポインタを入れておく

    wavAgent::SoundData soundData{};
    auto ret = wavAgent::Load(PATH_u8_1ch_4410, &soundData);
    ASSERT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS);

    ret = soundData.GetWave(&pWave, 0);
    ASSERT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_INVALID_FORMAT);
    ASSERT_EQ(pWave, nullptr);

    // Load関数でロードされていないSoundDataに対してGetWave関数を実行したらエラーコードとnullptrが返されることを調べる。
    soundData = wavAgent::SoundData();
    pWave = &dummyValue; // pWaveがnullptrに上書きされることを調べるために、適当に有効なポインタを設定
    ret = soundData.GetWave(&pWave, 0);
    ASSERT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_SOUND_DATA_IS_NOT_INITIALIZED);
    ASSERT_EQ(pWave, nullptr);
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
    wavAgent::MetaData *pMetaData = nullptr;
    ret = soundData.GetMetaData(&pMetaData);
    ASSERT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS);
    ASSERT_NE(pMetaData, nullptr);

    // メタデータから各値を読み込み
    int actualChannelCount, actualSamplingFreqHz, actualSampleCount;
    wavAgent::SampleFormatType actualSampleFormatType;
    ASSERT_EQ(wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS,
              pMetaData->GetChannelCount(actualChannelCount));
    ASSERT_EQ(wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS,
              pMetaData->GetSamplingFreqHz(actualSamplingFreqHz));
    ASSERT_EQ(wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS,
              pMetaData->GetSampleFormat(actualSampleFormatType));
    ASSERT_EQ(wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS,
              pMetaData->GetSampleCount(actualSampleCount));

    // 比較
    ASSERT_EQ(expectedChannelCount, actualChannelCount);
    ASSERT_EQ(expectedSamplengFreqHz, actualSamplingFreqHz);
    ASSERT_EQ(expectedSampleFormat, actualSampleFormatType);
    ASSERT_EQ(expectedSampleCount, actualSampleCount);
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

    auto dummy = wavAgent::MetaData(0,
                                    0,
                                    wavAgent::SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_UNSIGNED_8_BIT,
                                    0);
    wavAgent::MetaData *pMetaData = &dummy; // nullptrで上書きされるか調べるために、適当に有効なポインタを設定しておく
    auto ret = soundData.GetMetaData(&pMetaData);

    ASSERT_EQ(ret, wavAgent::WavAgentErrorCode::WAV_AGENT_SOUND_DATA_IS_NOT_INITIALIZED);
    ASSERT_EQ(pMetaData, nullptr);
}