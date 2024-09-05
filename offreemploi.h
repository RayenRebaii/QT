#ifndef OFFREEMPLOI_H
#define OFFREEMPLOI_H
#include "QString"
#include "QDateTime"
#include "ui_mainwindow.h"
#include "mainwindow.h"
class OffreEmploi
{
public:
    OffreEmploi();
    OffreEmploi(int, QString,QString,QDateTime);
    QString gettitre(){return titre;}
    QString getdescription(){return description;}
     QDateTime getdate_mise_en_actif(){return date_mise_en_actif;}
    int getOffreEmploi_id(){return id_offre;}
    void settitre(QString titre){this->titre=titre;}
    void setdescription(QString description){this->description=description;}
    void setiOffreEmploi_id(int id_offre){this->id_offre=id_offre;}
    void setdate_mise_en_actif(QDateTime date_mise_en_actif){this->date_mise_en_actif=date_mise_en_actif;}

bool ajouter();
bool supprimer(QString id);
bool modifier();
void afficher(Ui::MainWindow *ui);

private :
    QString titre,description;
    QDateTime date_mise_en_actif;
    int id_offre;
};

#endif // OFFREEMPLOI_H
