#include <string>
#include <vector>
#include <memory>

using namespace std;

class Item
{
public:
    string name;
    int sellIn;
    int quality;
    Item(string name, int sellIn, int quality) : name(name), sellIn(sellIn),
        quality(quality) {}
};

class Strategy
{
public:
    explicit Strategy(Item& item) : _item{item}{}
    virtual ~Strategy() = default;
    virtual void update() = 0;
    Item& _item;
    virtual void increaseQuality();
    virtual void decreaseQuality();
    void decreaseSellIn();
    bool isExpired();
};

class AgedBrieStrategy : public Strategy
{
public:
    explicit AgedBrieStrategy(Item& item) : Strategy {item} {}
    virtual ~AgedBrieStrategy() = default;
    virtual void update() override;
};

class BackstageStrategy : public Strategy
{
public:
    explicit BackstageStrategy(Item& item) : Strategy {item} {}
    virtual ~BackstageStrategy() = default;
    virtual void update() override;
    void resetQuality();
    virtual void increaseQuality() override;
private:
    unsigned int timesToIncreaseQuality();
};

class SulfurasStrategy : public Strategy
{
public:
    explicit SulfurasStrategy(Item& item) : Strategy {item} {}
    virtual ~SulfurasStrategy() = default;
    virtual void update() override;
};

class NormalStrategy : public Strategy
{
public:
    explicit NormalStrategy(Item& item) : Strategy {item} {}
    virtual ~NormalStrategy() = default;
    virtual void update() override;
};

class ConjuredStrategy : public NormalStrategy
{
public:
    explicit ConjuredStrategy(Item& item) : NormalStrategy {item} {}
    virtual ~ConjuredStrategy() = default;
    virtual void update() override;
    virtual void decreaseQuality() override;
};

class GildedRose
{
public:
    vector<Item> & items;
    GildedRose(vector<Item> & items);
    
    void updateQuality();
private:
    std::unique_ptr<Strategy> getSpecificStrategy(Item& item);
};
