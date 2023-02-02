#include "SampleDataTypeDefinitions.h"

namespace wavAgent
{
    // int型の変数iのidxバイト目の値を返す。idxは0-indexed
    inline char getOneByteInInteger(int i, int idx)
    {
        return ((unsigned char *)&i)[idx];
    }

    // dataはcharの要素数3の配列の先頭ポインタ。
    // それを24bitの数値と見なし、-1をかけたのと同じ操作をする。
    inline void invert(unsigned char *data)
    {
        // 全部のビットを反転した後1加える
        for (int i = 0; i < 3; i++)
        {
            data[i] ^= (char)0xFF;
        }

        for (int i = 0; i < 3; i++)
        {
            data[i]++;
            if (data[i] != 0)
            {
                // 1足して0にならなかったという事はオーバーフローしなかったので、ここで処理を打ち切る
                break;
            }
        }
    }

    SampleSigned24bit::SampleSigned24bit()
    {
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;
    }

    SampleSigned24bit::SampleSigned24bit(int i)
    {
        int val = i;

        // まずは絶対値を合わせる。
        if (val < 0)
        {
            val *= -1;
        }
        for (int j = 0; j < 3; j++)
        {
            data[j] = getOneByteInInteger(i, j);
        }

        data[2] &= (char)0x7F; // 符号ビットを0にする操作

        // 元の数値が負の数の場合は、絶対値があった状態で-1をかける
        if (i < 0)
        {
            invert(data);
        }
    }

    SampleSigned24bit::SampleSigned24bit(unsigned char c)
    {
    }

    SampleSigned24bit SampleSigned24bit::operator-() const
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator+() const
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator+(
        SampleSigned24bit other) const
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator+(int i) const
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator-(
        SampleSigned24bit other) const
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator-(int i) const
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator*(
        SampleSigned24bit other) const
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator-(int i) const
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator*(
        SampleSigned24bit other) const
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator*(int i) const
    {
        return 0_24bit;
    }

    bool SampleSigned24bit::operator<(SampleSigned24bit other) const
    {
        return false;
    }

    bool SampleSigned24bit::operator<(int i) const
    {
        return false;
    }

    bool SampleSigned24bit::operator<=(SampleSigned24bit other) const
    {
        return false;
    }

    bool SampleSigned24bit::operator<=(int i) const
    {
        return false;
    }

    bool SampleSigned24bit::operator>(SampleSigned24bit other) const
    {
        return false;
    }

    bool SampleSigned24bit::operator>(int i) const
    {
        return false;
    }

    bool SampleSigned24bit::operator>=(SampleSigned24bit other) const
    {
        return false;
    }

    bool SampleSigned24bit::operator>=(int i) const
    {
        return false;
    }

    bool SampleSigned24bit::operator==(SampleSigned24bit other) const
    {
        return false;
    }

    bool SampleSigned24bit::operator==(int i) const
    {
        return false;
    }

    bool SampleSigned24bit::operator!=(SampleSigned24bit other) const
    {
        return false;
    }

    bool SampleSigned24bit::operator!=(int i) const
    {
        return false;
    }

    SampleSigned24bit SampleSigned24bit::operator<<(
        SampleSigned24bit other) const
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator<<(int i) const
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator>>(
        SampleSigned24bit other) const
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator>>(int i) const
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator~() const
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator|(
        SampleSigned24bit other) const
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator|(int i) const
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator&(
        SampleSigned24bit other) const
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator&(int i) const
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator^(
        SampleSigned24bit other) const
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator^(int i) const
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator+=(
        SampleSigned24bit other)
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator+=(int i)
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator-=(
        SampleSigned24bit other)
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator-=(int i)
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator=(int i)
    {
        return 0_24bit;
    }

    SampleSigned24bit SampleSigned24bit::operator=(unsigned char c)
    {
        return 0_24bit;
    }

    SampleSigned24bit::operator int()
    {
        return 0;
    }

    int operator+(int i, SampleSigned24bit v24)
    {
        return 0;
    }

    int operator-(int i, SampleSigned24bit v24)
    {
        return 0;
    }

    int operator*(int i, SampleSigned24bit v24)
    {
        return 0;
    }

    bool operator<(int i, SampleSigned24bit v24)
    {
        return false;
    }

    bool operator<=(int i, SampleSigned24bit v24)
    {
        return false;
    }

    bool operator>(int i, SampleSigned24bit v24)
    {
        return false;
    }

    bool operator>=(int i, SampleSigned24bit v24)
    {
        return false;
    }

    bool operator==(int i, SampleSigned24bit v24)
    {
        return false;
    }

    bool operator!=(int i, SampleSigned24bit v24)
    {
        return false;
    }
}

wavAgent::SampleSigned24bit operator"" _24bit(unsigned long long i)
{
    return wavAgent::SampleSigned24bit();
}