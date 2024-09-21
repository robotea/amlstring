#include "../../AMCEFNV1a.h"
#include "gtest/gtest.h"

using namespace AMCore;


TEST(AMCEFNV1aAlgorithm, basicTest) {

	EXPECT_EQ(AMCEFNV1aAlgorithm::fnv1a64("ahoj"), 0xa55e1783bce0e169ULL );
    EXPECT_EQ(AMCEFNV1aAlgorithm::fnv1a32("ahoj"), 0xa05a00c9UL );

    EXPECT_EQ(AMCEFNV1aAlgorithm::fnv1a64(""), 0xcbf29ce484222325ULL );
    EXPECT_EQ(AMCEFNV1aAlgorithm::fnv1a32(""), 0x811c9dc5UL );

    EXPECT_EQ(AMCEFNV1aAlgorithm::fnv1a64("a"), 0xaf63dc4c8601ec8cULL );
    EXPECT_EQ(AMCEFNV1aAlgorithm::fnv1a32("a"), 0xe40c292cUL );

    EXPECT_EQ(AMCEFNV1aAlgorithm::fnv1a64("abc"), 0xe71fa2190541574bULL );
    EXPECT_EQ(AMCEFNV1aAlgorithm::fnv1a32("abc"), 0x1a47e90bUL );

    EXPECT_EQ(AMCEFNV1aAlgorithm::fnv1a64("message digest"), 0x2dcbcce86fce9934ULL );
    EXPECT_EQ(AMCEFNV1aAlgorithm::fnv1a32("message digest"), 0xb2c0f234UL );

    EXPECT_EQ(AMCEFNV1aAlgorithm::fnv1a64("abcdefghijklmnopqrstuvwxyz"), 0x8450deb1cdc382a2ULL );
    EXPECT_EQ(AMCEFNV1aAlgorithm::fnv1a32("abcdefghijklmnopqrstuvwxyz"), 0xb0bc0c82UL );

    EXPECT_EQ(AMCEFNV1aAlgorithm::fnv1a64("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"), 0xc35365f271d8c80eULL );
    EXPECT_EQ(AMCEFNV1aAlgorithm::fnv1a32("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"), 0x9b2bce4eUL );

    EXPECT_EQ(AMCEFNV1aAlgorithm::fnv1a64("12345678901234567890123456789012345678901234567890123456789012345678901234567890"), 0x95ee3578614f3045ULL );
    EXPECT_EQ(AMCEFNV1aAlgorithm::fnv1a32("12345678901234567890123456789012345678901234567890123456789012345678901234567890"), 0x5b52cd65UL );
}

int main(int argc, char **argv) {

     ::testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
}
