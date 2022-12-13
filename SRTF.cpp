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
    int burDef, starDef;
    bool flag;
    Process(){
        pn = arr = bur = res = tat = wt = star = fin = burDef = starDef = flag = 0;
    }
    void input(){
        cin >> this->pn >> this->arr >> this->bur;
        this->burDef = this->bur;
    }
    void output(){
        cout << setw(6) << this->pn << setw(6) << this->res << setw(6) << this->tat << setw(6) << this->wt << '\n';
    }

};

bool cmpArr(Process p1, Process p2){
    return (p1.arr < p2.arr);
}

bool cmpBur(Process p1, Process p2){
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

    //SRTF
    while(Terminated.size() < n){
        int dem = 0;
        bool flag = false;
        if(Ready.empty() && !New.empty()){
            Ready.push_back(New[0]);
            New.erase(New.begin());
            Ready[0].star = Ready[0].starDef = Ready[0].arr;
        }
        sort(Ready.begin(), Ready.end(), cmpBur);

        // Kiểm tra xem proc hiện tại sẽ gặp proc nào trong quá trình thực thi
        int ne = New.size();
        for(int i = 0; i < ne; i++){
            if(New[i].arr <= Ready[0].star + Ready[0].bur) 
                dem++;
        }

        if(dem > 0){
            for(int i = 0; i < dem; i++){
                if(New[0].bur < Ready[0].bur - (New[0].arr - Ready[0].star)){
                    Ready[0].bur = Ready[0].bur - (New[0].arr - Ready[0].star); 
                    flag = true;
                }
                Ready.push_back(New[0]);
                New.erase(New.begin());
                if(flag) break;
            }
            
            sort(Ready.begin()+1, Ready.end(), cmpBur); // sắp xếp lại các proc mới thêm vào sau proc đầu tiên 
            
            if(flag){ // nếu có P có bur CÓ khả năng (bur nhỏ) xen vào
                Ready[1].star = Ready[1].starDef = Ready[1].arr;
            }
            else{ // Nếu có P có bur KHÔNG CÓ khả năng (bur lớn) xen vào
                Ready[0].fin = Ready[0].star + Ready[0].bur;
                Ready[0].bur = 0;
                Ready[1].star = Ready[0].fin;
                if(!Ready[1].starDef) Ready[1].starDef = Ready[0].fin;
            }
        }
        else{ //dem == 0
            Ready[0].fin = Ready[0].star + Ready[0].bur;
            Ready[0].bur = 0;
            Ready[1].star = Ready[0].fin;
            if (!Ready[1].starDef) Ready[1].starDef = Ready[0].fin;
        }

        if(!Ready[0].bur){
            Terminated.push_back(Ready[0]);
            Ready.erase(Ready.begin());
        }
    }

    t = Terminated.size();
    for(int i = 0; i < t; i++){
        if(Terminated[i].flag) Terminated[i].starDef = Terminated[i].arr;
        Terminated[i].res = Terminated[i].starDef - Terminated[i].arr;
        Terminated[i].tat = Terminated[i].fin - Terminated[i].arr;
        Terminated[i].wt = Terminated[i].tat - Terminated[i].burDef;
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