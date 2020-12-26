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
 * ״̬0��û�а����κ����ֻ�����
 * ״̬1���Ѿ�������һ������
 * ״̬2���Ѿ�������һ�����ֺͼ������
 * ״̬3���Ѿ��������������ֺͼ����
 * ״̬4�����ڼ���
 *
 * 0-----���µ���->����Ӧ                  �Ѿ�ʵ��
 *     --��������->���ּ�����ʾ��������״̬1  �Ѿ�ʵ��
 * 1����---���¼����->����ǰ���ַ���洢1�����������洢3�������ʾ��������״̬2 �Ѿ�ʵ��
 * 2-----���µ���->����Ӧ                  �Ѿ�ʵ��
 *     --���¼����->���������洢3         �Ѿ�ʵ��
 *     --��������->���ּ�����ʾ��������״̬3   �Ѿ�ʵ��
 * 3-----��������->���ּ�����ʾ��            �Ѿ�ʵ��
 *     --���µ���->���ִ���洢2�������ʾ��������״̬4     �Ѿ�ʵ��
 *     --���¼����->���ִ���洢2�������ʾ��������״̬4    �Ѿ�ʵ��
 * 4----------->�ô洢1��2��3���м��㣬������ʾ��������״̬1
 *ȡ����
 *
 * �κ�ʱ����C��----�����ʾ�����ص�״̬0
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

    string senderName=sender()->objectName().mid(11).toStdString();//case�������ַ�����ǩ����������д����������ֵ���ʽ
    cout<<"SenderName="<<senderName<<"  Status="<<status;
    if(isdigit(senderName.at(0))){//������
        switch (status) {
        case 0:
        case 2:
               status+=1;
        case 1:
        case 3:
            ui->lcdNumber->display(stoi(senderName)+ui->lcdNumber->intValue()*10);//��̫Ť����
               break;
        case 4:break;
        }
    }else
       if(senderName=="equ"){//���ڼ�
        switch(status){
        case 0:
        case 1:
        case 2:break;
        case 3:num2=ui->lcdNumber->intValue();
               ui->lcdNumber->display(0);
               status=4;break;
        }
       }else if(senderName=="clear"){//C ��
           ui->lcdNumber->display(0);
           status=0;
       }else {//�����
           cout<<"�������"<<endl;
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
//4----------->�ô洢1��2��3���м��㣬������ʾ��������״̬1
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




