#pragma once


#include "../Backend/src/Backend.h"
#include "ownDataTypes.h"
#include "math.h"
#include "cmath"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QPointF>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <QFileDialog>


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
    void makeSupport();
    void clear();
    void save();
    void load();
    void linearStateChange();
    void updateE();
    void updateA();
    void solve();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    
    //Nodes
    std::vector<QPointF> nodes;
    std::vector<QGraphicsEllipseItem*> nodeItems;
    
    //Lines
    std::vector<QGraphicsLineItem*> lineItems;
    
    //Forces
    std::vector<force> forces;
    std::vector<forceGraphicsItem> forceGraphicsItems;

    //Support
    std::vector<QPointF> supports;
    std::vector<QGraphicsPolygonItem*> supportItems; 

    //Linear
    bool isLinear;
    double E, A;


    void drawCoordinateSystem();
    bool isLineConnectedToNode(QGraphicsLineItem* line, QGraphicsEllipseItem* node);  // Function to check line connection
};

//#endif // MAINWINDOW_H
