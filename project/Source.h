#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace std;

struct QuestionInfo
{
	string tag;
	string category;
	string level;
};
struct Question
{
	QuestionInfo info;
	string question;
	string answer;
};
const int num_question = 10;

int welcome(void);
string normalize(string);
void clearConsole();
int int_category(string);
int int_level(string);
vector<Question> save_data();

int get_choose_category(void);
int get_choose_level(void);
vector<int> random_num(int);
vector<Question> final_question(vector<int>, vector<Question>);

vector<Question> data_question(vector<Question>);
vector<string> print_question(vector<Question>);
void result(vector<string>, vector<Question>);
void doQuiz();
void addQuestion(vector<Question>&);
string convert_category(int);
string convert_level(int);
void deleteQuestion(vector<Question>&);
void updateData(vector<Question>);
int get_choose_level_add(void);
int get_choose_category_add(void);