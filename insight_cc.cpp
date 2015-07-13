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

using namespace std;

const int MAX_TWEETS = 512;
const int MAX_LENGTH = 512;
const int MAX_WORDS = 1024;

//int countwords(string tweet_words[MAX_LENGTH], string unique_words[MAX_WORDS], int word_count[MAX_WORDS], int tweet_length, int list_count);
//int parsetweet(string tweet, string tweet_words[MAX_LENGTH]);

int countwords(string * tweet_words, string * unique_words, int * word_count, int tweet_length, int list_count);
int parsetweet(string tweet, string * tweet_words);
int bubblesort(string * unique_words, int * word_count, int list_count);

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

	string * tweets;
	string * tweet_words;
	string * unique_words;
	string * temp_unique_words;


	tweets = new string[MAX_TWEETS];
	tweet_words = new string[MAX_LENGTH];
	unique_words = new string[MAX_WORDS];
	temp_unique_words = new string[MAX_WORDS];

	int word_count[MAX_WORDS] = {0};
	int temp_word_count[MAX_WORDS] = {0};

	float unique_tweet[MAX_TWEETS] = {0};

	int i, j;
	int tweet_number;
	int tweet_length;
	int list_count;
	int unique_count;

	//Open files for input and output.
	input_file.open("./tweet_input/tweets.txt");
	if (!input_file.is_open())
	{
		cout << "Unable to open input file: ./tweet_input/tweets.txt" << endl;
		return 0;
	}

	output_file_2.open("./tweet_output/ft2.txt");
	if (!output_file_2.is_open())
	{
		cout << "Unable to open output file: ./tweet_output/ft2.txt" << endl;
		return 0;
	}

	i = 0;
	while (getline(input_file, tweets[i])  && (i < MAX_TWEETS))
		i = i + 1;
	tweet_number = i;

	if (tweet_number == MAX_TWEETS)
		cout << "File length limit reached. This program will only process " << MAX_TWEETS << " tweets.\n";

	//Print the median word count per entry to a file.
	list_count = 0;
	for (i = 0; i < tweet_number; i++)
	{
		tweet_length = parsetweet(tweets[i], tweet_words);
		list_count = countwords(tweet_words, unique_words, word_count, tweet_length, list_count);
		unique_tweet[i] = countwords(tweet_words, temp_unique_words, temp_word_count, tweet_length, 0);
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
		cout << "Unable to open output file: ./tweet_output/ft1.txt" << endl;
		return 0;
	}

	bubblesort(unique_words, word_count, list_count);
	//Print the word list and word count to a file.
	for (i = 0; i < list_count; i++)
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
tweet_length: The number of words in the tweet_words array.
list_count: The number of words in the unique_words array.
unique_tweet: The number of unique words in this individual tweet.
*/
int countwords(string * tweet_words, string * unique_words, int * word_count, int tweet_length, int list_count)
{
	int i, j;
	int is_same;
	int start_value;

	start_value = 0;

	//If the list is empty, assign a first element.
	if (list_count == 0)
		if (tweet_length == 0)
			return 0;
		else
		{
			++list_count;
			unique_words[list_count - 1] = tweet_words[start_value];
			word_count[list_count - 1] = 1;
			++start_value;
		}

	for (i = start_value; i < tweet_length; i++)
	{
		is_same = 0;
		for (j = 0; j < list_count; j++)
		{
			if (j <= MAX_WORDS)
			{
				if(!(tweet_words[i]).compare(unique_words[j]))
				{
					word_count[j] = word_count[j] + 1;
					is_same = 1;
				}
			}
		}
		if (!(is_same))
			if (list_count < MAX_WORDS)
			{
				++list_count;
				unique_words[list_count - 1] = tweet_words[i];
				word_count[list_count - 1] = 1;
			}
			else
				cout << "Error in countwords(): The list of unique words has exceeded the program capacity of " << MAX_WORDS << ".\nResults may be inaccurate.\n";
	}

	return list_count;
}

/*
parsetweet Subroutine
---------------------
This subroutine splits the tweet into individual words.
tweet: This variable contains the tweet string.
tweet_words: This array holds the parsed tweet strings.
*/
int parsetweet(string tweet, string * tweet_words)
{
	istringstream input_string(tweet);
	int i;
	int tweet_length;

	i = 0;
	while (getline(input_string, tweet_words[i], ' ')  && i < MAX_LENGTH)
		i = i + 1;
	tweet_length = i;

	if (tweet_length == MAX_LENGTH)
		cout << "Error in parsetweet(): the tweet length has exceeded the program capacity of " << MAX_LENGTH << " words.\nResults may be inaccurate.\n";

	return tweet_length;
}

/*
bubblesort Subroutine
---------------------
Bubble sorts the array.
*/
int bubblesort(string * unique_words, int * word_count, int list_count)
{
	int i, j;
	int temp_count;
	string temp_word;

	for (i = 0; i < list_count; i++)
		for (j = i; j < list_count; j++)
			if (unique_words[j] < unique_words[i])
			{
				temp_word = unique_words[i];
				unique_words[i] = unique_words[j];
				unique_words[j] = temp_word;

				temp_count = word_count[i];
				word_count[i] = word_count[j];
				word_count[j] = temp_count;
			}

	return list_count;
}
