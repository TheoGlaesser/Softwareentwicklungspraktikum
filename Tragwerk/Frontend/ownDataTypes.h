#pragma once
#include <QGraphicsSceneMouseEvent>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QPointF>
#include <vector>
#include <iostream>
#include <string>
#include <QLabel>
#include <QMessageBox>
#include <iostream>
#include <string>


class MainWindow; 


struct support {
  QPointF p;
  bool xFixed, yFixed;
  double xDisp, yDisp;

  support(QPointF p, bool xFixed, bool yFixed, double xDisp, double yDisp) : p(p), xFixed(xFixed), yFixed(yFixed), xDisp(xDisp), yDisp(yDisp)  {}
};

struct force {
  QPointF point;
  qreal betrag;
  qreal winkel;
};



struct forceGraphicsItem {
  forceGraphicsItem(QGraphicsLineItem* line, QGraphicsPolygonItem* polygon) : forceLineItem(line), forcePolygonItem(polygon) {}

  QGraphicsLineItem* forceLineItem;
  QGraphicsPolygonItem* forcePolygonItem;
};



//Subclass QGraphicsEllipseItem to represent a selectable "point"
class nodeGraphicsItem : public QGraphicsEllipseItem {
  // Q_OBJECT
public:
    nodeGraphicsItem(const QPointF &point, MainWindow *mainWindow)
        : QGraphicsEllipseItem(point.x() - 4, point.y() - 4, 2 * 4, 2 * 4), currentLine(nullptr), isMoving(false), isLining(false), mainWindow(mainWindow) 
    {
        setFlags(QGraphicsItem::ItemIsSelectable);  // Allow the point to be selectable
        setBrush(Qt::black);  // Fill the point with a color
    }

    ~nodeGraphicsItem() {};
protected:
    // Override the mousePressEvent to handle selection
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event); 
    void mousePressEvent(QGraphicsSceneMouseEvent* event); 
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event); 
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event); 
private:
    // Display an information box next to the item when selected
    void showInformationBox(QGraphicsSceneMouseEvent *event);
        
    bool isMoving;
    bool isLining;
    QPointF startPosition;
    QGraphicsLineItem* currentLine;
    MainWindow* mainWindow;
};



struct resultGraphicsItems {
    std::vector<nodeGraphicsItem*> nodeItems;
    std::vector<QGraphicsLineItem*> lineItems;
    std::vector<forceGraphicsItem> forceGraphicsItems;
    std::vector<QGraphicsPolygonItem*> supportItems; 
};





