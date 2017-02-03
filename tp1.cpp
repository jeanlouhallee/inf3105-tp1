#include <iostream>
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
private:
  int _noPatient;
  int _tempAttente;
  int _priorite;
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




int main(int argc, char *arcv[]){
        /*
        Structure prototype pour lire les patients
        A verifier :
        Est-ce que cette facon de proceder est optimale?
         */
        int i = 0;
        Patient p;
        std::vector<Patient> salleAttente;
        while (cin >> p) { // Tant que la lecture du patient fonctionne
            salleAttente.push_back(p); // met le patient dans la salle d'attente
            cout << salleAttente[i] << endl; // Affiche le patient
        }
        cout << argc << endl;
        cout << arcv[0] << endl;
        cout << "Fin du programme" << endl;
        return 0;
}
