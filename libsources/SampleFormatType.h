#pragma once

namespace wavAgent
{
    // サンプルのデータ形式。ビット深度と、符号の有無等
    enum class SampleFormatType : int
    {
        WAV_AGENT_SAMPLE_STRUCTURE_UNSIGNED_8_BIT = 0,
        WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_16_BIT = 1,
        WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_24_BIT = 2,
        WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_32_BIT = 3,
        WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_32_BIT_FLOAT = 4,
    };
}