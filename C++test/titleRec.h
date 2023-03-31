// #pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//先按照python写完，后面再优化代码

struct OCRresultsDemo{
    int word_num;
    vector<vector<int>> points;
    string word_text;
};

vector<string> split_isContainsBF_2(string str, int &isContains_BeatFlag, int &isAll_BeatFlag2);

bool digitDet(string str);

int isExistTitle(OCRresultsDemo titleFlag, int w);

int max_erea_det(vector<OCRresultsDemo> ocr_results);

vector<int> title_detection(vector<OCRresultsDemo> ocr_results, int w, int maxEreaFlag);

vector<int> title_combine(vector<OCRresultsDemo> ocr_results);