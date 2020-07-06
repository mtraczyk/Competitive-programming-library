#include<iostream>
#include<cstdlib>
#include<string>

using namespace std;

int main() {

        string a = "./gen >test ";

        for(int i = 0; i < 100000000; i++) {
                system((a + to_string(i)).c_str());
                system("./wzorcówka <test >outwzorcówka");
                system("./brut <test >outbrut");
                if(system("diff outwzorcówka outbrut")) {
                        break;
                }
                cout<<i+1<<" OK"<<endl;
        }
}
