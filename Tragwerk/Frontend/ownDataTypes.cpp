#include "ownDataTypes.h"
#include "mainwindow.h"



void nodeGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsEllipseItem::mousePressEvent(event); 
    /*if (event->button() == Qt::LeftButton) {
        isMoving = true;
    }*/ if (event->button() == Qt::LeftButton) {
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
            bool differentNode = (otherNode != this);
             
            if (otherNode && differentNode) {
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
            else {mainWindow->scene->removeItem(currentLine);}// currentLine = nullptr;}*/
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


void ownGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
  QPointF newNode = event->scenePos();

  //Check if node already exists
  bool isDrawn = false;
  mainWindow->isAlreadyDrawn(newNode, true, isDrawn);

  //Make Point in Grid if Close
  double xRemainder = std::numeric_limits<double>::max(), yRemainder = std::numeric_limits<double>::max(), xGrid, yGrid;

  //Find closest GridPoint
  if(std::abs(std::remainder(newNode.x(), 20)) < 4)  {
    xRemainder = std::remainder(newNode.x(), 20);
    xGrid = newNode.x() - xRemainder;
  }
  else if(std::abs(std::remainder(newNode.x(), 20 + 4)) < 4)  {
    xRemainder = std::remainder(newNode.x() + 4, 20);
    xGrid = newNode.x() + xRemainder;
  }
  if(std::abs(std::remainder(newNode.y(), 20)) < 4)  {
    yRemainder = std::remainder(newNode.y(), 20);
    yGrid = newNode.y() - yRemainder;
  }
  else if(std::abs(std::remainder(newNode.y(), 20 + 4)) < 4)  {
    yRemainder = std::remainder(newNode.y() + 4, 20);
    yGrid = newNode.y() + yRemainder;
  }

  if(xRemainder < 4 && yRemainder < 4)  {
      newNode.setX(xGrid);
      newNode.setY(yGrid);
  }
  

  if(isDrawn) {std::cout << "Already node there\n"; return;}

  mainWindow->checkRedraw(newNode.x(), newNode.y());
  mainWindow->nodes.push_back(newNode);
  mainWindow->handleNewNodeGraphics(newNode);
  
  if (mainWindow->nodes.size() > 1) {//connect last node with new one
      QPointF lastNode = mainWindow->nodes[mainWindow->nodes.size() - 2];
      mainWindow->lines.push_back(std::pair(lastNode, newNode));
      mainWindow->handleNewLineGraphics(lastNode, newNode);
  }
}
