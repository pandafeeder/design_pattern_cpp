#include <iostream>
#include <string>
#include <memory>

class MainItem {
public:
    MainItem(const std::string& m)
        : _name(m) {}
    const std::string& content() const
    {
        return _name;
    }
private:
    std::string _name;
};

class SideItem {
public:
    SideItem(const std::string& s)
        : _name(s) {}
    const std::string& content() const
    {
        return _name;
    }
private:
    std::string _name;
};

class Drink {
public:
    Drink(const std::string& d)
        : _name(d) {}
    const std::string& content() const
    {
        return _name;
    }
private:
    std::string _name;
};


class Meal {
public:
    using MainItemUptr = std::unique_ptr<MainItem>;
    using DrinkUptr = std::unique_ptr<Drink>;
    using SideItemUptr = std::unique_ptr<SideItem>;
    void setMain(MainItemUptr& m) {
        _main = std::move(m);
    }
    void setDrink(DrinkUptr& d) {
        _drink = std::move(d);
    }
    void setSideItem(SideItemUptr& s) {
        _side_item = std::move(s);
    }
    void spec() const
    {
        std::cout << "Main: " << _main->content() << '\n'
                  << "drink: " << _drink->content() << '\n'
                  << "side: " << _side_item->content() << '\n';
    }
private:
    MainItemUptr _main;
    DrinkUptr _drink;
    SideItemUptr _side_item;
};


class MealBuilder {
public:
    virtual void setMeal(std::unique_ptr<Meal>& uptr) = 0;
};

class ChildMealBuilder: public MealBuilder {
public:
    virtual void setMeal(std::unique_ptr<Meal>& uptr) override
    {
        auto m = std::make_unique<MainItem>("child main item");
        auto d = std::make_unique<Drink>("child drink");
        auto s = std::make_unique<SideItem>("child side item");
        uptr->setMain(m);
        uptr->setDrink(d);
        uptr->setSideItem(s);
    }
};

class AdultMealBuilder: public MealBuilder {
public:
    virtual void setMeal(std::unique_ptr<Meal>& uptr) override
    {
        auto m = std::make_unique<MainItem>("adult main item");
        auto d = std::make_unique<Drink>("adult drink");
        auto s = std::make_unique<SideItem>("adult side item");
        uptr->setMain(m);
        uptr->setDrink(d);
        uptr->setSideItem(s);
    }
};


class Director {
public:
    void setBuilder(const std::shared_ptr<MealBuilder>& builder_ptr) {
        _builder = builder_ptr;
    }
    std::unique_ptr<Meal> getMeal() {
        auto m = std::make_unique<Meal>();
        _builder->setMeal(m);
        return m;
    }
private:
    std::shared_ptr<MealBuilder> _builder;
};

int main()
{
    auto child_meal_builder_ptr = std::make_shared<ChildMealBuilder>();
    auto adult_meal_builder_ptr = std::make_shared<AdultMealBuilder>();

    Director director;
    director.setBuilder(child_meal_builder_ptr);
    auto child_meal = director.getMeal();
    director.setBuilder(adult_meal_builder_ptr);    
    auto adult_meal = director.getMeal();

    child_meal->spec();
    adult_meal->spec();

}

