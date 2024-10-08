#pragma once

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

struct forceGraphicsItem {
  QGraphicsLineItem* forceLineItem;
  QGraphicsPolygonItem* forcePolygonItem;

  forceGraphicsItem(QGraphicsLineItem* line, QGraphicsPolygonItem* polygon) : forceLineItem(line), forcePolygonItem(polygon) {}
};

