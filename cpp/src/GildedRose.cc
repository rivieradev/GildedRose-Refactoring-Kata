#include "GildedRose.h"

GildedRose::GildedRose(vector<Item> & items) : items(items)
{}

const std::string kAgedBrie {"Aged Brie"};
const std::string kBackstage {"Backstage passes to a TAFKAL80ETC concert"};
const std::string kSulfuras {"Sulfuras, Hand of Ragnaros"};
const std::string kConjured {"Conjured Mana Cake"};
const int kMaxQuality {50};

void GildedRose::updateQuality() 
{
    for (Item& item : items)
    {
       std::unique_ptr<Strategy> itemStrategy {getSpecificStrategy(item)};
       itemStrategy->update();
    }
}

void Strategy::increaseQuality()
{
    if (_item.quality < kMaxQuality)
    {
        ++_item.quality;
    }
}

void BackstageStrategy::resetQuality()
{
    _item.quality = 0;
}

void Strategy::decreaseQuality()
{
    if (_item.quality > 0)
    {
        --_item.quality;
    }
}

void Strategy::decreaseSellIn()
{
    --_item.sellIn;
}

bool Strategy::isExpired()
{
    return _item.sellIn < 0;
}

void AgedBrieStrategy::update()
{
    increaseQuality();
    decreaseSellIn();
    if (isExpired())
    {
        increaseQuality();   
    }
}

unsigned int BackstageStrategy::timesToIncreaseQuality()
{
    unsigned int counter {1};
    if (_item.sellIn < 11)
    {
        ++counter;
    }
    if (_item.sellIn < 6)
    {
        ++counter;
    }
    return counter;
}

void BackstageStrategy::increaseQuality()
{
    for (unsigned int i {1}; i <= timesToIncreaseQuality(); ++i)
    {
        Strategy::increaseQuality();
    }
}

void BackstageStrategy::update()
{
    increaseQuality();
    decreaseSellIn();
    if (isExpired())
    {
        resetQuality();
    }
}

void SulfurasStrategy::update()
{
    return;
}

void NormalStrategy::update()
{
    decreaseQuality();
    decreaseSellIn();
    if (isExpired())
    {
        decreaseQuality();
    }
}

void ConjuredStrategy::decreaseQuality()
{
    Strategy::decreaseQuality();
    Strategy::decreaseQuality();
}

void ConjuredStrategy::update()
{
    NormalStrategy::update();
}

std::unique_ptr<Strategy> GildedRose::getSpecificStrategy(Item& item)
{
    if (item.name == kAgedBrie)
    {
        return std::make_unique<AgedBrieStrategy>(item);
    }
    else if (item.name == kBackstage)
    {
        return std::make_unique<BackstageStrategy>(item);
    }
    else if (item.name == kSulfuras)
    {
        return std::make_unique<SulfurasStrategy>(item);
    }
    else if (item.name == kConjured)
    {
        return std::make_unique<ConjuredStrategy>(item);
    }
    else
    {
        return std::make_unique<NormalStrategy>(item);
    }
}