#include "Source.h"

string normalize(string str)
{
    int size = str.length();
    for (int i = 0; i <= size; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (str[j] == ' ' && str[j + 1] == ' ')
            {
                str.erase(str.begin() + j);
                size--;
            }
            else if (str[0] == ' ')
            {
                str.erase(str.begin());
                size--;
            }
            else if (str[j] == '\0' && str[j - 1] == ' ')
            {
                str.erase(str.end() - 1);
                size--;
            }
        }
    }

    if (str[0] >= 'a' && str[0] <= 'z')
    {
        str[0] = str[0] - 32;
    }
    for (int i = 1; i < size; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] + 32;
        }
    }
    return str;
}
void clearConsole()
{
	if (system("CLS"))
		system("clear");
}

int welcome(void)
{ 
    int choice;
    
    cout << "Would you like to\n";
    cout << "0: quit the program" << endl;
    cout << "1: do quiz" << endl;
    cout << "2: add a new question" << endl;
    cout << "3: delete a question" << endl;
    cout << "Your choice: ";
    cin >> choice;
    return choice;
}

vector<Question> save_data()
{
    vector<Question> question;

    QuestionInfo tmp_info;
    Question tmp_question;
    string info, tmp_ino, string_category,string_level, string_question;
    ifstream inputFile;
    string fileName = "database.txt";
    inputFile.open(fileName);
    int count = 0;
    while (inputFile)
    {
        getline(inputFile, info);
        istringstream iss(info);

        getline(iss, tmp_info.tag, '#');

        getline(iss, tmp_info.category, '#');
        //tmp_info.category = int_category(string_category);

        getline(iss, tmp_info.level, '#');
        //tmp_info.level = int_level(string_level);

        tmp_question.info = tmp_info;

        getline(inputFile, tmp_question.question, '#');
        getline(inputFile, tmp_ino);
        getline(inputFile, string_question);
        tmp_question.answer = normalize(string_question);
        question.push_back(tmp_question);

    }
    question.pop_back();

    return question;
}

int int_category(string category)
{
    int tmp_cate= 0;
    if (category == "general")
        tmp_cate = 1;
    else if (category == "sport")
        tmp_cate = 2;
    else if (category == "geography")
        tmp_cate = 3;
    else if (category == "science")
        tmp_cate = 4;
    else
    {

    }
    return tmp_cate;
}

int int_level(string level)
{
    int tmp;
    if (level == "easy")
        tmp = 1;
    else if (level == "medium")
        tmp = 2;
    else if (level == "hard")
        tmp = 3;
    else
    {

    }
    return tmp;
}

int get_choose_category(void)
{
    int choice_category;
    cout << "Choose your category" << endl;
    cout << "0: all questions" << endl;
    cout << "1: general" << endl;
    cout << "2: sport" << endl;
    cout << "3: geography" << endl;
    cout << "4: science" << endl << endl;
    cout << "Your choice: ";
    cin >> choice_category;

    return choice_category;
}
int get_choose_level(void)
{
    int choice_level;
    cout << "\n\nChoose your level" << endl;
    cout << "0: all levels" << endl;
    cout << "1: easy" << endl;
    cout << "2: medium" << endl;
    cout << "3: hard" << endl << endl;
    cout << "Your choice: ";
    cin >> choice_level;
    cin.ignore();
    return choice_level;
}

vector<Question> data_question(vector<Question> saveData)
{
    int choose_category = get_choose_category();
    int choose_level = get_choose_level();
    clearConsole();
    cout << "\n\n\nYour QUIZ is ready, press enter to start...";
    system("pause");
    clearConsole();
    vector<Question> saveQuestion, tmp_question;
    for (int i = 0; i < saveData.size(); i++)
    {
        if (choose_category == 0)
        {
            tmp_question = saveData;
            break;
        }
        else if(int_category(saveData[i].info.category) == choose_category)
        {
            Question tmp = saveData[i];
            tmp_question.push_back(tmp);
        }
        else
        {

        }
    }

    for (int i = 0; i < tmp_question.size(); i++)
    {
        if (choose_level == 0)
        {
            saveQuestion = tmp_question;
            break;
        }
        else if(int_level(tmp_question[i].info.level) == choose_level)
        {
            Question tmp = tmp_question[i];
            saveQuestion.push_back(tmp);
        }
        else
        {

        }
    }
    
    return saveQuestion;
}

vector<string> print_question(vector<Question> question)
{
    vector<string> answer(num_question);
    for (int i = 0; i < num_question; i++)
    {
        string tmp_answer;
        cout << "QUESTION NUMBER " << i + 1 << endl << endl;
        cout << "Tag: " << question[i].info.tag << " - " << "Category: " 
            << question[i].info.category << " - " << "Level: " << question[i].info.level << endl << endl;
        cout << question[i].question << endl << endl;
        cout << "Your answer: ";
        getline(cin,tmp_answer);
        answer[i] = normalize(tmp_answer);
        clearConsole();
    }
    return answer;
}

void doQuiz()
{
    vector <Question> tmp = data_question(save_data());
    int tmp_size = tmp.size();
    vector <Question> final_ques = final_question(random_num(tmp_size), tmp);
    vector<string> answer = print_question(final_ques);
    result(answer, final_ques);
}

void result(vector<string> answer, vector<Question> final_data)
{
    int count = 0;
    cout << "Result of your Quiz" << endl << endl;
    for (int i = 0; i < num_question; i++)
    {
        if (answer[i] != final_data[i].answer)
        {
            cout << "Tag: #" << final_data[i].info.tag << " - " << "Category: "
                << final_data[i].info.category << " - " << "Level: " << final_data[i].info.level << endl;
            cout << final_data[i].question;
            cout << "Your answer: " << answer[i] << endl;
            cout << "Correct answer: " << final_data[i].answer << endl << endl;
            count++;
        }
    }
    cout << "Your score: " << (num_question - count) << "/" << num_question << endl << endl;
    final_data.clear();
    cout << "Press enter to go back to menu...";
    system("pause");
}

vector<int> random_num(int sizeData)
{
    srand(time(0));
    vector<int> question(sizeData), tmp(sizeData);
    for (int i = 0; i < sizeData; i++)
    {
        question[i] = i;
    }

    random_shuffle(question.begin(), question.end());
    tmp = question;
    question.clear();
    return tmp;
}

vector<Question> final_question(vector<int> random, vector<Question> data)
{
    vector <Question> final_data(num_question);
    for (int i = 0; i < num_question; i++)
    {
        final_data[i] = data[random[i]];
    }
    data.clear();

    return final_data;
}

string convert_category(int category)
{
    string string_category;

    if(category == 1)
        string_category = "general";
    else if (category == 2)
        string_category = "sport";
    else if (category == 3)
        string_category = "geography";
    else if (category == 4)
        string_category = "science";
    else
    {

    }

    return string_category;
}
string convert_level(int level)
{
    string string_level;
    if (level == 1)
        string_level = "easy";
    else if (level == 2)
        string_level = "medium";
    else if (level == 3)
        string_level = "hard";
    else
    {

    }

    return string_level;
}
void addQuestion(vector<Question>& question)
{
    QuestionInfo new_info;
    Question new_question;

    int choose_category, choose_level;
    string tmp_question_1, tmp_question_2, tmp_tag, tmp_category, tmp_level, tmp_answer;
    cout << "Add a question to the database\n\n";
    cout << "Enter the tag: ";
    cin >> new_info.tag;
    choose_category = get_choose_category_add();
    new_info.category = convert_category(choose_category);
    choose_level = get_choose_level_add();
    new_info.level = convert_level(choose_level);

    new_question.info = new_info;
    
    cout << "Enter the question" << endl;
    while (true)
    {
        cout << "> ";
        getline(cin, tmp_question_1);
        if (tmp_question_1 == "")
            break;
        new_question.question += tmp_question_1 + "\n";
    }
    
    cout << "> ";
   
    cout << "Enter the answer" << endl;
    cout << "> ";
    getline(cin, new_question.answer);

    question.push_back(new_question);

    updateData(question);
}

int get_choose_category_add(void)
{
    int choice_category;
    cout << "Choose your category" << endl;
    cout << "1: general" << endl;
    cout << "2: sport" << endl;
    cout << "3: geography" << endl;
    cout << "4: science" << endl << endl;
    cout << "Your choice: ";
    flag1:
    cin >> choice_category;
    if (choice_category < 1 || choice_category > 4)
        goto flag1;

    return choice_category;
}
int get_choose_level_add(void)
{
    int choice_level;
    cout << "\n\nChoose your level" << endl;
    cout << "1: easy" << endl;
    cout << "2: medium" << endl;
    cout << "3: hard" << endl << endl;
    cout << "Your choice: ";
    flag2:
    cin >> choice_level;
    if (choice_level < 1 || choice_level > 3)
        goto flag2;
    cin.ignore();

    return choice_level;
}

void updateData(vector<Question> question)
{
    fstream inputfile;
    inputfile.open("database.txt", ios::out);

    for (int i = 0; i < question.size(); i++)
    {
        inputfile << question[i].info.tag << "#" << question[i].info.category << "#" << question[i].info.level
            << "\n" << question[i].question << "#\n" << question[i].answer << endl;
    }

    inputfile.close();

}
void deleteQuestion(vector<Question>& question)
{
    int choice, num_delete;
    string tag;
    cout << "Delete a question from the database\n\n";
    cout << "Enter the tag of the question you wish to delete: ";
    cin >> tag;
    for (int i = 0; i < question.size(); i++)
    {
        if (tag == question[i].info.tag)
        {
            cout << "Tag: " << question[i].info.tag << " - " << "Category: "
                << question[i].info.category << " - " << "Level: " << question[i].info.level << endl << endl;
            cout << question[i].question << endl << endl;
            num_delete = i;
            break;
        }
    }

    cout << endl << "World you like to\n";
    cout << "0: cancel\n";
    cout << "1: delete question\n\n";
    cout << "Your choice: ";
    cin >> choice;

    if (choice == 0)
    {
        cout << "The question has not been deleted\n";
    }
    else if (choice == 1)
    {

        cout << "Question deleted!\n";
        question.erase(question.begin()+num_delete);
        updateData(question);
    }
    else
    {

    }

    //cout << "Press enter to go back to the menu...";
    system("pause");
}

