#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>


using namespace std; 

const int JUGADORES = 4;
const vector<string> mazo={"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A","2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A",
"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A","2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
const vector<bool> used(mazo.size(),false);

int elegirAleatorio() {
    random_device rd;  
    mt19937 gen(rd()); 
    uniform_int_distribution<> distrib(0, 51); 
    return distrib(gen);
}
string sacar_carta(&vector<string> mazo,&vector<bool> used){
	string carta;
    int indice_carta;
    do {
        indice_carta = elegirAleatorio();
    } while (used[indice_carta]);
    used[card] = true;
    carta = mazo[indice_carta];
    return carta;
}


int calcularMano(const vector<string>& mano) {
    int total = 0, aces = 0;
    for (const string& card : mano) {
        string val = card.substr(0, card.find(' '));

        if (val == "J" || val == "Q" || val == "K")
            total += 10;
        else if (val == "A") {
            total += 11;
            aces++;
        } else {
            total += stoi(val);  
        }
    }
    while (total > 21 && aces--) {
        total -= 10;
    }
    return total;
}
int conteo(&vector<string> mazo,&vector<bool> used){
    int cont = 0;
    for(int i =0; i<mazo.size();++i){
        if(used[i]){
            if(mazo[i] == "J" || mazo[i]=="Q" || mazo[i]=="K" || mazo[i] == "A"){
                cont-=1;
            }else if(stoi(mazo[i]) <= 6){
                cont +=1;
            }else{
                cont+=0;
            }
        }
    }
    return cont;
}
void iaBot(&vector<string> mano, &vector<string> mazo){
    while(true){
        int total = calcularMano(mano);
        if(total <= 11){
            cout << "Bot pide carta"<<endl;
            string carta = sacar_carta(mazo);
            mano.push_back(carta);
            cout <<"La carta es: "<<carta <<endl;
        }
        else if (total >= 19) {
            cout << "Bot se planta.\n";
            break;
        }
        else{
            double coef = rand()%2;
            if(coef == 0){
                cout<<"Bot pide carta"<<endl;
                string carta = sacar_carta(mazo);
                mano.push_back(carta);
                cout <<"La carta es: "<<carta <<endl;

            }else{
                cout << "Bot se planta.\n";
                break;
            }
        }
    }
}

void JuegoUsuario(vector<int>& mano,vector<int>& mazo) {
    string carta;
    while (true) {
        int total = calculateHand(mano);
        cout << "Tu total actual es: " << total << endl;
        if (total >= 21) break;
        cout << "¿Deseas pedir otra carta? (s/n): ";
        char choice;
        cin >> choice;
        if (choice == 's' || choice == 'S') {
            carta= sacar_carta(mazo);
            mano.push_back(carta);
            cout << "Nueva carta: " << carta << endl;
        } else break;
    }
}
void printMano(const string& who, const vector<int>& hand, bool showAll = true) {
    cout << who << " tiene: ";
    for (size_t i = 0; i < hand.size(); ++i) {
        if (i == 1 && !showAll)
            cout << "[carta oculta], ";
        else
            cout << deck[hand[i]] << ", ";
    }
    cout << endl;
}