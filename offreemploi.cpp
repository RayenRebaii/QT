#include "offreemploi.h"


OffreEmploi::OffreEmploi()
{
id_offre=0;
titre="";
description="";

}
OffreEmploi::OffreEmploi(int id_offre, QString titre, QString description ,QDateTime date_mise_en_actif)
{
this->id_offre=id_offre;
    this->titre=titre;
this->description=description;
this ->date_mise_en_actif=date_mise_en_actif;
}

bool OffreEmploi::ajouter()
{
    QSqlQuery query;
    QString res=QString::number(id_offre);

    query.prepare("insert into OffreEmploi (id_offre,titre,description,date_mise_en_actif)""values(:id_offre,:titre,:description,:date_mise_en_actif)");
    query.bindValue(":id_offre", res);
            query.bindValue(":titre", titre);
    query.bindValue(":description", description);
    query.bindValue(":date_mise_en_actif", date_mise_en_actif);
return query.exec();
}


bool OffreEmploi::supprimer(QString id_offre)
{
QSqlQuery query;

query.prepare("Delete from OffreEmploi where id_offre=:id_offre");
query.bindValue(":id_offre",id_offre);
return query.exec();
}
bool OffreEmploi::modifier()
{

    QSqlQuery query;
    QString res=QString::number(id_offre);
          query.prepare("UPDATE OffreEmploi "" SET id_offre=:id_offre,titre=:titre,  description=:description,date_mise_en_actif=:date_mise_en_actif  where id_offre='"+res+"' ");


          query.bindValue(":id_offre", res);
          query.bindValue(":titre", titre);
          query.bindValue(":description", description);

            query.bindValue(":date_mise_en_actif", date_mise_en_actif);
        return    query.exec();
}

void OffreEmploi::afficher(Ui::MainWindow *ui)
{

    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();

    qry->prepare("select * from OffreEmploi");
    qry->exec();
    modal->setQuery(*qry);
    modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    modal->setHeaderData(1,Qt::Horizontal,QObject::tr("titre"));
    modal->setHeaderData(2,Qt::Horizontal,QObject::tr("description"));
     modal->setHeaderData(3,Qt::Horizontal,QObject::tr("Titre"));

    ui->tableView_2->setModel(modal);

    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}


