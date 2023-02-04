#include <gtest/gtest.h>
#include <sstream>
#include <string>

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
    EXPECT_GT((int)wavAgent::WavAgentErrorCode::WAV_AGENT_FILE_IS_BROKEN, 0);
    EXPECT_GT((int)wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_SUPPORTED_FORMAT, 0);
}

const std::string SUCCESS_STRING = "WAV_AGENT_SUCCESS";
const std::string FILE_NOT_EXIST_STRING = "WAV_AGENT_FILE_NOT_EXIST";
const std::string NOT_WAV_FILE_STRING = "WAV_AGENT_NOT_WAV_FILE";
const std::string CHANNEL_OUT_OF_RANGE_STRING = "WAV_AGENT_CHANNEL_OUT_OF_RANGE";
const std::string INVALID_FORMAT_STRING = "WAV_AGENT_INVALID_FORMAT";
const std::string SOUND_DATA_IS_NOT_INITIALIZED_STRING = "WAV_AGENT_SOUND_DATA_IS_NOT_INITIALIZED";
const std::string FILE_IS_BROKEN_STRING = "WAV_AGENT_FILE_IS_BROKEN";
const std::string NOT_SUPPORTED_FORMAT_STRING = "WAV_AGENT_NOT_SUPPORTED_FORMAT";

// WavAgentErrorCodeを文字へ変換する処理を正しく行えるかどうかのテスト
TEST(WavAgentErrorCodeToStringTest, BasicAssertions)
{
    // 仕様と合っているかどうかなので、値はWavAgentErrorCodeのコードから持ってきたりせずに、仕様書の値をハードコードする
    EXPECT_EQ(wavAgent::ConvertWavAgentErrorCodeToString(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS),
              SUCCESS_STRING);

    EXPECT_EQ(wavAgent::ConvertWavAgentErrorCodeToString(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_FILE_NOT_EXIST),
              FILE_NOT_EXIST_STRING);

    EXPECT_EQ(wavAgent::ConvertWavAgentErrorCodeToString(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE),
              NOT_WAV_FILE_STRING);

    EXPECT_EQ(wavAgent::ConvertWavAgentErrorCodeToString(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_CHANNEL_OUT_OF_RANGE),
              CHANNEL_OUT_OF_RANGE_STRING);

    EXPECT_EQ(wavAgent::ConvertWavAgentErrorCodeToString(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_INVALID_FORMAT),
              INVALID_FORMAT_STRING);

    EXPECT_EQ(wavAgent::ConvertWavAgentErrorCodeToString(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_SOUND_DATA_IS_NOT_INITIALIZED),
              SOUND_DATA_IS_NOT_INITIALIZED_STRING);

    EXPECT_EQ(wavAgent::ConvertWavAgentErrorCodeToString(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_FILE_IS_BROKEN),
              FILE_IS_BROKEN_STRING);

    EXPECT_EQ(wavAgent::ConvertWavAgentErrorCodeToString(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_SUPPORTED_FORMAT),
              NOT_SUPPORTED_FORMAT_STRING);
}

// WavAgentCodeのストリーム挿入子が正常に動作するか確認する処理
void assertStreamString(
    wavAgent::WavAgentErrorCode code,
    const std::string &expectedString)
{
    std::stringstream ss;
    ss << code;

    EXPECT_EQ(ss.str(), expectedString);
}

// WavAgentCodeのストリーム挿入子が正しく動作するかのテスト
TEST(WavAgentErrorCodeToStreamTest, BasicAssertions)
{
    assertStreamString(
        wavAgent::WavAgentErrorCode::WAV_AGENT_SUCCESS,
        SUCCESS_STRING);

    assertStreamString(
        wavAgent::WavAgentErrorCode::WAV_AGENT_FILE_NOT_EXIST,
        FILE_NOT_EXIST_STRING);

    assertStreamString(
        wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_WAV_FILE,
        NOT_WAV_FILE_STRING);

    assertStreamString(
        wavAgent::WavAgentErrorCode::WAV_AGENT_CHANNEL_OUT_OF_RANGE,
        CHANNEL_OUT_OF_RANGE_STRING);

    assertStreamString(
        wavAgent::WavAgentErrorCode::WAV_AGENT_INVALID_FORMAT,
        INVALID_FORMAT_STRING);

    assertStreamString(
        wavAgent::WavAgentErrorCode::WAV_AGENT_SOUND_DATA_IS_NOT_INITIALIZED,
        SOUND_DATA_IS_NOT_INITIALIZED_STRING);

    assertStreamString(
        wavAgent::WavAgentErrorCode::WAV_AGENT_FILE_IS_BROKEN,
        FILE_IS_BROKEN_STRING);

    assertStreamString(
        wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_SUPPORTED_FORMAT,
        NOT_SUPPORTED_FORMAT_STRING);
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

    EXPECT_EQ(wavAgent::GetDescriptionOfErrorCode(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_FILE_IS_BROKEN),
              "WavAgent : Passed wav file is broken. Metadata or payload has invalid values.");

    EXPECT_EQ(wavAgent::GetDescriptionOfErrorCode(
                  wavAgent::WavAgentErrorCode::WAV_AGENT_NOT_SUPPORTED_FORMAT),
              "WavAgent : Passed wav file has a format which is not supported by this library.");
}