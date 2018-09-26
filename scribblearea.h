#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QWidget>
#include <QColor>
#include <QImage>
#include <QPoint>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QPoint>
#include <QSize>
#include <QPainter>
#include <QPen>

class ScribbleArea : public QWidget
{
    Q_OBJECT
public:
    explicit ScribbleArea(QWidget *parent = nullptr);
    bool openImage(const QString& fileName);
    bool saveImage(const QString& fileName, const char* fileFormat);
    void setPenColor(const QColor& newColor);
    void setPenWidth(int newWidth);

    bool isModified() const {return modified; }
    QColor penColor() const {return myPenColor; }
    int penWidth() const {return myPenWidth; }
signals:

public slots:
    void clearImage();
    void print();
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
private:
    void drawLineTo(const QPoint& endPoint);
    void resizeImage(QImage* image, const QSize& newSize);
    bool modified, scribbling;
    QColor myPenColor;
    QImage image;
    QPoint lastPoint;
    int myPenWidth;
};

#endif // SCRIBBLEAREA_H
