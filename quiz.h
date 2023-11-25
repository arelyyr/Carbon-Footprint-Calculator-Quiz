// concepts used: binary search, graph (directed acyclic graph)

// quiz:
// vertex categories: related to a specific vertex, or unrelated to any other vertices
//   related vertices/follow-up questions: only used when user answered wrong to a given question of a vertex
//   unrelated vertices/general knowledge questions: generated in a list in random order
// structure of the graph won't be the same each time
// loop in quiz function limits to 10 questions asked (max score is 10)
// user can quit at any time, but score isnt added to leaderboard

// leaderboard:
// reading leaderboard file stores into an vector of pairs storing name and score (string, int)
// data file (default filename: lb.txt) stores name and scores
// prompts user to clear leaderboard
// stores last 10 scores in data file
// inserts user's score at the lowest position (automatically in earliest date order)
// sorts scores and names in order by using binary search and inserting into vector
#ifndef QUIZ_H
#define QUIZ_H
#include <string>
#include <vector>
#include <utility>
#include "dag.h"

// traverses through graph and asks questions to user
// user can quit at any time, but quitting doesnt go to leaderboard
// saves users score to leaderboard after user answers 10 questions
void quizGame();

// reading leaderboard file stores into an array of pairs storing name and score (string, int)
// data file (indicated by LEADERBOARD_FILENAME, default: lb.txt) stores name and scores
// number of scores stored indicated by LEADERBOARD_POSITIONS, default: 10
// overwrite lowest score with the given new score of user (automatically in order of date each score was inputted)
// prompts user to clear leaderboard
//
// sorts scores in (descending) order using binary search
void leaderboard(int new_score);

/**
 * based on zybooks implementation of recursive binary search 14.10
   Finds an element in vector<pair<string, int>> sorted in backwards order of second value in the pair.
        binary search doesnt maintain insert order so it accounts for it by going to the last entry with value
   @param leaderboard vector of pairs, sorted backwards by int value in the pairs
   @param from the start of the range to search
   @param to the end of the range to search
   @param value the value to search for
   @return the index of the first match, or the start of the range if not found
*/
int binary_search(std::vector<std::pair<std::string, int>>& leaderboard, int from, int to, int value);

// initialize quiz graph
// (number of question vertices created should be higher than NUM_QUESTIONS)
// (order of questions should be randomized each run)
void initializeQuizGraph(DAG& quiz_graph);

#endif // QUIZ_H