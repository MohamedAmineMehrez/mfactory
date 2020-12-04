#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlDatabase>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    db.setDatabaseName(QString("Smart factory"));
     db.setUserName("mehrez");
     db.setPassword("mehrez333");
     if(!db.open()) {
       qDebug() << QString("Unable to open database");
       QMessageBox::warning(this, tr("MFactory"), tr("Unable to open database"), QMessageBox::Ok);
}
    ui->setupUi(this);
     ui->listView3->show();
    ui->lineEditcin->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEditcin1->setValidator(new QIntValidator(0,99999999,this));
   ui->tableView->setModel(ctmp.afficher());
   ui->tableView_2->setModel(com.afficher());

    ui->pushButton->setIcon((QIcon(":/images/2.png")));
    ui->pushButton->setIconSize(ui->pushButton->size());

    ui->pushButton_2->setIcon((QIcon(":/images/2.png")));
    ui->pushButton_2->setIconSize(ui->pushButton_2->size());

    /*ui->pushButton_3->setIcon((QIcon(":/images/5.png")));
    ui->pushButton_3->setIconSize(ui->pushButton_3->size());*/

  /*  ui->pb_ok1->setIcon((QIcon(":/images/4.png")));
    ui->pb_ok1->setIconSize(ui->pb_ok1->size());*/

    ui->pushButton_5->setIcon((QIcon(":/images/4.png")));
    ui->pushButton_5->setIconSize(ui->pushButton_5->size());

    ui->modifierchantier->setIcon((QIcon(":/images/1.png")));
    ui->modifierchantier->setIconSize(ui->modifierchantier->size());

    ui->supprimerchantier->setIcon((QIcon(":/images/3.png")));
    ui->supprimerchantier->setIconSize(ui->supprimerchantier->size());

    ui->modifierchantier_2->setIcon((QIcon(":/images/1.png")));
    ui->modifierchantier_2->setIconSize(ui->modifierchantier_2->size());

    ui->supprimerchantier_2->setIcon((QIcon(":/images/3.png")));
    ui->supprimerchantier_2->setIconSize(ui->supprimerchantier_2->size());
}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{   QString CIN=ui->lineEditcin->text();
    QString nom=ui->lineEditnom->text();
    QString prenom=ui->lineEditprenom->text();
     QString numero=ui->lineEditnumero->text();
    QString adresse=ui->lineEditadresse->text();
    QString date_naissance=ui->dateEdit->text();
    Client C(CIN,nom,prenom,numero,adresse,date_naissance);
    bool test=C.ajouter();
    if(test)
    {    ui->tableView->setModel(ctmp.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("ajout effectue \n Click cancel to exit"),QMessageBox::Cancel);
        ui->lineEditadresse->clear();
        ui->lineEditcin->clear();
        ui->lineEditnom->clear();
        ui->lineEditprenom->clear();
        ui->dateEdit->clear();
        ui->lineEditnumero->clear();
}
else QMessageBox::critical(nullptr,QObject::tr("not OK"),QObject::tr("Ajout non effectue\n Click cancel to exit"),QMessageBox::Cancel);
}

 void MainWindow::on_supprimerchantier_clicked()
{
    QString CIN=ui->lineEdit_cind->text();
    bool test=ctmp.supprimer(CIN);
    if(test)
    {ui->tableView->setModel(ctmp.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("Suppression effectue\n click cancel to exit"),QMessageBox::Cancel);
        ui->lineEdit_cind->clear();
    }
    else QMessageBox::critical(nullptr,QObject::tr("ok"),
                                  QObject::tr("Suppression non effectue\n click cancel to exit"),QMessageBox::Cancel);
     }



void MainWindow::on_modifierchantier_clicked()
{
    QString CIN=ui->lineEditcinm->text();
        QString nom=ui->lineEditnomm->text();
        QString prenom=ui->lineEditprenomm->text();
         QString numero=ui->lineEditnumerom->text();
        QString adresse=ui->lineEditadressem->text();
        QString date_naissance=ui->dateEdit_2->text();
        QSqlQuery query;
            query.prepare("update Client set CIN='"+CIN+"',nom='"+nom+"',prenom='"+prenom+"',numero='"+numero+"',adresse='"+adresse+"',date_naissance='"+date_naissance+"'where CIN='"+CIN+"'");

        if(query.exec())
        {    ui->tableView->setModel(ctmp.afficher());
            QMessageBox::information(nullptr,QObject::tr("ok"),
                                     QObject::tr("update effectue \n Click cancel to exit"),QMessageBox::Cancel);
            ui->lineEditadresse->clear();
            ui->lineEditcin->clear();
            ui->lineEditnom->clear();
            ui->lineEditprenom->clear();
            ui->dateEdit->clear();
            ui->lineEditnumero->clear();
         }
   }

void MainWindow::on_pushButton_2_clicked()
{   float prixunitaire=0;
    QString CINC=ui->lineEditcin1->text();
    QString adresse=ui->lineEdit_2->text();
     QString type=ui->comboBox_3->currentText();
     if(type=="mercedes")
         prixunitaire=100000;
     else if (type=="Audi")
         prixunitaire=50000;
     else if(type=="BMW")
         prixunitaire=75000;
     int quantite=ui->lineEdit->text().toInt();
      float prix=quantite*prixunitaire;
    QString date_paiment=ui->dateEdit_4->text();

    commande com(CINC,type,adresse,date_paiment,quantite,prixunitaire,prix);
    bool test=com.ajouter();
    if(test)
    {    ui->tableView_2->setModel(com.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("ajout effectue \n Click cancel to exit"),QMessageBox::Cancel);
        ui->lineEditcin1->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit->clear();
        ui->dateEdit_4->clear();


}else QMessageBox::critical(nullptr,QObject::tr("not OK"),QObject::tr("Ajout non effectue\n Click cancel to exit"),QMessageBox::Cancel);
}

void MainWindow::on_supprimerchantier_2_clicked()
{
    QString CINC=ui->lineEdit_20->text();
    bool test=com.supprimer(CINC);
    if(test)
    {ui->tableView_2->setModel(com.afficher());
      /*  QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("Suppression effectue\n click cancel to exit"),QMessageBox::Cancel);
       */ ui->lineEdit_20->clear();
    }
    else QMessageBox::critical(nullptr,QObject::tr("ok"),
                                  QObject::tr("Suppression non effectue\n click cancel to exit"),QMessageBox::Cancel);
}

void MainWindow::on_modifierchantier_2_clicked()
{   float prixunitaire=0,prix=0;
    QString CINC=ui->lineEditcin_3->text();
    QString type=ui->comboBox_4->currentText();
    QString adresse=ui->lineEditadres_3->text();
     QString date_paiment=ui->dateEdit_5->text();
    int quantite=ui->lineEdit_quantite5->text().toInt();
    if(type=="mercedes")
             prixunitaire=100000;
         else if (type=="Audi")
             prixunitaire=50000;
         else if(type=="BMW")
             prixunitaire=75000;
          prix=prixunitaire*quantite;
    QSqlQuery query;
        query.prepare("update COMMANDE set type=:type,adresse=:adresse,date_paiment=:date_paiment,quantite=:quantite,prixunitaire=:prixunitaire,prix=:prix where CINC=:CINC;");
        query.bindValue(":CINC",CINC);
        query.bindValue(":type",type);
        query.bindValue(":adresse",adresse);
        query.bindValue(":date_paiment",date_paiment);
        query.bindValue(":quantite",QString::number(quantite));
        query.bindValue(":prixunitaire", QString::number(prixunitaire));
        query.bindValue(":prix",QString::number(prix));
    if(query.exec())
    {    ui->tableView_2->setModel(com.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("update effectue \n Click cancel to exit"),QMessageBox::Cancel);

}}

void MainWindow::on_pushButton_5_clicked()
{
    QString CIN=ui->lineEdit_3->text();
     QString adresse=ui->lineEdit_4->text();
     QString numero=ui->lineEdit_5->text();
     ui->listView3->setModel(ctmp.rechercher_3(CIN,numero,adresse));

                   ui->listView3->show();
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    QPieSeries *series= new QPieSeries();
         QSqlQuery query;
         query.prepare("select type, quantite from commande;");
         QVector<int> q;
         QVector<QString> vectdesc;
         if(query.exec()){
             while(query.next()){
             vectdesc.push_back(query.value(0).toString());
             q.push_back(query.value(1).toInt());
               }

          int s=0;
          for (int i=0;i<q.size();i++) s+=q[i];

          for (int i=0;i<vectdesc.size();i++){
         series->append(vectdesc[i], (qreal)((qreal)q[i]/(qreal)s)*100.0);

            }
         QChart *ch= new QChart();
         ch->addSeries(series);
         ch->setTitle(QString("stat des quantitées des commandes par rapport au quantite"));
         ch->legend()->show();
         ch->setAnimationOptions(QChart::AllAnimations);
         QChartView *chart=new QChartView(ch);
         chart->setRenderHint(QPainter::Antialiasing);//graphique
         chart->setGeometry(ui->graphicsView_3->geometry());//taille de la page
         QGridLayout q;
         q.addWidget(chart);
         ui->graphicsView_3->setLayout(&q);
           }
}

void MainWindow::on_pushButton_4_clicked()
{
    QString strStream;
                     QTextStream out(&strStream);

                     const int rowCount = ui->tableView->model()->rowCount();
                     const int columnCount = ui->tableView->model()->columnCount();

                     out <<  "<html>\n"
                         "<head>\n"
                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                         <<  QString("<title>%1</title>\n").arg("strTitle")
                         <<  "</head>\n"
                         "<body bgcolor=#ffffff link=#5000A0>\n"

                        //     "<align='right'> " << datefich << "</align>"
                         "<center> <H1>Liste des commandes </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                     // headers
                     out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                     for (int column = 0; column < columnCount; column++)
                         if (!ui->tableView->isColumnHidden(column))
                             out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                     out << "</tr></thead>\n";

                     // data table
                     for (int row = 0; row < rowCount; row++) {
                         out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                         for (int column = 0; column < columnCount; column++) {
                             if (!ui->tableView->isColumnHidden(column)) {
                                 QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                             }
                         }
                         out << "</tr>\n";
                     }
                     out <<  "</table> </center>\n"
                         "</body>\n"
                         "</html>\n";

               QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                 if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                QPrinter printer (QPrinter::PrinterResolution);
                 printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
               printer.setOutputFileName(fileName);

                QTextDocument doc;
                 doc.setHtml(strStream);
                 doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                 doc.print(&printer);
}
