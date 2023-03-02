#include "puzzleSolver.hpp"
#include <string>
#include <unordered_set>
#include <list>

using namespace std;

bool verifySolution(std::string s1, std::string s2, std::string s3, const std::unordered_map<char, unsigned> & mapping)
{
    int i1 = 0, i2 = 0, i3 = 0;
    for (int i = 0; i < s1.length(); i++) {
        i1 = i1 * 10;
        i1 += mapping.at(s1[i]);
    }
    for (int i = 0; i < s2.length(); i++) {
        i2 = i2 * 10;
        i2 += mapping.at(s2[i]);
    }
    for (int i = 0; i < s3.length(); i++) {
        i3 = i3 * 10;
        i3 += mapping.at(s3[i]);
    }


    //if the equation is true, return true
    //else false
    if (i1 + i2 == i3) {
        return true;
    } else {
        return false;
    }
}

//create set of all letters
unordered_set<char> allLetters(const string& s1, const string& s2, const string& s3) {
	unordered_set<char> letters;
	for (char ch : s1) {
		letters.insert(ch);
	}
	for (char ch : s2) {
		letters.insert(ch);
	}
	for (char ch : s3) {
		letters.insert(ch);
	}
	return letters;
}

void mapConstructor (unordered_map<char, unsigned> & mapping, string& digits, unordered_set<char> letters) {
	int i = 0;
	for (char ch : letters) {
		mapping[ch] = (int) digits[i++] - 48;
	}
}

bool solvePermutations(int index, string& digits, string s1, string s2, string s3, unordered_map<char, unsigned> & mapping, unordered_set<char>& letters) {
	if (index == (digits.length() - 1)) {
		mapConstructor(mapping, digits, letters);
		if (verifySolution(s1, s2, s3, mapping)) {
			return true;
		}
	}

	for (int j = index; j < digits.length(); j++) {
		swap(digits[index], digits[j]);
		if (solvePermutations(index + 1, digits, s1, s2, s3, mapping, letters)) {
			return true;
		}

		swap(digits[index], digits[j]);
	}
	return false;
}

bool puzzleSolver(const std::string& s1, const std::string& s2, const std::string& s3, std::unordered_map<char, unsigned> & mapping)
{
	unordered_set<char> letters = allLetters(s1, s2, s3);
	string digits = "1234567890";

	return solvePermutations(0, digits, s1, s2, s3, mapping, letters);
}

//set of letters
//list of digits
//map of letters and numbers
//base case front digit is 0
//