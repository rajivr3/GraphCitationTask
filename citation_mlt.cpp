#include <bits/stdc++.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#define ll long long

using namespace std;

void writemptofile(map<long long, long long> mp, string fname){
    map<long long, long long> fr_mp;

    fstream f(fname, ios::out);
    for(auto x: mp){
        if(fr_mp.find(x.second) == fr_mp.end()) fr_mp[x.second] = 1;
        else fr_mp[x.second] += 1;
    }

    for(auto x: fr_mp) f << x.first <<"," << x.second << "\n";
    f.close();
}


void addzerodegnodestopmps(map<long long, long long> &mp1, map<long long, long long> &mp2, set<long long> s){
    for(auto x: s){
        if(mp1.find(x) == mp1.end())  mp1[x] = 0;
        if(mp2.find(x) == mp2.end())  mp2[x] = 0;
    }
}

void thread1(string fname, long long st_line, long long en_line, map<long long, long long> &indeg_mp, map<long long, long long> &outdeg_mp, set<long long> &node_set, long long &edge_cnt ){
    string line;
    long long ln_cnt = 0;
    bool header = 1;
    ifstream file (fname, ios::in);

    while(getline(file, line))
    {
        if(header){ 
            header = false;
            continue;
        }

        if(ln_cnt < st_line)  {
            ln_cnt++;
            continue;
        }
        if(ln_cnt > en_line)   return;
        
        ln_cnt++;

        stringstream str(line);
        string line_str = str.str();
        int pos = line.find(',');
        long long citing = stoll(line_str.substr(0, pos));
        long long cited = stoll(line_str.substr(pos+1));

        if(indeg_mp.find(cited) == indeg_mp.end())
            indeg_mp[cited] = 1;
        else
            indeg_mp[cited]++;
        
        if(outdeg_mp.find(citing) == outdeg_mp.end())
            outdeg_mp[citing] = 1;
        else
            outdeg_mp[citing]++;
        
        node_set.insert(cited);
        node_set.insert(citing);
        edge_cnt++;
    }
}

void combinethreadmps(map<long long, long long> &mp1, map<long long, long long> &mp2){
    for(auto x : mp2){
        if(mp1.find(x.first) != mp1.end())  mp1[x.first] += x.second;
        else mp1[x.first] = x.second;
    }
}

void combinethreadsets(set<long long> &s1, set<long long> &s2){
    for(auto x : s2)  s1.insert(x);
}

int main(int argc, char** argv){
    vector<vector<string>> content;
    string line, word;
    vector<map<ll, ll>> indeg_mp(10);
    vector<map<ll,ll>> outdeg_mp(10);
    vector<ll> edge_cnt(10,0);
    vector<set<long long>> node_set(10);
    string path=argv[1];
    std::thread threadObj0(thread1, path, 0, 20000000, ref(indeg_mp[0]), ref(outdeg_mp[0]), ref(node_set[0]), ref(edge_cnt[0]));
    std::thread threadObj2(thread1, path, 20000001, 40000000, ref(indeg_mp[1]), ref(outdeg_mp[1]), ref(node_set[1]), ref(edge_cnt[1]));
    std::thread threadObj4(thread1, path, 40000001, 60000000, ref(indeg_mp[2]), ref(outdeg_mp[2]), ref(node_set[2]), ref(edge_cnt[2]));
    std::thread threadObj6(thread1, path, 60000001, 80000000, ref(indeg_mp[3]), ref(outdeg_mp[3]), ref(node_set[3]), ref(edge_cnt[3]));
    std::thread threadObj9(thread1, path, 80000001, LONG_LONG_MAX, ref(indeg_mp[4]), ref(outdeg_mp[4]), ref(node_set[4]), ref(edge_cnt[4]));
    
    threadObj2.join();
    threadObj4.join();
    threadObj6.join();
    threadObj9.join();
    threadObj0.join();
    cout<<"Reads done";    
    for(int i = 1; i < 5; i++)
        combinethreadmps(indeg_mp[0], indeg_mp[i]);
    for(int i = 1; i < 5; i++)
        combinethreadmps(outdeg_mp[0], outdeg_mp[i]);
    for(int i = 1; i < 5; i++)
        combinethreadsets(node_set[0], node_set[i]);
    for(int i = 1; i < 5; i++)
        addzerodegnodestopmps(outdeg_mp[0], indeg_mp[0], node_set[0]);

    writemptofile(outdeg_mp[0], "outdeghis.csv");
    writemptofile(indeg_mp[0], "indeghis.csv");
    combinethreadmps(outdeg_mp[0], indeg_mp[0]);
    writemptofile(outdeg_mp[0], "deghis.csv");
    ll edge_tot = 0;
    for(auto x : edge_cnt) edge_tot += x;
    cout<<"Edge Count="<<edge_tot<<" Node count="<<node_set[0].size()<<"\n";
    return 0;
}


