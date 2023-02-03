#include <gtest/gtest.h>
#include "SampleDataTypeDefinitions.h"

// 他のテストを動かす前に、まずはテストで使用される比較演算子の動作確認を行う必要がある
TEST(SampleSinged24bitCompareTest, BasicAssertions)
{
    // SampleSigned24bitのコンストラクタ回りをチェックする
    wavAgent::SampleSigned24bit val; // デフォルトコンストラクタが呼ばれることを確認
    // == のチェック
    EXPECT_TRUE(val == 0); // 24bitが左辺にある場合と
    EXPECT_TRUE(0 == val); // 24bitが右辺にある場合の両方を調べる
    EXPECT_TRUE(val == 0_24bit);

    EXPECT_EQ(val, 0);
    EXPECT_EQ(0, val);
    EXPECT_EQ(val, 0_24bit);

    // != のチェック
    EXPECT_TRUE(val != 1);
    EXPECT_TRUE(-1 != val);
    EXPECT_TRUE(val != 1_24bit);
    EXPECT_TRUE(val != -1_24bit); // 正の数と負の数と両方比較しておく

    EXPECT_NE(val, 1);
    EXPECT_NE(-1, val);
    EXPECT_NE(val, 1_24bit);
    EXPECT_NE(val, -1_24bit);

    // < のチェック
    EXPECT_TRUE(val < 1);
    EXPECT_TRUE(-1 < val);
    EXPECT_TRUE(val < 1_24bit);

    EXPECT_LT(val, 1);
    EXPECT_LT(-1, val);
    EXPECT_LT(val, 1_24bit);

    // <= のチェック。差がある場合だけでなく、値が等しい時もチェックする
    EXPECT_TRUE(val <= 1);
    EXPECT_TRUE(-1 <= val);
    EXPECT_TRUE(val <= 0);
    EXPECT_TRUE(0 <= val);
    EXPECT_TRUE(val <= 1_24bit);
    EXPECT_TRUE(val <= 0_24bit);

    EXPECT_LE(val, 1);
    EXPECT_LE(-1, val);
    EXPECT_LE(val, 0);
    EXPECT_LE(0, val);
    EXPECT_LE(val, 1_24bit);
    EXPECT_LE(val, 0_24bit);

    // > のチェック
    EXPECT_TRUE(val > -1);
    EXPECT_TRUE(1 > val);
    EXPECT_TRUE(val > -1_24bit);

    EXPECT_GE(val, -1);
    EXPECT_GE(1, val);
    EXPECT_GE(val, -1_24bit);

    // >= のチェック
    EXPECT_TRUE(val >= -1);
    EXPECT_TRUE(1 >= val);
    EXPECT_TRUE(val >= 0);
    EXPECT_TRUE(0 >= val);
    EXPECT_TRUE(val >= -1_24bit);
    EXPECT_TRUE(val >= 0_24bit);

    EXPECT_GE(val, -1);
    EXPECT_GE(1, val);
    EXPECT_GE(val, 0);
    EXPECT_GE(0, val);
    EXPECT_GE(val, -1_24bit);
    EXPECT_GE(val, 0_24bit);
}

// SampleSigned24bitへの代入や初期化が上手く行く事を確認
TEST(SampleSigned24bitAssignment, BasicAssertions)
{
    // 24bitを用いた初期化
    wavAgent::SampleSigned24bit val1 = 10_24bit;
    EXPECT_EQ(val1, 10_24bit);

    // intを用いた初期化
    wavAgent::SampleSigned24bit val2 = 10;
    EXPECT_EQ(val2, 10_24bit);

    // charを用いた初期化
    char c = (char)0xFF;
    wavAgent::SampleSigned24bit val3 = c;
    EXPECT_EQ(val3, 255_24bit);

    // 16進数リテラルを用いた初期化
    wavAgent::SampleSigned24bit val4 = 0x012345;
    EXPECT_EQ(val4, 0x12345);

    // 24bitの代入
    val1 = 15_24bit;
    EXPECT_EQ(val1, 15_24bit);

    // intの代入
    val1 = 20;
    EXPECT_EQ(val1, 20);

    // charの代入
    c = 0x01;
    val3 = c;
    EXPECT_EQ(val3, 1_24bit);

    // 16進数リテラルを用いた代入
    val1 = 0x012345;
    EXPECT_EQ(val1, 0x012345);
}

// 足し算や引き算などの算術演算が上手く行く事を確認
TEST(SampleSigned24bitMathematics, BasicAssertions)
{
    // 符号演算子のチェック
    EXPECT_EQ(-1_24bit, -1);
    EXPECT_EQ(+4_24bit, 4);

    EXPECT_EQ(10_24bit + 12_24bit, 22_24bit);
    EXPECT_EQ(8_24bit + (-10_24bit), -2_24bit);
    EXPECT_EQ((-10_24bit) + 9_24bit, -1_24bit);
    EXPECT_EQ(1_24bit + 1, 2_24bit);
    EXPECT_EQ(100 + 100_24bit, 200);
    EXPECT_EQ(0x0FFFFFFF + 1_24bit, 0x10000000); // intが左辺に来る場合、計算結果がint型なので、24bit以上の計算結果がありうる

    EXPECT_EQ(32_24bit - 18_24bit, 14_24bit);
    EXPECT_EQ(25_24bit - 60_24bit, -35_24bit);
    EXPECT_EQ(-10_24bit - 13_24bit, -23_24bit);
    EXPECT_EQ(19_24bit - (-13_24bit), 32_24bit);
    EXPECT_EQ(-16_24bit - (-18_24bit), 2_24bit);
    EXPECT_EQ(22_24bit - 10, 14_24bit);
    EXPECT_EQ(18_24bit - 200, -182_24bit);
    EXPECT_EQ(120 - 2_24bit, 118);
    EXPECT_EQ(16 - 30_24bit, -14);
    EXPECT_EQ(0x1FFFFFFF - 1_24bit, 0x1FFFFFFE);
    EXPECT_EQ(-1000000000 - 1_24bit, -1000000001);

    EXPECT_EQ(10_24bit * 8_24bit, 80_24bit);
    EXPECT_EQ(-28_24bit * 3_24bit, -84_24bit);
    EXPECT_EQ(40_24bit * -3_24bit, -120_24bit);
    EXPECT_EQ(-56_24bit * -8_24bit, 448_24bit);
    EXPECT_EQ(0_24bit * 5_24bit, 0_24bit);
    EXPECT_EQ(6_24bit * 0_24bit, 0_24bit);

    EXPECT_EQ(10_24bit * 8, 80_24bit);
    EXPECT_EQ(-28_24bit * 3, -84_24bit);
    EXPECT_EQ(40_24bit * -3, -120_24bit);
    EXPECT_EQ(-56_24bit * -8, 448_24bit);
    EXPECT_EQ(0_24bit * 5, 0_24bit);
    EXPECT_EQ(6_24bit * 0, 0_24bit);

    EXPECT_EQ(10 * 8_24bit, 80);
    EXPECT_EQ(-28 * 3_24bit, -84);
    EXPECT_EQ(40 * -3_24bit, -120);
    EXPECT_EQ(-56 * -8_24bit, 448_24bit);
    EXPECT_EQ(0 * 5_24bit, 0_24bit);
    EXPECT_EQ(6 * 0_24bit, 0_24bit);

    EXPECT_EQ(100000000 * 10_24bit, 1000000000);
    EXPECT_EQ(-100000000 * 20_24bit, -2000000000);
    EXPECT_EQ(-10000000 * -210_24bit, 2100000000);

    // 算術代入。代入できているかどうかだけでなく、演算の返り値も確認する
    wavAgent::SampleSigned24bit v1 = 8_24bit;
    EXPECT_EQ(v1 += 6_24bit, 14_24bit);
    EXPECT_EQ(v1, 14_24bit);

    EXPECT_EQ(v1 += -15_24bit, -1_24bit);
    EXPECT_EQ(v1, -1_24bit);

    EXPECT_EQ(v1 += 7, 6_24bit);
    EXPECT_EQ(v1, 6_24bit);

    EXPECT_EQ(v1 += -3, 3_24bit);
    EXPECT_EQ(v1, 3_24bit);

    EXPECT_EQ(v1 -= 6_24bit, -3_24bit);
    EXPECT_EQ(v1, -3_24bit);

    EXPECT_EQ(v1 -= -15_24bit, 12_24bit);
    EXPECT_EQ(v1, 12_24bit);

    EXPECT_EQ(v1 -= 7, 5_24bit);
    EXPECT_EQ(v1, 5_24bit);

    EXPECT_EQ(v1 -= -3, 8_24bit);
    EXPECT_EQ(v1, 8_24bit);
}

// ビット演算を正しくできるか確認する。
TEST(SampleSigned24bitBitOperation, BasicAssertions)
{
    wavAgent::SampleSigned24bit val1 = 0x0000F0;
    EXPECT_EQ(val1 << 12_24bit, 0x0F0000);
    EXPECT_EQ(val1 << 17_24bit, 0xE00000); // あふれるパターン

    EXPECT_EQ(val1 << 8, 0x00F000);
    EXPECT_EQ(val1 << 18, 0xC00000);

    EXPECT_EQ(val1 >> 1_24bit, 0x000078);
    EXPECT_EQ(val1 >> 6_24bit, 0x000003);

    EXPECT_EQ(val1 >> 2, 0x00003C);
    EXPECT_EQ(val1 >> 7, 0x000001);

    EXPECT_EQ(~val1, 0xFFFF0F);
    EXPECT_EQ(~0_24bit, 0xFFFFFF);

    wavAgent::SampleSigned24bit val2 = 0x000FFF, val3 = 0xFFF000,
                                val4 = 0x0F0F0F;
    int i1 = 0xFFF000, i2 = 0xF0F0F0;
    EXPECT_EQ(val2 | val3, 0xFFFFFF);
    EXPECT_EQ(val2 | val4, 0x0F0FFF);

    EXPECT_EQ(val2 | i1, 0xFFFFFF);
    EXPECT_EQ(val2 | i2, 0xF0FFFF);

    EXPECT_EQ(val2 & val3, 0x000000);
    EXPECT_EQ(val2 & val4, 0x000F0F);

    EXPECT_EQ(val2 & i1, 0x000000);
    EXPECT_EQ(val2 & i2, 0x0000F0);

    EXPECT_EQ(val2 ^ val3, 0xFFFFFF);
    EXPECT_EQ(val2 ^ val4, 0x0F00F0);

    EXPECT_EQ(val2 ^ i1, 0xFFFFFF);
    EXPECT_EQ(val2 ^ i2, 0xF0FF0F);
}

// 24bitから他の値へのキャストが正しく動作するかの確認
TEST(SampleSigned24bitCast, BasicAssertions)
{
    int i = (int)10_24bit;
    EXPECT_EQ(i, 10);

    i = (int)-10_24bit;
    EXPECT_EQ(i, -10);
}