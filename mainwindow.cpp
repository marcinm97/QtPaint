#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), scribbledArea(new ScribbleArea())
{
    ui->setupUi(this);
    setCentralWidget(scribbledArea);
    createActions();
    createMenus();
    setWindowTitle(tr("Scribble"));
    resize(1024,600);
}

void MainWindow::closeEvent(QCloseEvent* event){
    if(maybeSave()){
        event->accept();
    }else{
        event->ignore();
    }
}

MainWindow::~MainWindow()
{
    delete scribbledArea;
    delete ui;
}
void MainWindow::open(){
    if(maybeSave()){
        QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),QDir::currentPath());
        if(!fileName.isEmpty())
            scribbledArea->openImage(fileName);
    }
}
void MainWindow::save(){
    QAction* action = qobject_cast<QAction*>(sender()); // similar as dynamic_cast with RTTI
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}
void MainWindow::penColor(){
    QColor newColor = QColorDialog::getColor(scribbledArea->penColor());
    if(newColor.isValid()){
        scribbledArea->setPenColor(newColor);
    }
}
void MainWindow::penWidth(){
    bool check;
    int newWidth = QInputDialog::getInt(this,tr("Scribble"),tr("Select pen width : "), scribbledArea->penWidth(),1,50,1,&check);

    if(check){
     scribbledArea->setPenWidth(newWidth);
     }
}
void MainWindow::about(){
    QMessageBox::about(this, tr("About Scribble"),tr("<p> The <b> Scribble</b> example created by Marcin Mucha </p>"));
}
