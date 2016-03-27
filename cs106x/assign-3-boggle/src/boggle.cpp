/**
 * File: boggle.cpp
 * ----------------
 * Implements the game of Boggle.
 */
 
#include <cctype>
#include <iostream>
#include <set>
using namespace std;

#include "simpio.h"
#include "lexicon.h"
#include "gwindow.h"
#include "gboggle.h"
#include "board.h"

const int kBoggleWindowWidth = 650;
const int kBoggleWindowHeight = 350;

const string kStandardCubes[16] = {
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

const string kBigBoggleCubes[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

static void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

static void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

// static void shuffleVector(vector<)

static void drawLetters(Board& board)
{
    int dim = board.get_dim();
    for (int row = 0; row < dim; ++row)
      for (int col = 0; col < dim; ++col)
        labelCube(row, col, board.get_letter(row, col));
}

static inline bool containsWord(const set<string>& words, const string& word)
{
    return words.find(word) != words.end();
}

static bool isHavePath(Board& board, string& word, int index, int row, int col)
{
    if (word[index] != board.get_letter(row, col)) return false;
    if (index == word.size() - 1) return true;
    
    int dim = board.get_dim();

    for (int row_offset = -1; row_offset <= 1; ++row_offset)
      for (int col_offset = -1; col_offset <= 1; ++col_offset)
      {
        if (row_offset != 0 || col_offset != 0)
        {
          int new_row = row + row_offset;
          int new_col = col + col_offset;

          if (new_row >= 0 && new_row < dim && 
              new_col >= 0 && new_col < dim &&
              !board.is_used(new_row, new_col))
          {

            board.set_used(new_row, new_col);
            if (isHavePath(board, word, index + 1, new_row, new_col))
              return true;
            board.set_unused(new_row, new_col);
          }
        }
      }

    return false;
}

static bool isHavePath(Board& board, string& word)
{
    int dim = board.get_dim();
    for (int row = 0; row < dim; ++row)
      for (int col = 0; col < dim; ++col)
      {
        board.set_used(row, col);
        if (isHavePath(board, word, 0, row, col))
          return true;
        board.set_unused(row, col);
      }

    return false;
}

static set<string> humanPlay(Board& board, Lexicon& english)
{
    set<string> humanWords;
    string inputWord;
    Player player = HUMAN;

    board.reset_used();

    while ((inputWord = getLine("Please input a valid word: ")).size() > 0)
    {
        if (english.contains(inputWord) && isHavePath(board, inputWord))
        {
          if (humanWords.find(inputWord) != humanWords.end())
          {
            cout << "This word has existed" << endl;
          }
          else
          {
            humanWords.insert(inputWord);
            recordWordForPlayer(inputWord, player);
          }
        }
        else
        {
          cout << "This word is invalid" << endl;
        }
    }
    return humanWords;
}

static void findAllWords(Board& board,
                         Lexicon& english,
                         set<string>& allWords,
                         string pre,
                         int row, int col)
{
    pre += board.get_letter(row, col);

    if (!english.containsPrefix(pre)) return;

    if (pre.size() >= 4 && english.contains(pre) && !containsWord(allWords, pre))
      allWords.insert(pre);

    int dim = board.get_dim();

    for (int row_offset = -1; row_offset <= 1; ++row_offset)
      for (int col_offset = -1; col_offset <= 1; ++col_offset)
      {
        if (row_offset != 0 || col_offset != 0)
        {
          int new_row = row + row_offset;
          int new_col = col + col_offset;

          if (new_row >= 0 && new_row < dim && 
              new_col >= 0 && new_col < dim &&
              !board.is_used(new_row, new_col))
          {

            board.set_used(new_row, new_col);
            findAllWords(board, english, allWords, pre, new_row, new_col);
            board.set_unused(new_row, new_col);
          }
        }
      }
}

static void findAllWords(Board& board, Lexicon& english, set<string>& allWords)
{
    int dim = board.get_dim();
      for (int row = 0; row < dim; ++row)
        for (int col = 0; col < dim; ++col)
        {
          board.set_used(row, col);
          findAllWords(board, english, allWords, "", row, col);
          board.set_unused(row, col);
        }
}

static void computerPlay(Board& board, Lexicon& english, set<string> humanWords)
{
    board.reset_used();

    set<string> computerWords;

    findAllWords(board, english, computerWords);

    Player player = COMPUTER;
    for (string word : computerWords)
    {
        if (!containsWord(humanWords, word))
          recordWordForPlayer(word, player);
    }
}

int main() {
   GWindow gw(kBoggleWindowWidth, kBoggleWindowHeight);
   Lexicon english("dictionary.txt");
   initGBoggle(gw);
   welcome();
   // if (getYesOrNo("Do you need instructions?")) {
   //    giveInstructions();
   // }

   drawBoard(4, 4);

   string letters = "eecaalephnboqtty";
   Board board(4, letters);

   drawLetters(board);

   set<string> humanWords = humanPlay(board, english);

   computerPlay(board, english, humanWords);

   return 0;
}
