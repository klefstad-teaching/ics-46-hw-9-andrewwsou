#include "ladder.h"
#include <iostream>
#include <fstream>
using namespace std;


void error(string word1, string word2, string msg) {
    cout << "Error: " << msg << word1 << "and " << word2 << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    if (str1 == str2) { return true; }

    int len1 = str1.length();
    int len2 = str2.length();

    if (abs(len1 - len2) > 1) {
        return false;
    }

    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
    
    for (int i = 1; i <= len1; ++i) {
        dp[i][0] = i;
    }
    for (int j = 1; j <= len2; ++j) {
        dp[0][j] = j;
    }
    int sub_cost;
    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            if (str1[i-1] == str2[j-1]) {
                sub_cost = 0;
            } else {
                sub_cost = 1;
            }
            dp[i][j] = min(dp[i-1][j] + 1, min(dp[i][j-1] + 1, dp[i-1][j-1] + sub_cost));
        }  
    }
    return dp[len1][len2] == d;
}


bool is_adjacent(const string& word1, const string& word2) {
    return (edit_distance_within(word1, word2, 1));
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        error(begin_word, end_word, "Invalid input, words are the same:");
        return {};
    }

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);

                    if (word == end_word) {
                        return new_ladder;
                    }
                    visited.insert(word);
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);

    string word;
    while (in >> word) {
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (!ladder.empty()) {
        for (size_t i = 0; i < ladder.size(); ++i) {
            cout << ladder[i] << " ";
        }
        cout << endl;
    }
    return;
}


#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}