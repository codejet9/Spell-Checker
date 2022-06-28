#include<bits/stdc++.h>
using namespace std;
using namespace chrono;
#define endl "\n"

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

unordered_map<string,long long int> wordList;
long long int totalFreq=0;


long double P(string& s){
    long double s_freq=wordList[s];
    long double totfreq=totalFreq;

    long double res=s_freq/totfreq;

    return res;
}




int editDistance(string s1,string s2){
    int n=s1.length(),m=s2.length();
    vector<vector<int>> dp(n+1,vector<int>(m+1,0));
    s1='.'+s1;
    s2='.'+s2;

    for(int i=n;i>0;i--){
        for(int j=m;j>0;j--){
            if(i==n or j==m){
                if(s1[i]==s2[j]){
                    dp[i][j]=max(n-i,m-j);
                }
                else{
                    dp[i][j]=1+max(n-i,m-j);
                }
            }
            else{
                if(s1[i]!=s2[j]){
                    dp[i][j]=1+min({dp[i][j+1],dp[i+1][j+1],dp[i+1][j]});
                }
                else{
                    dp[i][j]=dp[i+1][j+1];
                }
            }
        }
    }

    return dp[1][1];
}





string spellCorrect(string& word){
    if(wordList.find(word)!=wordList.end()){
        return word;
    }

    map<int,vector<string>> distances;

    for(auto& word_freq:wordList){
        int ed=editDistance(word_freq.first,word);
        distances[ed].push_back(word_freq.first);
    }

    auto lowestDistance=distances.begin();
    pair<string,long double> mostProbableWord={"",-1};

    for(string& s:lowestDistance->second){
        long double prob=P(s);
        if(prob>mostProbableWord.second){
            mostProbableWord={s,prob};
        }
    }

    return mostProbableWord.first;
}




int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    auto start1 = high_resolution_clock::now();


    // Reading all words and hashing them
    fstream dictFile;
    fstream freqFile;
    dictFile.open("dict.txt",ios::in); //read
    freqFile.open("freq.txt",ios::in); //read

    if(dictFile.is_open() and freqFile.is_open()){
        string s1,s2;
        while(getline(dictFile,s1) and getline(freqFile,s2)){
            long long int currentFreq=stoll(s2);
            wordList[s1]=currentFreq;
            totalFreq+=currentFreq;
        }
        dictFile.close();
        freqFile.close();
    }
    else{
        cout<<"Cannot find required files"<<endl;
        return 0;
    }
    /////////////////////////////////////////


    // Reading input sentence
    string inputString;
    getline(cin,inputString);
    int inputLength=inputString.length();
    ////////////////////////////////////

    
    cout<<endl;
    cout<<"Corrected paragraph is: "<<endl;
    cout<<endl;



    // Collecting individual words and correct
    string word="";
    for(int i=0;i<inputLength;i++){
        if(inputString[i]==' ' or inputString[i]==',' or inputString[i]=='.'){
            if(word!=""){
                string correctWord=spellCorrect(word);
                cout<<correctWord<<' ';
                word="";
            }
        }
        else{
            if(inputString[i]>='A' and inputString[i]<='Z') inputString[i]+=32;
            word.push_back(inputString[i]);
        }
    }
    string correctWord=spellCorrect(word);
    cout<<correctWord<<' ';
    ////////////////////////////////////////


    cout<<endl;
    cout<<endl;
    auto stop1 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop1 - start1);

    cout<<"Time: "<<duration.count()/1000<<" microseconds"<<endl;
    return 0;
}