﻿#include <iostream>
#include <string>
#include <memory>
#include "test_common.h"

/*
 * 饮料抽象类
*/
class Beverage 
{
public:
    Beverage()
    {
        description = "Unknown Beverage";
    }

    virtual ~Beverage() = default;

    virtual std::string getDescription() {
        return description;
    }

    virtual int cost() = 0;

protected:
     std::string description ;
};

typedef std::shared_ptr<Beverage> BeveragePtr;

/*
* 深焙咖啡类（一种具体的饮料）
*/
class DarkRoast : public Beverage
{
public:
    DarkRoast() {
        description = "DarkRoast";
    }
    virtual ~DarkRoast() = default;

    int cost() override {
        return 10;
    }
};

class Decaf : public Beverage
{
public: 
    Decaf() {
        description = "Decaf";
    }
    virtual ~Decaf() = default;
    int cost() override {
        return 15;
    }

};

/*
 * 调料装饰者抽象类
*/
class CondimentDecorator : public Beverage 
{
public:
    CondimentDecorator(const BeveragePtr& beverage) : mBeveragePtr(beverage) {}
    virtual ~CondimentDecorator() = default;
protected:
    BeveragePtr mBeveragePtr;
};

/*
 * 摩卡调料类
 */
class Mocha : public CondimentDecorator
{
public:
    Mocha(const BeveragePtr& beverage) : CondimentDecorator(beverage) {}
    ~Mocha() = default;

    //在原来饮料的基础上添加上Mocha描述（原来的饮料加入Mocha调料，被Mocha调料装饰）
    std::string getDescription() override {
        return mBeveragePtr->getDescription() + ",Mocha";
    }

    //在原来饮料的基础上加上Mocha的价格
    int cost() override {
        return mBeveragePtr->cost() + 5;
    }
};

/*
 * 咖啡店
 */
void StarbuzzCoffee()
{
    BeveragePtr beverage (new DarkRoast());
    beverage.reset(new Mocha(beverage));
    // std::cout << "Description: "<< beverage->getDescription() << std::endl;
    H_TEST_EQUAL(beverage->getDescription(), "DarkRoast,Mocha");
    H_TEST_EQUAL(beverage->cost(), 15);
}

TEST_UNIT(coffee_store_decorator_pattern)
{
    StarbuzzCoffee();
}