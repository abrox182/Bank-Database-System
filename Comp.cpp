#include "Comp.h"
using namespace std;

Comp::Comp(){
    number_of_elements = 0;
    for (int i = 0; i < 100000; i++){
        Account acc;
        acc.id = "_";
        acc.balance = -2;
        bankStorage1d.push_back(acc);
    }
}
void Comp::createAccount(std::string id, int count){
    int i = hash(id);
    Account banking;
    banking.id = id;
    banking.balance = count;

    if(bankStorage1d[i].id == "_"){
            bankStorage1d[i]=banking;
        }
    else{
        while(bankStorage1d[i].id != "_"){
            i = (i + 1)%100000;
        }
        bankStorage1d[i] = banking;
    }
    number_of_elements++;
}

std::vector<int> Comp::getTopK(int k) {
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

int Comp::getBalance(std::string id) {
    int a = hash(id);
    while(bankStorage1d[a].id != "_" || bankStorage1d[a].balance == -1){
        if(bankStorage1d[a].id == id){
            return bankStorage1d[a].balance;
        }
        a++;
        if(a > bankStorage1d.size()){
            a = a%100000;
        }
    }
    return -1; // Placeholder return value
}

void Comp::addTransaction(std::string id, int count) {
    int a = hash(id);
    while(bankStorage1d[a].id != "_" || bankStorage1d[a].balance == -1){
        if(bankStorage1d[a].id == id){
            bankStorage1d[a].balance += count;
            return;
        }
        a++;
        if(a > bankStorage1d.size()){
            a = a%100000;
        }
    }
    createAccount(id,count);
    return;    
}

bool Comp::doesExist(std::string id) {
    int a = hash(id);
    while(bankStorage1d[a].id != "_" || bankStorage1d[a].balance == -1){
        if(bankStorage1d[a].id == id){
            return true;
        }

        a++;
        if(a > bankStorage1d.size()){
            a = a%100000;
        }
    }
    return false; // Placeholder return value
}

bool Comp::deleteAccount(std::string id) {
    int a = hash(id);
    while(bankStorage1d[a].id != "_" || bankStorage1d[a].balance == -1){
        if (bankStorage1d[a].id == id){
            bankStorage1d[a].id =="_";
            bankStorage1d[a].balance = -1;
            number_of_elements--;
            return true;
        }
        a++;
        if(a > bankStorage1d.size()){
            a = a%100000;
        }
    }
    return false;
}

int Comp::databaseSize() {
    return number_of_elements;
}

int Comp::hash(std::string id) {
    {
        int hashvalue = 1;
        int k = 0;
        int prime = 23;
        for (char c : id){
            hashvalue = ((int)c*id[k]*prime + hashvalue);
            hashvalue%87111;
            prime = prime + 7993;
            k++;
            // n = n + hashvalue + c;
        }
        return hashvalue%100000; // Placeholder return value
    }
}
