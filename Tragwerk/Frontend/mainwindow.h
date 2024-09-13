#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../Backend/src/Backend.h"
#include "math.h"
#include "cmath"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QPointF>
#include <vector>

struct force {
  QPointF point;
  qreal betrag;
  qreal winkel;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addNode();
    void removeSelectedItems(); 
    void undoLastNode(); // Slot for removing selected items
    void makeForce();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    std::vector<QPointF> nodes;
    std::vector<QGraphicsEllipseItem*> nodeItems;

    std::vector<QGraphicsLineItem*> lineItems;

    std::vector<force> forces;
    std::vector<QGraphicsLineItem*> forceLineItems;
    std::vector<QGraphicsPolygonItem*> forcePolygonItems;


    void drawCoordinateSystem();
    bool isLineConnectedToNode(QGraphicsLineItem* line, QGraphicsEllipseItem* node);  // Function to check line connection
};

#endif // MAINWINDOW_H
