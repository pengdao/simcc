#include <iostream>
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

/* 
 * 低咖啡因咖啡类（一种具体的饮料）
*/
class Decaf : public Beverage
{
public: 
    Decaf() 
	{
		description = "Decaf";
    }

	virtual ~Decaf() = default;

	int cost() override {
		return 15;
	}
};

/**
* 浓缩咖啡类（一种具体饮料）
*/
class Espresso : public Beverage
{
public:
	Espresso() {
		description = "Espresso";
	}
	virtual ~Espresso() = default;

	int cost() override {
		return 20;
	}
};

/*
 * 调料装饰者抽象类
*/
class CondimentDecorator : public Beverage 
{
public:
	/**
	* 构造器初始化饮料变量
	*/
    CondimentDecorator(const BeveragePtr& beverage) : mBeveragePtr(beverage) {}
    virtual ~CondimentDecorator() = default;
protected:
	/**
	* 用一个实例变量记录饮料，也就是被装饰者
	*/
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

/**
* 豆浆调料类（继承自CondimentDecorator））
*/
class Soy : public CondimentDecorator
{
public:
	Soy(const BeveragePtr& beverage) : CondimentDecorator(beverage) {}
	~Soy() = default;
	
	//在原来饮料的基础上添加上Soy描述（原来的饮料加入Soy调料，被Soy调料装饰）
	std::string getDescription() override {
		return mBeveragePtr->getDescription() + ",Soy";
	}

	//在原来饮料的基础上加上Soy的价格
	int cost() override {
		return mBeveragePtr->cost() + 2;
	}
};

/**
* 奶泡调料类（继承自CondimentDecorator）
*/
class Whip : public CondimentDecorator
{
public:
	Whip(const BeveragePtr& beverage) : CondimentDecorator(beverage) {}
	~Whip() = default;

	//在原来饮料的基础上添加上Whip描述（原来的饮料加入Whip调料，被Whip调料装饰）
	std::string getDescription() override {
		return mBeveragePtr->getDescription() + ",Whip";
	}

	//在原来饮料的基础上加上Soy的价格
	int cost() override {
		return mBeveragePtr->cost() + 8;
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
	beverage.reset(new Whip(beverage));
    H_TEST_EQUAL(beverage->getDescription(), "DarkRoast,Mocha,Whip");
    H_TEST_EQUAL(beverage->cost(), 10+5+8);
}

TEST_UNIT(coffee_store_decorator_pattern)
{
    StarbuzzCoffee();
}