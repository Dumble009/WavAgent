#pragma once
#include <cstdint>

// サンプルのデータ形式を表す型を定義する。

namespace wavAgent
{
    // 8bit符号なし整数
    using SampleUnsigned8bit = uint8_t;

    // 16bit符号あり整数
    using SampleSigned16bit = int16_t;

    // 32bit符号あり整数
    using SampleSigned32bit = int32_t;

    // 32bit符号あり浮動小数
    using SampleSigned32bitFloat = float;

    // 24bit符号あり整数
    struct SampleSigned24bit
    {
    private:
        uint8_t data[3]; // データの実体
    public:
        SampleSigned24bit();
        SampleSigned24bit(int i);     // int型からSampleSigned24bitへのキャスト
        SampleSigned24bit(uint8_t c); // char型からSampleSigned24bitへのキャスト

        // 単項符号演算子
        SampleSigned24bit operator-() const; // 元の符号に寄らず符号を判定
        SampleSigned24bit operator+() const; // 元の符号に寄らず符号をそのままで返す

        SampleSigned24bit operator+(SampleSigned24bit other) const;
        SampleSigned24bit operator+(int i) const;
        SampleSigned24bit operator-(SampleSigned24bit other) const;
        SampleSigned24bit operator-(int i) const;
        SampleSigned24bit operator*(SampleSigned24bit other) const;
        SampleSigned24bit operator*(int i) const;

        bool operator<(SampleSigned24bit other) const;
        bool operator<(int i) const;

        bool operator<=(SampleSigned24bit other) const;
        bool operator<=(int i) const;

        bool operator>(SampleSigned24bit other) const;
        bool operator>(int i) const;

        bool operator>=(SampleSigned24bit other) const;
        bool operator>=(int i) const;

        bool operator==(SampleSigned24bit other) const;
        bool operator==(int i) const;

        bool operator!=(SampleSigned24bit other) const;
        bool operator!=(int i) const;

        SampleSigned24bit operator<<(SampleSigned24bit other) const;
        SampleSigned24bit operator<<(int other) const;
        SampleSigned24bit operator>>(SampleSigned24bit other) const;
        SampleSigned24bit operator>>(int other) const;
        SampleSigned24bit operator~() const;
        SampleSigned24bit operator|(SampleSigned24bit other) const;
        SampleSigned24bit operator|(int other) const;
        SampleSigned24bit operator&(SampleSigned24bit other) const;
        SampleSigned24bit operator&(int other) const;
        SampleSigned24bit operator^(SampleSigned24bit other) const;
        SampleSigned24bit operator^(int other) const;

        SampleSigned24bit operator+=(SampleSigned24bit other);
        SampleSigned24bit operator+=(int other);
        SampleSigned24bit operator-=(SampleSigned24bit other);
        SampleSigned24bit operator-=(int other);

        SampleSigned24bit operator=(int i);
        SampleSigned24bit operator=(unsigned char c);

        operator int() const;
    };

    // int型が左辺に来る演算子
    int operator+(int i, SampleSigned24bit v24);
    int operator-(int i, SampleSigned24bit v24);
    int operator*(int i, SampleSigned24bit v24);
    bool operator<(int i, SampleSigned24bit v24);
    bool operator<=(int i, SampleSigned24bit v24);
    bool operator>(int i, SampleSigned24bit v24);
    bool operator>=(int i, SampleSigned24bit v24);
    bool operator==(int i, SampleSigned24bit v24);
    bool operator!=(int i, SampleSigned24bit v24);
}

// 数値をSampleSigned24bitとして扱うことを宣言するリテラル
wavAgent::SampleSigned24bit operator"" _24bit(unsigned long long ull);