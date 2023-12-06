#include "Chaining.h"
using namespace std;

Chaining::Chaining(){
    number_of_elements = 0;
    bankStorage2d.resize(100000);
    for (int i = 0; i < 100000; i++){
        Account acc;
        acc.id = "_";
        bankStorage2d[i].push_back(acc);
    }
}
void Chaining::createAccount(std::string id, int count) {
    Account banking;
    banking.id = id;
    banking.balance = count;
    int a = hash(id);
    a = a%100000;
    vector<Account> &subv = bankStorage2d[a];
    for (Account &ac : subv){
        if (ac.id == "_"){
            ac = banking;
            number_of_elements++;
            return;
        }
    }
    subv.push_back(banking);
    number_of_elements++;
    return;
}

std::vector<int> Chaining::getTopK(int k) {
    
    vector <int> greatK;
    vector <int> sortMe;
    for(vector<Account> subv:bankStorage2d){
        for(Account &ac : subv){
            if (ac.id != "_"){
                sortMe.push_back(ac.balance);
            }
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

int Chaining::getBalance(std::string id) {
    int a = hash(id);
    for(Account &ac: bankStorage2d[a]){
        if(ac.id == id){
            return ac.balance;
        }
    }
    return -1; // Placeholder return value
}

void Chaining::addTransaction(std::string id, int count) {
    int a = hash(id);
    for(Account &ac : bankStorage2d[a]){
        if (ac.id == id){
            ac.balance = ac.balance+count;
            return;
        }
    }
    createAccount(id,count);
}

bool Chaining::doesExist(std::string id) {
    int a = hash(id);
    for(const Account &ac: bankStorage2d[a]){
        if(ac.id == id){
            return true;
        }
    }
    return false; // Placeholder return value
}

bool Chaining::deleteAccount(std::string id) {
    int a = hash(id);
    vector<Account>& subv = bankStorage2d[a];
    int idx = 0;
    while (subv[idx].id != id && idx < subv.size()){
        idx++;
    }
    if(idx < subv.size() && subv[idx].id == id){
        subv.erase(subv.begin() + idx);
        number_of_elements--;
        return true;
    }
    else{
        return false; // Placeholder return value
    }
}
int Chaining::databaseSize() {
    return number_of_elements; // Placeholder return value
}

int Chaining::hash(std::string id) {
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
