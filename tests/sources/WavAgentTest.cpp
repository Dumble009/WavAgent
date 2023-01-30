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

    for (int i = 0; i < channelCount; i++)
    {
        }
}

// 読み込んだ波形データが正しいかどうか
TEST(WavAgentWavDataTest, BasicAssertions)
{
}