#ifndef SLMUI_H
#define SLMUI_H
#include"ztpmanager.h"
#include"carinfo.h"
#include<QVector>
#include<QObject>
class QTableWidget;
class QWidget;
class SlmUi :public QObject
{
    Q_OBJECT
    QTableWidget* table1;
    QTableWidget* table2;

    ZTPManager* ztpm;
public:
    explicit SlmUi(QWidget *_uiPanel);

private:
    void procSlmInfo(const ZTPprotocol& ztp);
    void layoutSlmUI();
    int findRowIndexByVHeader(const QString& rowName);
private slots:
    void procNetPkg();
    
};

#endif // SLMUI_H
