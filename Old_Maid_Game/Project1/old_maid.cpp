// File Name: old_maid.cpp
// Author: Saipooja	Kongalla
// Date: 4/3/2023
// Compiler Used: MS build with Microsoft Visual studio c++
// This file contains the implementation of the functions that initialize the deck according to the input and Shuffle it and deal it to players.


#include <stdlib.h> 
#include "old_maid.h"

using namespace std;

bool operator== (const Card& crd1, const Card& crd2)
{
    if ((crd1.suit == crd2.suit) && (crd1.value == crd2.value))
        return true;
    else
        return false;
}
bool operator== (const Card& crd1, const int crd2_val)
{
    if (crd1.value == crd2_val)
        return true;
    else
        return false;
}
bool operator> (const Card& crd1, const Card& crd2)
{
    if (crd1.value > crd2.value)
        return true;
    else
        return false;
}
bool operator< (const Card& crd1, const Card& crd2)
{
    if (crd1.value < crd2.value)
        return true;
    else
        return false;
}


ifstream& operator>>(ifstream& ifs, Deck& deck_int)
{
    string text;
    for (int i = 0; i < 3; i++)
    {
        getline(ifs, text);
        deck_int.input_text.push_back(text);
        //cout << deck_int.input_text[i] << endl;
    }

    return ifs;
}

void Deck::extract_constrains()
{
    Card temp_card;
    vector<char> suits_list;
    vector<int> vals_list;
    vector<Card>::iterator invalid;
    string temp;
    int nocards;
    char str;


    temp = input_text[1][2];
    nocards = stoi(temp);
    
    str = input_text[1][0];
    
    // separating suits and values from the string to form a card and use that to remove from deck.
    for (int i = 0; i < input_text[2].length(); i++)
    {
        // Splitting Suits from input string 
        if(isalpha(input_text[2][i]))
            suits_list.push_back(input_text[2][i]);
        // Splitting values of cards from input string 
        if ((i!=0) && (input_text[2][i-1] == ' ') && isdigit(input_text[2][i]))
        {

            temp = input_text[2][i];
            if (input_text[2][i + 1] != ' ') temp += input_text[2][i+1];
            vals_list.push_back(stoi(temp));

        }
        
    }

    for (int i = 0; i < nocards; i++)
    {
        temp_card.suit = suits_list.at(i);
        temp_card.value = vals_list.at(i);
        if (str == 'r') //Removing the cards that are mentioned in the input
        {
            invalid = remove(cards.begin(), cards.end(), temp_card);
            cards.erase(invalid, cards.end());
        }
        else if (str == 'a') cards.push_back(temp_card); // Adding joker card that is mentioned in the inout file.
    }
    
}

void Deck::makeDeck() {
    for (int i = 1; i <= 13; i++) {
        cards.push_back(Card(i, 'C'));
        cards.push_back(Card(i, 'D'));
        cards.push_back(Card(i, 'H'));
        cards.push_back(Card(i, 'S'));
    }

    cout << "\n*******Deck initialized:" << endl;
    extract_constrains();
}

void Deck::shuffleDeck()
{
    cout << "\n*******Deck after Shuffling:" << endl;
    random_shuffle(cards.begin(), cards.end());
}

void printHand(vector<Card>& hand) {
    if (hand.size() == 0) cout << "\tEmpty Hand\n";
    else 
    {
        int counter = 0;
        for (Card i : hand)
        {
            if (counter % 13 == 0) cout << endl;
            cout << "\t" << i.value << i.suit;
            counter++;
        }
        cout << endl;
    }
}

template<typename T>

T print_output(T ofs, vector<Card>& hand) 
{
    string check = " ";
    int counter = 0;
    for (Card i : hand)
    {
        if (counter % 14 == 0) ofs << endl;
        ofs << "\t" << i.value << i.suit;
        counter++;
    }
    ofs << endl;
    return ofs;
}

ostream& operator<<(ostream& os, Deck& deck_int)
{
    //printHand(deck_int.cards);
    os << "Size of the Deck is: " << deck_int.cards.size() << endl;
    print_output<ostream&>(os, deck_int.cards);
    return os;
}


//output file stream:
 ofstream& operator<<(ofstream& ofs, Deck& deck_int)
{
    /*ofs << "Size of the Deck is: " << deck_int.cards.size() << endl;
    print_output<ostream&>(ofs, deck_int.cards);*/

    ofs << "\n*******Deck after Shuffling:" << endl;
    print_output<ofstream&>(ofs, deck_int.cards);

    return ofs;
}


template<typename T>
std::vector<T> findDuplicates(std::vector<T> const& vec)
{
    map<T, int> freq;
    for (T const& i : vec) {
        freq[i]++;
    }

    std::vector<T> duplicates;
    for (auto const& pair : vec) {
        if(freq[pair] > 1) {
            duplicates.push_back(pair);
        }
    }

    return duplicates;
}

void Player::check_pairs_remove(vector<Card> & p)
{
    int counter;
    //unordered_set<Card> removed_pairs;
    vector<Card> duplicates = findDuplicates(p);
    cout << "\n\n\t\t Observed Pairs: ";
    for (auto& i : duplicates) {
        cout <<i.value<<i.suit << '\t';
    }
    cout << endl;

    bool hasPairs = true;
    set<int> setObj;
    for (Card c : p)
    {
        setObj.insert(c.value);
    }

    for (int c : setObj)
    {
        counter = count(p.begin(), p.end(), c);
        
        if ((counter > 1) )
        {   
            auto ind = find(p.begin(), p.end(), c) - p.begin();
            Card temp = p[ind];
            auto end_i = remove(p.begin(), p.end(), c);
            p.erase(end_i, p.end());
            if (counter == 3)
            {
                p.insert(p.begin() + ind, temp);
            }
        }
        
    }
    //cout << "check pairs funtion passed";
}

void Player::removeCard(int index) {
    //Card selectedCard = hand[index];
    hand.erase(hand.begin() + index);
    cout << "\t\tremoved card at index- " << index;
    //return selectedCard;
}

int Left_Picker::play(vector<Card> prevPlayerhand)
{
    selected_card = prevPlayerhand[getPickIndex()];
    int i = rand() % hand.size() + 1;
    hand.insert(hand.begin() + i, selected_card);
    Player::check_pairs_remove(hand);
    return index;
}
int Right_Picker::play(vector<Card> prevPlayerhand)
{
    //cout << "before index assigned!!\n";
    index = prevPlayerhand.size() - 1;
    //cout << "After index decided: index - " << index << endl;
    selected_card = prevPlayerhand[index];
    int i = rand() % hand.size() + 1;
    hand.insert(hand.begin() + i, selected_card);
    Player::check_pairs_remove(hand);
    return index;
}
int Random_Picker::play(vector<Card> prevPlayerhand)
{
    index = rand() % prevPlayerhand.size();
    selected_card = prevPlayerhand[index];
    int i = rand() % hand.size() + 1;
    hand.insert(hand.begin() + i, selected_card);
    Player::check_pairs_remove(hand);
    return index;
}
int Shuffler::play(vector<Card> prevPlayerhand)
{
    //index = rand() % hand.size();
    if (index >= prevPlayerhand.size())
        index = 0;
    selected_card = prevPlayerhand[index];
    int i = rand() % hand.size() + 1;
    hand.insert(hand.begin() + i, selected_card);
    Player::check_pairs_remove(hand);
    Player::prepare_cards_for_next_player();
    //cout << "shuffler shuffled!";
    return index;
}
int Shuffler::getPickIndex() {
    //index = rand() % hand.size();
    if (index >= hand.size())
        return 0;
    return index;
}
void Player::prepare_cards_for_next_player()
{
    random_shuffle(hand.begin(), hand.end());
}

//Player* prepare_player(playersnum, input) {
//
//    Player* p;
//    int id = rand() % 100 + 1;
//    return p;
//    for (int i = 0; i < players_num; i++)
//    {
//        id = rand() % 100 + 1;
//        if (id <= lp) players_info[i] = new Left_Picker("LP");
//        else if (id <= lp + rp) players_info[i] = new Right_Picker("RP");
//        else if (id <= lp + rp + ranp) players_info[i] = new Random_Picker("RandP");
//        else if (id <= lp + rp + ranp + s) players_info[i] = new Shuffler("S");
//        player_num_type[i] = players_info[i]->PID;
//        players_info[i]->players_num = players_num;
//    }
//
//}

//Game class
OldMaidGame::OldMaidGame(Deck& d, int pnum) {
    deck = d;
    players_num = pnum;
    //player_info = p;  
}

ifstream& operator>>(ifstream& ifs, OldMaidGame& game_obj)
{
    string input_text;
    //game_obj.input_vals = {};
    //for (int i = 0; i < 3; i++)
    while(ifs.good())
    {
        ifs >> input_text;
        //cout << input_text << endl;
        game_obj.input_vals.push_back(stoi(input_text));
    }

    return ifs;
}
void OldMaidGame::decide_players()//(int lp, int rp, int ranp, int s)
{
    
    int lp = input_vals[2], rp = input_vals[3], ranp = input_vals[4], s = input_vals[5];
    int id=0;
    //player_num_type = {};
    for (int i = 0; i < players_num; i++)
    {
        id = rand() % 100 + 1;
        //cout << lp<<" "<<rp<<" "<<ranp<<" "<<s << "  id= " << id << "\t";
        if (id <= lp) players_info[i] = new Left_Picker("LP");
        else if (id <= lp+rp) players_info[i] = new Right_Picker("RP");
        else if (id <= lp+rp+ranp) players_info[i] = new Random_Picker("RandP");
        else if (id <= lp+rp+ranp+s) players_info[i] = new Shuffler("S");
        player_num_type[i]=players_info[i]->PID;
        
        players_info[i]->players_num = players_num;
    }
    
}

void OldMaidGame::deal_cards()
{
    int cnum = 0;

    //cout << "\nNumber of Player = " << players_num << endl;

    while (cnum < deck.cards.size())
    {
        for (int i = 0; i < players_num; i++)
        {
            players_info[i]->hand.push_back(deck.cards[cnum]);
            cnum++;
            if (cnum == deck.cards.size()) break;
        }
    }

    cout << "\n\nNumber of Player = " << players_num << endl;
    for (int i = 0; i < players_num; i++)
    {
        cout << "\n*******Player " << i + 1 << "of ID: "<<players_info[i]->PID<<" cards: ****" << endl;
        printHand(players_info[i]->hand);
    }

    for (int i = 0; i < players_num; i++)
    {
        cout << "\n*******Player " << i + 1 << "of ID: "<< players_info[i]->PID <<" ******* \n";
        players_info[i]->check_pairs_remove(players_info[i]->hand);
        cout << "\nCARDS: ";
        printHand(players_info[i]->hand);
    }

}

void OldMaidGame::start_game()
{
    deck.makeDeck();
    cout << deck;
    deck.shuffleDeck();
    cout << deck;
    decide_players();
    deal_cards();

    // playing the game
    int currentPlayer = 0;
    int previousPlayer = players_num - 1;
    vector<Card> prevPlayerHand;
    int loopcounter = 0;
    int curr_size;
    vector<Card> current_hand;
    numrounds += 1;
    bool OldMaid = false;
    cout << "\nPairs removed and Starting Game!!\n\nRound " << numrounds << ":\n\n";

    while (!OldMaid)
    {
        int prevci = currentPlayer, prevpi = previousPlayer;

        while (players_info[previousPlayer]->hand.size() == 0)
        {
            //cout << "Empty! so going to next previous player";
            previousPlayer = (previousPlayer - 1 + players_num) % players_num;
        }

        while (players_info[currentPlayer]->hand.size() == 0)
        {
            currentPlayer = (currentPlayer + 1) % players_num;
        }
        if (previousPlayer == currentPlayer) {
            OldMaid = true; break;
        }

        current_hand = players_info[currentPlayer]->hand;
        cout << "\nPlayer" << currentPlayer << "-----Player Type : " << players_info[currentPlayer]->PID << " -----" << endl;
        print << "\nPlayer" << currentPlayer << "-----Player Type : " << players_info[currentPlayer]->PID << " -----" << endl;
        printHand(current_hand);
        cout << endl;

        cout << "\n\t\tTaking card from Player #" << previousPlayer << " with ID : " << players_info[previousPlayer]->PID;
        prevPlayerHand = players_info[previousPlayer]->hand;
        int index = players_info[currentPlayer]->play(prevPlayerHand);
        players_info[previousPlayer]->removeCard(index);
        cout << "\n\t\tAfter taking card and removing pairs" << endl;
        printHand(players_info[currentPlayer]->hand);
        if (currentPlayer > (currentPlayer + 1) % players_num)
        {
            numrounds++;
            cout << "\n\nRound " << numrounds << ":\n\n";
        }
        currentPlayer = (currentPlayer + 1) % players_num;
        previousPlayer = (currentPlayer - 1 + players_num) % players_num;
        /*if ((prevci == previousPlayer) && (prevpi == currentPlayer))
        {*/
        //loopcounter++;
        //cout << "\n\t number of repetetive loops: " << loopcounter;
        if (numrounds > 111) { cout << "too many loops:"; break; }
        //}
    }
    cout << "\n\n\t\tGAME OVER!!!!!!\n\n";

    cout << "Finally hand of each player after " << numrounds << " rounds for total players : " << players_num << " looks like : \n";

    for (int i = 0; i < players_num; i++)
    {
        cout << "\n*******Player****" << i + 1 << " cards:" << endl;
        printHand(players_info[i]->hand);
        if (players_info[i]->hand.size() == 1 && players_info[i]->hand[0].value == 12)
        {
            cout << "--Player" << i + 1 << " is the OLD MAID!!!\n";
            loser = i;
            players_info[i]->isOldMaid = true;
        }
    }

}


//output file stream:
 ofstream& operator<<(ofstream& ofs, OldMaidGame& game_obj)
{

    ofs << "\nNumber of Player = " << game_obj.players_num << endl;
    for (int i = 0; i < game_obj.players_num; i++)
    {
        ofs << "\n******Player " << i + 1 << "of ID: " << game_obj.players_info[i]->PID << "******\nCARDS:" << endl;
        print_output<ofstream&>(ofs , game_obj.players_info[i]->hand);
    }
    
    return ofs;
}

void CardGameSimulator::get_user_input()
{
    cout << "\nEnter Number of games to be played: ";
    cin >> numgames;
    cout << "\nEnter name of input file1(.txt format): ";
    cin >> inputfile1;
    cout << "\nEnter name of input file2(.txt format): ";
    cin >> inputfile2;
    cout << "\nEnter name of output file(.txt format): ";
    cin >> outputfile;

    //cout << "end";
}

void CardGameSimulator::play_games()
{

    //ofstream file_out(outputfile);

    for (int i = 0; i < numgames; i++)
    {
        ifstream file_in(inputfile1);
        ifstream file_in2(inputfile2);
        OldMaidGame game;
        cout << "\n\t\tPlaying Game " << i + 1 << " \n\n";

        if (file_in.is_open())
        {
            file_in >> game.deck;
        }

        if (file_in2.is_open())
        {
            file_in2 >> game;
        }
        int pmin = game.input_vals[0];
        int pmax = game.input_vals[1];
        int players_count = rand() % (pmax - 1) + pmin;
        game.players_num = players_count;
        game.start_game();
        stats.recordGame(game.players_num, game.loser, game.numrounds, game.player_num_type);
        cout << endl;
        //file_in.close(); file_in2.close();
    }
}

void CardGameSimulator::display_statistics()
{
    cout <<"\n \t STATISTICS \n"
        << "\n\nTotal number of games played:\t" << stats.getTotalGamesPlayed()
        << "\n\nTotal number of players generated:\t" << stats.getTotalNumPlayers()
        << "\n\nMaximum number of players generated for a game:\t" << stats.getMaxNumPlayers()
        << "\n\nMinimum number of players generated for a game:\t" << stats.getMinNumPlayers()
        << "\n\nAverage number of players generated for a game:\t" << stats.getAverageNumPlayers()
        << "\n\nMaximum number of rounds played in a game:\t" << stats.getMaxNumRoundsPlayed()
        << "\n\nMinimum number of rounds played in a game:\t" << stats.getMinNumRoundsPlayed()
        << "\n\nAverage number of rounds played in a game:\t" << stats.getAverageNumRoundsPlayed()
        << endl;
    cout << "\nNumber of players generated based on Type of Player:\n";
    stats.printNumPlayersByType();
    cout << "\n\nLoser Statistic based on Type of Player:\n";
    stats.printNumLosersByType();
}


// statistics keeper class 

void statisticKeeper::recordGame(int numPlayers,int lost_player_num,int rounds, map<int, string>& players) {
    totalGamesPlayed++;
    numPlayersPerGame.push_back(numPlayers);
    numRoundsPlayedPerGame.push_back(rounds);
    for (const auto& player : players) {
        numPlayersByType[player.second]++;
        if (player.first== lost_player_num) {
            numLosersByType[player.second]++;
        }
    }
}

int statisticKeeper::getTotalGamesPlayed() const {
    return totalGamesPlayed;
}

int statisticKeeper::getTotalNumPlayers() const {
    if (numPlayersPerGame.empty()) {
        return 0;
    }
    int sum = accumulate(numPlayersPerGame.begin(), numPlayersPerGame.end(), 0);
    return sum;
}

int statisticKeeper::getMaxNumPlayers() const {
    return *max_element(numPlayersPerGame.begin(), numPlayersPerGame.end());
}

int statisticKeeper::getMinNumPlayers() const {
    return *min_element(numPlayersPerGame.begin(), numPlayersPerGame.end());
}

double statisticKeeper::getAverageNumPlayers() const {
    if (numPlayersPerGame.empty()) {
        return 0;
    }
    double sum = accumulate(numPlayersPerGame.begin(), numPlayersPerGame.end(), 0.0);
    return sum / numPlayersPerGame.size();
}

int statisticKeeper::getNumPlayersByType(string type) const {
    auto it = numPlayersByType.find(type);
    if (it == numPlayersByType.end()) {
        return 0;
    }
    return it->second;
}

int statisticKeeper::getNumLosersByType(string type) const {
    auto it = numLosersByType.find(type);
    if (it == numLosersByType.end()) {
        return 0;
    }
    return it->second;
}

int statisticKeeper::getMaxNumRoundsPlayed() const {
    return *max_element(numRoundsPlayedPerGame.begin(), numRoundsPlayedPerGame.end());
}

int statisticKeeper::getMinNumRoundsPlayed() const {
    return *min_element(numRoundsPlayedPerGame.begin(), numRoundsPlayedPerGame.end());
}

double statisticKeeper::getAverageNumRoundsPlayed() const {
    if (numRoundsPlayedPerGame.empty()) {
        return 0;
    }
    double sum = accumulate(numRoundsPlayedPerGame.begin(), numRoundsPlayedPerGame.end(), 0.0);
    return sum / numRoundsPlayedPerGame.size();
}

void statisticKeeper::printNumPlayersByType() const {
    for (auto type : numPlayersByType) cout << "Type " << type.first << "\t" << type.second<<endl;
}

void statisticKeeper::printNumLosersByType() const {
    for (auto type : numLosersByType) cout << "Type " << type.first << "\t" << type.second<<endl;
}