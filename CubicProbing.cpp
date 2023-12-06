#include "CubicProbing.h"
using namespace std;

CubicProbing::CubicProbing(){
    number_of_elements = 0;
    for (int i = 0; i < 100000; i++){
        Account acc;
        acc.id = "_";
        acc.balance = -2;
        bankStorage1d.push_back(acc);
    }
}
void CubicProbing::createAccount(std::string id, int count) {
    int i = hash(id);
    int j = 1;
    int temp = i;
    Account banking;
    banking.id = id;
    banking.balance = count;

    if(bankStorage1d[i].id == "_"){
        bankStorage1d[i] = banking;
    }
    else{
        while(bankStorage1d[i].id != "_"){
            i = (temp + j*j*j)%100000;
            j++;
        }
        bankStorage1d[i] = banking;
    }
    number_of_elements++;
}
std::vector<int> CubicProbing::getTopK(int k) {
    vector <int> greatK;
    vector <int> sortMe;
    for(int i = 0; i < bankStorage1d.size();i++){
        if (bankStorage1d[i].id != "_" && bankStorage1d[i].balance != -1){
            sortMe.push_back(bankStorage1d[i].balance);
        }
    }
    for(int i = 0; i < sortMe.size()-1; i++){
        for(int j = 0; j < sortMe.size()-i-1; j++){
            if (sortMe[j]<sortMe[j+1])
            {
                int temp = sortMe[j];
                sortMe[j] = sortMe[j+1];
                sortMe[j+1] = temp;
            }
        }
    }
    for (int i = 0; i < k && i < sortMe.size(); i++){
        greatK.push_back(sortMe[i]);
    }
    return greatK; // Placeholder return value
}


int CubicProbing::getBalance(std::string id) {
    int a = hash(id);
    int c = 1;
    int temp = a;
    while(bankStorage1d[a].id != "_" || bankStorage1d[a].balance == -1){
        if(bankStorage1d[a].id == id){
            return bankStorage1d[a].balance;
        }
        a = temp + c*c*c;
        c++;
        if(a > bankStorage1d.size()){
            a = a%100000;
        }
    }
    return -1; // Placeholder return value
}

void CubicProbing::addTransaction(std::string id, int count) {
    int a = hash(id);
    int c = 1;
    int temp = a;
    while(bankStorage1d[a].id != "_" || bankStorage1d[a].balance == -1){
        if(bankStorage1d[a].id == id){
            bankStorage1d[a].balance += count;
            return;
        }
        a = temp + c*c*c;
        c++;
        if(a > bankStorage1d.size()){
            a = a%100000;
        }
    }
    createAccount(id,count);
    return;    
}

bool CubicProbing::doesExist(std::string id) {
    int a = hash(id);
    int c = 1;
    int temp = a;
    while(bankStorage1d[a].id != "_" || bankStorage1d[a].balance == -1){
        if(bankStorage1d[a].id == id){
            return true;
        }
        a = temp + c*c*c;
        c++;
        if(a > bankStorage1d.size()){
            a = a%100000;
        }
    }
    return false; // Placeholder return value
}

bool CubicProbing::deleteAccount(std::string id) {
   int a = hash(id);
   int c = 1;
   int temp = a;
    while(bankStorage1d[a].id != "_" || bankStorage1d[a].balance == -1){
        if (bankStorage1d[a].id == id){
            bankStorage1d[a].id =="_";
            bankStorage1d[a].balance = -1;
            number_of_elements--;
            return true;
        }
        a = temp + c*c*c;
        c++;
        if(a > bankStorage1d.size()){
            a = a%100000;
        }
    }
    return false;
}
int CubicProbing::databaseSize() {
    return number_of_elements; // Placeholder return value
}

int CubicProbing::hash(std::string id) {
    {
        int hashvalue = 1;
        int k = 0;
        int prime = 23;
        for (char c : id){
            hashvalue = ((int)c*id[k]*prime + hashvalue);
            prime = prime + 7993;
            k++;
            // n = n + hashvalue + c;
        }
        return hashvalue%100000; // Placeholder return value
    }
}

