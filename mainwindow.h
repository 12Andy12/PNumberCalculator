#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <unordered_map>
#include "tpnumber.h"
#include "calculator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void btn_input_click(QString par);
    void btn_delete_click();
    void btn_clear_click();
    void btn_execute_click();
    void btn_reverse_click();
    void action_close_triggered();
    void action_story_triggered();
    void action_info_triggered();
    void action_log_triggered();
    void log_add(string new_text);


private:
    Calculator worker;
    Ui::MainWindow *ui;
    std::string story;
    std::string log;
};

#endif // MAINWINDOW_H
