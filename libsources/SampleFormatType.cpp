#include "SampleFormatType.h"

namespace wavAgent
{
    int GetByteSizeOfFormat(SampleFormatType formatType)
    {
        switch (formatType)
        {
        case SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_UNSIGNED_8_BIT:
            return 1;

        case SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_16_BIT:
            return 2;

        case SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_24_BIT:
            return 3;

        case SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_32_BIT:
        case SampleFormatType::WAV_AGENT_SAMPLE_STRUCTURE_SIGNED_32_BIT_FLOAT:
            return 4;

        default:
            return 0;
        }
    }
}