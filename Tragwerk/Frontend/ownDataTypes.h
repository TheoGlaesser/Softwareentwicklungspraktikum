#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QPointF>
#include <vector>
#include <iostream>
#include <string>

struct force {
  QPointF point;
  qreal betrag;
  qreal winkel;
};

struct forceGraphicsItem {
  QGraphicsLineItem* forceLineItem;
  QGraphicsPolygonItem* forcePolygonItem;

  forceGraphicsItem(QGraphicsLineItem* line, QGraphicsPolygonItem* polygon) : forceLineItem(line), forcePolygonItem(polygon) {}
};

struct resultGraphicsItems {
    std::vector<QGraphicsEllipseItem*> nodeItems;
    std::vector<QGraphicsLineItem*> lineItems;
    std::vector<forceGraphicsItem> forceGraphicsItems;
    std::vector<QGraphicsPolygonItem*> supportItems; 
};





