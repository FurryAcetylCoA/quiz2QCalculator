#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<QPushButton*> NumberButtons = this->ui->centralwidget->findChildren<QPushButton*>();
    for (int i=0;i<NumberButtons.count() ;i++ ) {
        connect(NumberButtons.at(i),SIGNAL(clicked()),this,SLOT(onButton()));
    }
    status=0;
    connect(this,SIGNAL(Status4()),this,SLOT(doStatus4()));

}
/*
 * 状态0：没有按下任何数字或计算符
 * 状态1：已经接收了一组数字
 * 状态2：已经接收了一组数字和计算符，
 * 状态3：已经接收了两组数字和计算符
 * 状态4：正在计算
 *
 * 0-----按下等于->不响应                  已经实现
 *     --按下数字->数字加入显示器，进入状态1  已经实现
 * 1附加---按下计算符->将当前数字放入存储1，计算符存入存储3，清空显示器，进入状态2 已经实现
 * 2-----按下等于->不响应                  已经实现
 *     --按下计算符->计算符存入存储3         已经实现
 *     --按下数字->数字加入显示器，进入状态3   已经实现
 * 3-----按下数字->数字加入显示器            已经实现
 *     --按下等于->数字存入存储2，清空显示器，进入状态4     已经实现
 *     --按下计算符->数字存入存储2，清空显示器，进入状态4    已经实现
 * 4----------->用存储1，2，3进行计算，加入显示器，进入状态1
 *取整？
 *
 * 任何时候按下C键----清空显示器，回到状态0
 * */
/*   *pushButton_plus;
     *pushButton_minus;
     *pushButton_mult;
     *pushButton_chufa;
     *pushButton_equ;
*/
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButton()
{

    string senderName=sender()->objectName().mid(11).toStdString();//case不能用字符串标签，所以这里写成了这种奇怪的形式
    cout<<"SenderName="<<senderName<<"  Status="<<status;
    if(isdigit(senderName.at(0))){//数字类
        switch (status) {
        case 0:
        case 2:
               status+=1;
        case 1:
        case 3:
            ui->lcdNumber->display(stoi(senderName)+ui->lcdNumber->intValue()*10);//这太扭曲了
               break;
        case 4:break;
        }
    }else
       if(senderName=="equ"){//等于键
        switch(status){
        case 0:
        case 1:
        case 2:break;
        case 3:num2=ui->lcdNumber->intValue();
               ui->lcdNumber->display(0);
               status=4;break;
        }
       }else if(senderName=="clear"){//C 键
           ui->lcdNumber->display(0);
           status=0;
       }else {//计算符
           cout<<"计算符！"<<endl;
           switch(status){
           case 0:break;
           case 1:num1=ui->lcdNumber->intValue();
                  ui->lcdNumber->display(0);
                  status=2;
           case 2:theoperator2=senderName;
                cout<<"setting operator to:"<<senderName<<endl;
               break;
           case 3:num2=ui->lcdNumber->intValue();
               ui->lcdNumber->display(0);
               status=4;break;
           }
       }
    if(status==4){
        emit Status4();
    }cout<<"->"<<status<<endl;
}
//4----------->用存储1，2，3进行计算，加入显示器，进入状态1
void MainWindow::doStatus4()
{
    cout<<"doStatus4"<<endl;
    double equalto=0;
    cout<<"  operator is:"<<theoperator2<<endl;
    if(theoperator2=="plus"){
        cout<<"plus";
        equalto=num1+num2;
    }else if(theoperator2=="minus"){
        equalto=num1-num2;
    }else if(theoperator2=="mult"){
        equalto=num1*num2;
    }else if(theoperator2=="chufa"){
        if(num2==0){
            QMessageBox::warning(this,"Divide by zero?","Sorry,I thought about that.");
        }else{
            equalto=num1*1.0/num2;
        }
     }else {cout<<"W:Unknown operator";}
    cout<<"  equalto:"<<equalto<<endl;
    ui->lcdNumber->display(equalto);
    status=1;
 }




