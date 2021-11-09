#include <iostream>
#include <entt.hpp>
#include <chrono>

constexpr uint32_t COUNT{ 1000000 };

class Monster
{
public:
    Monster() = default;
    virtual ~Monster() = default;

    [[nodiscard]] virtual int getAttackPoints() const = 0;
};

class Wolf: public Monster
{
public:
    Wolf() = default;
    ~Wolf() override = default;

    [[nodiscard]] int getAttackPoints() const override
    {
        return baseAttack;
    }
private:
    int baseAttack{ 5 };
};

class Wolf2 : public Monster
{
public:
    Wolf2() = default;
    ~Wolf2() override = default;

    [[nodiscard]] int getAttackPoints() const override
    {
        return baseAttack;
    }
private:
    int baseAttack{ 2 };
};

class Orc : public Monster
{
public:
    Orc() = default;
    ~Orc() override = default;

    [[nodiscard]] int getAttackPoints() const override
    {
        return baseAttack;
    }
private:
    int baseAttack{ 10 };
};

class Dragon : public Monster
{
public:
    Dragon() = default;
    ~Dragon() override = default;

    [[nodiscard]] int getAttackPoints() const override
    {
        return baseAttack;
    }
private:
    int baseAttack{ 100 };
};

void attack(const Monster* monster)
{
    const auto temp = monster->getAttackPoints() * 5;
    const auto temp2 = temp;
}

struct MonsterStruct
{
    int baseAttack{ 5 };
    MonsterStruct() = default;
    MonsterStruct(const int attack): baseAttack(attack) {}
    [[nodiscard]] int getAttackPoints() const
    {
        return baseAttack;
    }
};

void attackS(const MonsterStruct* monster)
{
    const auto temp = monster->getAttackPoints() * 5;
    const auto temp2 = temp;
}

Monster* globalMonster{nullptr};

int main()
{
    std::vector<Monster*> monsters;

    for (auto i{ 0 }; i < COUNT; i++)
    {
        if (i % 4 == 0)
        {
            const auto temp = new Wolf;
            monsters.push_back(temp);
        }
        else if (i % 4 == 1)
        {
            const auto temp = new Wolf2;
            monsters.push_back(temp);
        }
        else if (i % 4 == 2)
        {
            const auto temp = new Orc;
            monsters.push_back(temp);
        }
        else
        {
            const auto temp = new Dragon;
            monsters.push_back(temp);
        }
    }

    std::chrono::nanoseconds avgVirtual{ 0 };
    for (auto it{ 0 }; it < 100; it++)
    {
        auto start = std::chrono::steady_clock::now();

        for (const auto& monster : monsters)
        {
            globalMonster = monster;
            attack(globalMonster);
        }

        auto end = std::chrono::steady_clock::now();
        avgVirtual += (end - start);
    }

    avgVirtual /= 10;

    std::cout << "Avf time in milliseconds: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(avgVirtual).count()
        << " ms" << std::endl;

    entt::registry registry;

    for (auto i{ 0 }; i < COUNT; i++)
    {
        const auto entity = registry.create();

        if (i % 4 == 0)
        {
            registry.emplace<MonsterStruct>(entity, 5);
        }
        else if (i % 4 == 1)
        {
            registry.emplace<MonsterStruct>(entity, 2);
        }
        else if (i % 4 == 2)
        {
            registry.emplace<MonsterStruct>(entity, 10);
        }
        else
        {
            registry.emplace<MonsterStruct>(entity, 100);
        }
    }

    std::chrono::nanoseconds avgECS{ 0 };
    for (auto it{ 0 }; it < 100; it++)
    {
        auto start = std::chrono::steady_clock::now();

        const auto view = registry.view<MonsterStruct>();

        for (const auto entity : view)
        {
            const auto& monster = view.get<MonsterStruct>(entity);
            attackS(&monster);
        }

        auto end = std::chrono::steady_clock::now();
        avgECS += (end - start);
    }

    avgECS /= 10;

    std::cout << "Avf time in milliseconds: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(avgECS).count()
        << " ms" << std::endl;

    return 0;
}
