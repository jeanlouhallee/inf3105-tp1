/*
--------------------------------TASKLIST----------------------------------------
--1) Modifier le constructeur pour qu'il s'assure que la priorite du patient
     soit >= 1 et <= 5
--2) Implementer ou trouver un algorithme de tri ordonner le vecteur de
     [0] : le plus prioritaire a
     [N-1] : le moins prioritaire
     Side-Note : Changer vecteur pour une organisation en pile?
--3) Redifinir les surcharges d'operateurs booleen pour implementer
     un algorithme NON naif
--4) Modification du OUTPUT
--5) Lire correctement depuis un fichier //Done
--6) Ajouter un destructeur
 -------------------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <assert.h>
#include <vector>
using namespace std;
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
      /*
        Surcharge le l'operateur <<. A MODIFIER pour que ca conincide avec les specification du prof pour l'affichage
         */
        friend ostream& operator << (ostream& os, const Patient& patient) {
          os << "No Patient : " << patient._noPatient << ", Temp attendu dans la salle d'attente (s) : " << patient._tempAttente << " Priorite : " << patient._priorite;
          return os;
        }
        /*
        Surcharge de l'operateur >>. Va nous permettre de lire les donnees facilement en ignorant les espaces
         */
        friend istream& operator >> (istream& is, Patient& patient) {

          if(is >> patient._noPatient){
            is >> patient._tempAttente >> patient._priorite;
          }
          return is;
        }
        /*
        Surcharge naive de l'operateur <. Cette version ne prendra en consideration que la priorité et le temps d'attente
        On suppose que le PREMIER element du vecteur est CELUI QUI DOIT PASSER EN PREMIER
        On suppose que le DERNIER element du vecteur est CELUI QUI DOIT PASSER EN DERNIER
        p1 < p2 : suppose que p1 est plus prioritaire que p2
         */
        bool operator< (const Patient &p2){
            bool p1PlusPrioritairep2 = false;
            if (_priorite < p2._priorite){
                    p1PlusPrioritairep2 = true;
            } else {
                if (_priorite == p2._priorite){
                  if (_tempAttente > p2._tempAttente){
                      p1PlusPrioritairep2 = true;
                  }
              }
            }
            return p1PlusPrioritairep2;
        }
};

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
/*
modification
 */

void readFile(char *arcv, vector<Patient> *vp){
    ifstream file(arcv);
    if(file){
        Patient patient;
        while(file >> patient){
            vp->push_back(patient);
            cout << patient << endl;
        }
        file.close();
    }else{
        cout << "TENGO UN PROBLEMA SENOR" << endl;
    }
}


int main(int argc, char *arcv[]){
    vector<Patient> salleAttente;
    readFile(arcv[1], &salleAttente);
    cout << "-------TEST VECTOR--------" << endl;
    for(int i = 0; i < salleAttente.size(); ++i){
        cout << salleAttente[i] << endl;
    }
}
