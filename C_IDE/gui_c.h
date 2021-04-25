#ifndef GUI_C_H
#define GUI_C_H

#include <QMainWindow>
#include <QtCore>
#include<QtGui>

QT_BEGIN_NAMESPACE
namespace Ui { class GUI_C; }
QT_END_NAMESPACE
static const auto RLV_PRINT_RESPONSE= "100";
static const auto STD_PRINT_RESPONSE = "101";
static const auto APPLOG_PRINT_RESPONSE = "102";

class GUI_C : public QMainWindow
{
    Q_OBJECT

public:
    GUI_C(QWidget *parent = nullptr);
    ~GUI_C();
    int cont = 1;
    std::string line;
    Ui::GUI_C *ui;
    std::string message;




private slots:

    void on_runbtn_clicked();

    void on_stopbtn_clicked();

    void on_nextbtn_clicked();

    void on_clearbtn_clicked();

    void print(std::string json);

private:

    QString mFile;



};




#endif // GUI_C_H
