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
