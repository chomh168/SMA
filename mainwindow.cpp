#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "data.h"
#include "tcpclinet.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);




    //번호 가져오기
    ui->spinBox->setValue(getfileNum("port.txt"));
    ui->spinBox_2->setValue(getfileNum("inverter.txt"));

    plantNumber = ui->spinBox->value();
    invCount = ui->spinBox_2->value();

    //타이머 설정
    serTimer = new QTimer(this);
    serTimer->setInterval(600000);
    invTimer = new QTimer(this);
    invTimer->setInterval(10000);
    cheTimer = new QTimer(this);
    cheTimer->setInterval(1000);
    strTimer = new QTimer(this);
    strTimer->setInterval(5000);


    connect(serTimer,SIGNAL(timeout()),this,SLOT(serslot()));
    connect(invTimer,SIGNAL(timeout()),this,SLOT(invslot()));
    connect(cheTimer,SIGNAL(timeout()),this,SLOT(cheslot()));
    connect(strTimer,SIGNAL(timeout()),this,SLOT(strslot()));

    connect(ui->pushButton_5, SIGNAL(clicked()),this,SLOT(invslot()));

    strTimer->start();
    ui->textBrowser->setText("5초후 start");

    ui->listWidget->addItem("error list");

    //통신 설정
    for (int i = 0; i < 20; i++)
    {
         inv[i] = new Inverter(i);
    }
    MessageType=1;

}




MainWindow::~MainWindow()
{
    delete ui;
}


//클릭 이벤트(port)
void MainWindow::on_pushButton_clicked()
{
    plantNumber = ui->spinBox->value();

    QFile *file = new QFile;
    QString filename = "port.txt";

    file->setFileName(QApplication::applicationDirPath() + "/" + filename); //파일의 위치와 파일명 설정

    if (!file->open(QIODevice::WriteOnly)) //파일을 오픈
    {

    }
    QString str(QString::number(ui->spinBox->value())); //파일에 작성할 테스트
    file->write(str.toUtf8()); //파일에 텍스트를 작성
    file->close();
}

//클릭 이벤트(inverter)
void MainWindow::on_pushButton_2_clicked()
{

    invCount = ui->spinBox->value();

    QFile *file = new QFile;
    QString filename = "inverter.txt";

    file->setFileName(QApplication::applicationDirPath() + "/" + filename); //파일의 위치와 파일명 설정

    if (!file->open(QIODevice::WriteOnly)) //파일을 오픈
    {

    }

    QString str(QString::number(ui->spinBox_2->value())); //파일에 작성할 테스트
    file->write(str.toUtf8()); //파일에 텍스트를 작성
    file->close();

}

//번호 받기
int MainWindow::getfileNum(QString str)
{
    QString filename = str;
    QFile File(QApplication::applicationDirPath() + "/" + filename);

    if(!File.open(QFile::ReadOnly|QFile::Text)) // 읽기 전용, 텍스트로 파일 열기
    {
         if(!File.exists()) // 파일이 존재하지 않으면...
        {
             return 7777;
             // 파일이 존재하지 않으면 기본값 7777
        }

    }

    QTextStream OpenFile(&File);
    QString ConfigText;
    while(!OpenFile.atEnd())  // 파일 끝까지 읽어서
    {
         ConfigText=OpenFile.readLine(); // 한라인씩 읽어서 변수에 적용
    }
    File.close(); // 파일닫기

    return ConfigText.toInt();
}



void MainWindow::on_pushButton_3_clicked()
{
   invTimer->start();
   serTimer->start();
   cheTimer->start();

   ui->textBrowser->clear();
}
void MainWindow::on_pushButton_4_clicked()
{
    invTimer->stop();
    serTimer->stop();
    cheTimer->stop();
    strTimer->stop();
    ui->textBrowser->setText("stop");;
}


void MainWindow::serslot()
{

}
void MainWindow::invslot()
{
    int ipCount=0;

    if(MessageType == 1)
    {
        ui->textBrowser->clear();
        ui->textBrowser->append("Mesasage1");
        for(int i = 0; i<invCount;i++)
        {
            SEND1[1] = (char) i;
            SendMessage(invIP[i],SEND1);
        }
        MessageType++;
    }
    else if(MessageType == 2)
    {
        ui->textBrowser->clear();
        ui->textBrowser->append("Mesasage2");
        for(int i = 0; i<invCount;i++)
        {
            SEND2[1] = (char) i;
            SendMessage(invIP[i],SEND2);
        }
        MessageType++;
    }
    else if(MessageType== 3)
    {
        ui->textBrowser->clear();
        ui->textBrowser->append("Mesasage3");
        for(int i = 0; i<invCount;i++)
        {
            SEND3[1] = (char) i;
            SendMessage(invIP[i],SEND3);
        }
        MessageType++;
    }
    else if(MessageType==4)
    {
        ui->textBrowser->clear();
        ui->textBrowser->append("Mesasage4");
        for(int i = 0; i<invCount;i++)
        {
            SEND4[1] = (char) i;
            SendMessage(invIP[i],SEND4);
        }
        MessageType=1;


    }



}
void MainWindow::cheslot()
{
    ui->label_3->setText("server : "+QString::number(serTimer->remainingTime()/1000));//
    ui->label_4->setText("inverter : "+QString::number(invTimer->remainingTime()/1000));//
}
void MainWindow::strslot()
{
    invTimer->start();
    serTimer->start();
    cheTimer->start();


    strTimer->stop();
    ui->textBrowser->clear();
}


void MainWindow::SendMessage(QString server, char* data)
{
    QString sendData = "";
    QString recvData = "";

    char *rev = new char[256];

    TcpClient *client = new TcpClient();
    if(client->TcpConnect(server)==true)
    {


    client->sendRequst(data);

    qsnprintf(rev, sizeof(rev), "%s", client->readMessage().toUtf8().constData()); //receive


    if (selectSendMsgType == 1)
    {
        inv[data[1]]->totalYeild = rev[9] * 0x1000000 + rev[10] * 0x10000 + rev[11] * 0x100 + rev[12];
        inv[data[1]]->dailyYeild = rev[21] * 0x1000000 + rev[22] * 0x10000 + rev[23] * 0x100 + rev[24];

        ui->textBrowser->append("Received: ");
        ui->textBrowser->append("Device ID (Inv No) : " + QString::number(data[1]));
        ui->textBrowser->append("total yeild : "+QString::number(inv[data[1]]->totalYeild) + " kW");
        ui->textBrowser->append("daily yeild : "+ QString::number(inv[data[1]]->dailyYeild) +" kW");
        ui->textBrowser->append("");
    }
    else if (selectSendMsgType == 2)
    {
        inv[data[1]]->dcCurrentA = rev[9] * 0x1000000 + rev[10] * 0x10000 + rev[11] * 0x100 + rev[12];
        inv[data[1]]->dcVoltageA = rev[13] * 0x1000000 + rev[14] * 0x10000 + rev[15] * 0x100 + rev[16];
        inv[data[1]]->dcPowerA = rev[17] * 0x1000000 + rev[18] * 0x10000 + rev[19] * 0x100 + rev[20];
        inv[data[1]]->acPower = rev[21] * 0x1000000 + rev[22] * 0x10000 + rev[23] * 0x100 + rev[24];
        inv[data[1]]->acVoltage1 = rev[39] * 0x100 + rev[40] == 65535 ? 0 : (int)((rev[39] * 0x100 + rev[40]) * qSqrt(3));
        inv[data[1]]->acVoltage2 = rev[43] * 0x100 + rev[44] == 65535 ? 0 : (int)((rev[43] * 0x100 + rev[44]) * qSqrt(3));
        inv[data[1]]->acVoltage3 = rev[47] * 0x100 + rev[48] == 65535 ? 0 : (int)((rev[47] * 0x100 + rev[48]) * qSqrt(3));
        inv[data[1]]->acCurrent = rev[61] * 0x1000000 + rev[62] * 0x10000 + rev[63] * 0x100 + rev[64] == 65535 ? 0 : rev[61] * 0x1000000 + rev[62] * 0x10000 + rev[63] * 0x100 + rev[64];
        inv[data[1]]->acFrequency = rev[77] * 0x1000000 + rev[78] * 0x10000 + rev[79] * 0x100 + rev[80] == 65535 ? 0 : rev[77] * 0x1000000 + rev[78] * 0x10000 + rev[79] * 0x100 + rev[80];

        ui->textBrowser->append("Received: ");
        ui->textBrowser->append("Device ID (Inv No) : " + QString::number(data[1]));
        ui->textBrowser->append("dc current input A: "+ QString::number(inv[data[1]]->dcCurrentA) +" A");
        ui->textBrowser->append("dc voltage input A: "+ QString::number(inv[data[1]]->dcVoltageA) +" V");
        ui->textBrowser->append("dc power input A: "+ QString::number(inv[data[1]]->dcPowerA) +" W");
        ui->textBrowser->append("power : "+ QString::number(inv[data[1]]->acPower) +" W");
        ui->textBrowser->append("grid voltage phase L1 : "+ QString::number(inv[data[1]]->acVoltage1) +" V");
        ui->textBrowser->append("grid voltage phase L2 : "+ QString::number(inv[data[1]]->acVoltage2) +" V");
        ui->textBrowser->append("grid voltage phase L3 : "+ QString::number(inv[data[1]]->acVoltage3) + " V");
        ui->textBrowser->append("grid current : " + QString::number(inv[data[1]]->acCurrent) + " A");
        ui->textBrowser->append("grid frequency: "+ QString::number(inv[data[1]]->acFrequency) + " HZ");
        ui->textBrowser->append("");
    }
    else if (selectSendMsgType == 3)
    {
        inv[data[1]]->dcCurrentB = rev[9] * 0x1000000 + rev[10] * 0x10000 + rev[11] * 0x100 + rev[12];
        inv[data[1]]->dcVoltageB = rev[13] * 0x1000000 + rev[14] * 0x10000 + rev[15] * 0x100 + rev[16];
        inv[data[1]]->dcPowerB = rev[17] * 0x1000000 + rev[18] * 0x10000 + rev[19] * 0x100 + rev[20];

        inv[data[1]]->dcCurrent = (inv[rev[1]]->dcCurrentA + inv[rev[1]]->dcCurrentB);
        inv[data[1]]->dcVoltage = (inv[rev[1]]->dcVoltageA + inv[rev[1]]->dcVoltageB) / 2;
        inv[data[1]]->dcPower = (inv[rev[1]]->dcPowerA + inv[rev[1]]->dcPowerB);

        ui->textBrowser->append("Received: ");
        ui->textBrowser->append("Device ID (Inv No) : " + QString::number(data[1]));
        ui->textBrowser->append("dc current input B: " + QString::number(inv[data[1]]->dcCurrentB) + " A");
        ui->textBrowser->append("dc voltage input B: " + QString::number(inv[data[1]]->dcVoltageB) +  " V");
        ui->textBrowser->append("dc power input B: " + QString::number(inv[data[1]]->dcPowerB) +" W");
        ui->textBrowser->append("");
    }
    else if (selectSendMsgType == 4)
    {
        inv[data[1]]->operatingStatus = rev[11] * 0x100 + rev[12];

        ui->textBrowser->append("Received: ");
        ui->textBrowser->append("Device ID (Inv No) : " + QString::number(data[1]));
        ui->textBrowser->append("Operating status : "+ QString::number(inv[data[1]]->operatingStatus));
        ui->textBrowser->append("");
    }

    client->TcpDisconnect();
    }

    else
    {
        ui->listWidget->addItem(server);
    }



}









void MainWindow::on_pushButton_5_clicked()
{

}
