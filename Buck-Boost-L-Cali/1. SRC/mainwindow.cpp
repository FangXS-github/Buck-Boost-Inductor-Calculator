#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Buck-Boost-L-Cali");
// set default params for edit line
    // buck
    ui->lineEdit_IN_VIN->setText("3.3");
    ui->lineEdit_IN_Vout->setText("4.2");
    ui->lineEdit_IN_Iout->setText("1.0");
    ui->lineEdit_IN_Fsw->setText("1.2");
    ui->lineEdit_IN_Ymin->setText("0.2");
    ui->lineEdit_IN_max->setText("0.4");
    // boost
    ui->lineEdit_VIN->setText("3.0");
    ui->lineEdit_Vout->setText("3.3");
    ui->lineEdit_Iout->setText("1.0");
    ui->lineEdit_Fsw->setText("1.2");
    ui->lineEdit_Ymin->setText("0.1");
    ui->lineEdit_Ymax->setText("0.3");
    statusBar()->showMessage("Ready");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_getBuck_clicked()
{
    bool isOK;
    QString str[6] = { 0 };
    double input[6] = { 0.0f };
    double output_max = 0.0f;
    double output_min = 0.0f;
    str[0] =ui->lineEdit_IN_VIN->text();//获取输入电压
    str[1] =ui->lineEdit_IN_Vout->text();//获取输出电压
    str[2] =ui->lineEdit_IN_Iout->text();//获取输出电流
    str[3] =ui->lineEdit_IN_Fsw->text();//获取sw频率
    str[4] =ui->lineEdit_IN_Ymin->text();//获取Ymin
    str[5] =ui->lineEdit_IN_max->text();//获取Ymax
    for(unsigned char i=0; i<6;i++){
        input[i] = str[i].toDouble(&isOK);
        if(!isOK){
            ui->label_Buck_result_min->setText("error.");
            ui->label_Buck_result_max->setText("error.");
            return ;
        }
    }
    output_max = input[0] * (1.0f - input[0] / input[1]) / (input[2] * input[3] * input[4]);
    output_min = input[0] * (1.0f - input[0] / input[1]) / (input[2] * input[3] * input[5]);
    QString Buck_result_max = QString::number(output_max);
    QString Buck_result_min = QString::number(output_min);
    ui->label_Buck_result_max->setText(Buck_result_max);
    ui->label_Buck_result_min->setText(Buck_result_min);
    statusBar()->showMessage("Buck Cali done");
}



void MainWindow::on_pushButton_getBoost_clicked()
{
    QString str[6] = { 0 };
    bool isOK;
    double input[6] = { 0.0f };
    double output_max = 0.0f;
    double output_min = 0.0f;
    str[0] =ui->lineEdit_VIN->text();//获取输入电压
    str[1] =ui->lineEdit_Vout->text();//获取输出电压
    str[2] =ui->lineEdit_Iout->text();//获取输出电流
    str[3] =ui->lineEdit_Fsw->text();//获取sw频率
    str[4] =ui->lineEdit_Ymin->text();//获取Ymin
    str[5] =ui->lineEdit_Ymax->text();//获取Ymax
    for(unsigned char i=0; i<6;i++){
        input[i] = str[i].toDouble(&isOK);
        if(!isOK){
            ui->label_Boost_result_min->setText("error.");
            ui->label_Boost_result_max->setText("error.");
            return ;
        }
    }
    output_max =
       input[0] * input[0] * (input[1] - input[0]) /
            (input[1] * input[1] * input[2] * input[3] * input[4]);
    output_min =
       input[0] * input[0] * (input[1] - input[0]) /
            (input[1] * input[1] * input[2] * input[3] * input[5]);
    QString Buck_result_max = QString::number(output_max);
    QString Buck_result_min = QString::number(output_min);
    ui->label_Boost_result_max->setText(Buck_result_max);
    ui->label_Boost_result_min->setText(Buck_result_min);
    statusBar()->showMessage("Boost Cali done");
}

