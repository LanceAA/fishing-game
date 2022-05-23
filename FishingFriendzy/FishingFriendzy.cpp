/*
Author: Christopher Meyring
Date: 05-13-2022
Purpose: A fishing game in which the player can fish, as well as purchase items
from the shop that will increase the chance of successully catching a fish.
*/
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

mt19937 generator(random_device{}());

class Inventory {
private:
    int worms;
    int money;
    float multiplier;
    vector<string> toolName;

public:
    //default constructor
    Inventory() {
        worms = 8;
        money = 50;
        multiplier = 1;
    }

    //custom constructor
    Inventory(int w, int m, float multi) {
        worms = w;
        money = m;
        multiplier = multi;
    }

    void addWorms(int w) {
        worms += w;
    }

    void subtractWorms(int w) {
        worms -= w;
    }

    void subtractMoney(int m) {
        money -= m;
    }

    void addMoney(int m) {
        money += m;
    }

    void compoundMultiplier(int m) {
        multiplier += m;
    }

    //append string to end of toolName
    void addToolName(string s) {
        toolName.push_back(s);
    }

    //checks player inventory against a tool name to see if it exists
    bool compareToolName(string s) {
        if (find(toolName.begin(), toolName.end(), s) != toolName.end()) {
            return true;
        }
        return false;
    }

    int getWorms() {
        return worms;
    }

    int getMoney() {
        return money;
    }

    int getMultiplier() {
        return multiplier;
    }
};

char random_number_char()
{
    //uses a generator to select a random number inclusively between 0 and 9
    static uniform_int_distribution<size_t> distribution('0', '9');
    return distribution(generator);
}

//Provides functionality for the entire fishing section of the game
void fish(Inventory &inv) { //accepts class object by reference in order to make changes
    string option;
    int HIGH_SCORE = 8;
    int MID_SCORE = 6;
    int LOW_SCORE = 4;
    int rand;
    int score;

    //do-while loop to keep the player inside the fishing interface
    do {
        cout << "\nYou have " << inv.getWorms() << " worms. What would you like to do?\n\t1 - Cast Pole\n\t2 - Leave\n>";
        cin >> option;

        if (option == "1") {

            if (inv.getWorms() < 1) {
                cout << "\nYou have no worms!\n";
                option = "2";
            }
            else {
                inv.subtractWorms(1);
                rand = random_number_char() - 48; //converts from char to int on ASCII table
                score = rand + inv.getMultiplier();

                cout << "\nYou cast your line...\n";

                //setting bounds and rewards for successfully catching a fish
                if (score >= HIGH_SCORE) {
                    inv.addMoney(20);
                    cout << "Big catch! This one is worth a lot. $20 added to your wallet\n";
                    cout << "Wallet total: $" << inv.getMoney() << endl;
                }
                else if (score >= MID_SCORE) {
                    inv.addMoney(10);
                    cout << "Decent catch! $10 added to your wallet\n";
                    cout << "Wallet total: $" << inv.getMoney() << endl;
                }
                else if (score >= LOW_SCORE) {
                    inv.addMoney(5);
                    cout << "I mean, it's a fish. I think. $5 added to your wallet\n";
                    cout << "Wallet total: $" << inv.getMoney() << endl;
                }
                else {
                    cout << "Nothing\n";
                }
            }

        }
        //input validation
        else if (option != "2") {
            cout << "That is not a valid input!";
        }
    } while (option != "2");
}

//Provides functionality for the the entire shop interface
void shop(Inventory &inv, bool &endGame) {
    string option;

    cout << "\nWelcome to the shop! Give me all your money! - I mean, buy something!";

    //do-while loop to keep user in function until requested
    do {
        cout << "\n\nWallet: $" << inv.getMoney();
        cout << "\nWhat would you like to do?";
        cout << "\n\t1 - Buy more worms ($5)";
        cout << "\n\t2 - Buy silver pole ($30)";
        cout << "\n\t3 - Buy gold pole ($50)";
        cout << "\n\t4 - Buy better bait ($25)";
        cout << "\n\t5 - Buy fish tracker ($100)";
        cout << "\n\t6 - Leave";
        cout << "\n> ";

        cin >> option;

        if (option == "1") {

            //if user runs out of worms and money, then end game
            if (inv.getWorms() < 1 && inv.getMoney() < 5) {
                cout << "\nYou have no money, get out!";
                endGame = true;
                option = "6";
            }
            //else, purchase worm
            else {
                inv.addWorms(1);
                inv.subtractMoney(5);

                cout << "\nHere you go!";
                cout << "\nWorms: " << inv.getWorms();
            }
        }
        else if (option == "2") {
            //money check
            if (inv.getMoney() < 30) {
                cout << "\nYou can't afford that.";
            }
            //checks if tool exists in player inventory
            else if (inv.compareToolName("silver pole")) {
                cout << "\nYou already have this item!";
            }
            //adds silver pole to inventory
            else {
                inv.addToolName("silver pole");
                inv.compoundMultiplier(.03);
                inv.subtractMoney(30);
                cout << "\nEnjoy your purchase!";
            }
        }
        else if (option == "3") {
            if (inv.getMoney() < 50) {
                cout << "\nYou can't afford that.";
            }
            else if (inv.compareToolName("gold pole")) {
                cout << "\nYou already have this item!";
            }
            else {
                inv.addToolName("gold pole");
                inv.compoundMultiplier(.06);
                inv.subtractMoney(50);
                cout << "\nEnjoy your purchase!";
            }
        }
        else if (option == "4") {
            if (inv.getMoney() < 25) {
                cout << "\nYou can't afford that.";
            }
            else if (inv.compareToolName("better bait")) {
                cout << "\nYou already have this item!";
            }
            else {
                inv.addToolName("better bait");
                inv.compoundMultiplier(.02);
                inv.subtractMoney(25);
                cout << "\nEnjoy your purchase!";
            }
        }
        else if (option == "5") {
            if (inv.getMoney() < 100) {
                cout << "\nYou can't afford that.";
            }
            else if (inv.compareToolName("fish tracker")) {
                cout << "\nYou already have this item!";
            }
            else {
                inv.addToolName("fish tracker");
                inv.compoundMultiplier(.07);
                inv.subtractMoney(100);
                cout << "\nEnjoy your purchase!";
            }
        }
        //input validation
        else if (option != "6") {
            cout << "\nNot a valid input!";
        }

    } while (option != "6");
}

int main()
{
    string option;
    bool endGame = false;
    Inventory inv = Inventory(); //create instance of Inventory class

    cout << "Welcome to Fishing Friendzy!";

    do {
        cout << "\nWhat would you like to do?";
        cout << "\n\t1 - Fish";
        cout << "\n\t2 - Shop";
        cout << "\n\t3 - End Game";
        cout << "\n> ";
        cin >> option;

        if (option == "1") {
            fish(inv);
        }
        else if (option == "2") {
            shop(inv, endGame);
        }
        else if (option == "3") {
            cout << "\n\nI'll see you again, human.\n";
        }
        else {
            cout << "\nNot a valid input!";
        }

        //code block is triggered when player is out of money and worms
        if (endGame) {
            cout << "\n\nWormless and poor, you wander the lands in search of new purpose.";
            cout << "\n-----------";
            cout << "\nGAME OVER";
            cout << "\n-----------\n";
        }

    } while (option != "3" && !endGame);
}