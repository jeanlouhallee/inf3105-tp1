/**
 *  TP1 INF3105
 *  Structures de données et algorithmes
 *  Étienne Carrier CARE
 *  Jean-Lou Hallée HALJ05129309
 *
 *
 *  Remise : 1 mars 2017
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <math.h>
using namespace std;
static const int tab[4] = {15 ,30, 60 ,120};

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
    int get_noPatient();
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
bool operator < (const Patient &p1, const Patient &p2){
    bool p1PlusPrioritairep2 = false;

    if (p1._priorite < p2._priorite) {
        p1PlusPrioritairep2 = true;
    }else {
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
 int Patient::get_noPatient(){
         return _noPatient;
 }

int Patient::get_tempAttente(){
        return _tempAttente;
}
void Patient::set_tempAttente(int tempAttente){
        _tempAttente = tempAttente;
}
int Patient::get_priorite(){
    return _priorite;
}

/**
 *lireFichier Fonction qui permet de lire le fichier contenant les informations
 * sur les patients.
 * @param argv Argument du programme contenant le nom du fichier a lire.
 * @param vp le vector de patient dans lequel il faut ajouter les patients.
 */
void lireFichier(char *argv, vector<Patient> *vp){
        ifstream file(argv);
        if(file) {
                Patient patient;
                while(file >> patient) {
                        vp->push_back(patient);
                }
                file.close();
        }else{
                cout << "Fichier introuvable." << endl;
                exit(0);
        }
}

/**
 * findElem     Comme <vector> ne semblait pas offrir une fonction qui retourne
 * la premiere occurence d'un element dans un ensemble, nous avons fait une
 * petite fonction qui parcours l'ensemble.
 * @param  v    vector dans lequel la recherche se fait.
 * @param  elem Element recherche.
 * @return      Retourne la premiere occurence dans l'ensemble.
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
 * imprimerSalleAttente  Permet d'afficher l'etat actuel de la salle d'attente.
 * @param p Salle d'attente a afficher.
 */
void imprimerSalleAttente(const vector<Patient> &patient){
        int i = 0;
        for(int i = 0; i < patient.size(); ++i) {
                cout << "\tno_patient\tpriorite" << endl;
                cout << i+1 << patient[i] << endl;
        }

}

/**
 * traiterSalleAttente Fonction prenant en parametre une salle d'attente ainsi que
 * le delai pour traiter un patient. Ajoute (delaiTraitement*position) a chaque
 * patient pour savoir combien de temps ça aura pris pour que chacun ait été
 * traité.
 * @param salleAttente    vecteur de patient.
 * @param delaiTraitement Delai de traitement minimum.
 */
void traiterSalleAttente(vector<Patient> &salleAttente, int delaiTraitement){
    int i = 0;
    for ( i = 0; i < salleAttente.size(); i++){
          salleAttente[i].set_tempAttente(salleAttente[i].get_tempAttente() + (delaiTraitement*i));
    }
}
/**
 * lireTemps permet de lire le temps de traitement pour un patient. Elle lit un int
 * passé en argument au programme. Il s'assure de la validité du nombre entré.
 * Si aucun argument est passé, la valeur par défaut est 5.
 * @param argc  La valeur de argc de la fonction main.
 * @param argv  la valeur de arcv[2] provenant du main (le nombre a valider)
 * @return le temps de traitement d'un patient.
 */

int lireTemps(int argc, char *argv){
    int tempsConsultation = 5;
    char *endptr;

    if(argc == 3){
       tempsConsultation = (int)strtol(argv, &endptr, 10);
       if(endptr == argv || *endptr != '\0'){
            cerr << "Mauvais temps entré." << endl;
            exit(-1);
       }else if(tempsConsultation < 1){
            cerr << "Le temps de consultation doit être supérieur à 0." << endl;
            exit(-1);
       }
    }


    return tempsConsultation;
}

/**
 * statistique permet de calculer la moyenne géométrique correspondant à
 * la proportion de patient qui passe dans les temps recommandés. Elle calcule
 * @param sa  La salle d'attente qui contient la liste de tous les patients
 *            avec tous les temps traités.
 */
void statistiques(vector<Patient> &sa){
    int i = 0;
    double moyenneGeo = 1;
    double resultat = 0;
    double nbPatient[4] = {0,0,0,0};
    double nbPatientCorrect[4] = {0,0,0,0};
    double racine = 4;


    for(i ; i < sa.size(); ++i){
            int priorite = sa[i].get_priorite()-2;
            nbPatient[priorite]++;
             if(tab[priorite] - sa[i].get_tempAttente() >= 0 ) {
               nbPatientCorrect[priorite]++;
             }
        }

    for (i = 0; i < 4; i++){
        if(nbPatient[i] != 0){
            resultat = nbPatientCorrect[i]/nbPatient[i];
            cout <<"Priorite " << i+2 << " ";
            cout << resultat << "\t" << endl;
            moyenneGeo *= resultat;
        }else{
            --racine;
        }
        pow(moyenneGeo, 1/racine);
    }

    cout << moyenneGeo  << endl;
}

/**
 * deuxiemeTri la fonction qui permet de trier une deuxieme fois la liste de
 * patients, en essayant d'envoyer les patients impossibles a passer dans
 * les temps recommandes a la fin de la liste.
 * @param delaiTraitement Le delai necessaire pour passer un patient.
 * @param sa  La salle d'attente qui contient la liste de tous les patients.
 */
void deuxiemeTri(vector<Patient> &sa, int delaiTraitement){
  int i = 0;
  int temps = 0;
  int baremeTemps = 0;
  vector<Patient>::iterator it;
  Patient patient;

  it = sa.begin();

  for(it; it != sa.end(); ++it){
    Patient patient = *it;

    if( (patient.get_tempAttente() + delaiTraitement * i) > (tab[patient.get_priorite() - 2]) ){
      cout << patient.get_noPatient() << endl;
      sa.insert(sa.end(), patient);
      sa.erase(it);
      it = sa.begin() + i - 1;
    }
  ++i;
  }
}

int main(int argc, char *argv[]){
        vector<Patient> salleAttente;
        const int tempTraitement = lireTemps(argc, argv[2]);

        lireFichier(argv[1], &salleAttente);
        cout << "-------TEST VECTOR premier tri--------" << endl;
        sort(salleAttente.begin(), salleAttente.begin()+salleAttente.size());
        imprimerSalleAttente(salleAttente);

        cout << "-------TEST VECTOR deuxieme tri--------" << endl;
        deuxiemeTri(salleAttente, tempTraitement);
        imprimerSalleAttente(salleAttente);

        cout << "-------TEST VECTOR apres traitement--------" << endl;
        traiterSalleAttente(salleAttente, tempTraitement);
        imprimerSalleAttente(salleAttente);
        statistiques(salleAttente);
}
