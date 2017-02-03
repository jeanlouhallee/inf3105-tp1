/*
   --------------------------------TASKLIST----------------------------------------
   --1) Modifier le constructeur pour qu'il s'assure que la priorite du patient
     soit >= 1 et <= 5 // DONE
   --2) Implementer ou trouver un algorithme de tri ordonner le vecteur de
     [0] : le plus prioritaire a
     [N-1] : le moins prioritaire
     Side-Note : Changer vecteur pour une organisation en pile?
   --3) Redifinir les surcharges d'operateurs booleen pour implementer
     un algorithme NON naif
   --4) Modification du OUTPUT
   --5) Lire correctement depuis un fichier //DONE
   --6) Ajouter un destructeur
   --7) Trouver comment empecher que deux patient aille le meme noPatient
   -------------------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

int findElem(const vector<int> v, int elem);
/**
 * Classe Patient qui contient le numero de Patient, le temp attendu par le
 * patient ainsi que sa priorité.
 * --A RAJOUTER : Une surcharge des operateur >, <, ==, etc pour pouvoir etablir
 * des relations de grandeurs pour trier le vecteu qui va contenir les patients
 */
class Patient {
    private:
    int _noPatient;
    int _tempAttente;
    int _priorite;
    public:
    static vector<int> listeNoPatient;
    Patient(int noPatient = -1, int tempAttente = 0, int priorite = 5)
            : _noPatient(noPatient), _tempAttente(tempAttente), _priorite(priorite) {
    }
    int get_noPatient();
    int get_tempAttente();
    int get_priorite();
    void set_noPatient(int noPatient);
    void set_tempAttente(int tempAttente);
    void set_priorite(int priorite);
    friend bool operator< (const Patient &p1, const Patient &p2);
    friend istream& operator >> (istream& is, Patient& patient);
    friend ostream& operator << (ostream& os, const Patient& patient);
    /*
       Surcharge naive de l'operateur <. Cette version ne prendra en consideration que la priorité et le temps d'attente
       On suppose que le PREMIER element du vecteur est CELUI QUI DOIT PASSER EN PREMIER
       On suppose que le DERNIER element du vecteur est CELUI QUI DOIT PASSER EN DERNIER
       p1 < p2 : suppose que p1 est plus prioritaire que p2
     */
    bool operator< (const Patient &p2){
            bool p1PlusPrioritairep2 = false;
            if (_priorite < p2._priorite) {
                    p1PlusPrioritairep2 = true;
            }
            else {
                    if (_priorite == p2._priorite) {
                            if (_tempAttente > p2._tempAttente) {
                                    p1PlusPrioritairep2 = true;
                            }
                    }
            }
            return p1PlusPrioritairep2;
    }
};

vector<int> Patient::listeNoPatient;
/*
   Surcharge le l'operateur <<. A MODIFIER pour que ca conincide avec les specification du prof pour l'affichage
 */
ostream& operator << (ostream& os, const Patient& patient) {
        os << "No Patient : " << patient._noPatient << ", Temp attendu dans la salle d'attente (s) : " << patient._tempAttente << " Priorite : " << patient._priorite;
        return os;
}
/*
   Surcharge de l'operateur >>. Va nous permettre de lire les donnees facilement en ignorant les espaces
 */
istream& operator >> (istream& is, Patient& patient) {
        int noPatient, tempAttente, priorite;
        if(is >> noPatient) {
                is >> tempAttente >> priorite;
                if (noPatient < 0 || findElem(Patient::listeNoPatient, noPatient) != -1 || tempAttente < 1 || priorite < 2 || priorite > 5) {
                        throw invalid_argument("Erreur pendant la creation du patient");
                } else {
                        patient._noPatient = noPatient;
                        patient._tempAttente = tempAttente;
                        patient._priorite = priorite;
                        Patient::listeNoPatient.push_back(noPatient);
                }
        }
        return is;
}

/*
   Getters et setters. Principalement pour la forme.
   A potentiellement enlever vu que le friendship avec << et >> nous permettent de
   lire des patients dans un vecteur facilement
 */
int Patient::get_noPatient(){
        return _noPatient;
}
int Patient::get_tempAttente (){
        return _tempAttente;
}
int Patient::get_priorite(){
        return _priorite;
}
void Patient::set_noPatient(int noPatient){
        _noPatient = noPatient;
}
void Patient::set_tempAttente(int tempAttente){
        _tempAttente = tempAttente;
}
void Patient::set_priorite(int priorite){
        _priorite = priorite;
}

void readFile(char *arcv, vector<Patient> *vp){
        ifstream file(arcv);
        if(file) {
                Patient patient;
                while(file >> patient) {
                        vp->push_back(patient);
                        cout << patient << endl;
                }
                file.close();
        }else{
                cout << "TENGO UN PROBLEMA SENOR" << endl;
        }
}

int findElem(const vector<int> v, int elem){
        int pos = -1, i;
        bool trouve = false;
        if (!v.empty()) {
                for (i = 0; i < v.size() && !trouve; ++i) {
                        if (v[i] == elem) {
                                trouve = true;
                                pos = i;
                        }
                }
        }
        return pos;
}


int main(int argc, char *arcv[]){
        vector<Patient> salleAttente;
        readFile(arcv[1], &salleAttente);
        cout << "-------TEST VECTOR--------" << endl;
        for(int i = 0; i < salleAttente.size(); ++i) {
                cout << salleAttente[i] << endl;
        }
}
