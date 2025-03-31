#include "../include/bdd.h"

Base::Base()
{
    Driver *pilote = mariadb::get_driver_instance();
    SQLString sq = SQLString("jdbc:mariadb://localhost:3306/Bobinage");
    Properties idd = Properties({{"user", "superviseur"}, {"password", "superviseur"}});
    connec = pilote->connect(sq, idd);
}

Base::~Base()
{
    if (connec)
    {
        delete connec;
    }
}

Connection* Base::getConnection()
{
    return connec;
}

list<Temperature> *Base::obtenirDataFonctTemp(string dateDebut, string dateFin, int idMachine = 1)
{

    list<Temperature> *t_resultat = new list<Temperature>{};

    PreparedStatement *reqselec;
    if ((dateDebut != "") && (dateFin != ""))
    {
        reqselec = connec->prepareStatement("SELECT * FROM FonctionnementTemp WHERE date > ? AND date < ? AND idMachine = ?;");
        reqselec->setDateTime(1, dateDebut);
        reqselec->setDateTime(2, dateFin);
        reqselec->setInt(3, idMachine);
    }
    else
    {
        reqselec = connec->prepareStatement("SELECT * FROM FonctionnementTemp WHERE  idMachine = ?;");
        reqselec->setInt(1, idMachine);
    }
    ResultSet *resultat = reqselec->executeQuery();
    while (resultat->next())
    {
        string date = resultat->getString(2).c_str();
        float tempe = resultat->getFloat(3);
        t_resultat->push_back(Temperature(tempe, date));
    }
    connec->commit();
    return t_resultat;
}

list<Vibration> *Base::obtenirDataFonctVibra(string dateDebut, string dateFin, int idMachine = 1)
{

    list<Vibration> *v_resultat = new list<Vibration>{};

    PreparedStatement *reqselec;
    if ((dateDebut != "") && (dateFin != ""))
    {
        reqselec = connec->prepareStatement("SELECT * FROM FonctionnementVibra WHERE date > ? AND date < ? AND idMachine = ?;");

        reqselec->setDateTime(1, dateDebut);
        reqselec->setDateTime(2, dateFin);
        reqselec->setInt(3, idMachine);
    }
    else
    {
        reqselec = connec->prepareStatement("SELECT * FROM FonctionnementVibra WHERE  idMachine = ?;");
        reqselec->setInt(1, idMachine);
    }

    ResultSet *resultat = reqselec->executeQuery();

    while (resultat->next())
    {

        string date = resultat->getString(2).c_str();
        string axe = resultat->getString(3).c_str();
        float asymetrie = resultat->getFloat(4);
        float moyenne = resultat->getFloat(5);
        float aplatissement = resultat->getFloat(6);
        float dispersion = resultat->getFloat(7);
        float efficace = resultat->getFloat(8);
        float min = resultat->getFloat(9);
        float max = resultat->getFloat(10);

        v_resultat->push_back(Vibration(axe, asymetrie, moyenne, aplatissement, dispersion, efficace, min, max, date));
    }
    connec->commit();
    return v_resultat;
}

list<Contexte> *Base::obtenirDataCont(string dateDebut, string dateFin)
{

    list<Contexte> *c_resultat = new list<Contexte>{};

    PreparedStatement *reqselec = connec->prepareStatement("SELECT * FROM FonctionnementTemp WHERE date > ? AND date < ?;");

    reqselec->setDateTime(1, dateDebut);
    reqselec->setDateTime(2, dateFin);
    ResultSet *resultat = reqselec->executeQuery();

    while (resultat->next())
    {
        string date = resultat->getString(2).c_str();
        float tempAmb = resultat->getFloat(3);
        float humidite = resultat->getFloat(4);
        float tension_reseau = resultat->getFloat(5);
        c_resultat->push_back(Contexte(tempAmb, humidite, tension_reseau, date));
    }
    connec->commit();
    return c_resultat;
}

list<Evenement> *Base::obtenirListeEven(string dateDebut, string dateFin, int idMachine = 1)
{

    list<Evenement> *e_resultat = new list<Evenement>{};
    PreparedStatement *reqselec;
    if ((dateDebut != "") && (dateFin != ""))
    {
        reqselec = connec->prepareStatement("SELECT * FROM Evenements WHERE date > ? AND date < ? AND idMachine = ?;");

    reqselec->setDateTime(1, dateDebut);
    reqselec->setDateTime(2, dateFin);
    reqselec->setInt(3, idMachine);
    }
    else
    {
        reqselec = connec->prepareStatement("SELECT * FROM Evenements WHERE idMachine = ?;");
        reqselec->setInt(1, idMachine);        
    }
    ResultSet *resultat = reqselec->executeQuery();

    while (resultat->next())
    {
        string date = resultat->getString(2).c_str();
        string type = resultat->getString(3).c_str();
        e_resultat->push_back(Evenement(type, date));
    }
    connec->commit();
    return e_resultat;
}

list<Image> *Base::obtenirImage(string dateDebut, string dateFin, int idMachine = 1)
{

    list<Image> *i_resultat = new list<Image>{};

    PreparedStatement *reqselec = connec->prepareStatement("SELECT * FROM Evenements WHERE date > ? AND date < ? AND idMachine = ?;");

    reqselec->setDateTime(1, dateDebut);
    reqselec->setDateTime(2, dateFin);
    reqselec->setInt(3, idMachine);

    ResultSet *resultat = reqselec->executeQuery();

    while (resultat->next())
    {
        string date = resultat->getString(2).c_str();
        string nom = resultat->getString(3).c_str();
        string type = resultat->getString(4).c_str();
        i_resultat->push_back(Image(nom, type, date));
    }
    connec->commit();
    return i_resultat;
}
bool Base::obtenirApprentissageTemp(int idMachine = 1)
{
    bool apprentissage = false;

    PreparedStatement *reqselec = connec->prepareStatement("SELECT apprentissageTermineTemp from Machine WHERE id = ?;");

    reqselec->setInt(1, idMachine);

    ResultSet *resultat = reqselec->executeQuery();

    while (resultat->next())
    {
        apprentissage = resultat->getBoolean(1);
    }

    connec->commit();
    return apprentissage;
}

void Base::obtenirSeuilTemp(float &tempMax, float &tempMoy, int idMachine)
{
    PreparedStatement *reqselec = connec->prepareStatement("SELECT * FROM SeuilTemp");

    ResultSet *resultat = reqselec->executeQuery();

    while (resultat->next())
    {
        tempMax = resultat->getFloat(2);
        tempMoy = resultat->getFloat(3);
    }
}

void Base::obtenirSeuilVibra(float &vibraMaxX, float &vibraMaxY, float &vibraMaxZ,int idMachine)
{
    PreparedStatement *reqselec = connec->prepareStatement("SELECT * FROM SeuilVibra");

    ResultSet *resultat = reqselec->executeQuery();

    while (resultat->next())
    {
        vibraMaxX = resultat->getFloat(2);
        vibraMaxY = resultat->getFloat(3);
        vibraMaxZ = resultat->getFloat(4);
    }
}

//////                               //////
//////*        AJOUTER DONNEES      *//////
//////                               //////

int Base::ajouterDataFonctTemp(string date, float tempMachine, int idMachine = 1)
{

    PreparedStatement *reqadd = connec->prepareStatement("INSERT INTO FonctionnementTemp(date,tempMachine,idMachine) VALUES (?,?,?);");
    PreparedStatement *reqselec = connec->prepareStatement("SELECT id FROM FonctionnementTemp WHERE date = ?;");

    int idTemp;
    reqadd->setString(1, date);
    reqadd->setFloat(2, tempMachine);
    reqadd->setInt(3, idMachine);
    reqadd->executeQuery();
    connec->commit();

    reqselec->setString(1, date);
    reqselec->execute();
    ResultSet *resultat = reqselec->executeQuery();
    while (resultat->next())
    {

        idTemp = resultat->getInt(1);
    }

    connec->commit();
    return idTemp;
}

int Base::ajouterDataFonctVibra(string date, string axe, float asymetrie, float moyenne, float aplatissement, float dispersion, float efficace, float min, float max, int idMachine = 1)
{

    PreparedStatement *reqadd = connec->prepareStatement("INSERT INTO FonctionnementVibra(date, axe, asymetrie, moyenne, aplatissement, dispersion, efficace, min, max, idMachine) VALUES (?,?,?,?,?,?,?,?,?,?);");
    PreparedStatement *reqselec = connec->prepareStatement("SELECT id FROM FonctionnementVibra WHERE date = ?;");

    int idVibra;
    reqadd->setString(1, date);
    reqadd->setString(2, axe);
    reqadd->setFloat(3, asymetrie);
    reqadd->setFloat(4, moyenne);
    reqadd->setFloat(5, aplatissement);
    reqadd->setFloat(6, dispersion);
    reqadd->setFloat(7, efficace);
    reqadd->setFloat(8, min);
    reqadd->setFloat(9, max);
    reqadd->setInt(10, idMachine);

    reqadd->executeQuery();
    connec->commit();

    reqselec->setString(1, date);
    reqselec->execute();
    ResultSet *resultat = reqselec->executeQuery();
    while (resultat->next())
    {
        idVibra = resultat->getInt(1);
    }

    connec->commit();
    return idVibra;
}

int Base::ajouterDataCont(string date, float tempAmb, float humidite, float tension_reseau)
{
    PreparedStatement *reqadd = connec->prepareStatement("INSERT INTO Contexte(date,tempAmb,humidite,tensionReseau) VALUES (?,?,?,?);");
    PreparedStatement *reqselec = connec->prepareStatement("SELECT id FROM Contexte WHERE date = ?;");

    int idCont;
    reqadd->setString(1, date);
    reqadd->setFloat(2, tempAmb);
    reqadd->setFloat(3, humidite);
    reqadd->setFloat(4, tension_reseau);
    reqadd->executeQuery();
    connec->commit();

    reqselec->setString(1, date);
    reqselec->execute();
    ResultSet *resultat = reqselec->executeQuery();
    while (resultat->next())
    {
        idCont = resultat->getInt(1);
    }

    connec->commit();
    return idCont;
}

int Base::ajouterListeEven(string date, string type, Temperature* tempe, Contexte* contexte, Image* image,  int idMachine)
{
    int idTemp = 0, idVibra = 0, idContexte = 0, idEven = 0;
    idTemp = ajouterDataFonctTemp(date, tempe->getValeur(), idMachine);
    idContexte = ajouterDataCont(date,contexte->getTempAmb(),contexte->getHumidite(),contexte->getTensionReseau());
    
    PreparedStatement *reqadd = connec->prepareStatement("INSERT INTO Evenements(date,type,idContexte,idFonctTemp,idMachine) VALUES (?,?,?,?,?);");
    PreparedStatement *reqselec = connec->prepareStatement("SELECT id FROM Evenements WHERE date = ?;");

    reqadd->setString(1, date);
    reqadd->setString(2, type);
    reqadd->setInt(3, idContexte);
    reqadd->setInt(4, idTemp);
    reqadd->setInt(5, idMachine);
    reqadd->executeQuery();
    connec->commit();

    reqselec->setString(1, date);
    reqselec->execute();

    ResultSet *resultat = reqselec->executeQuery();
    while (resultat->next())
    {
        idEven = resultat->getInt(1);
    }

    ajouterImage(date,image->getNom(),image->getType(), idEven);

    return idEven;
}

int Base::ajouterImage(string date, string nom, string type, int idEven)
{
    PreparedStatement *reqadd = connec->prepareStatement("INSERT INTO Image(date,nom,type,idEven) VALUES (?,?,?,?);");
    PreparedStatement *reqselec = connec->prepareStatement("SELECT id FROM Image WHERE date = ?;");

    int idImage;
    reqadd->setString(1, date);
    reqadd->setString(2, nom);
    reqadd->setString(3, type);
    reqadd->setInt(4, idEven);    
    reqadd->executeQuery();
    connec->commit();

    reqselec->setString(1, date);
    reqselec->execute();
    ResultSet *resultat = reqselec->executeQuery();
    while (resultat->next())
    {
        idImage = resultat->getInt(1);
    }

    connec->commit();
    return idImage;
}

int Base::ajouterSeuilTemp(float tempMax, float tempMoy, int idMachine = 1)
{
    PreparedStatement *reqadd = connec->prepareStatement("INSERT INTO SeuilTemp(tempMax,tempMoy,idMachine) VALUES (?,?,?);");
    PreparedStatement *reqselec = connec->prepareStatement("SELECT id FROM SeuilTemp WHERE tempMax = ? AND tempMoy = ?;");

    int idSeuilT;
    reqadd->setFloat(1, tempMax);
    reqadd->setFloat(2, tempMoy);
    reqadd->setInt(3,idMachine);

    reqadd->executeQuery();
    connec->commit();

    reqselec->setFloat(1, tempMax);
    reqselec->setFloat(2, tempMoy);

    reqselec->execute();
    ResultSet *resultat = reqselec->executeQuery();
    while (resultat->next())
    {
        idSeuilT = resultat->getInt(1);
    }

    connec->commit();
    return idSeuilT;
}

int Base::ajouterSeuilVibra(float vibraMaxX, float vibraMaxY, float vibraMaxZ, int idMachine = 1)
{
    PreparedStatement *reqadd = connec->prepareStatement("INSERT INTO SeuilVibra(vibraMaxX,vibraMaxY,vibraMaxZ,idMachine) VALUES (?,?,?,?);");
    PreparedStatement *reqselec = connec->prepareStatement("SELECT id FROM SeuilVibra WHERE vibraMaxX = ? AND vibraMaxY = ? AND vibraMaxZ = ?;");

    int idSeuilV;
    reqadd->setFloat(1, vibraMaxX);
    reqadd->setFloat(2, vibraMaxY);
    reqadd->setFloat(3, vibraMaxZ);
    reqadd->setInt(4, idMachine);

    reqadd->executeQuery();
    connec->commit();

    reqselec->setFloat(1, vibraMaxX);
    reqselec->setFloat(2, vibraMaxY);
    reqselec->setFloat(3, vibraMaxZ);
    reqselec->execute();
    ResultSet *resultat = reqselec->executeQuery();
    while (resultat->next())
    {
        idSeuilV = resultat->getInt(1);
    }

    connec->commit();
    return idSeuilV;
}

PreparedStatement* effacer2;
void handle_signal(int sig) {
    static int count2 = 0;
    if (count2 <= 60) {
        cout << count2++ << endl;
    } else {
        effacer2->execute();
        Base* base = new Base();
        base->getConnection()->commit();   // commande delete affectée
        delete base;  
        //kill(getpid(),SIGINT);
    }
}


void Base::supprimer() {

    string dateMax;
    PreparedStatement *reqselec = connec->prepareStatement("SELECT MAX(date) FROM FonctionnementTemp;");
    effacer2 = connec->prepareStatement("DELETE FROM FonctionnementTemp WHERE date < DATE_SUB(?, INTERVAL 24 HOUR);");
    ResultSet *resultat = reqselec->executeQuery(); // resultat contient la date la plus récente

    while (resultat->next()) {
        dateMax = resultat->getString(1); // datemax contient la date la plus récente
    }

    effacer2->setString(1, dateMax); // commande delete prête

    timer_t timer_id;
    struct itimerspec timer_spec;

    struct sigaction action;
    action.sa_flags = 0;
    action.sa_handler = handle_signal;
    sigaction(SIGRTMIN, &action, NULL);

    struct sigevent evento;
    evento.sigev_signo = SIGRTMIN;
    evento.sigev_notify = SIGEV_SIGNAL;
    timer_create(CLOCK_MONOTONIC, &evento, &timer_id);

    timer_spec.it_value.tv_sec = 1;
    timer_spec.it_value.tv_nsec = 0;
    timer_spec.it_interval.tv_sec = 1;
    timer_spec.it_interval.tv_nsec = 0;
    timer_settime(timer_id, 0, &timer_spec, NULL);
    while(1){
    }
}
thread Base::renvoie_supprimer()
{
    while(true){
    return thread(&Base::supprimer, this);
    std::this_thread::sleep_for(std::chrono::hours(24));
   }
}
