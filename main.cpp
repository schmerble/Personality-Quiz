//
//   CS 251: Data Structures and Algorithims
//   PERSONALITY QUIZ || PROJECT 2 || Prof. Troy
//   Made by: Ryan Ly Joe || RLYJOE2@UIC.EDU
//      An Overview:
//          A small personality quiz to compare you to a user!
//          The quiz prompts you for how many questions you'd like answer
//          The more you answer, the more accurate it is
//          After answering all questions, simply input which group of-
//          characters you would like to be compared to.
//          There are currently 9 options available!
//          1. Baby Animals
//          2. Brooklyn99
//          3. Disney
//          4. Hogwarts
//          5. Myers Briggs
//          6. Sesame Street
//          7. Star Wars
//          8. Vegetables
//          9. Lost Ark Classes (custom)(Comes out 2/8 :D)
//
#include <set>

#include <vector>

#include <map>

#include <fstream>

#include <sstream>

#include <string>

#include <iostream>

#include "driver.h"

using namespace std;

//  addFactor  --  Helper Function
//   Function: Adds factors into a question struct
//   ARGS: Question instance to directly modify it
//         factor to know what factors to add.
//   What: Reads each factor a given string and adds it to the question
void addFactor(Question & instance, string factor) {
    string temp;
    stringstream fLtoken(factor);
    while (getline(fLtoken, temp, ' ')) {
        string integer = temp.substr(temp.find(':') + 1, temp.size());
        instance.factors[temp[0]] = stoi(integer);
    }
}

//  createQuestion  --  Helper Function
//   Function: Returns a created question
//   ARGS: Text contains question || Factors contained factor of questions
//   What: Creates a question instance and fills it up question text and factors
Question createQuestion(string text, string factors) {
    Question instance;
    instance.questionText = text;
    string temp;
    stringstream fLtoken(factors);
    while (getline(fLtoken, temp)) {
        addFactor(instance, temp);
    }
    return instance;
}

//  readQuestionFile
//   Function: Returns a set of questions from a file
//   ARGS: no args cause this was my last function and i got lazy
//   What: Reads each line of questions file. Splits line into 2 parts
//         Calls createQuestion and adds it into the set.
set < Question > readQuestionFile() {
    set < Question > questionList;
    string temp;
    ifstream questionFile;
    questionFile.open("questions.txt");
    while (!questionFile.eof()) {
        getline(questionFile, temp);
        if (temp.empty()) {
            break;
        }
        string questionLine = temp.substr(0, temp.find('.') + 1);
        string factors = temp.substr(temp.find('.') + 2, temp.size());
        questionList.insert(createQuestion(questionLine, factors));
    }
    return questionList;
}

//  createPerson  --  Helper Function
//   Function: Creates a person from given strings of text and factors
//   ARGS: Text contains name of person || Factors contained factor of person
//   What: Creates a person and turns the factors in a stream to be read
//         separates factors by space || temp.substr separates factor and value.
Person createPerson(string text, string factors) {
    Person instance;
    instance.name = text;
    string temp;
    stringstream fLtoken(factors);
    while (getline(fLtoken, temp)) {
        string temp;
        stringstream fLtoken(factors);
        while (getline(fLtoken, temp, ' ')) {
            string integer = temp.substr(temp.find(':') + 1, temp.size());
            instance.scores[temp[0]] = stoi(integer);
        }
    }
    return instance;
}

//  readPeopleFile
//   Function: Returns a set of person struct
//   ARGS: filename to pass what file to open
//   What:  Grabs every line of a person file, and splits name and factors
//   Calls createPerson to create a instance of a person to input into a set
set < Person > readPeoplefile(string fileName) {
    set < Person > instance;
    string temp;
    ifstream peopleFile;
    peopleFile.open(fileName + ".people");
    while (!peopleFile.eof()) {
        getline(peopleFile, temp);
        if (temp.empty()) {
            break;
        }
        string personName = temp.substr(0, temp.find('.'));
        string factors = temp.substr(temp.find('.') + 2, temp.size());
        instance.insert(createPerson(personName, factors));
    }
    return instance;
}

// displayQuestions  --  HELPER FUNCTION
//  Function: nabs a question from set and creates an index for answers
//  Args:   QuestionList for the set of questions to take from
//          AnswerList for the taken question to save responses
//  What:   Grabs random question, creates index, prints question
//          returns what question it grabbed for askQuestion()
Question displayQuestions(set < Question > & questionList, 
                        map < Question, int > & answerList) {
    Question instance = randomQuestionFrom(questionList);
    answerList[instance];
    cout << "How much do you agree with this statement?" << endl;
    cout << '"' << instance.questionText << '"' << endl << endl;
    return instance;
}

// displayPrompt  --  HELPER FUNCTION
// Function: YOU GET A PRINT AND YOU GET A PRINT
// What: i'm lazy
void displayPrompt() {
    cout << "1. Strongly disagree" << endl;
    cout << "2. Disagree" << endl;
    cout << "3. Neutral" << endl;
    cout << "4. Agree" << endl;
    cout << "5. Strongly agree" << endl;
    cout << endl << "Enter your answer here (1-5): " << endl;
}

// takeScore  --  HELPER FUNCTION
// Function: Asks the user for an int and returns it
// What: it looked really ugly in main()
int takeScore() {
    int takenScore;
    cin >> takenScore;
    return takenScore;
}

// askQuestion  --  HELPER FUNCTION
// Function: Saves the displayed question. Saves answer to a map.
// Args:    questionList to modify questionList in realtime
//          answerList to save answers and to record them
// How: Saves question asked, displays the possible entries, and saves entry.
void askQuestion(set < Question > & questionList,
                 map < Question, int > & answerList) {
    Question questionAsked = displayQuestions(questionList, answerList);
    displayPrompt();
    answerList[questionAsked] = takeScore();
}

// askQuestions
// Function: Asks how ever many questions queried by user
// Args:    questionList to grab questions from
//          answerList to save answers from grabbed questions
//          numQuestions is users input for how many questions to ask
// What: Loop to ask question
void askQuestions(set < Question > & questionList, 
                map < Question, int > & answerList, 
                                int numQuestions) {
    cout << endl;
    for (int i = 0; i < numQuestions; i++) {
        askQuestion(questionList, answerList);
        cout << endl;
    }
}

// parsePeoplefile  --  HELPER FUNCTION
// Function: Reads a given name to load file and compares user
// Args:    name is the fileName inputted to read
//          user is the person compared to all users in a file
// What: Creates a set of people from a file, and compares the user
//       returns the most similar person to user.
Person parsePeoplefile(string name, Person & user) {
    set < Person > peopleSet = readPeoplefile(name);
    return mostSimilarTo(user.scores, peopleSet);
}

// promptTestGroup  --  HELPER FUNCTION
// Function: Display's all elements of the array that stores
//           the possible files for comparing tests!
// What:     Quick loop and 0 to end program
void promptTestGroup(vector < string > & nameArray) {
    for (int i = 0; i < (int) nameArray.size(); i++) {
        cout << i + 1 << ". " << nameArray[i] << endl;
    }
    cout << "0. To end program." << endl;
    cout << "Choose test number (1-9, or 0 to end): ";
}

// createNameArray  --  HELPER FUNCTION
// Function: Creates and makes an array with all the names
// What: I was too lazy and it looked ugly in main()
vector < string > createNameArray() {
    vector < string > instance;
    instance.push_back("BabyAnimals");
    instance.push_back("Brooklyn99");
    instance.push_back("Disney");
    instance.push_back("Hogwarts");
    instance.push_back("MyersBriggs");
    instance.push_back("SesameStreet");
    instance.push_back("StarWars");
    instance.push_back("Vegetables");
    instance.push_back("mine");
    return instance;
}

//  takeAnswer  --  HELPER FUNCTION
//  Function: Prompts user to select which group to compare personalities
//  ARGS: nameArray for easy access of all possible groups to compare
//        user to compare to the people inside a specific group
//  What: Prints out all groups and asks user for input
//        Depending on input, will tell you the closest match
//        Repeats until input is 0.
void takeAnswer(vector < string > & nameArray, Person & user) {
    promptTestGroup(nameArray);
    int input;
    cin >> input;
    while (input != 0) {
        Person mostSimilar = parsePeoplefile(nameArray[input - 1], user);
        cout << "You got " << mostSimilar.name << '!' << endl << endl;
        promptTestGroup(nameArray);
        cin >> input;
    }
    cout << "Goodbye!" << endl;
}

int main() {
    // quick declarations
    set < Question > questionList = readQuestionFile();
    vector < string > testNames = createNameArray();

    cout << "Welcome to the Personality Quiz!" << endl << endl;
    cout << "Choose number of questions: ";

    // input for num of questions
    int numQuestions;
    cin >> numQuestions;

    // process to ask questions
    map < Question, int > queryProcess;
    askQuestions(questionList, queryProcess, numQuestions);

    // stores data from the user
    Person user;
    user.name = "User";
    user.scores = scoresFrom(queryProcess);

    // asks user to compare to what test
    takeAnswer(testNames, user);
    return 0;
}
