#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QPointF>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addNode();
    void removeSelectedItems();  // Slot for removing selected items

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    std::vector<QPointF> nodes;
    std::vector<QGraphicsEllipseItem*> nodeItems;
    std::vector<QGraphicsLineItem*> lineItems;

    void drawCoordinateSystem();
    bool isLineConnectedToNode(QGraphicsLineItem* line, QGraphicsEllipseItem* node);  // Function to check line connection
};

#endif // MAINWINDOW_H
