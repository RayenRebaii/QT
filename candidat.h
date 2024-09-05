#ifndef RAPPORT_H
#define RAPPORT_H

#include <QString>
#include <QDate>
#include "ui_mainwindow.h"
#include "mainwindow.h"
class Candidat
{
public:
    Candidat();
    Candidat(int, QString,QString,QString,int);
    QString getnom(){return nom;}
    QString getprenom(){return prenom;}
    int getcandidat_id(){return id_cand;}
    int getoEmpid(){return oEmpid;}
    void setoEmpid(int oEmpid){this->oEmpid=oEmpid;}

     QString gettitre_travail(){return titre_travail;}
    void setnom(QString nom){this->nom=nom;}
    void setprenom(QString prenom){this->prenom=prenom;}
    void seticandidat_id(int id_cand){this->id_cand=id_cand;}
    void settitre_travail(int titre_travail){this->titre_travail=titre_travail;}
bool ajouter();

bool supprimer(QString id);
bool modifier();
void afficher(Ui::MainWindow *ui);

private :
    QString nom,prenom,titre_travail;
    int id_cand;
    int oEmpid;

};

#endif // RAPPORT_H
