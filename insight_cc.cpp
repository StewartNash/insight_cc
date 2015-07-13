/*
Author:			Stewart Nash
Date:				July 10, 2015
Description:		Insight Data Fellowship Coding Challenge
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const int MAX_ENTRY = 512;
const int MAX_TWEETS = 512;

const int MAX_LENGTH = 512;

const int MAX_WORD = 512;
const int MAX_WORDS = 512;

const int MAX_SIZE = 512;

//int countwords(string tweet_words[MAX_LENGTH], string unique_words[MAX_WORDS], int word_count[MAX_WORDS], int tweet_length, int list_count);
//int parsetweet(string tweet, string tweet_words[MAX_LENGTH]);

int countwords(string * tweet_words, string * unique_words, int * word_count, int tweet_length, int list_count);
int parsetweet(string tweet, string * tweet_words);

int main()
{
	ofstream output_file_1;
	ofstream output_file_2;
	ifstream input_file;

	string * tweets;
	string * tweet_words;
	string * unique_words;


	tweets = new string[MAX_TWEETS];
	tweet_words = new string[MAX_LENGTH];
	unique_words = new string[MAX_WORDS];

	int word_count[MAX_WORDS] = {0};

	float unique_tweet[MAX_TWEETS] = {0};

	int i, j;
	int tweet_number;
	int tweet_length;
	int list_count;
	int temp_count;

	input_file.open("tweet_input/tweets.txt");
	if (!input_file.is_open())
	{
		cout << "Unable to open input file: tweet_input/tweets.txt\n";
		return 0;
	}

	output_file_2.open("tweet_output/ft2.txt");
	if (!output_file_2.is_open())
	{
		cout << "Unable to open output file: tweet_output/ft2.txt\n";
		return 0;
	}

	i = 0;
	while (getline(input_file, tweets[i])  && (i < MAX_TWEETS))
		i = i + 1;
	tweet_number = i;

	if (tweet_number == MAX_TWEETS)
		cout << "File length limit reached.\n";

	list_count = 1;
	unique_tweet[0] = 1;
	for (i = 0; i < tweet_number; i++)
	{
		tweet_length = parsetweet(tweets[i], tweet_words);
		temp_count = countwords(tweet_words, unique_words, word_count, tweet_length, list_count);
		unique_tweet[i] = temp_count - list_count;
		if (i % 2)
		{
			j = i / 2;
			output_file_2 << (unique_tweet[j] + unique_tweet[j + 1]) / 2.0  << endl;
		}
		else
		{
			j = i / 2;
			output_file_2 << unique_tweet[j] << endl;
		}
		list_count = temp_count;
	}

	output_file_2.close();

	output_file_1.open("tweet_output/ft1.txt");
	if (!output_file_1.is_open())
	{
		cout << "Unable to open output file: tweet_output/ft1.txt\n";
		return 0;
	}

	for (i = 0; i < list_count; i++)
		output_file_1 << unique_words[i] << "\t\t\t\t" << word_count[i] << endl;

	output_file_1.close();
	input_file.close();

	return 0;
}

int countwords(string * tweet_words, string * unique_words, int * word_count, int tweet_length, int list_count)
{
	int i, j;
	int is_same;

	for (i = 0; i < tweet_length; i++)
	{
		is_same = 0;
		for (j = 0; j < list_count; j++)
		{
			if (list_count <= MAX_WORD)
			{
				if(!(tweet_words[i]).compare(unique_words[j]))
				{
					word_count[j] = word_count[j] + 1;
					is_same= 1;
				}
			}
		}
		if (!is_same)
			if (list_count < MAX_WORD)
			{
				unique_words[++list_count - 1] = tweet_words[i];
				word_count[list_count - 1] = 1;
			}
	}

	return list_count;
}

int parsetweet(string tweet, string * tweet_words)
{
	istringstream input_string(tweet);
	int i;
	int tweet_length;

	i = 0;
	while (getline(input_string, tweet_words[i], ' ')  && i < MAX_LENGTH)
		i = i + 1;
	tweet_length = i + 1;

	return tweet_length;
}
