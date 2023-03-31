#include <string>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

struct OCRresultsDemo{
    int word_num;
    vector<vector<int>> points;
    string word_text;
};

//字符串分割（中英法德等均可）,分割再判定
vector<string> split_isContainsBF_2(string str, int &isContains_BeatFlag, int &isAll_BeatFlag2) {
    //包含以下,要用空格，逗号，句号分隔，并检测:音乐节拍速度标记，力度标记术语
    vector<string> beatFlag = {"largo", "larghetto", "adagio", "andante", "moderato", "allegro", "presto", "prestissimo",
                "poco", "più", "lentissimo", "tempo", "vivace", "grave", "lento", "andante", "andantino",
                "allegretto", "tempodimarcia", "tempodiballo", "rit", "riten", "ritenuto", "rall", "rallentando",
                "allarg", "allargando", "smorzando", "accel.","accelerando", "smorzando", "string", "stringendo", "listessotempo",
                "atempo", "molto", "assai", "meno", "possibile", "piu", "nontroppo", "sempre", "mosso", "rubato", "stretto",
                "lento", "cresc", "crescendo", "dim", "diminuendo", "comeprima", "precipitato", "vivo", "[", "]","(", ")", "（", "）", "{", "}"};

    // //不用空格分割，包含即否认
    // vector<string> parentheses = {};

    //边框内字符串仅由以下字符组成，则不为标题：阿拉伯数字，强度标记，乐器
    vector<string> beatFlag2 = {"Ⅰ", "Ⅱ", "Ⅲ", "Ⅳ", "Ⅴ", "Ⅵ", "Ⅶ", "Ⅷ", "Ⅸ", "Ⅹ", "Ⅺ", "Ⅻ",
                    "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII",
                    "piano", "violin", "cello", "viola", "pp", "ppp", "pppp" , "mf", "ff", "fff", "sf", "fp"};
    int size = str.size();
    std::cout<<size<<endl;
    vector<string> ans;
    int j = 0;
    isContains_BeatFlag = 0;
    isAll_BeatFlag2=1;
    for (int i = 0; i < size; i++) {
        if (str[i] == ' '||str[i] == ','||str[i] == '.') {
            string strElm= str.substr(j, i - j);
            ans.push_back(strElm);
            if(!isContains_BeatFlag && count(beatFlag.begin(), beatFlag.end(), strElm))     isContains_BeatFlag = 1;
            if(isAll_BeatFlag2 && !count(beatFlag2.begin(), beatFlag2.end(), strElm))      isAll_BeatFlag2=0;
        j = i+1;
        }
    }
    ans.push_back(str.substr(j, size - j));
    if(!isContains_BeatFlag && count(beatFlag.begin(), beatFlag.end(), str.substr(j, size - j)))     isContains_BeatFlag = 1;
    if(isAll_BeatFlag2 && !count(beatFlag2.begin(), beatFlag2.end(), str.substr(j, size - j)))      isAll_BeatFlag2=0;
    return ans;
}


bool digitDet(string str){
    for(char elm: str){
        if(!(isdigit(elm)||elm=='.'||elm==' '))    return false;
    }
    return true;
}


// 对面积最大者进行识别，返回是否存在标题
int isExistTitle(OCRresultsDemo titleFlag, int w){
    int titleExistFlag;
    int isContains_BeatFlag; 
    int isAll_BeatFlag2;

    //判定边框位置：居中或者边缘方可则执行以下。若不是，则直接返回0。（但是人工拍照的情况下，位置信息是很难确定的。但是最小值是可以定的）
    int left_edge = titleFlag.points[0][0];
    int right_edge = w - titleFlag.points[1][0]; 
    int min_letf_right = min(left_edge, right_edge);

    vector<string> titleTextSplit = split_isContainsBF_2(titleFlag.word_text, isContains_BeatFlag, isAll_BeatFlag2);
    cout<<"isContains_BeatFlag="<<isContains_BeatFlag<<"\t";
    cout<<"isAll_BeatFlag2="<<isAll_BeatFlag2<<"\t";
    cout<<"digitDet(titleFlag.word_text)"<<digitDet(titleFlag.word_text)<<endl;
    if(abs(left_edge-right_edge)<0.05*w || min_letf_right>1/13*w){
    // 关键字判定
        if(isContains_BeatFlag||isAll_BeatFlag2||digitDet(titleFlag.word_text))    return titleExistFlag=0;
        else return titleExistFlag = 1;
        }
    else return titleExistFlag = 0;
    return titleExistFlag;
}

int max_erea_det(vector<OCRresultsDemo> ocr_results){
    vector<int> titleCandidate;
    int max_erea_flag;
    std::cout<<"//-------------step1:计算当前边框单位字符面积, 并初始化flag标记-------------//"<<endl;
    vector<float> ereas;
    for(int i=0; i<ocr_results.size(); i++){
        vector<int> tempX={ocr_results[i].points[0][0], ocr_results[i].points[1][0], ocr_results[i].points[2][0], ocr_results[i].points[3][0]};
        vector<int> tempY={ocr_results[i].points[0][1], ocr_results[i].points[1][1], ocr_results[i].points[2][1], ocr_results[i].points[3][1]};
        auto max_X = max_element(tempX.begin(), tempX.end());
        auto max_Y = max_element(tempY.begin(), tempY.end());
        auto min_X = min_element(tempX.begin(), tempX.end());
        auto min_Y = min_element(tempY.begin(), tempY.end());
        float erea = (*max_X - *min_X) * (*max_Y - *min_Y)/float(ocr_results[i].word_num);
        ereas.push_back(erea);
    }
    auto max_ereas_index = max_element(ereas.begin(), ereas.end());
    std::cout<<"\n面积最大="<<*max_ereas_index<<"位置="<<max_ereas_index-ereas.begin()<<"\n"<<endl;
    max_erea_flag = max_ereas_index-ereas.begin();
    return max_erea_flag;
}


//传入的是整个det识别结果（测试的时候）),输出边框序号
//由于传入的数值始终为一个，因此，不再区分为不同的函数。仅一个即可
void title_detection(vector<OCRresultsDemo> ocr_results, int w, int flag, vector<int> &title_indexs){

    vector<vector<int>> flag_points(ocr_results[flag].points);

    std::cout<<"//------------------------------step1------------------------------//"<<endl;
    //-----------------------------------------计算当前边框单位字符面积, 并初始化flag标记----------------------------------------//
    // flag = maxEreaFlag;
    cout<<"面积最大者边框序号flag="<<flag<<endl;
    title_indexs.push_back(flag);

    std::cout<<"//------------------------------step2------------------------------//"<<endl; 
    //------------------------------------------找到单位字符面积最大者的同行边框, 并更新flag标记--------------------------------//  
    //-------------此处代码可精简提炼，暂不管
    // 左边同行
    if(flag>0){
        for(int i=flag-1; i <= 0; i--){
        if (abs(ocr_results[flag].points[0][1] - ocr_results[i].points[0][1]) < 0.5*abs(ocr_results[flag].points[0][1] - ocr_results[flag].points[3][1])){
            std::cout<<"2_1事实上的同行"<< i <<endl;
            int left_max_X = max(ocr_results[flag].points[1][0], ocr_results[i].points[1][0]);
            int left_min_X = min(ocr_results[flag].points[0][0], ocr_results[i].points[0][0]);
            int dif_flag_curr = ocr_results[i].points[0][0] - ocr_results[flag].points[1][0];
            //两个边框在x轴上的间距
            int dif_x = (dif_flag_curr > 0)? dif_flag_curr : (ocr_results[flag].points[0][0]-ocr_results[i].points[1][0]);
            std::cout<<left_max_X<<","<<left_min_X<<","<<dif_flag_curr<<","<<dif_x<<","<<endl;
            if ((dif_x < left_min_X) && (dif_x < (w-left_max_X))){
                title_indexs.push_back(i);
                flag_points = {{left_min_X, ocr_results[i].points[0][1]}, {left_max_X, ocr_results[i].points[1][1]}, {left_max_X, ocr_results[i].points[2][1]}, {left_min_X, ocr_results[i].points[3][1]}};
                std::cout<<"2_1标题中认为的同行"<<i<<endl;
            }
            else break;
        }
        else break;
    }
    title_indexs = vector<int>(title_indexs.rbegin(), title_indexs.rend());
    }
    //右边同行
    if(flag<ocr_results.size()-1){
        for(int i=flag+1; i <= ocr_results.size(); i++){
            if (abs(ocr_results[flag].points[0][1] - ocr_results[i].points[0][1]) < 0.5*abs(ocr_results[flag].points[0][1] - ocr_results[flag].points[3][1])){
                std::cout<<"2_2事实上的同行"<< i <<endl;
                std::cout<<ocr_results[flag].points[1][0]<<","<<ocr_results[i].points[1][0]<<","<<ocr_results[flag].points[0][0]<<","<<ocr_results[i].points[0][0]<<endl;
                int right_max_X = max(ocr_results[flag].points[1][0], ocr_results[i].points[1][0]);
                int right_min_X = min(ocr_results[flag].points[0][0], ocr_results[i].points[0][0]);

                int dif_flag_curr = ocr_results[i].points[0][0] - ocr_results[flag].points[1][0];
                int dif_x = (dif_flag_curr > 0)? dif_flag_curr : (ocr_results[i].points[1][0]-ocr_results[flag].points[0][0]);
                std::cout<<right_max_X<<","<<w - right_min_X<<","<<dif_flag_curr<<","<<dif_x<<","<<endl;
                if ((dif_x < right_min_X) && (dif_x < (w-right_max_X))){
                    title_indexs.push_back(i);
                    flag_points = {{right_min_X, ocr_results[i].points[0][1]}, {right_max_X, ocr_results[i].points[1][1]}, {right_max_X, ocr_results[i].points[2][1]}, {right_min_X, ocr_results[i].points[3][1]}};
                    std::cout<<"2_2标题中认为的同行"<<i<<endl;
                }
                else break;
            }
            else break;
        }
    }
    cout<<"step2结束后标题框序号"<<endl;
    for(int elm: title_indexs){
        cout<<elm;
    }
    cout<<"\n"<<endl;
    
    std::cout<<"//------------step3:首行标题flag上同列标题搜索---------------//"<<endl;
    vector<vector<int>> curr_ref(flag_points);
    vector<int> curr_row;
    int left_curr_index = title_indexs[0]-1;
    while(left_curr_index>=-1){
        if (left_curr_index>=0 && abs(curr_ref[0][1] - ocr_results[left_curr_index].points[3][1]) < 1.5 
        * ( ocr_results[left_curr_index].points[3][1]-  ocr_results[left_curr_index].points[0][1])){
            std::cout<<"3.事实上的同列"<<left_curr_index<<endl;
            curr_row.insert(curr_row.begin(), left_curr_index);
            --left_curr_index;
        }
        else{
            vector<int> title_curr_index;//存储当前候选同行标题
            int long_currRow = curr_row.size();
            if (long_currRow == 0)  break;  // res1.points = {{109,  46}, {138, 49}, {136, 68}, {107, 65}};
            else if(long_currRow == 1  && abs(0.5 *(ocr_results[curr_row[0]].points[0][0] + 
            ocr_results[curr_row[0]].points[1][0])-0.5*(curr_ref[0][0]+curr_ref[1][0]))<0.01*w) title_curr_index = curr_row;
            else if(long_currRow == 2){
                int curr_minX = min(ocr_results[curr_row[0]].points[0][0], ocr_results[curr_row[0]].points[3][0]);
                int curr_maxX = max(ocr_results[curr_row[1]].points[1][0], ocr_results[curr_row[1]].points[2][0]);

                int space = ocr_results[curr_row[1]].points[0][0] - ocr_results[curr_row[0]].points[1][0];
                int left_edge = ocr_results[curr_row[0]].points[0][0];
                int right_edge = w - ocr_results[curr_row[1]].points[1][0];
                if(abs(0.5*(curr_minX + curr_maxX)-0.5*(curr_ref[0][0]+curr_ref[1][0])) < 0.01*w){
                    if(left_edge-space > 0.01*w && right_edge-space > 0.01*w)   title_curr_index = curr_row;
                    else break; 
                    }
                else {
                    int elm = ((right_edge-space) >  0.01*w)?curr_row[1]:curr_row[0];
                    title_curr_index.push_back(elm);
                    }
                }
            else if(long_currRow == 3){
                int space_01 = ocr_results[curr_row[1]].points[0][0] - ocr_results[curr_row[0]].points[1][0];
                int space_12 = ocr_results[curr_row[2]].points[0][0] - ocr_results[curr_row[1]].points[1][0];
                int left_edge = ocr_results[curr_row[0]].points[0][0];
                int right_edge = w - ocr_results[curr_row[2]].points[1][0];
                // 只有中间一个是标题
                if (space_01-left_edge > 0.01*w and space_12-right_edge > 0.01*w)
                    title_curr_index.push_back(curr_row[1]);

                else if (left_edge-space_01 > 0.01*w and space_12 - right_edge >0.01*w){
                    title_curr_index.push_back(curr_row[0]);
                    title_curr_index.push_back(curr_row[1]);
                }

                else if (right_edge-space_12 > 0.01*w and space_01 - left_edge >0.01*w){
                    title_curr_index.push_back(curr_row[1]);
                    title_curr_index.push_back(curr_row[2]);
                }
            }
            //同行大于3个，则认为不是标题
            if(title_curr_index.size()==0)    break;
            else{
            title_indexs.insert(title_indexs.begin(), title_curr_index.begin(), title_curr_index.end());
            vector <int>().swap(curr_row); //当前轮结束
            int next_minX = min(ocr_results[title_curr_index[0]].points[0][0], ocr_results[title_curr_index[0]].points[3][0]);
            int next_maxX = max(ocr_results[title_curr_index.back()].points[1][0], ocr_results[title_curr_index.back()].points[2][0]);
            int next_minY = min(ocr_results[title_curr_index[0]].points[0][1], ocr_results[title_curr_index[0]].points[1][1]);
            int next_maxY = max(ocr_results[title_curr_index.back()].points[2][1], ocr_results[title_curr_index.back()].points[3][1]);
            vector <vector<int>>().swap(curr_ref);
            curr_ref = {{next_minX, next_minY}, {next_maxX, next_minY}, {next_maxX, next_maxY}, {next_minX, next_maxY}};
            }
        }
    }
    vector <int>().swap(curr_row); //当前轮结束
    cout<<"step3结束后标题框序号"<<endl;
    for(int elm: title_indexs){
        cout<<elm;
    }
    cout<<"\n"<<endl;

    std::cout<<"//------------step4:首行标题flag下同列标题搜索---------------//"<<endl;
    curr_ref.insert(curr_ref.begin(), flag_points.begin(), flag_points.end());
    int right_curr_index = title_indexs.back()+1;
    cout<<"right_curr_index="<<right_curr_index<<"\t"<<ocr_results.size()<<endl;
    for(vector<int> elms : flag_points){
        for(int elm: elms){
            cout<<elm<<endl;
        }    
    }
    while (right_curr_index <= ocr_results.size()){
        if (right_curr_index < ocr_results.size() && abs(curr_ref[3][1] - ocr_results[right_curr_index].points[0][1]) < 
        1.5 * (ocr_results[right_curr_index].points[3][1]- ocr_results[right_curr_index].points[0][1])){
            std::cout<<"right_curr_index="<<right_curr_index<<endl;
            curr_row.push_back(right_curr_index);
            right_curr_index++;
        }
        else{
            vector<int> title_curr_index;
            int long_currRow = curr_row.size();
            std::cout<<"下同列"<<long_currRow<<endl;
            if(long_currRow == 0) break;
            else if(long_currRow == 1 && abs(0.5 *(ocr_results[curr_row[0]].points[0][0] + 
            ocr_results[curr_row[0]].points[1][0])-0.5*(curr_ref[0][0]+curr_ref[1][0]))<0.05*w) title_curr_index = curr_row;
            else if(long_currRow == 2){
                int curr_minX = min(ocr_results[curr_row[0]].points[0][0], ocr_results[curr_row[0]].points[3][0]);
                int curr_maxX = max(ocr_results[curr_row[1]].points[1][0], ocr_results[curr_row[1]].points[2][0]);
                int space = ocr_results[curr_row[1]].points[0][0] - ocr_results[curr_row[0]].points[1][0];
                int left_edge = ocr_results[curr_row[0]].points[0][0];
                int right_edge = w - ocr_results[curr_row[1]].points[1][0];
                if (abs(0.5*(curr_minX + curr_maxX)-0.5*(curr_ref[0][0]+curr_ref[1][0])) < 0.01*w){
                    if (left_edge-space > 0.01*w and right_edge-space > 0.01*w) title_curr_index = curr_row;
                    else    break;
                }       
                else{
                    int elm = ((right_edge-space) >  0.01*w)?curr_row[1]:curr_row[0];
                    title_curr_index.push_back(elm);
                }                    
            }
            else if(long_currRow == 3){
                int space_01 = ocr_results[curr_row[1]].points[0][0] - ocr_results[curr_row[0]].points[1][0];
                int space_12 = ocr_results[curr_row[2]].points[0][0] - ocr_results[curr_row[1]].points[1][0];
                int left_edge = ocr_results[curr_row[0]].points[0][0];
                int right_edge = w - ocr_results[curr_row[2]].points[1][0];
                if(space_01-left_edge > 0.01*w and space_12-right_edge > 0.005*w)   title_curr_index.push_back(curr_row[1]);
                else if(left_edge-space_01 > 0.01*w and space_12 - right_edge >0.01*w){
                    title_curr_index.push_back(curr_row[0]);
                    title_curr_index.push_back(curr_row[1]);
                }
                else if(right_edge-space_12 > 0.01*w and space_01 - left_edge >0.01*w){
                    title_curr_index.push_back(curr_row[1]);
                    title_curr_index.push_back(curr_row[2]);
                }
            }    
            title_indexs.insert(title_indexs.end(), title_curr_index.begin(), title_curr_index.end());
            if(title_curr_index.size()==0)    break;
            else{
                vector <int>().swap(curr_row); //当前轮结束
                int next_minX = min(ocr_results[title_curr_index[0]].points[0][0], ocr_results[title_curr_index[0]].points[3][0]);
                int next_maxX = max(ocr_results[title_curr_index.back()].points[1][0], ocr_results[title_curr_index.back()].points[2][0]);
                int next_minY = min(ocr_results[title_curr_index[0]].points[0][1], ocr_results[title_curr_index[0]].points[1][1]);
                int next_maxY = max(ocr_results[title_curr_index.back()].points[2][1], ocr_results[title_curr_index.back()].points[3][1]);
                vector <vector<int>>().swap(curr_ref);
                curr_ref = {{next_minX, next_minY}, {next_maxX, next_minY}, {next_maxX, next_maxY}, {next_minX, next_maxY}};                     
            }  
        }            
    }
    cout<<"step4结束后标题框序号"<<endl;
    for(int elm: title_indexs){
        cout<<elm;
    }
    cout<<"\n"<<endl;
}

//串接整个流程
void title_combine(vector<OCRresultsDemo> ocr_results, vector<int> &title_indexs){
    int w = 665;
    int h = 705;
    //step1:获取单位字符最大面积的边框序号
    int maxEreaFlag = max_erea_det(ocr_results);
    // step2:需要对最大面积边框进行字符识别: 本处需要根据项目求改
    ocr_results[maxEreaFlag].word_text = "GUOhuiming";
    // step3:判定当前最大面积边框是否为标题候选项
    int titleExistFlag = isExistTitle(ocr_results[maxEreaFlag], w);
    cout<<"titleExistFlag="<<titleExistFlag<<endl;
    // step4:根据标题候选项的判定情况，求取最终的标题框
    if(titleExistFlag){
        cout<<"标题存在"<<endl;
        cout<<"+++++++++++++++++++++2022.10.23,bug调试++++++++++++++++++++++++"<<endl;
        title_detection(ocr_results, w, maxEreaFlag, title_indexs);
        cout<<"+++++++++++++++++++++++++++bug调试over+++++++++++++++++++++++++"<<endl;

    }
}

int main(){
    
    vector<OCRresultsDemo> ocr_results;
    OCRresultsDemo res1;
    OCRresultsDemo res2;
    OCRresultsDemo res3;
    OCRresultsDemo res4;
    OCRresultsDemo res5;
    OCRresultsDemo res6;
    OCRresultsDemo res7;
    OCRresultsDemo res8;
    OCRresultsDemo res9;
    OCRresultsDemo res10;
    OCRresultsDemo res11;
    // struct OCRresults ocr_results;
    res1.points = {{109,  46}, {138, 49}, {136, 68}, {107, 65}};
    res1.word_num = 3;
    ocr_results.push_back(res1);

    res2.points = {{232, 119}, {277, 124}, {275, 143}, {230, 138}};
    res2.word_num = 5;
    ocr_results.push_back(res2);

    res3.points = {{390, 121}, {444, 121}, {444, 142}, {390, 142}};
    res3.word_num = 6;
    ocr_results.push_back(res3);

    res4.points = {{618, 123}, {647, 123}, {647, 142}, {618, 142}};
    res4.word_num = 3;
    ocr_results.push_back(res4);

    res5.points = {{241, 161}, {333, 158}, {334, 180}, {242, 184}};
    res5.word_num = 7;
    ocr_results.push_back(res5);

    res6.points = {{373, 162}, {418, 162}, {418, 181}, {373, 181}};
    res6.word_num = 3;
    ocr_results.push_back(res6);

    res7.points = {{25, 200}, {55, 200}, {55, 219}, {25, 219}};
    res7.word_num = 4;
    ocr_results.push_back(res7);

    res8.points = {{233, 199}, {283, 199}, {283, 217}, {233, 217}};
    res8.word_num = 6;
    ocr_results.push_back(res8);

    res9.points = {{417, 199}, {456, 196}, {458, 218}, {419, 221}};
    res9.word_num = 5;
    ocr_results.push_back(res9);

    res10.points = {{312, 228}, {348, 228}, {348, 247}, {312, 247}};
    res10.word_num = 4;
    ocr_results.push_back(res10);

    res11.points = {{314, 266}, {350, 266}, {350, 285}, {314, 285}};
    res11.word_num = 4;
    ocr_results.push_back(res11);
    vector<int> title_indexs;
    title_combine(ocr_results, title_indexs);
    cout<<"------------------------标题框输出----------------------"<<endl;
    for(int elm:title_indexs){
        cout<<elm<<"\t";
    }
    cout<<"\n"<<endl;
    return 0;
}