#pragma once

#include "Constants.h"
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
#include <QGraphicsSceneMouseEvent>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    friend class ::nodeGraphicsItem;

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
    void showResult();
    void showDisplacement();
    void showOriginal();
    void graphicalExport();
    void onButtonZoomIn();
    void onButtonZoomOut();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    
    //Nodes
    std::vector<QPointF> nodes;
    std::vector<nodeGraphicsItem*> nodeItems;
    
    //Lines
    std::vector<std::pair<QPointF, QPointF>> lines;
    std::vector<QGraphicsLineItem*> lineItems;
    
    //Forces
    std::vector<force> forces;
    std::vector<forceGraphicsItem> forceGraphicsItems;

    //Support
    std::vector<QPointF> supports;
    std::vector<QGraphicsPolygonItem*> supportItems; 

    //Results
    Backend::results result;
    resultGraphicsItems resultGraphicsItem;

    //Displaclement
    std::vector<forceGraphicsItem> displacementVectors;

    //Linear
    bool isLinear;
    double E, A;

    //originalVisible 0 because it gets changed as show Original is called in the Constructor
    bool originalVisible = 0;
    bool resultVisible = 0;
    bool displacementVisible = 0;


    void drawCoordinateSystem(); double width, height;
    bool isLineConnectedToNode(QGraphicsLineItem* line, nodeGraphicsItem* node);  // Function to check line connection
    bool isLineBetweenNodes(QPointF lhs, QPointF rhs);
    bool isForceOnNode(nodeGraphcisItem* , force);
    bool isSupportOnNode(nodeGraphcisItem*, QPointF);
};

//#endif // MAINWINDOW_H





