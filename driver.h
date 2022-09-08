//
// driver.h || Starter code provided by Prof. Troy ||
//  Overview:
//      Functions and struct defined for personality quiz
//      2 structs: Question, and Person
//      9 functions: (Abridged, read function headers)
//       randomElement - Grabs a random element
//       randomQuestionFrom - Grabs question
//       returnFactor - returns a factor
//       readKeys - reads factors
//       modifyScore - modifies a person's score
//       scoresFrom - reads scores to modify person
//       normalize - normalizes a set of scores
//       cosineSimiliarityOf - compares two users similarity
//       mostSimilarTo - finds whoever is most similar to user
//
#include <math.h>

#include <cmath>

#include <limits>

#include <string>

#include <map>

#include <set>

#include "myrandom.h"

using namespace std;

constexpr double lowest_double = std::numeric_limits < double > ::lowest();

/* Type: Question
 *
 * Type representing a personality quiz question.
 */
struct Question {
    string questionText;
    map < char, int > factors;
    friend bool operator < (const Question & lhs,
        const Question & rhs) {
        return lhs.questionText < rhs.questionText;
    }
    friend bool operator == (const Question & lhs,
        const Question & rhs) {
        return lhs.questionText == rhs.questionText;
    }
    friend bool operator != (const Question & lhs,
        const Question & rhs) {
        return lhs.questionText != rhs.questionText;
    }
};

/* Type: Person
 *
 * Type representing a person, used to represent people when determining
 * who's the closest match to the user.
 */
struct Person {
    string name;
    map < char, int > scores;
    friend bool operator < (const Person & lhs,
        const Person & rhs) {
        return lhs.name < rhs.name;
    }
    friend bool operator == (const Person & lhs,
        const Person & rhs) {
        return lhs.name == rhs.name;
    }
    friend bool operator != (const Person & lhs,
        const Person & rhs) {
        return lhs.name != rhs.name;
    }
};

/* randomElement
 *
 * This function selects, at random, a Question from the inputted questions set
 * and returns the question.  Note, this function does not remove the randomly
 * selected question from the set.
 */
Question randomElement(set < Question > & questions) {
    int ind = randomInteger(0, (int) questions.size() - 1);
    int i = 0;
    for (auto e : questions) {
        if (i == ind) {
            return e;
        }
        i++;
    }
    return {};
}

// randomQuestionFrom
// Function: Given a set of questions, return a single question from the set
// Args: questions provides the set of questions
// What:  Checks if list is empty and errors out
// A single question called instance grabs and erase a random question from set

Question randomQuestionFrom(set < Question > & questions) {
    if (questions.empty() == true) {
        throw runtime_error("question list: empty");
    }
    Question Instance = randomElement(questions);
    questions.erase(Instance);
    return Instance;
}

// returnFactor  --  HELPER FUNCTION
// Function: returns the appropiate multiplier to be applied to question
// Args: weight is the # the user provided to a question
// What: I mean its one line of math.
int returnFactor(int weight) {
    return weight - 3;
}

// readKeys  --  HELPER FUNCTION
// Function: Reads a single factor of a question and it's corresponding value
// modifies the given user while also keeping a multiple in mind
// Args:    keyInstance is the single factor of a question
//          userF is the user map information
//          factor is the multiplier to the score.
// How: Checks if factor exists in user's map
//          if(not found) simply create a new value
//          if(found) grab factor and increment by value multiplier
//          Replace value mapped to whatever factor given
void readKeys(pair < char, int > keyInstance,
                    map < char, int > & userF,
                                    int factor) {
    int value = 0;
    if (userF.count(keyInstance.first) == 0) {
        value = keyInstance.second * factor;
    } else {
        int value1 = userF.at(keyInstance.first);
        int value2 = keyInstance.second * factor;
        value = value1 + value2;
    }
    userF.emplace(keyInstance.first, value);
    userF.at(keyInstance.first) = value;
}

// modifyScore  --  HELPER FUNCTION
// Function: Given a single question and it's answer, modify user's map
// Args: pair that contains the question and answer.
//       userF map that contains saved user information
// What: Evaluates factor of the question to be applied
// Goes through each of the question's factors and reads it.
void modifyScore(pair < const Question, int > & answers,
                             map < char, int > & userF) {
    int factor = returnFactor(answers.second);
    for (auto & questionInt : answers.first.factors) {
        readKeys(questionInt, userF, factor);
    }
}

// scoresFrom
// Function: Given a map of a question and it's numbered answer
// Read through the entire map, and modify the user's score according
// to their answers
// Args: map answers contains database of questions answered by user
// What: Creates a map called user, iterates over given args
// modifies user's map.
map < char, int > scoresFrom(map < Question, int > & answers) {
    map < char, int > user;
    for (auto & instance : answers) {
        modifyScore(instance, user);
    }
    return user;
}

// normalize
// Function: normalizes a given map of scores by apply pythagoreans theorum
// btw idk how to spell that and i didn't bother to look it up
// Args:    scores are the user's total factors and value.
// What: edgeCase for when score's are all 0; impossible to normalize
//       iterates over all factors in scores: squared value and added to double
//       transform variable is to turn int to double
//       for all the factors given in arg scores: add the normalized value to
//       the new map and return that map.
//       normalizing = original value divided by normalizer value (pythagorean)
map < char, double > normalize(map < char, int > & scores) {
    bool edgeCase = true;
    map < char, double > norm;
    double pythagoreanValue = 0;
    for (auto & instance : scores) {
        if (instance.second != 0) {
            edgeCase = false;
        }
        double transform = instance.second * 1.0;
        pythagoreanValue += pow(transform, 2);
    }
    if (edgeCase) {
        throw runtime_error("scores are all 0's");
    }
    pythagoreanValue = sqrt(pythagoreanValue);
    for (auto & instance : scores) {
        norm.emplace(instance.first, instance.second / pythagoreanValue);
    }
    return norm;
}

// cosinesimilarityOf
// Function: Compares to given maps of factors and normalized values
//           Evalutes the cosine similarity of them
// Args:    lhs in this case will always be the user's factors and values
//          rhs will always be the one compared to user (everyone else)
// How: Goes through each factor of user and checks if it exists in rhs
//      if(found) increment cosine by the two values mapped to the same factor
//      if(not found) do nothing
//      when each factor is done, return the final cosine value.
double cosineSimilarityOf(const map < char, double > & lhs,
    const map < char, double > & rhs) {
    double cosine = 0;
    for (auto & instance : lhs) {
        if (rhs.count(instance.first) == 1) {
            cosine += instance.second * rhs.at(instance.first);
        }
    }
    return cosine;
}

// mostSimilarTo
// Function: Compares a given user map to a set of people
//           Evaluates the closest match
// Args:    scores is user's map
//          people is the set of people to be comparing
// How:     Normalize user's score (uNormal)
//          Establish the lowest possible double for my sanity
//          Check if set is empty and error out if so
//          If(not empty) iterate through each person of set
//          Normal each person, check cosine similarity of user and person
//          If similarity is higher then benchmark(base) change the base
//          Highest match is saved so return that match when done iterating
Person mostSimilarTo(map < char, int > & scores, set < Person > & people) {
    map < char, double > uNormal = normalize(scores);
    double base = lowest_double;
    Person Match;
    if (people.empty() == false) {
        for (auto & person : people) {
            Person temp = person;
            map < char, double > pNormal = normalize(temp.scores);
            double similarity = cosineSimilarityOf(uNormal, pNormal);
            if (similarity > base) {
                base = similarity;
                Match = person;
            }
        }
    } else {
        throw runtime_error("empty set!");
    }
    return Match;
}
