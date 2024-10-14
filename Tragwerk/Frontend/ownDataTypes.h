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

struct resultGraphicsItems {
    std::vector<QGraphicsEllipseItem*> nodeItems;
    std::vector<QGraphicsLineItem*> lineItems;
    std::vector<forceGraphicsItem> forceGraphicsItems;
    std::vector<QGraphicsPolygonItem*> supportItems; 
};



/*class Node : public QGraphicsEllipseItem {
public:
    Node(QPointF position, QGraphicsItem* parent = nullptr)
        : QGraphicsEllipseItem(parent), isMoving(false), currentLine(nullptr) {
        setRect(-10, -10, 20, 20);  // Set node size as 20x20 circle
        setBrush(Qt::blue);
        setPos(position);
        setFlag(QGraphicsItem::ItemIsMovable);
        setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    }

    /*void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
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
    }*/

/*private:
    bool isMoving;
    QPointF startPosition;
    QGraphicsLineItem* currentLine;
};

class NodeScene : public QGraphicsScene {
public:
    NodeScene(QObject* parent = nullptr) : QGraphicsScene(parent) {}

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override {
        // Add new node on double click
        QPointF position = event->scenePos();
        Node* node = new Node(position);
        addItem(node);
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Create a scene and a view
    NodeScene scene;
    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setSceneRect(0, 0, 800, 600);
    view.setWindowTitle("Node Connection with Drag and Drop");
    view.resize(800, 600);

    view.show();
    return app.exec();
}*/

