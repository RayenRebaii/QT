#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>
#include <QTextStream>
#include <QTextDocument>
#include "offreemploi.h"
#include <QBarSeries>
#include <QBarSet>
#include <QtCharts>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Candidat Can;
    OffreEmploi off;
    off.afficher(ui);
    Can.afficher(ui);
    setCamera(QCameraInfo::defaultCamera());
ui->stackedWidget_2->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_2_clicked()
{
    int id_Candidat = ui->le_id_candidat->text().toInt();
    QString travail = ui->le_travail->text();
    QString nom = ui->le_nom->text();
    QString prenom = ui->le_prenom->text();
    int emploi = ui->Emploi->text().toInt();

    // Reset previous error messages
    ui->label_4->clear();
    ui->label_5->clear();
    ui->label_6->clear();
    ui->label_9->clear();
    ui->label_20->clear();

    bool isValid = true;

    if (ui->le_id_candidat->text().isEmpty()) {
        ui->label_4->setText("ID Candidat vide");
        isValid = false;
    }
    if (nom.isEmpty()) {
        ui->label_5->setText("Nom vide");
        isValid = false;
    }
    if (prenom.isEmpty()) {
        ui->label_6->setText("Prénom vide");
        isValid = false;
    }
    if (travail.isEmpty()) {
        ui->label_9->setText("Travail vide");
        isValid = false;
    }
    if (ui->Emploi->text().isEmpty()) {
        ui->label_20->setText("Emploi vide");
        isValid = false;
    }

    if (isValid) {
        Candidat Can(id_Candidat, nom, prenom, travail, emploi);
        bool test = Can.modifier();
        if (test) {
            Can.afficher(ui);
        }
    }
}




void MainWindow::updateChart(QVBoxLayout *layout) {
    // Create the chart and series
    QChart *chart = new QChart();
    QLineSeries *dateSeries = new QLineSeries();

    chart->setTitle("Statistiques - Dates de Mise en Actif");
    chart->legend()->hide();

    // Prepare and execute the query
    QSqlQuery query;
    query.prepare("SELECT id_offre, date_mise_en_actif FROM OffreEmploi");


    // Add data points to the series
    while (query.next()) {
        int id = query.value(0).toInt(); // Get the ID
        QString date = query.value(1).toString(); // Get the date

        // Convert date to integer for X-axis, if necessary (this example assumes you need numeric X-axis)
        // Here we use a simple index if the date cannot be converted directly
        int xValue = id; // This can be customized based on your actual data representation

        // Convert date to numeric value for Y-axis (this example assumes the date can be represented numerically)
        // You might need a more complex conversion depending on how you want to represent dates
        int yValue = id; // Replace with an actual conversion if necessary

        dateSeries->append(xValue, yValue);
    }

    chart->addSeries(dateSeries);

    // Configure the axes
    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("ID de l'employé");
    chart->addAxis(axisX, Qt::AlignBottom);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Date de Mise en Actif (Valeur Numérique)");
    chart->addAxis(axisY, Qt::AlignLeft);

    // Attach the axes to the series
    dateSeries->attachAxis(axisX);
    dateSeries->attachAxis(axisY);

    // Create QChartView to display the chart
    QChartView *chartView = new QChartView(chart, ui->chartview);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(561, 241);

    chartView->show();

}



void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int i;
i=index.row();
QModelIndex in=index.sibling(i,0);
QString val=ui->tableView->model()->data(in).toString();

    QSqlQuery qry;
    qry.prepare("select id_cand,nom,prenom,titre_travail,oEmpid from Candidat where id_cand='"+val+"' " );


    if(qry.exec())
    {
        while(qry.next())
        {
            ui->le_id_candidat->setText(qry.value(0).toString());
            ui->Emploi->setText(qry.value(4).toString());

            ui->le_nom->setText(qry.value(1).toString());
            ui->le_prenom->setText(qry.value(2).toString());
            ui->le_travail->setText(qry.value(3).toString());


        }
}
    updateQRImage();
}

void MainWindow::on_pushButton_3_clicked()
{
    QModelIndex index=ui->tableView->currentIndex();
        int i=index.row();
        QModelIndex in=index.sibling(i,0);
        QString val=ui->tableView->model()->data(in).toString();
        Candidat Can;


        bool test=Can.supprimer(val);
        if (test)
        {

            Can.afficher(ui);

        }
}

void MainWindow::on_pb_ajouter_clicked()
{
    int id_Candidat = ui->le_id_candidat->text().toInt();
    QString nom = ui->le_nom->text();
    QString prenom = ui->le_prenom->text();
    QString travail = ui->le_travail->text();
    int emploi = ui->Emploi->text().toInt();

    // Reset previous error messages
    ui->label_4->clear();
    ui->label_5->clear();
    ui->label_6->clear();
    ui->label_9->clear();
    ui->label_20->clear();

    bool isValid = true;

    // Validate the input fields
    if (ui->le_id_candidat->text().isEmpty()) {
        ui->label_4->setText("ID Candidat vide");
        isValid = false;
    }
    if (nom.isEmpty()) {
        ui->label_5->setText("Nom vide");
        isValid = false;
    }
    if (prenom.isEmpty()) {
        ui->label_6->setText("Prénom vide");
        isValid = false;
    }
    if (travail.isEmpty()) {
        ui->label_9->setText("Travail vide");
        isValid = false;
    }
    if (ui->Emploi->text().isEmpty()) {
        ui->label_20->setText("Emploi vide");
        isValid = false;
    }

    // Proceed with the addition if all fields are valid
    if (isValid) {
        Candidat Can(id_Candidat, nom, prenom, travail, emploi);

        bool test = Can.ajouter();
        if (test) {
            Can.afficher(ui);
        }
    }
}

    void MainWindow::setCamera(const QCameraInfo &cameraInfo)
    {
        Camera = new QCamera(cameraInfo);
        imageCapture = new QCameraImageCapture(Camera);
        Camera->setViewfinder(ui->viewfinder_4);
        connect(imageCapture, &QCameraImageCapture::readyForCaptureChanged, this, &MainWindow::readyForCapture);
        Camera->start();
    }


    void MainWindow::readyForCapture(bool ready)
    {
        ui->takeImageButton->setEnabled(ready);
    }
    void MainWindow::on_takeImageButton_clicked()
    {
        isCapturingImage = true;
        imageCapture->capture();
    }







void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();
    QString text=ui->lineEdit->text();

    if(text.isEmpty())
    {
         Candidat Can;
       Can.afficher(ui);


    }
    else
    {
        qry->prepare("select * from Candidat where ( id_cand LIKE'%"+text+"%' OR nom LIKE'%"+text+"%' OR prenom LIKE'%"+text+"%'OR titre_travail LIKE'%"+text+"%'OR oEmpid LIKE'%"+text+"%' ) ");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
    }
}



void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();
    QString type=ui->comboBox->currentText();
    if (type=="Par defaut"){
        qry->prepare("select * from Candidat");
        qry->exec();
        modal->setQuery(*qry);
        modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
        modal->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
        modal->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
         modal->setHeaderData(3,Qt::Horizontal,QObject::tr("Travail"));
           modal->setHeaderData(4,Qt::Horizontal,QObject::tr("Emploi"));
        ui->tableView->setModel(modal);}

        else if (type=="nom"){
            qry->prepare("select * from Candidat order by nom");
            qry->exec();
            modal->setQuery(*qry);
            modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
            modal->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
            modal->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
             modal->setHeaderData(3,Qt::Horizontal,QObject::tr("Travail"));
               modal->setHeaderData(4,Qt::Horizontal,QObject::tr("Emploi"));
            ui->tableView->setModel(modal);


        }
        else if (type=="prenom"){
            qry->prepare("select * from Candidat order by prenom");
            qry->exec();
            modal->setQuery(*qry);
            modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
            modal->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
            modal->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
             modal->setHeaderData(3,Qt::Horizontal,QObject::tr("Travail"));
               modal->setHeaderData(4,Qt::Horizontal,QObject::tr("Emploi"));
            ui->tableView->setModel(modal);


        }
    else if (type=="travail"){
        qry->prepare("select * from Candidat order by titre_travail ");
        qry->exec();
        modal->setQuery(*qry);
        modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
        modal->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
        modal->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
         modal->setHeaderData(3,Qt::Horizontal,QObject::tr("Travail"));
           modal->setHeaderData(4,Qt::Horizontal,QObject::tr("Emploi"));
        ui->tableView->setModel(modal);


    }
}

void MainWindow::on_pushButton_clicked()
{

    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView->model()->rowCount();
    const int columnCount = ui->tableView->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("col1")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<table border=1 cellspacing=0 cellpadding=2>\n";


    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView->isColumnHidden(column)) {
                QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QString savePath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/output.pdf";  // Save to the desktop

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(savePath);

    document->print(&printer);

    delete document;

}
void MainWindow::updateQRImage()
{


    int levelIndex = 1;
    int versionIndex = 0;
    bool bExtent = true;
    int maskIndex = -1;
QString d;





    QString encodeString = "Candidat:"+ui->le_id_candidat->text()+"\n nom :"+ui->le_nom->text()+"\n prenom :"+ui->le_prenom->text()+"\n Travail :"+ui->le_travail->text();

    successfulEncoding = qrEncode.EncodeData( levelIndex, versionIndex, bExtent, maskIndex, encodeString.toUtf8().data() );
    if ( !successfulEncoding )
    {
        ui->qrcode->clear();
        ui->qrcode->setText( tr("QR Code...") );

        return;
    }

    int qrImageSize = qrEncode.m_nSymbleSize;


    encodeImageSize = qrImageSize + ( QR_MARGIN * 2 );
    QImage encodeImage( encodeImageSize, encodeImageSize, QImage::Format_Mono );
    encodeImage.fill( 1 );


    for ( int i = 0; i < qrImageSize; i++ )
        for ( int j = 0; j < qrImageSize; j++ )
            if ( qrEncode.m_byModuleData[i][j] )
                encodeImage.setPixel( i + QR_MARGIN, j + QR_MARGIN, 0 );

    ui->qrcode->setPixmap( QPixmap::fromImage( encodeImage ) );
ui->qrcode->setScaledContents(true);


}










void MainWindow::on_pushButton_9_clicked()
{
    Candidat Can;
    OffreEmploi off;
    off.afficher(ui);
    Can.afficher(ui);
    ui->stackedWidget_2->setCurrentIndex(0);

}

void MainWindow::on_pushButton_10_clicked()
{
    Candidat Can;
    OffreEmploi off;
    off.afficher(ui);
    Can.afficher(ui);
    ui->stackedWidget_2->setCurrentIndex(1);

}

void MainWindow::on_pb_ajouter_2_clicked()
{
    int id_offre = ui->le_id_offre->text().toInt();
    QString titre = ui->le_titre->text();
    QString desc = ui->le_descrpition->text();
    QDateTime date = ui->dateTimeEdit->dateTime();

    // Reset previous error messages
    ui->label->clear();
    ui->label_2->clear();
    ui->label_3->clear();
    ui->label_4->clear();

    bool isValid = true;

    // Validate the input fields
    if (ui->le_id_offre->text().isEmpty()) {
        ui->label->setText("ID Offre vide");
        isValid = false;
    }
    if (titre.isEmpty()) {
        ui->label_3->setText("Titre vide");
        isValid = false;
    }
    if (desc.isEmpty()) {
        ui->label_2->setText("Description vide");
        isValid = false;
    }
    if (!date.isValid()) {
        ui->label_4->setText("Date invalide");
        isValid = false;
    }

    // Proceed with the addition if all fields are valid
    if (isValid) {
        OffreEmploi off(id_offre, titre, desc, date);

        bool test = off.ajouter();
        if (test) {
            off.afficher(ui);
        }
    }
}


void MainWindow::on_pushButton_8_clicked()
{
    int id_offre = ui->le_id_offre->text().toInt();
    QString titre = ui->le_titre->text();
    QString desc = ui->le_descrpition->text();
    QDateTime date = ui->dateTimeEdit->dateTime();

    // Reset previous error messages
    ui->label->clear();
    ui->label_2->clear();
    ui->label_3->clear();
    ui->label_4->clear();

    bool isValid = true;

    // Validate the input fields
    if (ui->le_id_offre->text().isEmpty()) {
        ui->label->setText("ID Offre vide");
        isValid = false;
    }
    if (titre.isEmpty()) {
        ui->label_3->setText("Titre vide");
        isValid = false;
    }
    if (desc.isEmpty()) {
        ui->label_2->setText("Description vide");
        isValid = false;
    }
    if (!date.isValid()) {
        ui->label_4->setText("Date invalide");
        isValid = false;
    }

    // Proceed with the modification if all fields are valid
    if (isValid) {
        OffreEmploi off(id_offre, titre, desc, date);
        bool test = off.modifier();
        if (test) {
            off.afficher(ui);
        }
    }
}

void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    QSqlQueryModel * modal= new QSqlQueryModel ();
    QSqlQuery*qry=new QSqlQuery();
    QString type=ui->comboBox_2->currentText();
    if (type=="Par defaut"){
        qry->prepare("select * from OFFREEMPLOI");
        qry->exec();
        modal->setQuery(*qry);
        modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
        modal->setHeaderData(1,Qt::Horizontal,QObject::tr("titre"));
        modal->setHeaderData(2,Qt::Horizontal,QObject::tr("description"));
         modal->setHeaderData(3,Qt::Horizontal,QObject::tr("date"));
        ui->tableView_2->setModel(modal);}

        else if (type=="titre"){
            qry->prepare("select * from OffreEmploi order by titre");
            qry->exec();
            modal->setQuery(*qry);
            modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
            modal->setHeaderData(1,Qt::Horizontal,QObject::tr("titre"));
            modal->setHeaderData(2,Qt::Horizontal,QObject::tr("description"));
             modal->setHeaderData(3,Qt::Horizontal,QObject::tr("date"));
            ui->tableView_2->setModel(modal);


        }
        else if (type=="description"){
            qry->prepare("select * from OffreEmploi order by description");
            qry->exec();
            modal->setQuery(*qry);
            modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
            modal->setHeaderData(1,Qt::Horizontal,QObject::tr("titre"));
            modal->setHeaderData(2,Qt::Horizontal,QObject::tr("description"));
             modal->setHeaderData(3,Qt::Horizontal,QObject::tr("date"));
            ui->tableView_2->setModel(modal);


        }
    else if (type=="date"){
        qry->prepare("select * from OffreEmploi order by date_mise_en_actif ");
        qry->exec();
        modal->setQuery(*qry);
        modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
        modal->setHeaderData(1,Qt::Horizontal,QObject::tr("titre"));
        modal->setHeaderData(2,Qt::Horizontal,QObject::tr("description"));
         modal->setHeaderData(3,Qt::Horizontal,QObject::tr("date"));
        ui->tableView_2->setModel(modal);


    }
}

void MainWindow::on_pushButton_6_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView_2->model()->rowCount();
    const int columnCount = ui->tableView_2->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("col1")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<table border=1 cellspacing=0 cellpadding=2>\n";


    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView_2->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView_2->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView_2->isColumnHidden(column)) {
                QString data = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

        document->print(&printer);


    delete document;
}

void MainWindow::on_pushButton_7_clicked()
{
    QModelIndex index=ui->tableView_2->currentIndex();
        int i=index.row();
        QModelIndex in=index.sibling(i,0);
        QString val=ui->tableView_2->model()->data(in).toString();
        OffreEmploi off;

        bool test=off.supprimer(val);
        if (test)
        {

            off.afficher(ui);

        }
}


void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{

        QSqlQueryModel * modal= new QSqlQueryModel ();
        QSqlQuery*qry=new QSqlQuery();
        QString text=ui->lineEdit_2->text();

        if(text.isEmpty())
        {
             OffreEmploi off;
           off.afficher(ui);


        }
        else
        {
            qry->prepare("select * from OFFREEMPLOI where ( id_offre LIKE'%"+text+"%' OR titre LIKE'%"+text+"%' OR description LIKE'%"+text+"%' ) ");
            qry->exec();
            modal->setQuery(*qry);
            ui->tableView_2->setModel(modal);
        }
}

void MainWindow::on_tableView_2_clicked(const QModelIndex &index)
{
    int i;
i=index.row();
QModelIndex in=index.sibling(i,0);
QString val=ui->tableView_2->model()->data(in).toString();

    QSqlQuery qry;
    qry.prepare("select * from OFFREEMPLOI where id_offre='"+val+"' " );


    if(qry.exec())
    {
        while(qry.next())
        {
            ui->le_id_offre->setText(qry.value(0).toString());

            ui->le_titre->setText(qry.value(1).toString());
            ui->le_descrpition->setText(qry.value(2).toString());
            ui->dateTimeEdit->setDateTime(qry.value(3).toDateTime());


        }
}
}
