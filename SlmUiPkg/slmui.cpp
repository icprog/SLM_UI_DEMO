#include "slmui.h"
#include<QWidget>
#include<QTableWidget>
#include<QDebug>
#include<QHeaderView>
SlmUi::SlmUi(QWidget* _uiPanel)
{


    ztpm = new ZTPManager(3320,QHostAddress("224.102.228.40"));
    connect(ztpm,SIGNAL(readyRead()),this,SLOT(procNetPkg()));
    int table_w = 260;
    int table_h = 350;
    table1 = new QTableWidget(0,2,_uiPanel);

    table1->resize(table_w,table_h);
    QString headerStr("slm1,slm2");
    table1->setHorizontalHeaderLabels(headerStr.split(QChar(',')));

    QRect rect =  table1->geometry();

    rect.setLeft(_uiPanel->size().width()/2- 20 -table_w);
    rect.setTop((_uiPanel->size().height() - table_h)/3);
    rect.setWidth(table_w);
    rect.setHeight(table_h);

    table1->setGeometry(rect);
    table2 = new QTableWidget(0,2,_uiPanel);
    table2->setHorizontalHeaderLabels(headerStr.split(QChar(',')));
    rect.setLeft(_uiPanel->size().width()/2+ 20);
    rect.setWidth(table_w);
    rect.setHeight(table_h);
    table2->setGeometry(rect);

    table1->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    table2->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
}

 void SlmUi::procNetPkg()
 {
     ZTPprotocol ztp;
     ztpm->getOneZtp(ztp);
     if(ztp.getPara("T") == "SLM_STATE")
     {
         procSlmInfo(ztp);
     }
 }

int SlmUi::findRowIndexByVHeader(const QString& rowName)
 {

     for(int i = 0;i<table1->rowCount();i++)
     {
         if(table1->verticalHeaderItem(i)->text() == rowName)
         {
             return i;
         }
     }
     for(int i = 0;i<table2->rowCount();i++)
     {
         if(table1->verticalHeaderItem(i)->text() == rowName)
             return 100+i;
     }
     return -1;
 }

 void SlmUi::procSlmInfo(const ZTPprotocol& ztp)
 {
     int carID = ztp.getPara("CAR_ID").toInt();
     if(CarInfo::v_carInfos[carID] == NULL)
     {
         CarInfo::v_carInfos[carID] = new CarInfo("CAR"+ztp.getPara("CAR_ID"));
         CarInfo::v_carInfos[carID]->slm1 = ztp.getPara("SLM1");
         CarInfo::v_carInfos[carID]->slm2 = ztp.getPara("SLM2");
         layoutSlmUI();
     }
     else
     {
         int rowNu = findRowIndexByVHeader(CarInfo::v_carInfos[carID]->carID);
         if(rowNu == -1)
         {
             qDebug("not find valid row");
             return;
         }
         else if(rowNu < 100)
         {
             table1->setItem(rowNu,0,new QTableWidgetItem(CarInfo::v_carInfos[carID]->slm1));
             table1->setItem(rowNu,1,new QTableWidgetItem(CarInfo::v_carInfos[carID]->slm2));
         }
         else if(rowNu >= 100)
         {
             table2->setItem(rowNu - 100,0,new QTableWidgetItem(CarInfo::v_carInfos[carID]->slm1));
             table2->setItem(rowNu - 100,1,new QTableWidgetItem(CarInfo::v_carInfos[carID]->slm2));
         }
     }
 }

 void SlmUi::layoutSlmUI()
 {
     table1->setRowCount(0);
     table2->setRowCount(0);
     int pos = 0;
     for(int i = 0;i< CarInfo::v_carInfos.count();i++)
     {
         CarInfo* carInfo = CarInfo::v_carInfos[i];
         if(carInfo != NULL)
         {
             if(pos++%2== 0 )
             {
                 table1->insertRow(table1->rowCount());

                 table1->setItem(table1->rowCount()-1,0,new QTableWidgetItem(carInfo->slm1));
                 table1->setItem(table1->rowCount()-1,1,new QTableWidgetItem(carInfo->slm2));
                 table1->setVerticalHeaderItem(table1->rowCount()-1,new QTableWidgetItem(carInfo->carID));
             }
             else
             {
                 table2->insertRow(table2->rowCount());
                 table2->setItem(table2->rowCount()-1,0,new QTableWidgetItem(carInfo->slm1));
                 table2->setItem(table2->rowCount()-1,1,new QTableWidgetItem(carInfo->slm2));
                 table2->setVerticalHeaderItem(table2->rowCount()-1,new QTableWidgetItem(carInfo->carID));
             }
         }
     }
 }
