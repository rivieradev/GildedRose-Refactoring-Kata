// Include header files for test frameworks 
#include <gtest/gtest.h>
#include <ApprovalTests.hpp>

// Include code to be tested
#include "GildedRose.h"

std::ostream& operator<<(std::ostream& os, const Item& obj)
{
    return os
        << "name: " << obj.name
        << ", sellIn: " << obj.sellIn
        << ", quality: " << obj.quality;
}

TEST(GildedRoseApprovalTests, VerifyCombinations) {

    std::vector<Item> items;
    items.push_back(Item("+5 Dexterity Vest", 10, 20));
    items.push_back(Item("Aged Brie", 2, 0));
    items.push_back(Item("Elixir of the Mongoose", 5, 7));
    items.push_back(Item("Sulfuras, Hand of Ragnaros", 0, 80));
    items.push_back(Item("Sulfuras, Hand of Ragnaros", -1, 80));
    items.push_back(Item("Backstage passes to a TAFKAL80ETC concert", 15, 20));
    items.push_back(Item("Backstage passes to a TAFKAL80ETC concert", 10, 49));
    items.push_back(Item("Backstage passes to a TAFKAL80ETC concert", 5, 49));
    // this Conjured item doesn't yet work properly
    items.push_back(Item("Conjured Mana Cake", 3, 6));
    GildedRose app(items);
 
    std::stringstream out_stream;
 
    for (int day = 0; day <= 30; day++) {
        out_stream << "-------- day " << day << " --------" << '\n';
        out_stream << "name, sellIn, quality" << '\n';
        for (const auto item : items) {
            out_stream << item << '\n';
        }
        out_stream << '\n';
 
        app.updateQuality();
    }
 
    ApprovalTests::Approvals::verify(out_stream.str());

}
