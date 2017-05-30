#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <random>
#include <ctime>

using namespace std;

class voca{
public:
    voca(string w,string d){
        word = w;
        defi = d;
    }
    string get_word() const {return word;}
    string get_defi() const {return defi;}
private:
    string word;
    string defi;
};

void guess_what(vector<voca> vocaa){
    int number_of_voc = vocaa.size();
    srand(time(0));
    int num = rand() % number_of_voc;
    cout << vocaa[num].get_word() << " is:" << endl;
    vector<string> choice;
    choice.push_back(vocaa[num].get_defi());
    int tempnum;
    while(choice.size() < 4){
        tempnum = rand() % number_of_voc;
        bool not_have = true;
        for(const auto &i:choice){
            if(vocaa[tempnum].get_defi() == i){
                not_have = false;
            }
        }
        if(not_have){
            choice.push_back(vocaa[tempnum].get_defi());
        }
    }
    int start_num = rand() % 4;
    for(int i=0;i<4;i++){
        cout << i+1 << "." << choice[(start_num+i)%4] << " ";
    }
    cout << endl << "Ans: ";
    int ans;
    cin >> ans;
    if(ans < 5 && choice[(start_num+ans-1)%4] == vocaa[num].get_defi()){
        cout << "Correct!!" << endl;
    }
    else{
        cout << "Wrong" << endl << "The answer is " << vocaa[num].get_defi() << endl;;
    }


}

int question_num(){
    cout << "How many question do you want? ";
    int qs;
    while(cin >> qs){
        if(qs <= 20 && qs > 0)
            break;
        cout << "Please input less than 20." << endl;
        cout << "How many question do you want? ";
    }
    return qs;
}

void review_or_not(const map<string,string> &voc){
    cout << "Do you want to review the vocabulary first or not?\n";
    cout << "(Y/n)? ";
    string an;
    getline(cin,an);
    // cin >> an;
    if(an != "n" && an != "N"){
        for(const auto &i:voc){
            cout << i.first << " " << i.second << endl;
        }
        cout << "------------------------------" << endl;
    }
}

int main(int argc, char *argv[]){
    if(argc != 2){
        cout << "Example usage: \n" << endl << "./tfo ./TPO1.md \n" << endl;
        return 0;
    }

    // fstream infile("TPO1.md");
    fstream infile(argv[1]);
    string temp;

    map<string,string> voc;
    vector<voca> vocs;

    // read file into map and vector
    while(getline(infile,temp)){
        // if(temp[0] == '#')
        //     continue;

        if( temp.find('-') <= temp.size() ){
            stringstream ss;
            ss << temp;
            string tempZ, tempA, word, meaning;
            ss >> tempZ;
            while(ss >> tempA){
                if(tempA == "-")
                    break;
                word += (tempA + " ");
            }
            while(ss >> tempA){
                if(tempA == "-")
                    break;
                meaning += (tempA + " ");
            }
            voc[word] = meaning;
            voca tempVoca(word,meaning);
            vocs.push_back(tempVoca);
        }
    }
    cout << vocs.size() << endl;
    // for(const auto &i:voc){
    //     cout << i.first << " " << i.second << endl;
    // }
    // cout << "----------------------------" << endl;
    // for(const auto &i:vocs){
    //     cout << i.get_word() << " " << i.get_defi() << endl;
    // }
    // cout << endl << endl;
    review_or_not(voc);
    int qs = question_num();

    

    for(int i = 0; i < qs; i++){
        cout << "\033[2J\033[H";
        guess_what(vocs);
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }

}
