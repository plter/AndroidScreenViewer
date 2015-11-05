#ifndef ADBPROCESS_H
#define ADBPROCESS_H

#include <QObject>
#include <QThread>
#include <QProcess>

class AdbProcess;

class AdbThread :public QThread
{
public:
    AdbThread(AdbProcess * adbProcess):stoped(false) {
        _theProcess = adbProcess;
    }

    void setStoped(bool b){
        stoped = b;
    }

protected:
    virtual void run();

private:
    AdbProcess * _theProcess;
    bool stoped;
};

class AdbProcess : public QObject
{
    Q_OBJECT
public:
    explicit AdbProcess(QObject *parent = 0);
    QString & getAdbPath();

signals:
    void snap(QString path);
    void showAlert(QString msg);
    void showStatusMsg(QString msg);

public slots:
    void startSnapAndPull();
    void stop();
    void setAdbPath(QString adbPath);

private:
    AdbThread adbThread;
    QString _theAdbPath;
};

#endif // ADBPROCESS_H
