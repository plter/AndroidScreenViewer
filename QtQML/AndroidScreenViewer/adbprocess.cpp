#include "adbprocess.h"
#include <iostream>
#include <QFileInfo>


AdbProcess::AdbProcess(QObject *parent) : QObject(parent),adbThread(this)
{
}

QString & AdbProcess::getAdbPath()
{
    return _theAdbPath;
}

void AdbProcess::startSnapAndPull()
{
    if (!adbThread.isRunning()) {
        adbThread.setStoped(false);
        adbThread.start();
    }
}

void AdbProcess::stop()
{
    adbThread.setStoped(true);
}

void AdbProcess::setAdbPath(QString adbPath)
{
    _theAdbPath = adbPath;
}



void AdbThread::run()
{
    bool use1 = true;

    while(!stoped){
        _theProcess->showStatusMsg("正在设备中截屏...");

        QString cmd;
        cmd+= _theProcess->getAdbPath();
        cmd+= "  shell screencap -p /mnt/sdcard/screen.png";

        int code = QProcess::execute(cmd);
        if (code) {
            _theProcess->showAlert("无法从设备截屏");
            break;
        }

        _theProcess->showStatusMsg("正在将截图传入电脑...");
        cmd.clear();
        cmd+= _theProcess->getAdbPath();
        cmd+= " pull /mnt/sdcard/screen.png ";
        QString imageName;
        if(use1){
            imageName += "screen1.png";
        }else{
            imageName+="screen2.png";
        }
        cmd+=imageName;
        code = QProcess::execute(cmd);
        if (code) {
            _theProcess->showAlert("无法从设备获取图片");
            break;
        }

        QFileInfo file(imageName);
        _theProcess->snap(file.absoluteFilePath());

        use1 = !use1;
    }
}
