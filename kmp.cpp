#include "kmp.h"

// Fills lps[] for given pattern pat[0..M-1]
void computeLPSArray(const std::string &pat, std::vector<int> &lps) {
//Implement here
    lps.push_back(-1);
    int i=1,j=0, P = pat.size();
    while(i<P){
        if(pat[i]!=pat[j]){
            lps.push_back(j);
            while(j>=0 && pat[j]!=pat[i]){
                j = lps[j];
            }
        } else {
            lps.push_back(lps[j]);
        }
        i++; j++;
    }
    lps.push_back(j);
}

// KMP search: returns vector of starting indices of pattern in text
std::vector<int> KMPSearch(const std::string &pat, const std::string &txt) {
//Implement here
    std::vector<int> ans, lps;
    computeLPSArray(pat,lps);
    int i=0,j=0, T=txt.size(), P=pat.size();
    while(i<T){
        if(txt[i]==pat[j]){
            i++; j++;
            if(j==P){
                ans.push_back(i-j);
                j=lps[j];
            }
        } else{
            j = lps[j];
            if(j<0){
                i++; j++;
            }
        }
    }
    return ans;
}
