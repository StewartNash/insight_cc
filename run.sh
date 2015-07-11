#!/bin/bash

mkdir tweet_output
g++ -ansi -pedantic-errors -Wall insight_cc.cpp -o insight_cc
./insight_cc
