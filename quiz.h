#ifndef QUIZ_H
#define QUIZ_H
#include <string>
#include <vector>
#include <utility>
#include "dag.h"


void quizGame();

void leaderboard(int new_score);

int binary_search(std::vector<std::pair<std::string, int>>& leaderboard, int from, int to, int value);

void initializeQuizGraph(DAG& quiz_graph);

#endif // QUIZ_H
