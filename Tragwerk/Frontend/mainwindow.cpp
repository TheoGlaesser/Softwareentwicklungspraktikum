#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Log.cpp"
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this)),
    E(std::numeric_limits<double>::max()),
    A(std::numeric_limits<double>::max())
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
    connect(ui->checkBox_3, &QCheckBox::stateChanged, this, &MainWindow::linearStateChange);
    connect(ui->parametersButton, &QPushButton::clicked, this, &MainWindow::updateE);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::updateA);
    connect(ui->solveButton, &QPushButton::clicked, this, &MainWindow::solve);
    connect(ui->checkBox_4, &QCheckBox::stateChanged, this, &MainWindow::showResult);
    connect(ui->checkBox_2, &QCheckBox::stateChanged, this, &MainWindow::showDisplacement);
    connect(ui->checkBox, &QCheckBox::stateChanged, this, &MainWindow::showOriginal);
   
    //Greying out the Displacement and Result Checkbox before the user simulates
    ui->checkBox_2->setEnabled(false);
    ui->checkBox_4->setEnabled(false);
    ui->checkBox->setChecked(true);

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
        if(originalVisible) {
          QPointF newNode(x, y);
          nodes.push_back(newNode);

          QGraphicsEllipseItem* newNodeItem = scene->addEllipse(x - 2, y - 2, 4, 4, QPen(), QBrush(Qt::SolidPattern));
          newNodeItem->setFlag(QGraphicsItem::ItemIsSelectable, true);  // Enable selection
          nodeItems.push_back(newNodeItem);

          if (nodes.size() > 1) {//connect last node with new one
              const QPointF& lastNode = nodes[nodes.size() - 2];
              QGraphicsLineItem* newLineItem = scene->addLine(lastNode.x(), lastNode.y(), newNode.x(), newNode.y(), QPen(Qt::black));
              newLineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);  // Enable selection
              lineItems.push_back(newLineItem);
              lines.push_back(std::pair(QPointF(lastNode.x(), lastNode.y()) , QPointF(newNode.x(), newNode.y())));
          }
       }

       else {
          QPointF newNode(x, y);
          nodes.push_back(newNode);

          if (nodes.size() > 1) {//connect last node with new one
              const QPointF& lastNode = nodes[nodes.size() - 2];
              lines.push_back(std::pair(QPointF(lastNode.x(), lastNode.y()) , QPointF(newNode.x(), newNode.y())));
          }
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
                ptrdiff_t index = lineIt - lineItems.begin();
                lines.erase(lines.begin() + index);
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
        
        if(originalVisible) {
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
          if(originalVisible) {
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
  lines.clear();

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

  outputFile << nodes.size() << " " << lineItems.size() << " " << forces.size() <<  " " << supports.size() << std::endl;
  
  //Nodes
  for(auto node : nodes) {
    outputFile << node.x() << " " << node.y() << " ";
  }
  outputFile << std::endl;

  //Lines
  for(auto line : lineItems) {
    outputFile << line->line().p1().x() << " " << line->line().p1().y() << " " << line->line().p2().x()  << " " << line->line().p2().y() << " ";
  }
  outputFile << std::endl;

  //Forces
  for(auto force : forces) {
    outputFile << force.point.x()  << " " << force.point.y() << " " << force.betrag << " " << force.winkel << " ";
  }
  outputFile << std::endl;

  //Support
  for(auto support : supports) {
    outputFile << support.x()  << " " << support.y() << " ";
  }
  outputFile << std::endl;


}





void MainWindow::load()
{

  clear();

  QString fileName = QFileDialog::getOpenFileName(this, tr("load Data"), "", tr("Data Files (*.txt)"));
  std::ifstream stream(fileName.toStdString());

  int numNodes, numLines, numForces, numSupports;
  stream >> numNodes; stream  >> numLines; stream >> numForces; stream >> numSupports;


  for(int i=0; i<numNodes; i++) {
    double x, y; stream >> x; stream >> y; 
    QPointF newNode(x,y); nodes.push_back(newNode);

    QGraphicsEllipseItem* newNodeItem = scene->addEllipse(x - 2, y - 2, 4, 4, QPen(), QBrush(Qt::SolidPattern));
    newNodeItem->setFlag(QGraphicsItem::ItemIsSelectable, true);  // Enable selection
    nodeItems.push_back(newNodeItem);
  }

  
 for(int i=0; i<numLines; i++) {
    double x1, y1, x2, y2; stream >> x1; stream >> y1; stream >> x2; stream >> y2;

    QGraphicsLineItem* newLineItem = scene->addLine(x1, y1, x2, y2, QPen(Qt::black));
    newLineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);  // Enable selection
    lineItems.push_back(newLineItem);
 }


 for(int i=0; i<numForces; i++) {
    double x, y, betrag, winkel; stream >> x; stream >> y; stream >> betrag; stream >> winkel;

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
  

 for(int i=0; i<numSupports; i++) {
    double x, y; stream >> x; stream >> y;
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
}






void MainWindow::linearStateChange()
{
  isLinear = !(isLinear);
}





void MainWindow::updateA()
{
  QString AStr = ui->lineEditX_9->text();

  if (AStr.isEmpty()) {
      return;
  }

  bool okA;
  double newA = AStr.toDouble(&okA);
  if(okA) {A = newA;}
  std::cout << A << std::endl;
}



void MainWindow::updateE()
{
  QString EStr = ui->lineEditX_8->text();

  if (EStr.isEmpty()) {
      return;
  }

  bool okE;
  double newE = EStr.toDouble(&okE);
  if(okE) {E = newE;}
  std::cout << E << std::endl;
}





void MainWindow::solve() 
{
  //Make Variables compatible with Backend
  std::vector<Backend::Bearing> backendBearings(supports.size());
  for(int i=0; i<backendBearings.size(); i++) {
    backendBearings[i] = Backend::Bearing(supports[i].x(), supports[i].y(), 1, 1);
  } 


  std::vector<Backend::Rod> backendRods(lineItems.size());
  for(int i=0; i<backendRods.size(); i++) {
    backendRods[i] = Backend::Rod(lineItems[i]->line().p1().x(), lineItems[i]->line().p1().y(), lineItems[i]->line().p2().x(), lineItems[i]->line().p2().y()); 
  }
  
  std::vector<Backend::Node> backendNodes(nodes.size());
  for (int i=0; i < nodes.size(); i++) {
	  backendNodes[i].p.x = nodes[i].x();
	  backendNodes[i].p.y = nodes[i].y();
	  backendNodes[i].id = i;
  }

  std::vector<Backend::Force> backendForces(forces.size());
  for(int i=0; i<backendForces.size(); i++) {
    backendForces[i] = Backend::Force(forces[i].point.x(), forces[i].point.y(),  forces[i].betrag, forces[i].winkel);
  }

  
  //CREATE AND RUN SIMULATOR
  Backend::Simulator simulator(isLinear);
  result = simulator.run(backendRods, backendForces, backendBearings, backendNodes, E, A);
  

  //ENABLE DISPLACEMENT AND RESULT VISIBILITY
  ui->checkBox_2->setEnabled(true);
  ui->checkBox_4->setEnabled(true);
}





void MainWindow::showResult() 
{

  if(resultVisible) {
    for(int i=0; i<result.nodes.size(); i++) {
        QGraphicsEllipseItem* newNodeItem = scene->addEllipse(result.nodes[i].p.x - 2.0, result.nodes[i].p.y - 2.0, 4.0, 4.0, QPen(), QBrush(Qt::SolidPattern));
        newNodeItem->setFlag(QGraphicsItem::ItemIsSelectable, true);  // Enable selection
        resultGraphicsItem.nodeItems.push_back(newNodeItem);
     }

     for(int i=0; i<result.rods.size(); i++) {
        QGraphicsLineItem* newLineItem = scene->addLine(result.rods[i].p1.x, result.rods[i].p1.y, result.rods[i].p2.x, result.rods[i].p2.y, QPen(Qt::black));
        newLineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);  // Enable selection
        resultGraphicsItem.lineItems.push_back(newLineItem);
     }


     for(int i=0; i<result.forces.size(); i++) {
        double x = result.forces[i].p.x;
        double y = result.forces[i].p.y;
        double betrag = result.forces[i].norm;
        double winkel = result.forces[i].angle;

        
        qreal arrowSize = 10; // size of head
                      
        //Line
        double xEnd = x + cos(winkel) * 30; double yEnd = y + sin(winkel) * 30;
        QPointF start = QPoint(x,y); QPointF end = QPoint(xEnd, yEnd);
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
        resultGraphicsItem.forceGraphicsItems.push_back(newforceGraphicsItem);



     }

     for(int i=0; i<result.bearings.size(); i++) {
        double x = result.bearings[i].p.x;
        double y = result.bearings[i].p.y;

        QPointF newNode(x, y); 
        QPointF arrowP1(x-7.0, y-7.0);
        QPointF arrowP2(x+7.0, y-7.0);

        QPolygonF arrowHead;
        arrowHead.clear();
        arrowHead << newNode << arrowP1 << arrowP2;

        QGraphicsPolygonItem* newPolygonItem = scene->addPolygon(arrowHead , QPen(), QBrush(Qt::FDiagPattern));
        newPolygonItem->setFlag(QGraphicsItem::ItemIsSelectable, true);  // Enable selection
        resultGraphicsItem.supportItems.push_back(newPolygonItem);
     }
  }

  else {
     for(auto nodeItem : resultGraphicsItem.nodeItems) {
        scene->removeItem(nodeItem);
        delete nodeItem;
      }
      resultGraphicsItem.nodeItems.clear();

      //lines
      for(auto lineItem : resultGraphicsItem.lineItems) {
        scene->removeItem(lineItem);
        delete lineItem;
      }
      resultGraphicsItem.lineItems.clear();

      //Forces

      for(auto forceItem : resultGraphicsItem.forceGraphicsItems) {
        scene->removeItem(forceItem.forceLineItem); 
        scene->removeItem(forceItem.forcePolygonItem);
        delete forceItem.forceLineItem;
        delete forceItem.forcePolygonItem;
      }
      resultGraphicsItem.forceGraphicsItems.clear();

      //Supports

      for(auto supportItem : resultGraphicsItem.supportItems) {
        scene->removeItem(supportItem);
        delete supportItem;
      }
      resultGraphicsItem.supportItems.clear();
  }

  resultVisible = !(resultVisible);
}





void MainWindow::showDisplacement() {
  
}





void MainWindow::showOriginal() 
{

  if(originalVisible) {
      std::cout << "clear\n";
      //Nodes
      for(auto nodeItem : nodeItems) {
        scene->removeItem(nodeItem);
        delete nodeItem;
      }
      nodeItems.clear();

      //Lines
      for(auto lineItem : lineItems) {
        scene->removeItem(lineItem);
        delete lineItem;
      }
      lineItems.clear();

      //Forces
      for(auto forceItem : forceGraphicsItems) {
        scene->removeItem(forceItem.forceLineItem); 
        scene->removeItem(forceItem.forcePolygonItem);
        delete forceItem.forceLineItem;
        delete forceItem.forcePolygonItem;
      }
      forceGraphicsItems.clear();

      //Supports
      for(auto supportItem : supportItems) {
        scene->removeItem(supportItem);
        delete supportItem;
      }
      supportItems.clear();
  }

  else {
    std::cout << "Redraw\n";
    for(int i=0; i<nodes.size(); i++) {
        QGraphicsEllipseItem* newNodeItem = scene->addEllipse(nodes[i].x() - 2.0, nodes[i].y() - 2.0, 4.0, 4.0, QPen(), QBrush(Qt::SolidPattern));
        newNodeItem->setFlag(QGraphicsItem::ItemIsSelectable, true);  // Enable selection
        nodeItems.push_back(newNodeItem);
     }

     for(int i=0; i<lines.size(); i++) {
        QGraphicsLineItem* newLineItem = scene->addLine(lines[i].first.x(), lines[i].first.y(), lines[i].second.x(), lines[i].second.y(), QPen(Qt::black));
        newLineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);  // Enable selection
        lineItems.push_back(newLineItem);
     }


     for(int i=0; i<forces.size(); i++) {
        double x = forces[i].point.x();
        double y = forces[i].point.y();
        double betrag = forces[i].betrag;
        double winkel = forces[i].winkel;

        
        qreal arrowSize = 10; // size of head
                      
        //Line
        double xEnd = x + cos(winkel) * 30; double yEnd = y + sin(winkel) * 30;
        QPointF start = QPoint(x,y); QPointF end = QPoint(xEnd, yEnd);
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

     for(int i=0; i<supports.size(); i++) {
        double x = supports[i].x();
        double y = supports[i].y();

        QPointF newNode(x, y); 
        QPointF arrowP1(x-7.0, y-7.0);
        QPointF arrowP2(x+7.0, y-7.0);

        QPolygonF arrowHead;
        arrowHead.clear();
        arrowHead << newNode << arrowP1 << arrowP2;

        QGraphicsPolygonItem* newPolygonItem = scene->addPolygon(arrowHead , QPen(), QBrush(Qt::FDiagPattern));
        newPolygonItem->setFlag(QGraphicsItem::ItemIsSelectable, true);  // Enable selection
        supportItems.push_back(newPolygonItem);
     }
  }

  originalVisible = !(originalVisible);
}





/*void MainWindow::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override {
        // Add new node on double click
        QPointF position = event->scenePos();
        Node* node = new Node(position);
        nodes.push_back(node);

        QGraphicsEllipseItem* newNodeItem = scene->addEllipse(x - 2, y - 2, 4, 4, QPen(), QBrush(Qt::SolidPattern));
        newNodeItem->setFlag(QGraphicsItem::ItemIsSelectable, true);  // Enable selection
        nodeItems.push_back(newNodeItem);
}*/

