#include "ownDataTypes.h"
#include "mainwindow.h"


void nodeGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
      QGraphicsEllipseItem::mousePressEvent(event);
      if (isSelected()) {
          showInformationBox(event);
      }
  }


void nodeGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    // QGraphicsEllipseItem::mousePressEvent(event); 
    if (event->button() == Qt::LeftButton) {
        isMoving = true;
    } else if (event->button() == Qt::RightButton) {
        isLining = true;
        startPosition = this->rect().center();
    }
}


void nodeGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    // QGraphicsEllipseItem::mouseMoveEvent(event);
    if (isMoving) {
        // Move node logic
        //setPos(event->scenePos());
    } else if (isLining) {
        // Drag line while connecting
        if(currentLine != nullptr) delete currentLine;
        currentLine = nullptr;
        QLineF newLine(startPosition, event->scenePos());
        currentLine = mainWindow->scene->addLine(newLine);
    }
}


void nodeGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    // QGraphicsEllipseItem::mouseReleaseEvent(event);
    if (isLining) {
        // Finish connecting nodes
        QPointF endPosition = event->scenePos();
        QList<QGraphicsItem*> itemsAtEnd = mainWindow->scene->items(endPosition);

        // Check if the mouse was released over another node
        for (QGraphicsItem* item : itemsAtEnd) {
            nodeGraphicsItem* otherNode = dynamic_cast<nodeGraphicsItem*>(item);
            if (otherNode && otherNode != this) {
                bool lineAlreadyExists = mainWindow->isLineBetweenNodes(startPosition, otherNode->rect().center());
                if(lineAlreadyExists) { std::cout << "line Bool: " << lineAlreadyExists << "\n"; return;}

                QLineF finalLine(startPosition, otherNode->rect().center());
                mainWindow->lines.push_back(std::pair(QPointF(finalLine.p1().x(), finalLine.p1().y()), QPointF(finalLine.p2().x(), finalLine.p2().y())));

                QGraphicsLineItem* newLineItem = mainWindow->scene->addLine(finalLine);
                newLineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                if(newLineItem!=NULL) {
                mainWindow->lineItems.push_back(newLineItem);
                }
            }
            else {mainWindow->scene->removeItem(currentLine);}// currentLine = nullptr;}
        }
    }
    isLining = false; isMoving = false;
}



void nodeGraphicsItem::showInformationBox(QGraphicsSceneMouseEvent *event) {
        // Get the current position of the item (center of the ellipse)
        QPointF itemPos = this->rect().center() + this->pos();

        QMessageBox *infoLabel = new QMessageBox;
        infoLabel->setInformativeText("Node");
        infoLabel->setText("x-Koordinate: " + QVariant(itemPos.x()).toString() + "\n" + "y-Koordinate: " + QVariant(itemPos.y()).toString());

        infoLabel->show();
}

