#include "candidat.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlQueryModel>
Candidat::Candidat()
{
id_cand=0;
nom="";
prenom="";
titre_travail="";
oEmpid=0;
}
Candidat::Candidat(int id_cand, QString nom, QString prenom ,QString titre_travail,int oEmpid)
{
this->id_cand=id_cand;
    this->nom=nom;
this->prenom=prenom;
this ->titre_travail=titre_travail;
    this -> oEmpid=oEmpid;
}

bool Candidat::ajouter()
{
    QSqlQuery query;
    QString res=QString::number(id_cand);

    query.prepare("insert into candidat (id_cand,nom,prenom,titre_travail,oEmpid)""values(:id_cand,:nom,:prenom,:titre_travail,:oEmpid)");
    query.bindValue(":id_cand", res);
            query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":titre_travail", titre_travail);
    query.bindValue(":oEmpid", oEmpid);

return query.exec();
}


bool Candidat::supprimer(QString id_cand)
{
QSqlQuery query;

query.prepare("Delete from candidat where id_cand=:id_cand");
query.bindValue(":id_cand",id_cand);
return query.exec();
}
bool Candidat::modifier()
{

    QSqlQuery query;
    QString res=QString::number(id_cand);
          query.prepare("UPDATE candidat "" SET id_cand=:id_cand,nom=:nom,  prenom=:prenom,titre_travail=:titre_travail, oEmpid=:oEmpid  where id_cand='"+res+"' ");


          query.bindValue(":id_cand", res);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);

            query.bindValue(":titre_travail", titre_travail);
             query.bindValue(":oEmpid", oEmpid);
        return    query.exec();
}

void Candidat::afficher(Ui::MainWindow *ui)
{

    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();

    qry->prepare("select * from candidat");
    qry->exec();
    modal->setQuery(*qry);
    modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    modal->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    modal->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
     modal->setHeaderData(3,Qt::Horizontal,QObject::tr("Titre"));
     modal->setHeaderData(3,Qt::Horizontal,QObject::tr("ID Emploi"));

    ui->tableView->setModel(modal);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}
