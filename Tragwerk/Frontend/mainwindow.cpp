#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Log.cpp"
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
    connect(ui->supportButton, &QPushButton::clicked, this, &MainWindow::makeSupport);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::clear);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::save);
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::load);

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

    Log::print_nodes(nodes);
    Log::print_nodeItems(nodeItems);
    Log::print_lines(lineItems);
    Log::print_forces(forces);
    Log::print_forceGraphicsItems(forceGraphicsItems);
    Log::print_supportItems(supports);
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
        
      
      //IF NODE SELECTED
        if (QGraphicsEllipseItem* node = dynamic_cast<QGraphicsEllipseItem*>(item)) 
        {
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
                ptrdiff_t index = nodeIt - nodeItems.begin();
                nodes.erase(nodes.begin() + index);
            }
        } 



        //IF LINE SELECTED
        else if (QGraphicsLineItem* line = dynamic_cast<QGraphicsLineItem*>(item)) 
        {
            // Remove the line
            scene->removeItem(line);
            delete line;

            auto lineIt = std::find(lineItems.begin(), lineItems.end(), line);
            if (lineIt != lineItems.end()) {
                lineItems.erase(lineIt);
            }

           //deleting the according PolygonItem
           auto forceGraphicsIt = std::find_if(forceGraphicsItems.begin(), forceGraphicsItems.end(),
               [&line] (const forceGraphicsItem& x) -> bool {return line == x.forceLineItem;}); 
           if (forceGraphicsIt != forceGraphicsItems.end()) {
               scene->removeItem(forceGraphicsIt->forcePolygonItem);
               delete forceGraphicsIt->forcePolygonItem;
               forceGraphicsItems.erase(forceGraphicsIt);

               ptrdiff_t index = forceGraphicsIt - forceGraphicsItems.begin();
               forces.erase(forces.begin() + index);
           }
        }



       //IF POLYGON SELECTED
       else if (QGraphicsPolygonItem* polygon = dynamic_cast<QGraphicsPolygonItem*>(item)) 
        {
            // Remove the line
           scene->removeItem(polygon);
           delete polygon;

            auto supportIt = std::find(supportItems.begin(), supportItems.end(), polygon);
            if (supportIt != supportItems.end()) {
                supportItems.erase(supportIt);

                ptrdiff_t index = supportIt - supportItems.begin();
                supports.erase(supports.begin() + index);
            }

           auto forceGraphicsIt = std::find_if(forceGraphicsItems.begin(), forceGraphicsItems.end(),
               [&polygon] (const forceGraphicsItem& x) -> bool {return polygon == x.forcePolygonItem;}); 
           if (forceGraphicsIt != forceGraphicsItems.end()) {
               scene->removeItem(forceGraphicsIt->forceLineItem);
               delete forceGraphicsIt->forceLineItem;
               forceGraphicsItems.erase(forceGraphicsIt);

               ptrdiff_t index = forceGraphicsIt - forceGraphicsItems.begin();
               forces.erase(forces.begin() + index);
           }
        } 
        

        else 
        {
            // Handle other types of items if needed
            scene->removeItem(item);
            delete item;
        }
    }
    Log::print_nodes(nodes);
    Log::print_nodeItems(nodeItems);
    Log::print_lines(lineItems);
    Log::print_forces(forces);
    Log::print_forceGraphicsItems(forceGraphicsItems);
    Log::print_supportItems(supports);
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
        //forceLineItems.push_back(newLineItem);
        
        //Polygon
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
        //forcePolygonItems.push_back(newPolygonItem);
        
        //forceGraphicItem
        forceGraphicsItem newforceGraphicsItem(newLineItem, newPolygonItem);
        forceGraphicsItems.push_back(newforceGraphicsItem);
    }

    Log::print_nodes(nodes);
    Log::print_nodeItems(nodeItems);
    Log::print_lines(lineItems);
    Log::print_forces(forces);
    Log::print_forceGraphicsItems(forceGraphicsItems);
    Log::print_supportItems(supports);

}


 


void MainWindow::makeSupport()
{
    QString xStr = ui->lineEditX_6->text();
    QString yStr = ui->lineEditX_7->text();

    if (xStr.isEmpty() || yStr.isEmpty()) {
        return;
    }

    bool okX, okY;
    double x = xStr.toDouble(&okX);
    double y = yStr.toDouble(&okY);


    if (okX && okY) {
        QPointF newNode(x, y); supports.push_back(newNode);
        QPointF arrowP1(x-7, y-7);
        QPointF arrowP2(x+7, y-7);

        QPolygonF arrowHead;
        arrowHead.clear();
        arrowHead << newNode << arrowP1 << arrowP2;

        QGraphicsPolygonItem* newPolygonItem = scene->addPolygon(arrowHead , QPen(), QBrush(Qt::FDiagPattern));
        newPolygonItem->setFlag(QGraphicsItem::ItemIsSelectable, true);  // Enable selection
        supportItems.push_back(newPolygonItem);
    }

    Log::print_nodes(nodes);
    Log::print_nodeItems(nodeItems);
    Log::print_lines(lineItems);
    Log::print_forces(forces);
    Log::print_forceGraphicsItems(forceGraphicsItems);
    Log::print_supportItems(supports);

}
   





void MainWindow::clear() {
  //nodes
  nodes.clear();

  for(auto nodeItem : nodeItems) {
    scene->removeItem(nodeItem);
    delete nodeItem;
  }
  nodeItems.clear();

  //lines
  for(auto lineItem : lineItems) {
    scene->removeItem(lineItem);
    delete lineItem;
  }
  lineItems.clear();

  //Forces
  forces.clear();

  for(auto forceItem : forceGraphicsItems) {
    scene->removeItem(forceItem.forceLineItem); 
    scene->removeItem(forceItem.forcePolygonItem);
    delete forceItem.forceLineItem;
    delete forceItem.forcePolygonItem;
  }
  forceGraphicsItems.clear();

  //Supports
  supports.clear();

  for(auto supportItem : supportItems) {
    scene->removeItem(supportItem);
    delete supportItem;
  }
  supportItems.clear();
}






void MainWindow::save() {
  QString fileName = ui->lineEdit->text();

  if (fileName.isEmpty())
  {
        return;
  }

  std::ofstream outputFile("../savedStructures/" + fileName.toStdString() + ".txt");
  
  //Nodes
  outputFile << "nodes" << std::endl;
  for(auto node : nodes) {
    outputFile << node.x() << " " << node.y() << " ";
  }
  outputFile << std::endl;

  //Lines
  outputFile << "lines" << std::endl;
  for(auto line : lineItems) {
    outputFile << line->line().p1().x() << " " << line->line().p1().y() << " " << line->line().p2().x()  << " " << line->line().p2().y() << " ";
  }
  outputFile << std::endl;

  //Forces
  outputFile << "forces" << std::endl;
  for(auto force : forces) {
    outputFile << force.point.x()  << " " << force.point.y() << " " << force.betrag << " " << force.winkel << " ";
  }
  outputFile << std::endl;

  //Support
  outputFile << "supports" << std::endl;
  for(auto support : supports) {
    outputFile << support.x()  << " " << support.y() << " ";
  }
  outputFile << std::endl;


}





void MainWindow::load() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("load Data"), "/home", tr("Data Files (*.txt)"));
	
  
 /* std::ifstream stream(filepath);
	
	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	
	std::string line;
	std::stringstream ss[2];	
	ShaderType type = ShaderType::NONE;
	
	ShaderStrings result;

 	while(getline(stream, line)) {
		if(line.find("#shader") != std::string::npos) {
			if(line.find("vertex") 	!= std::string::npos) {
				//SET MODE TO VERTEX
				type = ShaderType::VERTEX;
			}
 			else if(line.find("fragment") != std::string::npos) {
				//SET MODE TO FRAGMENT
				type = ShaderType::FRAGMENT;
			}
			else {
				ss[(int)type] << line;
			}
		}
		else {
			ss[(int)type] << line << "\n";
		}	
	}*/
 
}

























