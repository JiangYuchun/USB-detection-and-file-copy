#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <QMainWindow>
#include <QMessageBox>
#include <unistd.h>                         //Used for UART
#include <fcntl.h>                          //Used for UART
#include <stdio.h>
#include <QDebug>
#include <iostream>   //checking the exiting file
#include <stdlib.h>
#include <QApplication>
#include <QProcess>
#include <QString>
#include <string>                          
#include <sstream>

void MainWindow::file_copy()
{
   QString Command;

    QString args;
    args.clear();
    args ="-h";
    qDebug()<<args;
    Command= QString("df %1").arg(args);
    qDebug()<<Command;



   QProcess* process = new QProcess(this);
  process->start(Command);
  process->waitForFinished();

  QString tmp = process->readAll();

    const char* USB_LOG;

    const char* mem_LOG;

    string USB_string;
    string mem_string;
    USB_string = LIMS_USB_PATH + (string) LIMS_Logfilename.toUtf8().constData();
    mem_string = LIMS_LOG_PATH + (string) LIMS_Logfilename.toUtf8().constData();
    USB_LOG=USB_string.c_str();
    mem_LOG=mem_string.c_str();

    ifstream check_USB_file(USB_LOG);
    if (check_USB_file)
    {
        remove(USB_LOG);
        ui->statusBar->showMessage("file deleted");
    }
    else ui->statusBar->showMessage("file not deleted");

    if ( tmp.contains("/media/usb0",Qt::CaseInsensitive)){
    bool i = QFile::copy(mem_LOG, USB_LOG);
   if (i){
       ui->statusBar->showMessage("File Saved");
   }
   else ui->statusBar->showMessage("Saving File Error Please Try Again");
    }
    else ui->statusBar->showMessage("Saving File Error Please Insert USB");
}
