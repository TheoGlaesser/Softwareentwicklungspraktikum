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
#include <QMessageBox>
#include <QString>
#include <iostream>
#include <utility>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include <QString>


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
    friend class ::ownGraphicsScene;

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
    void xFixedChange();
    void yFixedChange();
    void getInfo();

private:
    void drawCoordinateSystem(); double width, height;
    void showBox(const QString &);
    bool isLineConnectedToNode(QGraphicsLineItem* line, nodeGraphicsItem* node) const;  // Function to check line connection
    bool isLineBetweenNodes(QPointF lhs, QPointF rhs) const;
    bool isForceOnNode(nodeGraphicsItem* , force) const;
    bool isSupportOnNode(nodeGraphicsItem*, QPointF) const;
    void checkRedraw(const double& x, const double& y);
    void isAlreadyDrawn(QPointF, bool isCreatedByClick, bool& isDrawn);

    void handleNewNodeGraphics(const QPointF&);
    void handleNewLineGraphics(const QPointF& lhs, const QPointF& rhs); 
    void handleNewForceGraphics(const double& x, const double& y, const double& betrag, const double& winkel); 
    void handleNewSupportGraphics(const QPointF&);


private:
    Ui::MainWindow *ui;
    ownGraphicsScene *scene;
    
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
    std::vector<support> supports;
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
  
    //Bools for newsupportItems
    bool xFixed = 0, yFixed = 0;
};

//#endif // MAINWINDOW_H





