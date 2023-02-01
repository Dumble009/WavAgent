#include <gtest/gtest.h>

#include "WavAgentErrorCode.h"

// WavAgentErrorCodeをint型とみなした際の値が適切かのテスト
TEST(WavAgentErrorCodeValueTest, BasicAssertions)
{
    // SUCCESSは0と等価
    EXPECT_EQ((int)wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS, 0);

    // SUCCESS以外の値は0以上の値
    EXPECT_GT((int)wavAgent::WavAgentErrorCode::WAV_AGENT_FILE_NOT_EXIST, 0);
    EXPECT_GT((int)wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE, 0);
    EXPECT_GT((int)wavAgent::WavAgentErrorCode::WAV_AGENT_CHANNEL_OUT_OF_RANGE, 0);
    EXPECT_GT((int)wavAgent::WavAgentErrorCode::WAV_AGENT_INVALID_FORMAT, 0);
    EXPECT_GT((int)wavAgent::WavAgentErrorCode::WAV_AGENT_SOUND_DATA_IS_NOT_INITIALIZED, 0);
}

// WavAgentErrorCodeを文字へ変換する処理を正しく行えるかどうかのテスト
TEST(WavAgentErrorCodeToStringTest, BasicAssertions)
{
    // 仕様と合っているかどうかなので、値はWavAgentErrorCodeのコードから持ってきたりせずに、仕様書の値をハードコードする
    EXPECT_EQ(wavAgent::ConvertWavAgentErrorCodeToString(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS),
              "WAV_AGENT_SUCCESS");

    EXPECT_EQ(wavAgent::ConvertWavAgentErrorCodeToString(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_FILE_NOT_EXIST),
              "WAV_AGENT_FILE_NOT_EXIST");

    EXPECT_EQ(wavAgent::ConvertWavAgentErrorCodeToString(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE),
              "WAV_AGENT_NOT_WAV_FILE");

    EXPECT_EQ(wavAgent::ConvertWavAgentErrorCodeToString(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_CHANNEL_OUT_OF_RANGE),
              "WAV_AGENT_CHANNEL_OUT_OF_RANGE");

    EXPECT_EQ(wavAgent::ConvertWavAgentErrorCodeToString(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_INVALID_FORMAT),
              "WAV_AGENT_INVALID_FORMAT");

    EXPECT_EQ(wavAgent::ConvertWavAgentErrorCodeToString(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_SOUND_DATA_IS_NOT_INITIALIZED),
              "WAV_AGENT_SOUND_DATA_IS_NOT_INITIALIZED");
}

// GetDescriptionOfErrorCode関数でエラーコードの説明を得られるかどうかのテスト
TEST(WavAgentGetDescriptionOfErrorCodeTest, BasicAssertions)
{
    EXPECT_EQ(wavAgent::GetDescriptionOfErrorCode(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS),
              "WavAgent : Operation successfully completed.");

    EXPECT_EQ(wavAgent::GetDescriptionOfErrorCode(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_FILE_NOT_EXIST),
              "WavAgent : Loading a file failed. A file does not exist.");

    EXPECT_EQ(wavAgent::GetDescriptionOfErrorCode(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE),
              "WavAgent : Loading a file failed. A file is not a wav file.");

    EXPECT_EQ(wavAgent::GetDescriptionOfErrorCode(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_CHANNEL_OUT_OF_RANGE),
              "WavAgent : Invalid channel index was passed. Please check a channel count in a meta data.");

    EXPECT_EQ(wavAgent::GetDescriptionOfErrorCode(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_INVALID_FORMAT),
              "WavAgent : Claimed format does not match with a format of data. Please check a sample format in a meta data.");

    EXPECT_EQ(wavAgent::GetDescriptionOfErrorCode(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_SOUND_DATA_IS_NOT_INITIALIZED),
              "WavAgent : A sound data was not initialized. Please initialize it using Load function before accessing its members.");
}