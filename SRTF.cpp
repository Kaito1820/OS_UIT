#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

class Process{
public:
    int pn;
    int arr, bur;
    int res, tat, wt;
    int star, fin;
    int bur2, star2;
    bool flag;
    Process(){
        pn = arr = bur = res = tat = wt = star = fin = bur2 = star2 = flag = 0;
    }
    void input(){
        cin >> this->pn >> this->arr >> this->bur;
        this->bur2 = this->bur;
    }
    void output(){
        cout << setw(6) << this->pn << setw(6) << this->res << setw(6) << this->tat << setw(6) << this->wt << '\n';
    }

};

bool cmpArr(Process p1, Process p2)
{
    return (p1.arr < p2.arr);
}

bool cmpBur(Process p1, Process p2)
{
    return (p1.bur < p2.bur);
}


int main(){
    vector<Process> New;
    vector<Process> Ready;
    vector<Process> Terminated;
    int n, t;
    float resAv, tatAv, wtAv;
    cin >> n;
    for(int i = 0; i < n; i++){
        Process input;
        input.input();
        New.push_back(input);
    }
    
    sort(New.begin(), New.end(), cmpArr); // sắp xếp lại theo arrivalTime

    New[0].flag = 1; // đánh dấu đây là tiến trình đầu tiên -> luôn có res = 0

    // Cho tiến trình đầu tiên vào Ready
    Ready.insert(Ready.begin(),New[0]);
    Ready[0].star = Ready[0].star2 = Ready[0].arr;
    New.erase(New.begin());

    //SRTF
    while(Terminated.size() < n){
        int dem = 0;
        int ne = New.size();
        bool flag = false;

        for(int i = 0; i < ne; i++){
            if(New[i].arr <= Ready[0].star + Ready[0].bur) 
                dem++;
        }

        if(dem > 0){
            for(int i = 0; i < dem; i++){
                if(New[i].bur < Ready[0].bur - (New[i].arr - Ready[i].star)){
                    Ready[0].bur = Ready[0].bur - (New[i].arr - Ready[0].star); 
                    Ready.insert(Ready.begin(), New[0]);
                    New.erase(New.begin()+i);
                    sort(Ready.begin()+1, Ready.end(), cmpBur);
                    flag = true;
                    break;
                }
                else{
                    Ready.push_back(New[i]);
                    sort(Ready.begin()+1, Ready.end(), cmpBur);
                    New.erase(New.begin()+i);
                }
            }
            if(flag){ // nếu có P có bur CÓ khả năng (bur nhỏ) xen vào
                Ready[0].star = Ready[0].star2 = Ready[0].arr;
                
            }
            else{ // Nếu có P có bur KHÔNG CÓ khả năng (bur lớn) xen vào
                Ready[0].fin = Ready[0].star + Ready[0].bur;
                Ready[0].bur = 0;
                Ready[1].star = Ready[0].fin;
                if (!Ready[1].star2) Ready[1].star2 = Ready[0].fin;
                
            }
        }
        else{ //dem == 0
            Ready[0].fin = Ready[0].star + Ready[0].bur;
            Ready[0].bur = 0;
            Ready[1].star = Ready[0].fin;
            if (!Ready[1].star2) Ready[1].star2 = Ready[0].fin;
        }

        if(!Ready[0].bur){
            Terminated.push_back(Ready[0]);
            Ready.erase(Ready.begin());
        }
    }

    t = Terminated.size();
    for(int i = 0; i < Terminated.size(); i++){
        if(Terminated[i].flag) Terminated[i].star2 = 0;
        Terminated[i].res = Terminated[i].star2 - Terminated[i].arr;
        Terminated[i].tat = Terminated[i].fin - Terminated[i].arr;
        Terminated[i].wt = Terminated[i].tat - Terminated[i].bur2;
        resAv += Terminated[i].res;
        tatAv += Terminated[i].tat;
        wtAv += Terminated[i].wt;
    }
    cout << setw(6) << "pn" << setw(6) << "res" << setw(6) << "tat" << setw(6) << "wt" << '\n';
    for(int i = 0; i < Terminated.size(); i++){
        Terminated[i].output();
    }
    cout << "---------------------------\n";
    cout << setw(9) << "resAv" << setw(9) << "tatAv" << setw(9) << "wtAv" << '\n';
    cout << setw(9) << resAv/n << setw(9) << tatAv/n << setw(9) << wtAv/n << '\n';
    return 0;
}