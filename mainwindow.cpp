#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tpnumber.h"
#include <QPushButton>
#include <string>
#include <QString>
#include <QAction>
#include <QMessageBox>

void MainWindow::btn_input_click(QString par)
{
    if (par == "." and ui->le_input->text().contains('.', Qt::CaseInsensitive))
        return;

    if (par == "." and ui->le_input->text().size() == 0)
        par = "0.";
    ui->le_input->setText(ui->le_input->text() + par);
    ui->le_output->setText("");
}

void MainWindow::btn_delete_click()
{
    QString text = ui->le_input->text();
    if (text.size() == 0)
        return;
    text.chop(1);
    ui->le_input->setText(text);
}

void MainWindow::btn_clear_click()
{
    ui->le_input->setText("");
}

void MainWindow::action_close_triggered()
{
    this->close();
}

void MainWindow::action_story_triggered()
{
    QMessageBox storyMess;
    storyMess.setText("История");
    storyMess.setInformativeText(QString::fromStdString(story));
    storyMess.addButton("Поставить зачет", QMessageBox::AcceptRole);
    storyMess.exec();
}

void MainWindow::action_info_triggered()
{
    QMessageBox info;
    info.setText("ИП-017");
    info.setInformativeText("Костин Андрей ЪУЪ, Извеков Иван :3");
    info.addButton("Поставить зачет", QMessageBox::AcceptRole);
    info.exec();
}

void MainWindow::action_log_triggered()
{
    QMessageBox logMess;
    logMess.setText("here is the log, if u wanna to see more details, just click on details, If there is no button with details, it means there are no details yet, do a couple of operations in the calculator");
    logMess.setDetailedText(QString::fromStdString(log));
    logMess.addButton("Смирится с ошибками", QMessageBox::AcceptRole);
    logMess.addButton("Уверовать в бога", QMessageBox::AcceptRole);
    logMess.exec();
}

bool is_operator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^')
        return true;
    return false;
}

void MainWindow::btn_reverse_click()
{
    string input_text = ui->le_input->text().toStdString();
    int id_new_minus = -1;
    for (int i = input_text.size()-1; i>=0; --i)
    {
        if(is_operator(input_text[i]) && input_text[i] != '(' && input_text[i] != ')')
        {
            if(input_text[i] == '-')
            {
                input_text[i] = '+';
                ui->le_input->setText(QString::fromStdString(input_text));
                return;
            }
            else if(input_text[i] == '+')
            {
                input_text[i] = '-';
                ui->le_input->setText(QString::fromStdString(input_text));
                return;
            }
            else
            {
                id_new_minus = i;
                break;
            }
        }
    }
    if(id_new_minus == -1)
    {
        ui->le_input->setText(QString::fromStdString("-" + input_text));
        return;
    }
    string left = input_text.substr(0, id_new_minus+1);
    string right = input_text.substr(id_new_minus+1, input_text.size() - id_new_minus);
    left+="(-";
    right+=")";
    ui->le_input->setText(QString::fromStdString(left + right));
}

void MainWindow::log_add(string new_text)
{
    log = new_text + "\n" + log;
}

void MainWindow::btn_execute_click()
{
    //a+b*c

    QString base = ui->sb_in->text();
    QString res_base = ui->sb_out->text();
    int tocnost = 0;
    if (ui->le_input->text().contains('.', Qt::CaseInsensitive))
        tocnost = 5;
    else
        tocnost = 0;

    string input_text = ui->le_input->text().toStdString();

    string temp_str = "";
    string calc_str = "";

    /*
             * 1 парсим число в 16
             * 2 перевод в 10
             * 3 зпрись в calc_str числа и знака
             * 4 повторить пока есть числа и знаки
             * 5 отправить в калькулятор
             * 6 перевести результат в res_base
             */
    cout << "_\n";
    log_add("input_text = " + input_text);
    bool error = false;
    char old_i = '~';
    for(auto &i : input_text)
    {
        if ((i == '+' && old_i == '~') || (i == '+' && old_i == '('))
        {
            calc_str += "0+";
            old_i = i;
        }
        else if ((i == '-' && old_i == '~') || (i == '-' && old_i == '('))
        {
            calc_str += "0-";
            old_i = i;
        }
        else if (is_operator(i))
        {
            if(temp_str.size() != 0)
            {

                TPNumber pnum(temp_str, base.toStdString(), to_string(tocnost));
                log_add("В " + base.toStdString() + ": temp str = " + temp_str + "; calc_str += " + pnum.getNumberString());
                pnum.setBase(10);
                log_add("В 10: temp str = " + temp_str + "; calc_str += " + pnum.getNumberString());
                calc_str += pnum.getNumberString();
                temp_str = "";
                if (!pnum.isCorrect)
                    error = true;
            }
            log_add("calc_str += " + to_string(i));
            calc_str += i;
            old_i = i;
        }
        else if(!is_operator(i))
        {
            temp_str += i;
            old_i = i;
        }
    }
    if(temp_str.size() != 0)
    {
        TPNumber pnum(temp_str, base.toStdString(), to_string(tocnost));
        log_add("В " + base.toStdString() + ": temp str = " + temp_str + "; calc_str += " + pnum.getNumberString());
        pnum.setBase(10);
        log_add("В 10: temp str = " + temp_str + "; calc_str += " + pnum.getNumberString());
        calc_str += pnum.getNumberString();
        temp_str = "";
        if (!pnum.isCorrect)
            error = true;
    }

    log_add("calc_str = " + calc_str);
    double result = worker.run(calc_str);
    log_add("result = " + to_string(result));
    string str_res = to_string(result);
    while(str_res[str_res.size()-1] == '0')
        str_res.resize(str_res.size()-1);
    if(str_res[str_res.size()-1] == '.')
        str_res.resize(str_res.size()-1);
    log_add("str_res = " + str_res);
    for(size_t i = 0; i < str_res.size(); ++i)
    {
        if(str_res[i] == '.')
            tocnost = str_res.size() - i;
    }

    log_add("tocnost = " + to_string(tocnost));

    cout << "str_res = " << str_res << ";\n";
    TPNumber pnum(str_res, "10", to_string(tocnost));

    log_add("pnum.getNumber = " + pnum.getNumberString());

    pnum.setBase(res_base.toStdString());
    if (!pnum.isCorrect || worker.error_brackets)
        error = true;
    string res = pnum.getNumberString();
    if (error || worker.error0)
        res = "Error";
    log_add("res = " + res);
    while(res[res.size()-1] == '0')
        res.resize(res.size()-1);
    if(res[res.size()-1] == '.')
        res.resize(res.size()-1);

    if(res[0] == '.')
        res = "0" + res;
    log_add("(after fix) res = " + res);
    ui->le_output->setText(QString::fromStdString(res));
    if (pnum.isCorrect)
        story+= to_string(result) + "(" + base.toStdString() + ") = " + res + "(" + res_base.toStdString() + ")\n";
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action_close, &QAction::triggered, [this](){this->action_close_triggered();});
    connect(ui->action_story, &QAction::triggered, [this](){this->action_story_triggered();});
    connect(ui->action_info, &QAction::triggered, [this](){this->action_info_triggered();});
    connect(ui->action_log, &QAction::triggered, [this](){this->action_log_triggered();});

    connect(ui->btn_0, &QPushButton::clicked, this, [this](){this->btn_input_click("0");});
    connect(ui->btn_1, &QPushButton::clicked, this, [this](){this->btn_input_click("1");});
    connect(ui->btn_2, &QPushButton::clicked, this, [this](){this->btn_input_click("2");});
    connect(ui->btn_3, &QPushButton::clicked, this, [this](){this->btn_input_click("3");});
    connect(ui->btn_4, &QPushButton::clicked, this, [this](){this->btn_input_click("4");});
    connect(ui->btn_5, &QPushButton::clicked, this, [this](){this->btn_input_click("5");});
    connect(ui->btn_6, &QPushButton::clicked, this, [this](){this->btn_input_click("6");});
    connect(ui->btn_7, &QPushButton::clicked, this, [this](){this->btn_input_click("7");});
    connect(ui->btn_8, &QPushButton::clicked, this, [this](){this->btn_input_click("8");});
    connect(ui->btn_9, &QPushButton::clicked, this, [this](){this->btn_input_click("9");});
    connect(ui->btn_a, &QPushButton::clicked, this, [this](){this->btn_input_click("A");});
    connect(ui->btn_b, &QPushButton::clicked, this, [this](){this->btn_input_click("B");});
    connect(ui->btn_c, &QPushButton::clicked, this, [this](){this->btn_input_click("C");});
    connect(ui->btn_d, &QPushButton::clicked, this, [this](){this->btn_input_click("D");});
    connect(ui->btn_e, &QPushButton::clicked, this, [this](){this->btn_input_click("E");});
    connect(ui->btn_f, &QPushButton::clicked, this, [this](){this->btn_input_click("F");});
    connect(ui->btn_plus, &QPushButton::clicked, this, [this](){this->btn_input_click("+");});
    connect(ui->btn_minus, &QPushButton::clicked, this, [this](){this->btn_input_click("-");});
    connect(ui->btn_multiple, &QPushButton::clicked, this, [this](){this->btn_input_click("*");});
    connect(ui->btn_divide, &QPushButton::clicked, this, [this](){this->btn_input_click("/");});
    connect(ui->btn_pow, &QPushButton::clicked, this, [this](){this->btn_input_click("^");});
    connect(ui->btn_sqrt, &QPushButton::clicked, this, [this](){this->btn_input_click("^(1/2)");});
    connect(ui->btn_percent, &QPushButton::clicked, this, [this](){this->btn_input_click("/100");});
    connect(ui->btn_brackets_1, &QPushButton::clicked, this, [this](){this->btn_input_click("(");});
    connect(ui->btn_brackets_2, &QPushButton::clicked, this, [this](){this->btn_input_click(")");});
    connect(ui->btn_reverse, &QPushButton::clicked, this, [this](){this->btn_reverse_click();});
    connect(ui->btn_point, &QPushButton::clicked, this, [this](){this->btn_input_click(".");});
    connect(ui->btn_delete, &QPushButton::clicked, this, [this](){this->btn_delete_click();});
    connect(ui->btn_clear, &QPushButton::clicked, this, [this](){this->btn_clear_click();});
    connect(ui->btn_execute, &QPushButton::clicked, this, [this](){this->btn_execute_click();});

    QString const style = ":hover{\nbackground-color: #adcbb5;\n}\n:pressed{\nbackground-color: #1c4a33;\ncolor:#62a77c;\n}\nQPushButton{\nborder:none;\nborder-radius: 15px;\nbackground-color: #7cc398;\ncolor: #153626;\nfont-size: 18px;\nfont-weight: 600;}";
    QString const style_void = ":hover{\nbackground-color: #62a77c;\n}\n:pressed{\nbackground-color: #62a77c;\ncolor:#62a77c;\n}\nQPushButton{\nborder:none;\nborder-radius: 15px;\nbackground-color: #62a77c;\ncolor: #62a77c;\nfont-size: 18px;\nfont-weight: 600;}";

    ui->btn_0->setStyleSheet(style);
    ui->btn_1->setStyleSheet(style);
    ui->btn_2->setStyleSheet(style);
    ui->btn_3->setStyleSheet(style);
    ui->btn_4->setStyleSheet(style);
    ui->btn_5->setStyleSheet(style);
    ui->btn_6->setStyleSheet(style);
    ui->btn_7->setStyleSheet(style);
    ui->btn_8->setStyleSheet(style);
    ui->btn_9->setStyleSheet(style);
    ui->btn_a->setStyleSheet(style);
    ui->btn_b->setStyleSheet(style);
    ui->btn_c->setStyleSheet(style);
    ui->btn_d->setStyleSheet(style);
    ui->btn_e->setStyleSheet(style);
    ui->btn_f->setStyleSheet(style);
    ui->btn_plus->setStyleSheet(style);
    ui->btn_minus->setStyleSheet(style);
    ui->btn_multiple->setStyleSheet(style);
    ui->btn_divide->setStyleSheet(style);
    ui->btn_pow->setStyleSheet(style);
    ui->btn_sqrt->setStyleSheet(style);
    ui->btn_percent->setStyleSheet(style);
    ui->btn_delete->setStyleSheet(style);
    ui->btn_clear->setStyleSheet(style);
    ui->btn_execute->setStyleSheet(style);
    ui->btn_point->setStyleSheet(style);
    ui->btn_reverse->setStyleSheet(style);
    ui->btn_brackets_1->setStyleSheet(style);
    ui->btn_brackets_2->setStyleSheet(style);

    ui->sb_in->setMinimum(2);
    ui->sb_in->setMaximum(16);
    ui->sb_in->setValue(10);
    ui->sb_out->setMinimum(2);
    ui->sb_out->setMaximum(16);
    ui->sb_out->setValue(10);


}

MainWindow::~MainWindow()
{
    delete ui;
}
