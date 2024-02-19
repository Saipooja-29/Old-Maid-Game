//Header file 
// File Name: old_maid.h
// Author: Saipooja Kongalla
// Date: 4/3/2023
// Compiler Used: MS build with Microsoft Visual studio c++
// This file contains the definitions of the functions that initialize the deck according to the input and Shuffle it and deal it to players.


#include<iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <random>
#include <numeric> 
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace std;
class Card {
public:
    Card(int val = 1, char s = 'H') : value(val), suit(s) {}
    ~Card() {}
    int value;
    char suit;
    int get_value() const { return value; }
    char get_suit() const { return suit; }
    friend bool operator== (const Card& crd1, const Card& crd2);
    friend bool operator== (const Card& crd1, const int crd2_val);
    friend bool operator> (const Card& crd1, const Card& crd2);
    friend bool operator< (const Card& crd1, const Card& crd2);
};


class Deck {
private:
    vector<string> input_text;
public:
    Deck() { cards = {}; input_text = {};}
    ~Deck() { cards.clear(); input_text.clear(); }
    Card card;
    vector<Card> cards;
    void extract_constrains();
    void makeDeck();
    void shuffleDeck();
    void clearDeck() { cards.clear(); input_text.clear(); }
    friend ifstream& operator>>(ifstream& ifs, Deck& deck_int);
    friend ostream& operator<<(ostream& os, Deck& deck_int);
    //friend ofstream& operator<<(ofstream& ofs, Deck& deck_int);
    friend vector<Card> findDuplicates(std::vector<Card> const& vec);

};

void printHand(vector<Card>& hand);

class Player {

public:
    Player(string ID) { PID = ID; hand = {}; };
    Player(string ID, vector<Card> ph) { PID = ID; hand = ph; };
    ~Player() {}
    //virtual ~Player() {}
    int players_num = 2;
    string player_name;
    vector<string> player_ID;
    string PID;
    vector<Card> hand;
    Card selected_card;
    int index;
    bool isOldMaid = false;
    void check_pairs_remove(vector<Card>& p);
    //void pick_card(int previousPlayer, int index);
    void prepare_cards_for_next_player();
    //virtual void play(Card cardToPick);
    virtual int play(vector<Card> prevPlayerhand) = 0;//{ return 0; };
    void removeCard(int ind);
    virtual int getPickIndex() { return 0; }
    virtual bool isLoser() = 0;

};

class Left_Picker :public Player
{
private:
    int index=0;
public:
    Left_Picker(const string ID) :Player(ID) {}
    Left_Picker(const string ID, vector<Card> ph) :Player(ID, ph) {}
    //virtual void play(Card cardToPick);
    virtual int play(vector<Card> prevPlayerhand);
    //int index;
    int getPickIndex() { return index; }
    virtual bool isLoser() { return isOldMaid; }
};

class Right_Picker :public Player 
{
private:
    int index = Player::players_num - 1;
public:
    Right_Picker(const string ID) :Player(ID) {}
    Right_Picker(const string ID, vector<Card> ph) :Player(ID, ph) {}
    //virtual void play(Card cardToPick);
    virtual int play(vector<Card> prevPlayerhand);
    //int index = players_num - 1;
    int getPickIndex() { return index; }
    virtual bool isLoser() { return isOldMaid; }
};

class Random_Picker :public Player
{
private:
    int index=0;
public:
    Random_Picker(const string ID) :Player(ID) {}
    Random_Picker(const string ID, vector<Card> ph) :Player(ID, ph) {}
    //virtual void play(Card cardToPick);
    virtual int play(vector<Card> prevPlayerhand);
    //int index;
    int getPickIndex() { return index; }
    virtual bool isLoser() { return isOldMaid; }
};

class Shuffler :public Player
{
private:
    int index = rand() % 10;
public:
    Shuffler(const string ID) :Player(ID) {}
    Shuffler(const string ID, vector<Card> ph) :Player(ID, ph) {}
    //virtual void play(Card cardToPick);
    virtual int play(vector<Card> prevPlayerhand);
    int getPickIndex();
    //int index;
    virtual bool isLoser() { return isOldMaid; }
};

class OldMaidGame {
public:
    //OldMaidGame() {};
    OldMaidGame(int pnum = 2) :players_num(pnum) { }//players_info[0] = {};}
    OldMaidGame(Deck& d, int pnum=2);
    //~OldMaidGame() {};
    Deck deck;
    ofstream print;
    int players_num;
    map<int,string> player_num_type;
    //Player player_obj;
    Player* players_info[8];
    void decide_players();// int lp, int rp, int ranp, int s);
    void deal_cards();
    int numrounds = 0;
    int loser = 0;
    void start_game();
    vector<int> input_vals;
    friend ifstream& operator>>(ifstream& ifs, OldMaidGame& game_obj);
    friend ofstream& operator<<(ofstream& ofs, OldMaidGame& game_obj);
};  

//Player* prepare_player(int playersnum,vector<int> input);

class statisticKeeper {
private:
    int totalGamesPlayed;
    vector<int> numPlayersPerGame;
    vector<int> numRoundsPlayedPerGame;
    map<string, int> numPlayersByType;
    map<string, int> numLosersByType;
public:
    statisticKeeper() : totalGamesPlayed(0) {}
    void recordGame(int numPlayers, int lost_player_num, int rounds, map<int, string>& players);
    int getTotalGamesPlayed() const;
    int getTotalNumPlayers() const;
    int getMaxNumPlayers() const;
    int getMinNumPlayers() const;
    double getAverageNumPlayers() const;
    int getNumPlayersByType(std::string type) const;
    int getNumLosersByType(std::string type) const;
    int getMaxNumRoundsPlayed() const;
    int getMinNumRoundsPlayed() const;
    double getAverageNumRoundsPlayed() const;
    void printNumPlayersByType() const;
    void printNumLosersByType() const;
};

class CardGameSimulator {

public:
    CardGameSimulator(int ng = 1)
        :numgames(ng), inputfile1("input.txt"), inputfile2("input2.txt"), outputfile("output.txt") {}

    int numgames;
    int pmin = 2, pmax = 8, players_count = 2;
    ofstream file_out;
    string inputfile1, inputfile2, outputfile;
    statisticKeeper stats;
    OldMaidGame game;
    void get_user_input();
    void play_games();
    void display_statistics();

};

