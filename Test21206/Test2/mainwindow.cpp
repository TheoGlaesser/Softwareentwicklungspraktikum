#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    // Verbindung des Signals mit dem Slot
    connect(ui->addNodeButton, &QPushButton::clicked, this, &MainWindow::addNode);
    connect(ui->undoButton, &QPushButton::clicked, this, &MainWindow::undoLastNode);  // Verbindung für Undo

    // Koordinatensystem erstellen
    drawCoordinateSystem();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addNode()
{
    // Beispiel: Knoten von zwei QLineEdit-Widgets (x und y) hinzufügen
    QString xStr = ui->lineEditX->text();
    QString yStr = ui->lineEditY->text();

    if (xStr.isEmpty() || yStr.isEmpty()) {
        return; // Keine Eingabe
    }

    bool okX, okY;
    double x = xStr.toDouble(&okX);
    double y = yStr.toDouble(&okY);

    if (okX && okY) {
        // Knoten in der Szene hinzufügen
        QPointF newNode(x, y);
        nodes.push_back(newNode);

        QGraphicsEllipseItem* newNodeItem = scene->addEllipse(x - 2, y - 2, 4, 4, QPen(), QBrush(Qt::SolidPattern));
        nodeItems.push_back(newNodeItem);

        // Verbindung zu den vorherigen Knoten hinzufügen
        if (nodes.size() > 1) {
            const QPointF& lastNode = nodes[nodes.size() - 2];
            QGraphicsLineItem* newLineItem = scene->addLine(lastNode.x(), lastNode.y(), newNode.x(), newNode.y(), QPen(Qt::black));
            lineItems.push_back(newLineItem);
        }
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

void MainWindow::drawCoordinateSystem()
{
    int width = ui->graphicsView->width();
    int height = ui->graphicsView->height();

    // Hintergrundfarbe der Szene setzen
    scene->setBackgroundBrush(QBrush(QColor(255, 255, 224)));  // Hellgelb

    // Transformation anpassen, um die y-Achse nach oben positiv zu machen
    QTransform transform;
    transform.scale(1, -1);  // y-Achse invertieren
    ui->graphicsView->setTransform(transform);

    // Achsen zeichnen
    QPen axisPen(Qt::black);
    axisPen.setWidth(2);
    scene->addLine(-width / 2, 0, width / 2, 0, axisPen);  // X-Achse
    scene->addLine(0, -height / 2, 0, height / 2, axisPen);  // Y-Achse

    // Gitterlinien zeichnen
    QPen gridPen(Qt::gray);
    gridPen.setStyle(Qt::SolidLine);

    int step = 20;  // Abstand zwischen den Gitterlinien
    for (int x = -width / 2; x <= width / 2; x += step) {
        scene->addLine(x, -height / 2, x, height / 2, gridPen);
    }
    for (int y = -height / 2; y <= height / 2; y += step) {
        scene->addLine(-width / 2, y, width / 2, y, gridPen);
    }
}
