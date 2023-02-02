#include "WavAgentErrorCode.h"

namespace wavAgent
{
    std::ostream &operator<<(std::ostream &os, WavAgentErrorCode code)
    {
        return os;
    }

    std::string ConvertWavAgentErrorCodeToString(WavAgentErrorCode code)
    {
        return "";
    }

    std::string GetDescriptionOfErrorCode(WavAgentErrorCode code)
    {
        return "";
    }
}