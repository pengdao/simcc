#include <string>
#include <memory>
#include <iostream>

#include "test_common.h"

class IPlayer
{
public:
    virtual ~IPlayer() = default;
public:
    virtual std::string getName() const = 0;
    virtual std::string sendInstantMessage(std::string message) const = 0;
};

class Player : public IPlayer
{
public:
    virtual ~Player() = default;
    virtual std::string getName() const override
    {
        return "Player";
    }
    virtual std::string sendInstantMessage(std::string message) const override
    {
        // std::cout << __PRETTY_FUNCTION__ << ", " << message.c_str() << std::endl;
        return "yes";
    }
};

class PlayerProxy : public IPlayer
{
public:
    PlayerProxy(std::unique_ptr<IPlayer> player) : mPlayer(std::move(player)) {}
    virtual ~PlayerProxy() = default;
public:
    virtual std::string getName() const override
    {
        return "PlayerProxy";
    }
    
    virtual std::string sendInstantMessage(std::string message) const override 
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        if (hasNetworkConnectivity()) {
            return mPlayer->sendInstantMessage(message);
        } else {
            return "The player has gone offline.";
        }

    }

    bool hasNetworkConnectivity() const
    {
        return true;
    }

private:
    std::unique_ptr<IPlayer> mPlayer;
};

bool informWinner(const IPlayer& player)
{
    auto result = player.sendInstantMessage("You have won! Play again?");
    if (result == "yes") {
        std::cout << player.getName() << " wants to play again." << std::endl;
        return true;
    } else {
        std::cout << player.getName() << " does not want to play again." << std::endl;
        return false;
    }
}

TEST_UNIT(pattern_proxy)
{
    std::unique_ptr<IPlayer> p (new Player());
    PlayerProxy proxyer(std::move(p));
    H_TEST_ASSERT(true == informWinner(proxyer));
}