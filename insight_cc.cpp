/*
Author:			Stewart Nash
File:			insight_cc.cpp
Date:			July 13, 2015
Description:	Insight Data Fellowship Coding Challenge
				The purpose of this program is to count appearances of individual words in a tweet and
				document the median number of appearances of unique words after each tweet. The tweets
				are all contained in one file separated on individual lines.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

int count(vector <string> tweet_words, vector <string> & unique_words, vector <int> & word_count);
vector <string> parse(string tweet);
void bubblesort(vector <string> & unique_words, vector <int> & word_count);

/*
main Function
-------------
tweets: Holds text of each tweet, which is a single string in an array.
tweet_words: Temporarily holds words for each tweet during parsing.
unique_words: Holds a list of all unique words in order of appearance.
word_count: Holds the number of appearance of each word in order of appearance.
unique_cout: Number of unique words per tweet.
*/
int main()
{
	ofstream output_file_1;
	ofstream output_file_2;
	ifstream input_file;

	string tweet;

	vector <string> tweets;
	vector <string> unique_words;
	vector <string> temp_unique_words;
	vector <string> tweet_words;

	vector <int> word_count;
	vector <int> temp_word_count;

	vector <float> unique_tweet;

	unsigned int i, j;

	//Open files for input and output.
	input_file.open("./tweet_input/tweets.txt");
	if (!input_file.is_open())
	{
		cout << "Unable to open input file: tweet_input/tweets.txt" << endl;
		return 0;
	}

	output_file_2.open("./tweet_output/ft2.txt");
	if (!output_file_2.is_open())
	{
		cout << "Unable to open output file: tweet_output/ft2.txt" << endl;
		return 0;
	}

	while (getline(input_file, tweet))
		tweets.push_back(tweet);

	//Print the median word count per entry to a file.
	for (i = 0; i < tweets.size(); i++)
	{
		tweet_words = parse(tweets[i]);
		count(tweet_words, unique_words, word_count);
		temp_unique_words.clear();
		temp_word_count.clear();
		unique_tweet.push_back(count(tweet_words, temp_unique_words, temp_word_count));
		if (i % 2)
		{
			j = i / 2;
			output_file_2 << fixed << setprecision(1) << (unique_tweet[j] + unique_tweet[j + 1]) / 2.0  << endl;
		}
		else
		{
			j = i / 2;
			output_file_2 << fixed << setprecision(1) << unique_tweet[j] << endl;
		}
	}

	output_file_2.close();

	output_file_1.open("./tweet_output/ft1.txt");
	if (!output_file_1.is_open())
	{
		cout << "Unable to open output file: tweet_output/ft1.txt" << endl;
		return 0;
	}

	bubblesort(unique_words, word_count);
	//Print the word list and word count to a file.
	for (i = 0; i < unique_words.size(); i++)
		output_file_1 << left << setw(25) << unique_words[i] << right << "\t\t" << word_count[i] << endl;

	//Close remaining open files.
	output_file_1.close();
	input_file.close();

	return 0;
}

/*
countwords Subroutine
---------------------
tweet_words: An array of words which appear in the tweet.
unique_words: The unique words which have appeared so far.
word_count: The number of each unique word which has appeared.
*/
int count(vector <string> tweet_words, vector <string> & unique_words, vector <int> & word_count)
{
	unsigned int i, j;
	int is_same;
	int start_value;

	start_value = 0;

	//If the list is empty, assign a first element.
	if (unique_words.size() == 0)
	{
		if (tweet_words.size() == 0)
			return 0;
		else
		{
			unique_words.push_back(tweet_words[start_value]);
			word_count.push_back(1);
			++start_value;
		}
	}

	for (i = start_value; i < tweet_words.size(); i++)
	{
		is_same = 0;
		for (j = 0; j < unique_words.size(); j++)
		{
			if(!(tweet_words[i]).compare(unique_words[j]))
			{
				word_count[j] = word_count[j] + 1;
				is_same = 1;
			}
		}
		if (!is_same)
		{
			unique_words.push_back(tweet_words[i]);
			word_count.push_back(1);
		}
	}

	return unique_words.size();
}

/*
parsetweet Subroutine
---------------------
This subroutine splits the tweet into individual words.
tweet: This variable contains the tweet string.
tweet_words: This vector holds the parsed tweet strings.
tweet_word: This variable should be distinguished from the vector tweet_words.
It only serves to hold a temporary string value.
*/
vector <string> parse(string tweet)
{
	vector <string> tweet_words;
	istringstream input_string(tweet);
	string tweet_word;

	while (getline(input_string, tweet_word, ' '))
		tweet_words.push_back(tweet_word);

	return tweet_words;
}

/*
bubblesort Subroutine
---------------------
Bubble sorts the array.
*/
void bubblesort(vector <string> & unique_words, vector <int> & word_count)
{
	unsigned int i, j;
	int temp_count;
	string temp_word;

	for (i = 0; i < unique_words.size(); i++)
		for (j = i; j < unique_words.size(); j++)
			if (unique_words[j] < unique_words[i])
			{
				temp_word = unique_words[i];
				unique_words[i] = unique_words[j];
				unique_words[j] = temp_word;

				temp_count = word_count[i];
				word_count[i] = word_count[j];
				word_count[j] = temp_count;
			}
}
