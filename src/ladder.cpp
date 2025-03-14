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

    if (abs(len1 - len2) > d) {
        return false;
    }

    int count = 0;
    int i = 0, j = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            if (count == d) { return false; }

            if (len1 > len2) {
                ++i;
            } else if (len2 > len1) {
                ++j;
            } else {
                ++i;
                ++j;
            }
            ++count;
        } else {
            ++i;
            ++j;  
        }
    }
    if (i < len1 || j < len2)
        count++;
    return count <= d;
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
        cout << "Word ladder found: ";
        for (size_t i = 0; i < ladder.size(); ++i) {
            cout << ladder[i] << " ";
        }
        cout << endl;
    } else {
        cout << "No word ladder found." << endl;
    }
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