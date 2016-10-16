#ifndef MSC_H
#define MSC_H

#include <QMouseEvent>
#include <QMainWindow>
#include <QSettings>

namespace Ui {
class MSc;
}

class MSc : public QMainWindow
{
    Q_OBJECT

public:
    explicit MSc(QWidget *parent = 0);
    ~MSc();
    bool setArg(QStringList);
    void keySignal();

private slots:
    void timerIn();
    void on_pushButton_clicked();

    void on_checkBox_toggled(bool checked);

    void on_pushButton_2_clicked();

private:
    Ui::MSc *ui;
    QPoint pLast;
    void screenShot(QString fname);
    bool isHide, isShot;
    QSettings* settings;
    QString savePath;
    bool first;
};

#endif // MSC_H
