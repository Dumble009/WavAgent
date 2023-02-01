#pragma once

// サンプルのデータ形式を表す型を定義する。

namespace wavAgent
{
    // 8bit符号なし整数
    using SampleUnsigned8bit = unsigned char;

    // 16bit符号あり整数
    using SampleSigned16bit = signed short;

    // 32bit符号あり整数
    using SampleSigned32bit = int;

    // 32bit符号あり浮動小数
    using SampleSigned32bitFloat = float;

    // 24bit符号あり整数
    struct SampleSigned24bit
    {
    private:
        char data[3]; // データの実体

    public:
        SampleSigned24bit(int i); // int型からSampleSigned24bitへのキャスト

        SampleSigned24bit operator+(SampleSigned24bit other);
        SampleSigned24bit operator-(SampleSigned24bit other);

        bool operator<(SampleSigned24bit other);
        bool operator>(SampleSigned24bit other);
        bool operator==(SampleSigned24bit other);
        bool operator==(int other);
        bool operator!=(SampleSigned24bit other);

        SampleSigned24bit operator<<(SampleSigned24bit other);
        SampleSigned24bit operator<<(int other);
        SampleSigned24bit operator>>(SampleSigned24bit other);
        SampleSigned24bit operator>>(int other);
        SampleSigned24bit operator~();
        SampleSigned24bit operator|(SampleSigned24bit other);
        SampleSigned24bit operator|(int other);
        SampleSigned24bit operator&(SampleSigned24bit other);
        SampleSigned24bit operator&(int other);
        SampleSigned24bit operator^(SampleSigned24bit other);
        SampleSigned24bit operator^(int other);

        SampleSigned24bit operator=(int other);
        SampleSigned24bit operator+=(int other);
        SampleSigned24bit operator+=(SampleSigned24bit other);
        SampleSigned24bit operator-=(int other);
        SampleSigned24bit operator-=(SampleSigned24bit other);

        SampleSigned24bit operator=(int other);
        SampleSigned24bit operator=(char other);

        operator int();
    };
}