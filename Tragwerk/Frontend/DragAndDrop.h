#pragma once
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QMouseEvent>
#include <QDebug>
#include <vector>

class DragAndDrop {
public:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        QGraphicsEllipseItem::mousePressEvent(event);
        if (event->button() == Qt::LeftButton) {
            isMoving = true;
        } else if (event->button() == Qt::RightButton) {
            // Start connecting nodes
            startPosition = this->pos();
            currentLine = new QGraphicsLineItem(QLineF(startPosition, startPosition));
            currentLine->setPen(QPen(Qt::black, 2));
            scene()->addItem(currentLine);
        }
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override {
        QGraphicsEllipseItem::mouseMoveEvent(event);
        if (isMoving) {
            // Move node logic
            setPos(event->scenePos());
        } else if (currentLine) {
            // Drag line while connecting
            QLineF newLine(startPosition, event->scenePos());
            currentLine->setLine(newLine);
        }
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override {
        QGraphicsEllipseItem::mouseReleaseEvent(event);
        if (isMoving) {
            isMoving = false;
        } else if (currentLine) {
            // Finish connecting nodes
            QPointF endPosition = event->scenePos();
            QList<QGraphicsItem*> itemsAtEnd = scene()->items(endPosition);

            // Check if the mouse was released over another node
            for (QGraphicsItem* item : itemsAtEnd) {
                Node* otherNode = dynamic_cast<Node*>(item);
                if (otherNode && otherNode != this) {
                    // Connect the two nodes
                    QLineF finalLine(startPosition, otherNode->pos());
                    currentLine->setLine(finalLine);
                    currentLine = nullptr;
                    return;
                }
            }

            // If not over another node, remove the line
            scene()->removeItem(currentLine);
            delete currentLine;
            currentLine = nullptr;
        }
    }

private:
    bool isMoving;
    QPointF startPosition;
    QGraphicsLineItem* currentLine;
};


