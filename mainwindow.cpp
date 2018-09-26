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
    //- with currently sending action we need to get fileFormat
    //- sender returns last using action
    QByteArray fileFormat = action->data().toByteArray(); // returns fileFormat
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

void MainWindow::createActions(){
    // Create the action tied to the menu
    openAction = new QAction(tr("&Open..."), this);

    // Define the associated shortcut key
    openAction->setShortcuts(QKeySequence::Open);

    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
        QString text = tr("%1...").arg(QString(format).toUpper());

        // Create an action for each file format
        QAction *action = new QAction(text, this);
        action->setData(format);

        connect(action, SIGNAL(triggered()), this, SLOT(save()));


        saveAsActs.append(action);
    }


    printAct = new QAction(tr("&Print..."), this);
    connect(printAct, SIGNAL(triggered()), scribbledArea, SLOT(print()));


    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));


    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));


    penWidthAct = new QAction(tr("Pen &Width..."), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));


    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()),
            scribbledArea, SLOT(clearImage()));


    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));


    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus(){

      saveAsMenu = new QMenu(tr("&Save As"), this);
      foreach (QAction *action, saveAsActs) // the same as range for
            saveAsMenu->addAction(action);


      fileMenu = new QMenu(tr("&File"), this);
      fileMenu->addAction(openAction);
      fileMenu->addMenu(saveAsMenu);
      fileMenu->addAction(printAct);
      fileMenu->addSeparator();
      fileMenu->addAction(exitAct);


      optionMenu = new QMenu(tr("&Options"), this);
      optionMenu->addAction(penColorAct);
      optionMenu->addAction(penWidthAct);
      optionMenu->addSeparator();
      optionMenu->addAction(clearScreenAct);


      helpMenu = new QMenu(tr("&Help"), this);
      helpMenu->addAction(aboutAct);
      helpMenu->addAction(aboutQtAct);


      menuBar()->addMenu(fileMenu);
      menuBar()->addMenu(optionMenu);
      menuBar()->addMenu(helpMenu);
}

bool MainWindow::maybeSave(){
    if(scribbledArea->isModified()){
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("&Scribblg"),tr("The image has been modified.\n" "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if(ret == QMessageBox::Save){
            return saveFile("png");
        }
        else if(ret == QMessageBox::Cancel) {
            return false;
        }

    }
   return true; // if the file was not modified return true
}

bool MainWindow::saveFile(const QByteArray& fileFormat){  // changing a path to save file
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
    initialPath, tr("%1 Files (*.%2);;All Files (*)").arg(QString::fromLatin1(fileFormat.toUpper())).arg(QString::fromLatin1(fileFormat)));
    if(fileName.isEmpty()){
        return false;
    }else{
        return scribbledArea->saveImage(fileName,fileFormat.constData());
    }
}
