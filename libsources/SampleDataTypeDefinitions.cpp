#include "SampleDataTypeDefinitions.h"

// SampleSigned24bit型の値の符号ビットをbool値で返す
#define ISMARKBIT(v) (((v).data[2] & (unsigned char)0x80) != 0)

namespace wavAgent
{
    // int型の変数iのidxバイト目の値を返す。idxは0-indexed
    inline unsigned char getOneByteInInteger(int i, int idx)
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
            data[j] = getOneByteInInteger(val, j);
        }

        data[2] &= (unsigned char)0x7F; // 符号ビットを0にする操作

        // 元の数値が負の数の場合は、絶対値があった状態で-1をかける
        if (i < 0)
        {
            invert(data);
        }
    }

    SampleSigned24bit::SampleSigned24bit(unsigned char c)
    {
        data[0] = c;
        data[1] = 0;
        data[2] = 0;
    }

    SampleSigned24bit SampleSigned24bit::operator-() const
    {
        // 自身のコピーを作成して、それに-1をかけた値を返す
        auto copy = *this;
        invert(copy.data);
        return copy;
    }

    SampleSigned24bit SampleSigned24bit::operator+() const
    {
        return *this;
    }

    SampleSigned24bit SampleSigned24bit::operator+(
        SampleSigned24bit other) const
    {
        SampleSigned24bit result = 0_24bit;
        int carry = 0;
        for (int i = 0; i < 3; i++)
        {
            int calcRes = this->data[i] + other.data[i] + carry;

            // オーバーフローの判定
            carry = (calcRes > 0xFF) ? 1 : 0;

            result.data[i] = getOneByteInInteger(calcRes, 0);
        }
        return result;
    }

    SampleSigned24bit SampleSigned24bit::operator+(int i) const
    {
        return *this + (SampleSigned24bit)i;
    }

    SampleSigned24bit SampleSigned24bit::operator-(
        SampleSigned24bit other) const
    {
        return *this + (-other);
    }

    SampleSigned24bit SampleSigned24bit::operator-(int i) const
    {
        return *this + (-i);
    }

    SampleSigned24bit SampleSigned24bit::operator*(
        SampleSigned24bit other) const
    {
        return (*this) * ((int)other);
    }

    SampleSigned24bit SampleSigned24bit::operator*(int i) const
    {
        int thisI = (int)(*this);
        return (SampleSigned24bit)(thisI * i);
    }

    bool SampleSigned24bit::operator<(SampleSigned24bit other) const
    {
        return (*this) < ((int)other);
    }

    bool SampleSigned24bit::operator<(int i) const
    {
        return ((int)*this) < i;
    }

    bool SampleSigned24bit::operator<=(SampleSigned24bit other) const
    {
        return (*this) <= ((int)other);
    }

    bool SampleSigned24bit::operator<=(int i) const
    {
        return ((int)*this) <= i;
    }

    bool SampleSigned24bit::operator>(SampleSigned24bit other) const
    {
        return (*this) > ((int)other);
    }

    bool SampleSigned24bit::operator>(int i) const
    {
        return ((int)*this) > i;
    }

    bool SampleSigned24bit::operator>=(SampleSigned24bit other) const
    {
        return (*this) >= ((int)other);
    }

    bool SampleSigned24bit::operator>=(int i) const
    {
        return ((int)*this) >= i;
    }

    bool SampleSigned24bit::operator==(SampleSigned24bit other) const
    {
        return (*this) == ((int)other);
    }

    bool SampleSigned24bit::operator==(int i) const
    {
        return ((int)*this) == i;
    }

    bool SampleSigned24bit::operator!=(SampleSigned24bit other) const
    {
        return (*this) != ((int)other);
    }

    bool SampleSigned24bit::operator!=(int i) const
    {
        return ((int)*this) != i;
    }

    SampleSigned24bit SampleSigned24bit::operator<<(
        SampleSigned24bit other) const
    {
        return (*this) << ((int)other);
    }

    SampleSigned24bit SampleSigned24bit::operator<<(int i) const
    {
        // 一旦int型でシフト結果を計算してから、それをSampleSigned24bitに変換する
        int shiftedInt = ((int)this->data[0]) << i;
        shiftedInt |= ((int)this->data[1]) << (i + 8);
        shiftedInt |= ((int)this->data[2]) << (i + 16);

        SampleSigned24bit retVal;
        retVal.data[0] = getOneByteInInteger(shiftedInt, 0);
        retVal.data[1] = getOneByteInInteger(shiftedInt, 1);
        retVal.data[2] = getOneByteInInteger(shiftedInt, 2);

        return retVal;
    }

    SampleSigned24bit SampleSigned24bit::operator>>(
        SampleSigned24bit other) const
    {
        return (*this) >> ((int)other);
    }

    SampleSigned24bit SampleSigned24bit::operator>>(int i) const
    {
        // 一旦int型でシフト結果を計算してから、それをSampleSigned24bitに変換する
        int shiftedInt = ((int)this->data[0]) >> i;
        shiftedInt |= ((((int)this->data[1]) << 8) >> i);
        shiftedInt |= ((((int)this->data[2]) << 16) >> i);

        SampleSigned24bit retVal;
        retVal.data[0] = getOneByteInInteger(shiftedInt, 0);
        retVal.data[1] = getOneByteInInteger(shiftedInt, 1);
        retVal.data[2] = getOneByteInInteger(shiftedInt, 2);

        return retVal;
    }

    SampleSigned24bit SampleSigned24bit::operator~() const
    {
        SampleSigned24bit copy = *this;
        copy.data[0] = ~copy.data[0];
        copy.data[1] = ~copy.data[1];
        copy.data[2] = ~copy.data[2];
        return copy;
    }

    SampleSigned24bit SampleSigned24bit::operator|(
        SampleSigned24bit other) const
    {
        SampleSigned24bit copy = *this;
        copy.data[0] |= other.data[0];
        copy.data[1] |= other.data[1];
        copy.data[2] |= other.data[2];
        return copy;
    }

    SampleSigned24bit SampleSigned24bit::operator|(int i) const
    {
        SampleSigned24bit copy = *this;
        copy.data[0] |= getOneByteInInteger(i, 0);
        copy.data[1] |= getOneByteInInteger(i, 1);
        copy.data[2] |= getOneByteInInteger(i, 2);
        return copy;
    }

    SampleSigned24bit SampleSigned24bit::operator&(
        SampleSigned24bit other) const
    {
        SampleSigned24bit copy = *this;
        copy.data[0] &= other.data[0];
        copy.data[1] &= other.data[1];
        copy.data[2] &= other.data[2];
        return copy;
    }

    SampleSigned24bit SampleSigned24bit::operator&(int i) const
    {
        SampleSigned24bit copy = *this;
        copy.data[0] &= getOneByteInInteger(i, 0);
        copy.data[1] &= getOneByteInInteger(i, 1);
        copy.data[2] &= getOneByteInInteger(i, 2);
        return copy;
    }

    SampleSigned24bit SampleSigned24bit::operator^(
        SampleSigned24bit other) const
    {
        SampleSigned24bit copy = *this;
        copy.data[0] ^= other.data[0];
        copy.data[1] ^= other.data[1];
        copy.data[2] ^= other.data[2];
        return copy;
    }

    SampleSigned24bit SampleSigned24bit::operator^(int i) const
    {
        SampleSigned24bit copy = *this;
        copy.data[0] ^= getOneByteInInteger(i, 0);
        copy.data[1] ^= getOneByteInInteger(i, 1);
        copy.data[2] ^= getOneByteInInteger(i, 2);
        return copy;
    }

    SampleSigned24bit SampleSigned24bit::operator+=(
        SampleSigned24bit other)
    {
        *this = (*this) + other;
        return *this;
    }

    SampleSigned24bit SampleSigned24bit::operator+=(int i)
    {
        *this = (*this) + i;
        return *this;
    }

    SampleSigned24bit SampleSigned24bit::operator-=(
        SampleSigned24bit other)
    {
        *this = (*this) - other;
        return *this;
    }

    SampleSigned24bit SampleSigned24bit::operator-=(int i)
    {
        *this = (*this) - i;
        return *this;
    }

    SampleSigned24bit SampleSigned24bit::operator=(int i)
    {
        *this = (SampleSigned24bit)i;
        return *this;
    }

    SampleSigned24bit SampleSigned24bit::operator=(unsigned char c)
    {
        *this = (SampleSigned24bit)c;
        return *this;
    }

    SampleSigned24bit::operator int() const
    {
        SampleSigned24bit copy = *this;
        // まずは絶対値をint型に変換する
        if (ISMARKBIT(copy))
        {
            invert(copy.data);
        }
        int absInt = (copy.data[0]) | (copy.data[1] << 8) | (copy.data[2] << 16);

        // 元々の符号が負の場合は絶対値iに-1をかける
        if (ISMARKBIT(*this))
        {
            absInt *= -1;
        }

        return absInt;
    }

    int operator+(int i, SampleSigned24bit v24)
    {
        return i + ((int)v24);
    }

    int operator-(int i, SampleSigned24bit v24)
    {
        return i - ((int)v24);
    }

    int operator*(int i, SampleSigned24bit v24)
    {
        return i * ((int)v24);
    }

    bool operator<(int i, SampleSigned24bit v24)
    {
        return v24 > i;
    }

    bool operator<=(int i, SampleSigned24bit v24)
    {
        return v24 >= i;
    }

    bool operator>(int i, SampleSigned24bit v24)
    {
        return v24 < i;
    }

    bool operator>=(int i, SampleSigned24bit v24)
    {
        return v24 <= i;
    }

    bool operator==(int i, SampleSigned24bit v24)
    {
        return v24 == i;
    }

    bool operator!=(int i, SampleSigned24bit v24)
    {
        return v24 != i;
    }
}

wavAgent::SampleSigned24bit operator"" _24bit(unsigned long long ull)
{
    int intVal = (int)ull;

    return (wavAgent::SampleSigned24bit)intVal;
}