#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    // Enable item selection
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    ui->graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Connect signals to slots
    connect(ui->addNodeButton, &QPushButton::clicked, this, &MainWindow::addNode);
    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::removeSelectedItems);
    connect(ui->undoButton, &QPushButton::clicked, this, &MainWindow::undoLastNode);  // Verbindung für Undo
    connect(ui->makeForceButton, &QPushButton::clicked, this, &MainWindow::makeForce);

    drawCoordinateSystem();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addNode()
{
    QString xStr = ui->lineEditX->text();
    QString yStr = ui->lineEditY->text();

    if (xStr.isEmpty() || yStr.isEmpty()) {
        return;
    }

    bool okX, okY;
    double x = xStr.toDouble(&okX);
    double y = yStr.toDouble(&okY);

    if (okX && okY) {
        QPointF newNode(x, y);
        nodes.push_back(newNode);

        QGraphicsEllipseItem* newNodeItem = scene->addEllipse(x - 2, y - 2, 4, 4, QPen(), QBrush(Qt::SolidPattern));
        newNodeItem->setFlag(QGraphicsItem::ItemIsSelectable, true);  // Enable selection
        nodeItems.push_back(newNodeItem);

        if (nodes.size() > 1) {
            const QPointF& lastNode = nodes[nodes.size() - 2];
            QGraphicsLineItem* newLineItem = scene->addLine(lastNode.x(), lastNode.y(), newNode.x(), newNode.y(), QPen(Qt::black));
            newLineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);  // Enable selection
            lineItems.push_back(newLineItem);
        }
    }
}

bool MainWindow::isLineConnectedToNode(QGraphicsLineItem* line, QGraphicsEllipseItem* node)
{
    QPointF nodeCenter = node->rect().center() + node->pos();
    return line->line().p1() == nodeCenter || line->line().p2() == nodeCenter;
}

void MainWindow::removeSelectedItems()
{
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();
    for (QGraphicsItem* item : selectedItems) {
        if (QGraphicsEllipseItem* node = dynamic_cast<QGraphicsEllipseItem*>(item)) {
            // Remove lines connected to this node
            auto it = lineItems.begin();
            while (it != lineItems.end()) {
                if (isLineConnectedToNode(*it, node)) {
                    scene->removeItem(*it);
                    delete *it;
                    it = lineItems.erase(it);
                } else {
                    ++it;
                }
            }
            // Remove the node itself
            scene->removeItem(node);
            delete node;
            auto nodeIt = std::find(nodeItems.begin(), nodeItems.end(), node);
            if (nodeIt != nodeItems.end()) {
                nodeItems.erase(nodeIt);
            }
        } else if (QGraphicsLineItem* line = dynamic_cast<QGraphicsLineItem*>(item)) {
            // Remove the line
            scene->removeItem(line);
            delete line;
            auto lineIt = std::find(lineItems.begin(), lineItems.end(), line);
            if (lineIt != lineItems.end()) {
                lineItems.erase(lineIt);
            }
        } else {
            // Handle other types of items if needed
            scene->removeItem(item);
            delete item;
        }
    }
}

void MainWindow::drawCoordinateSystem()
{
    int width = ui->graphicsView->width();
    int height = ui->graphicsView->height();

    scene->setBackgroundBrush(QBrush(QColor(255, 255, 224)));

    QTransform transform;
    transform.scale(1, -1);
    ui->graphicsView->setTransform(transform);

    QPen axisPen(Qt::black);
    axisPen.setWidth(2);
    scene->addLine(-width / 2, 0, width / 2, 0, axisPen);
    scene->addLine(0, -height / 2, 0, height / 2, axisPen);

    QPen gridPen(Qt::gray);
    gridPen.setStyle(Qt::SolidLine);

    int step = 20;
    for (int x = -width / 2; x <= width / 2; x += step) {
        scene->addLine(x, -height / 2, x, height / 2, gridPen);
    }
    for (int y = -height / 2; y <= height / 2; y += step) {
        scene->addLine(-width / 2, y, width / 2, y, gridPen);
    }
}

void MainWindow::undoLastNode()
{
    if (!nodes.empty()) {
        // Letzten Knoten und sein grafisches Element entfernen
        nodes.pop_back();
        if (!nodeItems.empty()) {
            QGraphicsEllipseItem* lastNodeItem = nodeItems.back();
            nodeItems.pop_back();
            scene->removeItem(lastNodeItem);
            delete lastNodeItem;
        }

        // Letzte Linie und ihr grafisches Element entfernen, falls vorhanden
        if (!lineItems.empty()) {
            QGraphicsLineItem* lastLineItem = lineItems.back();
            lineItems.pop_back();
            scene->removeItem(lastLineItem);
            delete lastLineItem;
        }
    }
}

void MainWindow::makeForce()
{
    QString xStr = ui->lineEditX_2->text();
    QString yStr = ui->lineEditX_3->text();
    QString betragStr = ui->lineEditX_4->text();
    QString winkelStr = ui->lineEditX_5->text();

    if (xStr.isEmpty() || yStr.isEmpty() || betragStr.isEmpty() || winkelStr.isEmpty()) {
        return;
    }

    bool okX, okY, okBetrag, okWinkel;
    double x = xStr.toDouble(&okX);
    double y = yStr.toDouble(&okY);
    double betrag = betragStr.toDouble(&okBetrag);
    double winkel = winkelStr.toDouble(&okWinkel);


    if (okX && okY && okWinkel && okBetrag) {
        QPointF newPoint(x, y);
        qreal newBetrag(betrag);
        qreal newWinkel(winkel);
        
        force newForce; newForce.point = newPoint; newForce.betrag = newBetrag; newForce.winkel = newWinkel;
        forces.push_back(newForce);
        qreal arrowSize = 10; // size of head
                                             
        //Line
        double xEnd = x + cos(winkel) * 30; double yEnd = y + sin(winkel) * 30;
        QPointF start = newPoint; QPointF end = QPoint(xEnd, yEnd);
        QLineF line(start, end);
        //Line Item
        QPen pen; pen.setWidth(pow(betrag, 0.1));
        QGraphicsLineItem* newLineItem = scene->addLine(end.x(), end.y(), start.x(), start.y(), pen);
        newLineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);  // Enable selection
        forceLineItems.push_back(newLineItem);
        
        //Polygon
        
        double angle = std::atan2(-line.dy(), line.dx()); std::cout << angle << std::endl; std::cout << winkel << std::endl;

        QPointF arrowP1 = line.p1() + QPointF(sin(-(winkel + 4*M_PI / 3)) * arrowSize,
                                              cos(-(winkel + 4*M_PI / 3)) * arrowSize);
        QPointF arrowP2 = line.p1() + QPointF(sin(-(winkel + 2*M_PI - M_PI / 3)) * arrowSize,
                                              cos(-(winkel + 2*M_PI - M_PI / 3)) * arrowSize);
        QPolygonF arrowHead;
        arrowHead.clear();
        arrowHead << line.p1() << arrowP1 << arrowP2;
        //PolygonItem
        QGraphicsPolygonItem* newPolygonItem = scene->addPolygon(arrowHead , QPen(), QBrush(Qt::SolidPattern));
        newPolygonItem->setFlag(QGraphicsItem::ItemIsSelectable, true);  // Enable selection
        forcePolygonItems.push_back(newPolygonItem);
    }
}


    

    

