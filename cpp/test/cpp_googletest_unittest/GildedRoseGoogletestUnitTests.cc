#include <gtest/gtest.h>
#include "GildedRose.h"

TEST(GildedRoseTest, ConjuredItemLosesQualityTwiceAsFastNotExpired) {
    vector<Item> items;
    int CurrentItemQuality {10};
    int NextDayItemQuality {8};
    items.push_back(Item("Conjured Mana Cake", 5, CurrentItemQuality));
    GildedRose app(items);
    app.updateQuality();
    EXPECT_EQ(NextDayItemQuality, app.items[0].quality);
}

TEST(GildedRoseTest, ConjuredItemLosesQualityTwiceAsFastExpired) {
    vector<Item> items;
    int CurrentItemQuality {10};
    int NextDayItemQuality {6};
    items.push_back(Item("Conjured Mana Cake", -1, CurrentItemQuality));
    GildedRose app(items);
    app.updateQuality();
    EXPECT_EQ(NextDayItemQuality, app.items[0].quality);
}

TEST(GildedRoseTest, SulfurasRemainsUnaffected) {
    vector<Item> items;
    int CurrentItemQuality {80};
    int NextDayItemQuality {80};
    items.push_back(Item("Sulfuras, Hand of Ragnaros", 5, CurrentItemQuality));
    items.push_back(Item("Sulfuras, Hand of Ragnaros", -1, CurrentItemQuality));
    GildedRose app(items);
    app.updateQuality();
    EXPECT_EQ(NextDayItemQuality, app.items[0].quality);
    EXPECT_EQ(NextDayItemQuality, app.items[1].quality);
}

TEST(GildedRoseTest, AgedBrieIncreasesInQualityTheOlderItGets) {
    vector<Item> items;
    int CurrentItemQuality {12};
    int NextDayItemQuality {13};
    items.push_back(Item("Aged Brie", 5, CurrentItemQuality));
    GildedRose app(items);
    app.updateQuality();
    EXPECT_EQ(NextDayItemQuality, app.items[0].quality);
}

TEST(GildedRoseTest, NormalItemDecreasesInQualityTheOlderItGets) {
    vector<Item> items;
    int CurrentItemQuality {12};
    int NextDayItemQuality {11};
    items.push_back(Item("Elixir of the Mongoose", 5, CurrentItemQuality));
    GildedRose app(items);
    app.updateQuality();
    EXPECT_EQ(NextDayItemQuality, app.items[0].quality);
}

TEST(GildedRoseTest, QualityOfAnItemIsNeverNegative) {
    vector<Item> items;
    int CurrentItemQuality {0};
    int NextDayItemQuality {0};
    items.push_back(Item("Elixir of the Mongoose", 5, CurrentItemQuality));
    GildedRose app(items);
    app.updateQuality();
    EXPECT_EQ(NextDayItemQuality, app.items[0].quality);
}

TEST(GildedRoseTest, QualityOfAnItemIsNeverMoreThan50) {
    vector<Item> items;
    int CurrentItemQuality {50};
    int NextDayItemQuality {50};
    items.push_back(Item("Aged Brie", 5, CurrentItemQuality));
    GildedRose app(items);
    app.updateQuality();
    EXPECT_EQ(NextDayItemQuality, app.items[0].quality);
}

TEST(GildedRoseTest, QualityIncreasesBy2WhenThereAre10DaysOrLess) {
    vector<Item> items;
    int CurrentItemQuality {32};
    int NextDayItemQuality {34};
    items.push_back(Item("Backstage passes to a TAFKAL80ETC concert", 10,
        CurrentItemQuality));
    GildedRose app(items);
    app.updateQuality();
    EXPECT_EQ(NextDayItemQuality, app.items[0].quality);
}

TEST(GildedRoseTest, QualityIncreasesBy3WhenThereAre5DaysOrLess) {
    vector<Item> items;
    int CurrentItemQuality {32};
    int NextDayItemQuality {35};
    items.push_back(Item("Backstage passes to a TAFKAL80ETC concert", 5,
        CurrentItemQuality));
    GildedRose app(items);
    app.updateQuality();
    EXPECT_EQ(NextDayItemQuality, app.items[0].quality);
}

TEST(GildedRoseTest, AgedBrieIncreasesInQualityAsItsSellInValueApproaches) {
    vector<Item> items;
    int CurrentItemQuality {41};
    int NextDayItemQuality {43};
    items.push_back(Item("Aged Brie", -1, CurrentItemQuality));
    GildedRose app(items);
    app.updateQuality();
    EXPECT_EQ(NextDayItemQuality, app.items[0].quality);
}
