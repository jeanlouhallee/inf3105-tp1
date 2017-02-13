/*
   --------------------------------TASKLIST----------------------------------------
   --1) Modifier le constructeur pour qu'il s'assure que la priorite du patient
     soit >= 1 et <= 5 // DONE
   --2) Implementer ou trouver un algorithme de tri ordonner le vecteur de
    [0] : le plus prioritaire a
    [N-1] : le moins prioritaire
    Side-Note : Changer vecteur pour une organisation en pile?
    //DONE
   --3) Modification du OUTPUT //DONE
   --4) Lire correctement depuis un fichier //DONE
   --5) Ajouter un destructeur //DONE
   --6) Trouver comment empecher que deux patient aille le meme noPatient //DONE
   --7) Ajout d'une fonction traitementSalleAttente qui ajoute de facon iterati-
   ve le temps de traitement a la position du patient // DONE
   --8) Faire la fonction qui fait la moyenne geometrique
   --9) Afficher les moyennes geometriques
   --10) Redifinir les surcharges d'operateurs booleen pour implementer
     un algorithme NON naif
   --11)
   --12)
   -------------------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <algorithm>
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
    ~Patient() {}
    int get_priorite();
    int get_tempAttente();
    void set_tempAttente(int tempAttente);
    friend bool operator< (const Patient &p1, const Patient &p2);
    friend istream& operator >> (istream& is, Patient& patient);
    friend ostream& operator << (ostream& os, const Patient& patient);
  };
    /*
       Surcharge naive de l'operateur <. Cette version ne prendra en consideration que la priorité et le temps d'attente
       On suppose que le PREMIER element du vecteur est CELUI QUI DOIT PASSER EN PREMIER
       On suppose que le DERNIER element du vecteur est CELUI QUI DOIT PASSER EN DERNIER
       p1 < p2 : suppose que p1 est plus prioritaire que p2
     */
bool operator< (const Patient &p1, const Patient &p2){
            bool p1PlusPrioritairep2 = false;
            if (p1._priorite < p2._priorite) {
                    p1PlusPrioritairep2 = true;
            }
            else {
                    if (p1._priorite == p2._priorite) {
                            if (p1._tempAttente > p2._tempAttente) {
                                    p1PlusPrioritairep2 = true;
                            }
                    }
            }
            return p1PlusPrioritairep2;
    }


vector<int> Patient::listeNoPatient;
/*
   Surcharge le l'operateur <<. A MODIFIER pour que ca conincide avec les specification du prof pour l'affichage
 */
ostream& operator << (ostream& os, const Patient& patient) {
        os << "\t" << patient._noPatient << "\t\t" << patient._priorite << "\t\tTemp attendu: " << patient._tempAttente;
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
int Patient::get_tempAttente(){
        return _tempAttente;
}
void Patient::set_tempAttente(int tempAttente){
        _tempAttente = tempAttente;
}
int Patient::get_priorite(){
    return _priorite;
}
void readFile(char *arcv, vector<Patient> *vp){
        ifstream file(arcv);
        if(file) {
                Patient patient;
                while(file >> patient) {
                        vp->push_back(patient);
                }
                file.close();
        }else{
                cout << "Fichier introuvable." << endl;
        }
}
/**
 * findElem     Comme <vector> ne semblait pas offrir une fonction qui retourne
 * la premiere occurence d'un element dans un ensemble, nous avons fait une
 * petite fonction qui parcours l'ensemble
 * @param  v    vector dans lequel la recherche se fait
 * @param  elem Element recherche
 * @return      Retourne la premiere occurence dans l'ensemble
 */
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
/**
 * imprimerSalleAttent  Permet d'afficher l'etat actuel de la salle d'attente
 * @param p             Salle d'attente a afficher
 */
void imprimerSalleAttente(const vector<Patient> &p){
        int i = 0;
        for(int i = 0; i < p.size(); ++i) {
                cout << "\tno_patient\tpriorite" << endl;
                cout << i+1 << p[i] << endl;
        }

}
/**
 * traiterSalleAttente Fonction prenant en parametre une salle d'attente ainsi que
 * le delai pour traiter un patient. Ajoute (delaiTraitement*position) a chaque
 * patient pour savoir combien de temps ça aura pris pour que chacun ait été
 * traité
 * @param salleAttente    vecteur de patient
 * @param delaiTraitement Delai de traitement minimum
 */
void traiterSalleAttente(vector<Patient> &salleAttente, int delaiTraitement){
    int i = 0;
    for ( i = 0; i < salleAttente.size(); i++){
          salleAttente[i].set_tempAttente(salleAttente[i].get_tempAttente() + (delaiTraitement*i));
    }
}

void statistiques(vector<Patient> &sa, const int tab[]){
    int i = 0;
    double nbDeux = 0, nbTrois = 0, nbQuatre = 0, nbCinq = 0;
    double deuxOk = 0, troisOk = 0, quatreOk = 0, cinqOk = 0;


    for(i ; i < sa.size(); ++i){
    
        if(sa[i].get_priorite() == 2){
            ++nbDeux;
            if( (tab[0] - sa[i].get_tempAttente()) >= 0 ){
                ++deuxOk;
            }
        }else if(sa[i].get_priorite() == 3){
            ++nbTrois;
            if( (tab[1] - sa[i].get_tempAttente()) >= 0 ){
                ++troisOk;
            }

        }else if(sa[i].get_priorite() == 4){
            ++nbQuatre;
            if( (tab[2] - sa[i].get_tempAttente()) >= 0 ){
                ++quatreOk;
            }

        }else if(sa[i].get_priorite() == 5){
            ++nbCinq;
            if( (tab[3] - sa[i].get_tempAttente()) >= 0 ){
                ++cinqOk;
            }

        }
    }
    cout << sa[0].get_tempAttente() << endl;
    cout << endl << nbDeux << endl << deuxOk << endl;
    cout << "--------" << endl << "Priorite 2 " << "Priorite 3 " << "Priorite 4 "  << "Priorite 5" << endl;
    cout << deuxOk/nbDeux  << "      " << troisOk/nbTrois << "      "  << quatreOk/nbQuatre  << "      " << cinqOk/nbCinq  << endl;
    cout << (deuxOk/nbDeux) * (troisOk/nbTrois) * (quatreOk/nbQuatre) * (cinqOk/nbCinq) <<endl;
}

int main(int argc, char *arcv[]){
        enum {prior2, prior3, prior4, prior5};
        vector<Patient> salleAttente;
        const int tempTraitement = 5;
        const int tempPriorite[4] = {15, 30, 60, 120};
        readFile(arcv[1], &salleAttente);
        cout << "-------TEST VECTOR--------" << endl;
        imprimerSalleAttente(salleAttente);
        cout << "-------TEST VECTOR Trie--------" << endl;
        sort(salleAttente.begin(), salleAttente.begin()+salleAttente.size());
        imprimerSalleAttente(salleAttente);
        cout << "-------TEST VECTOR apres traitement--------" << endl;
        traiterSalleAttente(salleAttente, 5);
        imprimerSalleAttente(salleAttente);
        statistiques(salleAttente, tempPriorite);
}
