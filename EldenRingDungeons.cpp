#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

class Weapon{
private:
    std::string Name;
    std::string Type;
public:
    /* Constructors */
    Weapon() : Name(""), Type("") {}
    Weapon(const std::string& name, const std::string& type)
    : Name(name), Type(type) {}

    /* Getters */
    std::string getName() const{
        return Name;
    }
    std::string getType() const{
        return Type;
    }
};

class Tarnished{
private:
    std::string Name;
    int Hp;
    int Ap;
    Weapon weapon;  //Tarnished's weapon
    int Gold;
    int Healing_potions;
public:
    /* Constructors */
    Tarnished() : Name(""), Hp(0), Ap(0), Gold(0), Healing_potions(10) {}
    Tarnished(const std::string& name, int hp, const Weapon& weapon)
        : Name(name), Hp(hp), Ap(0), weapon(weapon), Gold(0), Healing_potions(10) {}

    /* Getters */
    std::string getName() const{
        return Name;
    }
    int getHp() const{
        return Hp;
    }
    int getAp() const{
        return Ap;
    }
    Weapon getWeapon() const{
        return weapon;
    }
    int getGold() const{
        return Gold;
    }
    int getHealingPotions() const{
        return Healing_potions;
    }

    void getDamage(int damage){  //Method to take damage
        Hp -= damage;
        if (Hp < 0){
            Hp = 0;
        }
    }
    void heal(){  //Method to heal
        if (Healing_potions > 0){
            Hp += 150;
            std::cout << "You Consumed a Healing Potion!" << std::endl;
        }
        else{
            std::cout << "No Potions Left!" << std::endl;
        }
        Healing_potions--;  //Decrease potions every use
    }
    void takeGold(int value){  //Method to take gold from Npcs
        Gold += value;
        if (Gold > 200){
            std::cout << "You Upgraded Your Armor!" << std::endl;
            Hp += 150;
            Gold -= 200;
        }
    }
    void specialAttack(){  //Method of special attack based on the weapon's type
        if (weapon.getType() == "Greatsword"){
            Ap = 500;
        }
        else if (weapon.getType() == "Sword"){
            Ap = 300;
        }
        else if (weapon.getType() == "Spear"){
            Ap = 250;
        }
        else{
            return;
        }
    }
    void lightAttack(){  //Method of light attack based on the weapon's type
        if (weapon.getType() == "Greatsword"){
            Ap = 50;
        }
        else if (weapon.getType() == "Sword"){
            Ap = 100;
        }
        else if (weapon.getType() == "Spear"){
            Ap = 150;
        }
        else{
            return;
        }
    }
};

class Boss{
private:
    std::string Name;
    int Hp;
    int Ap;
public:
    /* Constructor */
    Boss(const std::string& name, int hp, int ap)
        : Name(name), Hp(hp), Ap(ap) {}

    /* Getters */
    std::string getName() const{
        return Name;
    }
    int getHp() const{
        return Hp;
    }
    int getAp() const{
        return Ap;
    }
    void getDamage(int damage){  //Method to take damage
        Hp -= damage;
        if (Hp < 0){
            Hp = 0;
        }
    }
};

class Npc{
private:
    std::string Name;
    int Gold;
public:
    /* Constructor */
    Npc(const std::string& name, int gold) : Name(name), Gold(gold) {}

    /* Getters */
    std::string getName() const{
        return Name;
    }
    int getGold() const{
        return Gold;
    }

};

class EldenRing{
private:
    Tarnished tarnished;
    std::vector<Boss> bosses;
    std::vector<Npc> npcs;

    void explore(){  //Method that chooses the event that happens
        int event = rand() % 2;
        if (event == 0){
            if (!bosses.empty()){
                encounterBoss();
            }
        }
        else{
            if (!npcs.empty()){
                talkWithNpc();
            }
        }
    }
    void encounterBoss(){
        int boss_index = rand() % bosses.size();
        Boss& boss = bosses[boss_index];  //Random Boss from the vector
        std::cout << "You have encountered " << boss.getName() << "!" << std::endl;
        while (boss.getHp() > 0 && tarnished.getHp() > 0){  //While both the tarnished and the boss is alive
            std::cout << tarnished.getName() << " Hp: " << tarnished.getHp() << "  Gold: " << tarnished.getGold() << " Potions: " << tarnished.getHealingPotions() << std::endl;  //Display tarnished's stats
            std::cout << boss.getName() << " Hp: " << boss.getHp() << std::endl;  //Display boss's stats
            std::cout << "1 - Special Attack" << std::endl;
            std::cout << "2 - Light Attack" << std::endl;
            std::cout << "3 - Heal" << std::endl;
            std::cout << "4 - Dodge" << std::endl;
            int choice;
            std::cin >> choice;
            if (choice == 1){
                tarnished.specialAttack();  //Set Ap based on the weapon's type
                boss.getDamage(tarnished.getAp());  //The boss gets hit by tarnished
                if (boss.getHp() > 0){  //If the boss is still alive
                    tarnished.getDamage(boss.getAp());  //Tarnished gets hit by boss
                }
                else{  //The boss is dead
                    std::cout << "You Defeated " << boss.getName() << "!" << std::endl;
                    bosses.erase(bosses.begin() + boss_index);  //Erase this boss from the vector
                }
            }
            else if (choice == 2){
                tarnished.lightAttack();  //Set Ap based on the weapon's type
                boss.getDamage(tarnished.getAp());  //The boss gets hit by tarnished
                if (boss.getHp() > 0){  //If the boss is still alive
                    tarnished.getDamage(boss.getAp());  //Tarnished gets hit by boss
                }
                else{  //The boss is dead
                    std::cout << "You Defeated " << boss.getName() << "!" << std::endl;
                    bosses.erase(bosses.begin() + boss_index);  //Erase this boss from the vector
                }
            }
            else if (choice == 3){
                tarnished.heal();
            }
            else if (choice == 4){
                std::cout << boss.getName() << " Missed!" << std::endl;
            }
            else{
                std::cout << "Invalid Choice. Please Try Again" << std::endl;
            }
        }
    }
    void talkWithNpc(){
        int npc_index = rand() % npcs.size();
        Npc& npc = npcs[npc_index];  //Random Npc from the vector
        std::cout << "You Met " << npc.getName() << ". You Received " << npc.getGold() << " gold!" << std::endl;
        tarnished.takeGold(npc.getGold());
        npcs.erase(npcs.begin() + npc_index);  //Erase this npc from the vector
    }
public:
    /* Constructor */
    EldenRing(const std::string& name, const std::string& weapon_name, const std::string& weapon_type){
        tarnished = Tarnished(name, 800, Weapon(weapon_name, weapon_type));
        bosses = {
            Boss("Mohg", 1750, 120),
            Boss("Messmer", 2000, 150),
            Boss("Malenia", 1800, 110),
            Boss("Radagon", 1900, 130),
            Boss("Godfrey", 2000, 160),
            Boss("Renalla", 1300, 100)
        };
        npcs = {
            Npc("Blaidd", 150),
            Npc("Patches", 1),
            Npc("Ranni", 100),
            Npc("Alexander", 120)
        };
        std::srand(std::time(nullptr));
    }
    void start(){  //Method that starts the game
        std::cout << "***********************************************" << std::endl;
        std::cout << "Welcome to Elden Ring Dungeons" << std::endl;
        std::cout << "***********************************************" << std::endl;
        while (tarnished.getHp() > 0 && !bosses.empty()){ 
            explore();                                      
        }
        if (tarnished.getHp() > 0) {
            std::cout << "***********************************************" << std::endl;
            std::cout << "Congratulations! You have become an Elden Lord" << std::endl;
            std::cout << "***********************************************" << std::endl;
        }
        else{
            std::cout << "***********************************************" << std::endl;
            std::cout << "Game Over. You died." << std::endl;
            std::cout << "***********************************************" << std::endl;
        }                                              
    }
};

int main()
{
    std::cout << "***********************************************" << std::endl;
    std::cout << "Customize Your Character" << std::endl;
    std::cout << "***********************************************" << std::endl;

    std::string name;
    std::cout << "Enter Name: ";
    std::getline(std::cin, name);

    while (true){
        std::cout << "Choose Weapon:" << std::endl;
        std::cout << "1 - Blasphemus Blade(Greatsword)" << std::endl;
        std::cout << "2 - Crystal Sword(Sword)" << std::endl;
        std::cout << "3 - Bolt Of Gransaxx(Spear)" << std::endl;
        int choice;
        std::cin >> choice;

        if (choice == 1){  //Choosing the weapon in order to construct the object 
            EldenRing game(name, "Blasphemous Blade", "Greatsword");
            game.start();
            break;   
        }
        else if (choice == 2){
            EldenRing game(name, "Crystal Sword", "Sword");
            game.start();
            break;
        }
        else if (choice == 3){
            EldenRing game(name, "Bolt Of Gransaxx", "Spear");
            game.start();
            break;
        }
        else{
            std::cout << "Invalid Choice. Please Try Again" << std::endl;
        }
    }

    return 0;
}