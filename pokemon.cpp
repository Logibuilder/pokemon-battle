 #include <cstdlib>
 #include <ctime>
 #include <iostream>
 #include <list>
 #include <map>
 #include <windows.h>

 using namespace std;
            

 // Classe de mère : Pokemon

 class Pokemon{
    protected :
            string nom;
            int id, idJoueur, pV, attaque, defense, vitesse;
            map<string,int> puissanceAttaque;
    public :
            //Constructeur par défaut
            Pokemon():id(0), idJoueur(0), nom(""), pV(0), attaque(0), defense(0), vitesse(0){
            }
            
           // Constructeur classique
            Pokemon(int id, int idJoueur, string n, int pv, int a, int d, int v): id(id), idJoueur(idJoueur), nom(n), pV(pv), attaque(a), defense(d), vitesse(v){
            }
            // Constructeur par recopie
            Pokemon(const Pokemon & p): id(id), idJoueur(idJoueur), nom(p.nom), pV(p.pV), attaque(p.attaque), defense(p.defense), vitesse(p.vitesse){
                
            }
            // Destructeur

            virtual ~Pokemon(){};
            
            void afficherStat(){

                cout << "Nom : " << nom << endl;
                cout << "PV : " << pV << endl;
                cout << "Attaque : " << attaque << endl;
                cout << "Defense : " << defense << endl;
                cout << "Vitesse : " << vitesse << endl;

            }

            //méthode virtuelle pure renvoyant le type du Pokémon sous forme d’entier.
            virtual int getType() const = 0;

            // retourn le nom d'un pokemon
            string getNom() const {
                return to_string(idJoueur) + "_" + nom + "_" + to_string(id);
            }


            //méthode renvoyant la puissance d'attaque d'un pokemon.
            pair<string,int> getPuissanceAttaque(){

                // Générer un nombre aléatoire entre 1 et 3
                int index = rand() % 3; // 0, 1 ou 2

                // Obtenir l'itérateur correspondant au numéro généré
                auto it = puissanceAttaque.begin();
                std::advance(it, index); // Avancer jusqu'à l'élément index

                // Renvoyer la clé (nom de l'attaque) et la valeur (puissance)
                return *it;

            };
            double calculerMultiplicateurType(const Pokemon & cible) const{
                int atq = getType(); 
                int cib = cible.getType(); 

                if (atq == 1) {
                    switch (cib) {
                        case 1: return 1.0 ;
                        case 2: return 0.5 ;
                        case 3: return 2.0 ;
                    }
                } else if (atq == 2) {
                    switch (cib) {
                        case 1: return 2.0 ;
                        case 2: return 1.0 ;
                        case 3: return 0.5 ;
                    }
                } else {
                    switch (cib) {
                        case 1: return 0.5 ;
                        case 2: return 2.0 ;
                        case 3: return 1.0 ;
                    }
                }
                return 1.0;
            }
            // gère l'algorithme d'attaque entre deux pokemons
            void attaquer(Pokemon & cible){
                int attaqueAttaquant = this->attaque;
                int defenseCible = cible.getDefense();
                pair<string,int> puissanceAttaque = this->getPuissanceAttaque();
                string typePuissance = puissanceAttaque.first;
                int valeurPuissance = puissanceAttaque.second;
                double multiplicateurType = this->calculerMultiplicateurType(cible);
                // générer un nombre entre 0.85 et 1.0 
                double facteurAleatoire = (85 + rand() % 16)/ 100.0;

                double degats = (attaqueAttaquant * valeurPuissance /defenseCible) 
                                * multiplicateurType //dépendant du type des deux pokémons
                                * facteurAleatoire; //valeur aléatoire permettant ajouter du dynamisme au jeu
                
                cible.perdrePV(static_cast<int>(degats));

                cout << getNom() << " utilise " << typePuissance << " sur " << cible.getNom() << " et inflige " << static_cast<int>(degats) << " dégâts !" << endl;

                if (cible.estKO()) {
                     cout << cible.getNom() << " est KO !" << endl;
                }
                Sleep(2000); // Pause de 3000 millisecondes (3 secondes)
                
            }

            void perdrePV(int montant){
                pV -= montant;

            }
            bool estKO(){
                return pV<=0;
            }

            int getAttaque(){
                return attaque;
            }

            int getDefense(){
                return defense;
            }
            int getVitesse(){
                return vitesse;
            }


 };
 // Classes filles 
 class FirePokemon: public Pokemon{

    public :
        FirePokemon(int id,int idJoueur, int pv, int a, int d, int v) : Pokemon(id, idJoueur, "Fire", pv, a, d, v){
            puissanceAttaque = {
            {"flameche",20},
            {"lance_flamme",45},
            {"deflagration", 55}
            };
        };


    FirePokemon() : Pokemon(){
    };
    
    int getType()  const override {
        return 1;
    }
 };

 class WaterPokemon: public Pokemon{


    public :
    WaterPokemon(int id,int idJoueur, int pv, int a, int d, int v) : Pokemon(id, idJoueur, "Water", pv, a, d, v){
        puissanceAttaque = {
        {"pistolet_a_Eau", 20},
        {"surf", 45},
        {"hydrocano", 55}
        };
    };
    
    int getType()  const override {
        return 2;
    }
 };

 class GrassPokemon: public Pokemon{

    public :
    GrassPokemon(int id,int idJoueur, int pv, int a, int d, int v) : Pokemon(id, idJoueur, "Grass" , pv, a, d, v){
        puissanceAttaque = {
        {"racine_enlacante", 20},
        {"feuille_magique", 45},
        {"canon_graine", 55}
      };
    };
    
    int getType()  const override {
        return 3;
    }
 };

  static void combat(Pokemon *P1, Pokemon *P2){
    int tour = 1;
    cout << "Début du combat entre " << P1->getNom() 
    << " et " << P2->getNom() << " !" << endl;

    int v1 = P1->getVitesse();
    int v2 = P2->getVitesse();

    if (v1 > v2) {
        while (!P1->estKO()&&!P2->estKO()){
            cout << "Tour " << tour++ << " :" << endl;
            P1->attaquer(*P2);
            //si P2 n'est pas KO alors il attaque sinon on sort de la boucle while
            if ( !P2->estKO() ) {
                P2->attaquer(*P1);
            }
        }
      
    } else if (v1<v2) {

        while (!P1->estKO()&&!P2->estKO()){
            cout << "Tour " << tour++ << " :" << endl;
            P2->attaquer(*P1);
            
            //si P1 n'est pas KO alors il attaque sinon on sort de la boucle while
            if ( !P1->estKO() ) {
                P1->attaquer(*P2);
            }
        }

    } else {
        // Tirage au sort
        bool pileFace = rand() % 2 == 0;
        if(pileFace){
            while (!P1->estKO()&&!P2->estKO()){
                cout << "Tour " << tour++ << " :" << endl;
                //si P2 n'est pas KO alors il attaque sinon on sort de la boucle while
                if ( !P2->estKO() ) {
                    P2->attaquer(*P1);
                }
            }
        }else{
            while (!P1->estKO()&&!P2->estKO()){
                cout << "Tour " << tour++ << " :" << endl;
                P2->attaquer(*P1);
                //si P1 n'est pas KO alors il attaque sinon on sort de la boucle while
                if ( !P1->estKO() ) {
                    P1->attaquer(*P2);
                }
            }  
        }
        
    }
    cout << "Fin du combat ! ";
    if (P1->estKO()) {
        cout << P2->getNom() << " remporte le combat !" << endl;
    } else {
        cout << P1->getNom() << " remporte le combat !" << endl;
    }

 }


 class Joueur{
    private :   
                int id;
                string nom;
                // on ajoute le pointeur * pour eviter de creer que des 
                //copies de Pokemon et permettre le polymorphisme sur les sous classes.
                // liste de Pokemon de base
                list<Pokemon*> listePokemon;
                // liste de Pokemon avec lesquels le joueur va jouer
                list<Pokemon*> equipePokemon;
    public : 
    
        Joueur(int id,string nom) :id(id), nom(nom){};

        ~Joueur(){};
    
        int getId() { return id;}

        string getNom() { return nom;}

        list<Pokemon*> getEquipePokemon(){
            return equipePokemon;
        }

        void ajouterPokemon(Pokemon* p){
            listePokemon.push_back(p);
        }

        // renvoit une selection d'equipe de pokemon 
        void selectionnerEquipe() {
        int nb = 3 + rand() % listePokemon.size();
        auto it = listePokemon.begin();
        for (int i = 0; i < nb && it != listePokemon.end(); ++i, ++it) {
            equipePokemon.push_back(*it);
        }
        }

        // afficher l'equipe de pokemon du Joueur

        void afficherEquipe(){
            string res = "";
            for (auto p : equipePokemon) {
                res += p->getNom() + " ";
            }
            cout << "La liste des pokemons du joueur " <<getId()<<" est : \n" 
            <<res << endl;

        }

    void autoBattle(Joueur  * J2) {
        cout << "Début du combat automatique entre " << nom << " et " << J2->nom << " !" << endl;

    // Obtenir les équipes des deux joueurs
    list<Pokemon*> equipe1 = this->equipePokemon;
    list<Pokemon*> equipe2 = J2->equipePokemon;

    auto it1 = equipe1.begin();
    auto it2 = equipe2.begin();

    // Tant qu'il reste des Pokémon dans les deux équipes
    while (it1 != equipe1.end() && it2 != equipe2.end()) {

        Pokemon* P1 = *it1;
        Pokemon* P2 = *it2;

        cout << "Combat entre " << P1->getNom() << " et " << P2->getNom() << " !" << endl;

        // Simuler le combat entre les deux Pokémon
        combat(P1, P2);

        // Vérifier quel Pokémon est KO
        if (P1->estKO()) {
            ++it1; // Passer au Pokémon suivant dans l'équipe 1
        }
        if (P2->estKO()) {
            ++it2; // Passer au Pokémon suivant dans l'équipe 2
        }
    }

    // Déterminer le gagnant
    if (it1 == equipe1.end() && it2 != equipe2.end()) {
        cout << J2->getNom() << " remporte le combat automatique !" << endl;
    } else if (it2 == equipe2.end() && it1 != equipe1.end()) {
        cout << this->nom << " remporte le combat automatique !" << endl;
    } else {
        cout << "Le combat se termine par une égalité !" << endl;
    }

    // Réinitialiser les points de vie des Pokémon
    for (Pokemon* p : equipe1) {
        p->perdrePV(-p->getAttaque()); // Simule une restauration de PV
    }
    for (Pokemon* p : equipe2) {
        p->perdrePV(-p->getAttaque()); // Simule une restauration de PV
    }

    cout << "Fin du combat automatique !" << endl;
    }

};

 static Pokemon* creerPokemon(int id, int idJoueur){
     int type = rand() % 3;
     int pv = rand() % 100 + 250;
     int attaque = rand() % 20 + 10;
     int defense = rand() % 20 + 10;
     int vitesse = rand() % 20 + 10;
     switch(type) {
        case 0 : return new FirePokemon(id, idJoueur, pv, attaque, defense, vitesse);
        case 1 : return new WaterPokemon(id, idJoueur, pv, attaque, defense, vitesse);
        default : return new  GrassPokemon(id, idJoueur, pv, attaque, defense, vitesse);
    }
 }

 static Joueur* genererJoueur(int id){
    // Générer un nom de Joueu aléatoire
    string nom = "Joueur_" + to_string(id);
    Joueur* joueur = new Joueur(id,nom);
    // le nombre de pokemon doit être compris entre 3 et 6 car le minimum de pokemon pour jouer 
    // c'est 3 et le maximum c'est 6.
    int nbPokemon = 3 + rand() % 4;
    int j = 1;
    for(int i = 0; i<nbPokemon; i++){
        (*joueur).ajouterPokemon(creerPokemon(j, id));
        j++;
    }
    // remplir sa liste d'équipe
    joueur->selectionnerEquipe();

    // retourner le joueur
    return joueur;
 }


 int main() {
    srand(time(0)); // À faire une seule fois au début du programme


    // Génération des joueurs
    Joueur* joueur1 = genererJoueur(1);
    Joueur* joueur2 = genererJoueur(2);
    //cout<< joueur1->getEquipePokemon().size()<<endl;
    //cout<< joueur2->getEquipePokemon().size()<<endl;

    joueur1->afficherEquipe();
    joueur2->afficherEquipe();

    joueur1->autoBattle(joueur2) ; 
    //P1->afficherStat();
    //P2->afficherStat();
    //combat(P1,P2);
    return 0;
}