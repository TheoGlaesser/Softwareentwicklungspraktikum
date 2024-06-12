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
    void addNode();  // Slot für das Hinzufügen eines Knotens
    void undoLastNode();  // Slot für das Rückgängig machen des letzten Knotens

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    std::vector<QPointF> nodes;  // Liste der Knoten
    std::vector<QGraphicsEllipseItem*> nodeItems;  // Liste der Knoten-Elemente
    std::vector<QGraphicsLineItem*> lineItems;  // Liste der Linien-Elemente

    void drawCoordinateSystem();  // Methode zum Zeichnen des Koordinatensystems
};

#endif // MAINWINDOW_H
