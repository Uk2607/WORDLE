#include<bits/stdc++.h>
#include<windows.h>
#include<ctime>
#include<iomanip>
using namespace std;

// GLOBAL
// ======================================================
string _WORD_ = "";
int guessNo = 0;
// ======================================================

void setConsoleColor(WORD c) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); }

void instructions() {
    setConsoleColor(6);
    cout<<"There is a five letter word you need to guess.\n";
    cout<<"And you have got 6 chances to guess it.\n";
    cout<<"Suerly we will help:\n";
    cout<<"1. If the the word contains the same character but\n   in different position then it will be shown in yellow\n";
    cout<<"2. If the word contains the same character and you guessed\n   its correct position then it will be highlighted in green\n";
    cout<<"3. If word doesn't any of the character you guessed\n   the it will we shown naturally.\n\n";
    cout<<"Example::\n";
    cout<<"Let the word is \'LIGHT\'\n";
    cout<<"And you guessed \'SALET\'\n";
    cout<<"It will be shown as\n";
    setConsoleColor(7);
    cout<<" S ";
    cout<<" A ";
    setConsoleColor(96);
    cout<<" L ";
    setConsoleColor(7);
    cout<<" E ";
    setConsoleColor(32);
    cout<<" T ";
    setConsoleColor(7);
    cout<<"\n\n";
}

void resetVariables()
{
    guessNo = 0;
    _WORD_ = "";
}

void updateFreq()
{
    vector<int>freq(6,0);
    ifstream dbFile("db/db.txt");
    string line;
    while(getline(dbFile,line)) freq[line[0]-'1'] = stoi(line.substr(3));
    dbFile.close();

    // for(int i=0;i<freq.size();i++) cout<<i+1<<": "<<freq[i]<<"\n";

    ++freq[guessNo-1];

    ofstream of("db/db.txt", ofstream::trunc);
    for(int i=0;i<freq.size();i++) of<<i+1<<": "<<freq[i]<<"\n";
    of.close();
}

void updateHistory(bool won)
{
    ifstream fin;
    ofstream fout;
    fin.open("db/history.txt");
    fout.open("db/history.txt",ios::app);

    if(fin.is_open())
    {
        auto t = time(nullptr);
        auto tm = *localtime(&t);
        fout << put_time(&tm, "%d-%m-%Y::%H:%M:%S") << " " <<_WORD_ << " " << (won ? "S "+ to_string(guessNo) : "U #") << "\n";
    }
    fin.close();
    fout.close();
}

void printState(vector<string>&guessedWords, vector<vector<WORD>>&state, set<char>&wordCharSet) {
    system("cls");
    setConsoleColor(4);
    cout<<"Guess left :: "<<6-guessNo;
    if(wordCharSet.size()==4) cout<<"\nWord contains a duplicate character";
    cout<<"\n\n";
    setConsoleColor(7);
    cout<<"  <<uWORDLE>>\n\n";
    for(int i=0;i<guessedWords.size();i++) {
        string word = guessedWords[i];
        for(int j=0;j<5;j++)
        {
            setConsoleColor(state[i][j]);
            cout<<" "<<word[j]<<" ";
            setConsoleColor(7);
        }
        cout<<"\n";
    }
}

vector<string>loadData_5_filtered() {
    vector<string>wordsList;
    ifstream file("data/5_filtered_words.txt");
    string word;
    while(getline(file,word)) wordsList.push_back(word);
    file.close();
    return wordsList;
}

void wordle() {
    vector<string>guessedWords,wordList = loadData_5_filtered();
    set<string>wordsSet(wordList.begin(), wordList.end());
    int randomIdx = rand()%wordList.size();
    _WORD_ = wordList[randomIdx];
    Sleep(3000);
    
    set<char>wordCharSet(_WORD_.begin(), _WORD_.end());
    vector<vector<WORD>>state;
    string guess;
    bool won = false;

    do {
        printState(guessedWords, state, wordCharSet);
        bool flag = false;
        cin>>guess;
        if(wordsSet.find(guess)==wordsSet.end()) {
            cout<<"Enter a valid word...";
            Sleep(2000);
            system("cls");
            continue;
        }
        vector<WORD>charState(5);
        guessedWords.push_back(guess);
        for(int i=0;i<5;i++) {
            if(_WORD_[i]==guess[i]) charState[i] = 32;
            else if(wordCharSet.find(guess[i])!=wordCharSet.end()) charState[i] = 96;
            else charState[i] = 7;
        }
        state.push_back(charState);
        ++guessNo;

        if(guess==_WORD_) {
            won = true;
            break;
        }
        
    } while(guessNo<6);
    printState(guessedWords, state, wordCharSet);

    if(won) {
        updateFreq();
        setConsoleColor(10);
        cout<<"\nYOU WIN\n\n";
        setConsoleColor(7);
    }
    else {
        setConsoleColor(4);
        cout<<"\nYOU LOSE\nTHE WORD WAS<< ";
        setConsoleColor(7);
        setConsoleColor(32);
        cout<<_WORD_;
        setConsoleColor(7);
        setConsoleColor(4);
        cout<<" >>\n\n";
        setConsoleColor(7);
    }

    // Update DB here
    updateHistory(won);
    // Till here

    resetVariables();
    Sleep(5000);
}

int main() {
    srand(time(0));
    bool wantToPlay = true;
    char op;
    do {
        system("cls");
        instructions();
        cout<<"Do you want to play(Y/N): ";
        cin>>op;
        switch (op) {
        case 'y':
        case 'Y':
            wordle();
            break;
        case 'n':
        case 'N':
            wantToPlay = false;
            break;
        default:
            cout<<"Enter a valid option...\n";
            break;
        }
    } while (wantToPlay);
}