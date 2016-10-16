#include "msc.h"
#include "ui_msc.h"
#include <iostream>
#include <QTimer>
#include <QPixmap>
#include <QWindow>
#include <QScreen>
#include <QDateTime>
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>


using namespace std;



MSc::MSc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MSc)
{
    first = true;
    isShot = false;
    ui->setupUi(this);
    pLast = QCursor::pos();
    QTimer *timer = new QTimer();
    timer->setInterval(500);
    connect(timer,&QTimer::timeout,this,&MSc::timerIn);
    timer->start();
    settings = new QSettings("HKEY_LOCAL_MACHINE\\Software\\Screen",QSettings::NativeFormat);
    ui->checkBox->setChecked(settings->value("autostart",false).toBool());
    ui->screenPath->setText(settings->value("screenPath","C:\\").toString());
    savePath = settings->value("screenPath","C:\\").toString();
    first = false;
}
void MSc::keySignal(){
    isShot = true;
}
MSc::~MSc()
{
    delete ui;
}
void MSc::timerIn(){
    if(!isHide) return;
    if(!isShot) return;
    isShot = false;
    QDateTime local(QDateTime::currentDateTime());
    screenShot(local.toString("dd.MM.yyyy HH.mm.ss"));
    QPoint ps = QCursor::pos();
    if (pLast.x()!=ps.x() || pLast.y()!=ps.y()){
        pLast.setX(ps.x());
        pLast.setY(ps.y());
    }
}
bool MSc::setArg(QStringList sData){
    isHide = false;
    foreach(QString param, sData){
        if(param=="-h"){
            isHide = true;
        }
    }
    return isHide;
}
void MSc::screenShot(QString fname){
    QScreen *screen = QGuiApplication::primaryScreen();
        if (const QWindow *window = windowHandle())
            screen = window->screen();
        if (!screen)
            return;

        QPixmap originalPixmap = screen->grabWindow(0);
        originalPixmap.save(savePath+"/"+fname+".png");
}

void MSc::on_pushButton_clicked()
{
    QString tpath = QFileDialog::getExistingDirectory(this,
                          "Выберите путь для хранения скриншотов",
                          ui->screenPath->text(), QFileDialog::ShowDirsOnly);
    if(tpath!=""){
        tpath = tpath.split("/").join("\\");
        ui->screenPath->setText(tpath);
        settings->setValue("screenPath",tpath);
        settings->sync();
        savePath = settings->value("screenPath","C:\\").toString();
    }
}

void MSc::on_checkBox_toggled(bool checked)
{
    if(first) return;
    settings->setValue("autostart",checked);
    settings->sync();
    QString aName = QCoreApplication::applicationFilePath().split("/").join("\\");
    QSettings sett("HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",QSettings::NativeFormat);
    if(checked){
        if (sett.value("mScreen.exe","c").toString()=="c"){
            sett.setValue("mScreen.exe",aName+" -h");
        }
    }else {
        if (sett.value("mScreen.exe","c").toString()!="c"){
            sett.remove("mScreen.exe");
        }
    }
    sett.sync();
    if(sett.status() != QSettings::NoError){
        QMessageBox::warning(this,"Не удается записать значение","Произошла ошибка при записи значения в автозапуск.<br />Пожалуйста, проверьте права на запись.");
    }
}

void MSc::on_pushButton_2_clicked()
{
    QString aName = QCoreApplication::applicationFilePath()+" -h &";
    system(aName.toUtf8().data());
}
