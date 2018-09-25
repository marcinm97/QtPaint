#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "scribblearea.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QIcon>
#include <QDebug>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <QPalette>
#include <QTimer>
#include <QDateTime>
#include <QDir>
#include <QByteArray>
#include <QInputDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent* event) override;  // if the user tries to shut down the app without saving
    // we will protect against
private slots:
    void open();
    void save();
    void penColor();
    void penWidth();
    void about();
private:
    Ui::MainWindow *ui;
    void createActions();
    void createMenus();
    bool maybeSave();
    bool saveFile(const QByteArray& fileFormat);
    ScribbleArea* scribbledArea;
    QMenu* saveAsMenu;
    QMenu* fileMenu;
    QMenu* optionMenu;
    QMenu* helMenu;
    QAction* openAction;
    QList<QAction*> saveAsActs;
    QAction* printAct;
    QAction* penColorAct;
    QAction* clearScreenAct;
    QAction* aboutAct;
    QAction* acoutQtAct;
};

#endif // MAINWINDOW_H
