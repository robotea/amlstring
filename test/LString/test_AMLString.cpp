#include <iostream>
#include "../../AMLString.h"
#include "../../AMBasicCString.h"
#include "gtest/gtest.h"

using namespace std;
using namespace AMCore;

std::vector<std::vector<char> > g_translated_strings;

TEST(AMLString, BasicTest) {

    constexpr AMLString ppp =  _T_AM_String_getTextImpl([]()constexpr{ return "chuus";});
    EXPECT_STREQ(ppp.c_str(), "chuus");
    EXPECT_STREQ(_("welcome").c_str(), "welcome");

    AMLString texts[] = {_("quick"), _("brown"), _("fox")};
    EXPECT_STREQ(texts[0].c_str(), "quick");
    EXPECT_STREQ(texts[1].c_str(), "brown");
    EXPECT_STREQ(texts[2].c_str(), "fox");

    EXPECT_EQ(5, texts[1].size());

    _T_AM_StringList* list = _T_AM_StringList::GetStringTable("blah");
    EXPECT_EQ(list, nullptr);
    list = _T_AM_StringList::GetStringTable("default");
    EXPECT_NE(list, nullptr);

    _T_AM_StringItemBase* p = list->_M_first_item;
    EXPECT_STREQ(p->getOriginalString(), "brown");
    p = p->getNextItem();
    EXPECT_STREQ(p->getOriginalString(), "chuus");
    p = p->getNextItem();
    EXPECT_STREQ(p->getOriginalString(), "fox");
    p = p->getNextItem();
    EXPECT_STREQ(p->getOriginalString(), "quick");
    p = p->getNextItem();
    EXPECT_STREQ(p->getOriginalString(), "welcome");
    p = p->getNextItem();
    EXPECT_EQ(p, nullptr);

    p = list->_M_first_item;
    EXPECT_NE(p, nullptr);
    bool first = true;
    while (p) {
        g_translated_strings.resize(g_translated_strings.size() + 1);
        g_translated_strings.back().resize(strlen(p->getOriginalString()) + (first ? 2 : 1));
        strcpy(&g_translated_strings.back()[0], p->getOriginalString());
        char* sp = &g_translated_strings.back()[0];
        while (*sp) {
            *sp = toupper(*sp);
            ++sp;
        }
        if (first) {
            *sp = '_';
            ++sp;
	    first = false;
        }
        *sp = 0;
        p->setTranslatedString(&g_translated_strings.back()[0]);
        p = p->getNextItem();
    }

    EXPECT_STREQ(texts[0].c_str(), "QUICK");
    EXPECT_STREQ(texts[1].c_str(), "BROWN_");
    EXPECT_STREQ(texts[2].c_str(), "FOX");

    EXPECT_EQ(6, texts[1].size());

    EXPECT_STREQ("brown", texts[1].getOriginalString());
    EXPECT_STREQ("brown", texts[1].getOriginalStringView().data());
    EXPECT_EQ(5, texts[1].getOriginalLength());
    EXPECT_EQ(5, texts[1].getOriginalStringView().size());

    EXPECT_EQ(texts[0], "QUICK");
    EXPECT_EQ(texts[1], "BROWN_");
    EXPECT_EQ(texts[2], "FOX");

    p = list->_M_first_item;
    p->setTranslatedString("BROWN");
    EXPECT_EQ(5, texts[1].size());

    EXPECT_EQ(false, texts[0].empty());

    EXPECT_EQ(true, (texts[2] != texts[0]));
    EXPECT_EQ(false, (texts[2] == texts[0]));
    EXPECT_EQ(true, (texts[2] == "FOX"));
    EXPECT_EQ(false, (texts[2] > texts[0]));
    EXPECT_EQ(true, (texts[2] < texts[0]));
    EXPECT_EQ(false, (texts[2] >= texts[0]));
    EXPECT_EQ(true, (texts[2] <= texts[0]));

    std::stringstream str_strm;
    str_strm << texts[1];
    EXPECT_EQ("BROWN", str_strm.str());

}

TEST(AMLString, IteratorsTest) {
    auto list = _T_AM_StringList::GetStringTable("default");
    EXPECT_NE(list, nullptr);

    _T_AM_StringItemBase* p = list->_M_first_item;
    EXPECT_STREQ(p->getOriginalString(), "brown");
    EXPECT_STREQ(p->getTranslatedString(), "BROWN");

    AMLString mls = p->getAMLString();

    for (AMLString::iterator i = mls.begin(); i < mls.end(); ++i) {
        EXPECT_EQ("BROWN"[i - mls.begin()], *i);
    }

    for (AMLString::const_iterator i = mls.cbegin(); i < mls.cend(); ++i) {
        EXPECT_EQ("BROWN"[i - mls.cbegin()], *i);
    }

    for (AMLString::reverse_iterator i = mls.rbegin(); i < mls.rend(); ++i) {
        EXPECT_EQ("NWORB"[i - mls.rbegin()], *i);
    }

    for (AMLString::const_reverse_iterator i = mls.crbegin(); i < mls.crend(); ++i) {
        EXPECT_EQ("NWORB"[i - mls.crbegin()], *i);
    }

    for (size_t i = 0; i < mls.size(); ++i) {
        EXPECT_EQ("BROWN"[i], mls[i]);
    }

    EXPECT_EQ('O', mls.at(2));

    EXPECT_EQ('B', mls.front());
    EXPECT_EQ('N', mls.back());

    p = p->getNextItem();
    EXPECT_STREQ(p->getOriginalString(), "chuus");
    EXPECT_STREQ(p->getTranslatedString(), "CHUUS");
    AMLString mls1 = p->getAMLString();

    mls1.swap(mls);

    EXPECT_EQ("BROWN", mls1);

    char buf[16] = {0,};

    const size_t copied = mls1.copy(buf, 10, 1);
    EXPECT_EQ(4, copied);
    EXPECT_STREQ("ROWN", buf);

    EXPECT_EQ(true, mls1.compare(1, 10, mls) > 0);
    EXPECT_EQ(true, mls1.compare(1, 10, mls, 2, 10) < 0);

    EXPECT_EQ(0, mls.compare(2, 10, "UUS"));
    EXPECT_EQ(0, mls.compare(2, 10, "UUSXXX", 3));
}

TEST(AMLString, FindTest) {
    auto list = _T_AM_StringList::GetStringTable("default");
    EXPECT_NE(list, nullptr);

    _T_AM_StringItemBase* p = list->_M_first_item;
    EXPECT_STREQ(p->getOriginalString(), "brown");
    EXPECT_STREQ(p->getTranslatedString(), "BROWN");
    AMLString mls = p->getAMLString();

    p = p->getNextItem();
    EXPECT_STREQ(p->getOriginalString(), "chuus");
    EXPECT_STREQ(p->getTranslatedString(), "CHUUS");
    AMLString mls1 = p->getAMLString();

    p = p->getNextItem();
    EXPECT_STREQ(p->getOriginalString(), "fox");
    EXPECT_STREQ(p->getTranslatedString(), "FOX");
    AMLString mls2 = p->getAMLString();

    EXPECT_EQ(std::string::npos, mls.find(mls1));
    EXPECT_EQ(std::string::npos, mls.find(mls1, 2));
    EXPECT_EQ(3, mls.find("WN"));
    EXPECT_EQ(3, mls.find("WN", 3));

    EXPECT_EQ(std::string::npos, mls.rfind(mls1));
    EXPECT_EQ(std::string::npos, mls.rfind(mls1, 2));
    EXPECT_EQ(3, mls.rfind("WN"));
    EXPECT_EQ(3, mls.rfind("WN", 3));

    EXPECT_EQ(2, mls.find_first_of(mls2));
    EXPECT_EQ(2, mls.find_first_of(mls2, 1));
    EXPECT_EQ(3, mls.find_first_of('W'));
    EXPECT_EQ(3, mls.find_first_of('W', 1));
    EXPECT_EQ(2, mls1.find_first_of("STUV"));
    EXPECT_EQ(2, mls1.find_first_of("STUV", 1));

    EXPECT_EQ(1, mls2.find_last_of(mls));
    EXPECT_EQ(1, mls2.find_last_of(mls,1));
    EXPECT_EQ(3, mls1.find_last_of('U'));
    EXPECT_EQ(3, mls1.find_last_of('U', 4));
    EXPECT_EQ(4, mls1.find_last_of("STUV"));
    EXPECT_EQ(4, mls1.find_last_of("STUV", 4));

    EXPECT_EQ(0, mls.find_first_not_of(mls2));
    EXPECT_EQ(3, mls.find_first_not_of(mls2, 2));

    EXPECT_EQ(1, mls.find_first_not_of('B'));
    EXPECT_EQ(3, mls.find_first_not_of('B', 3));

    EXPECT_EQ(1, mls.find_first_not_of("ABCDEF"));
    EXPECT_EQ(3, mls.find_first_not_of("ABCDEF", 3));

    EXPECT_EQ(4, mls.find_last_not_of(mls2));
    EXPECT_EQ(1, mls.find_last_not_of(mls2, 2));

    EXPECT_EQ(4, mls.find_last_not_of('W'));
    EXPECT_EQ(2, mls.find_last_not_of('W', 3));

    EXPECT_EQ(4, mls.find_last_not_of("ABCDEFW"));
    EXPECT_EQ(2, mls.find_last_not_of("ABCDEFW", 3));
}

TEST(AMLString, SpeedDemo) {
    printf("Start\n");
    AMLString foxl = _("fox");
    const char *foxc = foxl.c_str();
    printf("%s\n", foxc);
}

int main(int argc, char **argv) {

     ::testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
}
