#ifndef LEVEL_2_COMMAND_LINE_FUNCTIONS_H
#define LEVEL_2_COMMAND_LINE_FUNCTIONS_H

#include <bits/stdc++.h>
#include "UsersGraph.cpp"


void draw_graph(string xml ,string outputFile);
pair<long, string> get_most_active(string xml);
pair<long, string> get_most_influencer(string xml);
vector<long> get_mutual(string xml, const vector<long>& IDs);
vector<long> get_suggest(string xml, long ID);

#endif //LEVEL_2_COMMAND_LINE_FUNCTIONS_H
