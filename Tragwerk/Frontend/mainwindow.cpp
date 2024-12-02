#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Log.cpp"
#include <algorithm>
#include <QPrinter>

#define M_PI 3.14159265358979323846 //pi

/**
 * Connect GUI actions to technical implementation
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this)),
    E(100000),
    A(1)

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
    connect(ui->pushButton_2, &QCheckBox::clicked, this, &MainWindow::graphicalExport);
    connect(ui->button_zoom_in, &QPushButton::clicked, this, &MainWindow::onButtonZoomIn);
    connect(ui->button_zoom_out, &QPushButton::clicked, this, &MainWindow::onButtonZoomOut);
    connect(ui->checkBox_y_fixed_2, &QCheckBox::stateChanged, this, &MainWindow::xFixedChange);
    connect(ui->checkBox_y_fixed, &QCheckBox::stateChanged, this, &MainWindow::yFixedChange);
    
   
    //Greying out the Displacement and Result Checkbox before the user simulates
    ui->checkBox_2->setEnabled(false);
    ui->checkBox_4->setEnabled(false);
    ui->checkBox->setChecked(true);
    ui->checkBox_y_fixed->setChecked(true);
    ui->checkBox_y_fixed_2->setChecked(true);


    width = ui->graphicsView->width();
    height = ui->graphicsView->height();
    drawCoordinateSystem();
}




MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * Print out a box
 */
void MainWindow::showBox(const QString & myStr) {
	QMessageBox infoLabel;
        infoLabel.setInformativeText(myStr);
        infoLabel.exec();
}


/**
 * Add a node to the grid
 */
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

    //Redraw  grid if out of bounds
    if(y > height/2 || x > width/2) {

      if(y > x) {height = std::abs(2*y) + 20;}
      else {height = std::abs(2*x) + 20;} 
      width = height;

      scene->setSceneRect(-height/2, -height/2, height, height);
      drawCoordinateSystem();
    } 


    bool isDrawn = false;
    QPointF* nodeP;
    
    //check if node has been already created    
    for (size_t i = 0; i < nodes.size(); i++) {
	    if (nodes[i].x() == x && nodes[i].y() == y) {
		    isDrawn = true;
		    nodeP = &nodes[i];
		    break;
	    }
    }
	

    if (okX && okY) {
        if(originalVisible) {
	  if (isDrawn) {
	      if (nodes.size() > 1) {
              const QPointF& lastNode = nodes[nodes.size() - 1];
              QGraphicsLineItem* newLineItem = scene->addLine(lastNode.x(), lastNode.y(), (*nodeP).x(), (*nodeP).y(), QPen(Qt::black));
              newLineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);  // Enable selection
              lineItems.push_back(newLineItem);
              lines.push_back(std::pair(QPointF(lastNode.x(), lastNode.y()) , QPointF((*nodeP).x(), (*nodeP).y())));
              }
	  }
	  else {

          QPointF newNode(x, y);
          nodes.push_back(newNode);

          nodeGraphicsItem* newNodeItem = new nodeGraphicsItem(newNode, this); scene->addItem(newNodeItem);
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
	}
       
	else {
	  if(isDrawn) {
	      if (nodes.size() > 1) {
	    	  const QPointF& lastNode = nodes[nodes.size() - 1];
          lines.push_back(std::pair(QPointF(lastNode.x(), lastNode.y()) , QPointF((*nodeP).x(), (*nodeP).y())));
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
    }
    Log::print_lines(lineItems);
}




/**
 * Check if node is connected to a rod
 */
bool MainWindow::isLineConnectedToNode(QGraphicsLineItem* line, nodeGraphicsItem* node)
{
    QPointF nodeCenter = node->rect().center() + node->pos();
    return line->line().p1() == nodeCenter || line->line().p2() == nodeCenter;
}

/**
 * Check if there is a rod between two nodes
 */
bool MainWindow::isLineBetweenNodes(QPointF lhs, QPointF rhs) {
  for(auto line : lines) 
  {
    if(line.first == lhs && line.second == rhs) 
    {
      return true;
    }

    else if(line.first == rhs && line.second == lhs) {
      return true;
    }

    return false;
  }
}

/**
 * Check if there is already a force on a node
 */
bool MainWindow::isForceOnNode(nodeGraphicsItem* node,force force) {
    QPointF nodeCenter = node->rect().center() + node->pos();
    return (force.point == nodeCenter);
}

/**
 * Check if there is already a bearing/support on a node
 */
bool MainWindow::isSupportOnNode(nodeGraphicsItem* node, QPointF support) {
	QPointF nodeCenter = node->rect().center() + node->pos();
	return (support == nodeCenter);
}

/*
 * Function to remove a selected graphical item
 */
void MainWindow::removeSelectedItems()
{
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();
    for (QGraphicsItem* item : selectedItems) {
        
      
      //if node is selected
        if (nodeGraphicsItem* node = dynamic_cast<nodeGraphicsItem*>(item)) 
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

	    //Remove potential force on that point
	    for(int i=0; i<forces.size(); i++) {
		if(isForceOnNode(node, forces[i])) {
			scene->removeItem(forceGraphicsItems[i].forceLineItem);
		       delete forceGraphicsItems[i].forceLineItem;
		       scene->removeItem(forceGraphicsItems[i].forcePolygonItem);
           		 delete forceGraphicsItems[i].forcePolygonItem;

			 forces.erase(forces.begin() + i);
			 forceGraphicsItems.erase(forceGraphicsItems.begin() + i);
		}
		}

    	    for(int i=0; i < supports.size(); i++) {
		if (isSupportOnNode(node, supports[i].p)) {
			    scene->removeItem(supportItems[i]);
		    	    delete supportItems[i];
			    supports.erase(supports.begin() + i);
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



        //If line is selected
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



       //if polygon is selected
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
}






/**
 * Draw the coordinate system of the grid
 */
void MainWindow::drawCoordinateSystem()
{
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

    QFont font;
    font.setPointSize(6); font.setBold(true);

    //X-Axis
    for (int x = 0; x <= width / 2; x += step) {
        scene->addLine(x, -height / 2, x, height / 2, gridPen);
        scene->addLine(-x, -height / 2, -x, height / 2, gridPen);

        QGraphicsTextItem* rowNumber = new QGraphicsTextItem(QString::number(x));

        rowNumber->setFont(font);
        rowNumber->setPos(x+1, 1);
        rowNumber->setTransform(transform);
        //rowNumber->scale(-1,1);  // Position to the left of the grid
        scene->addItem(rowNumber);

        QGraphicsTextItem* rowMinusNumber = new QGraphicsTextItem(QString::number(-x));

        rowMinusNumber->setFont(font);
        rowMinusNumber->setPos(-x+1, 1);  // Position to the left of the grid
        rowMinusNumber->setTransform(transform);

        scene->addItem(rowMinusNumber);

    }

    //Y-Axis
    for (int y = 0; y <= height / 2; y += step) {
        scene->addLine(-width / 2, y, width / 2, y, gridPen);
        scene->addLine(-width / 2, -y, width / 2, -y, gridPen);

        QGraphicsTextItem* rowNumber = new QGraphicsTextItem(QString::number(y));
        rowNumber->setFont(font); 
        rowNumber->setPos(-1, y-1);  // Position to the left of the grid
        rowNumber->setTransform(transform);
        scene->addItem(rowNumber);

        QGraphicsTextItem* rowMinusNumber = new QGraphicsTextItem(QString::number(-y));

        rowMinusNumber->setFont(font); 
        rowMinusNumber->setPos(-1, -y-1);  // Position to the left of the grid
        rowMinusNumber->setTransform(transform);

        scene->addItem(rowMinusNumber);

    }
}



/**
 * Undo the last node that has been created
 */
void MainWindow::undoLastNode()
{
    if (!nodes.empty()) {
        // Remove node and its graphical element
        nodes.pop_back();
        if (!nodeItems.empty()) {
            nodeGraphicsItem* lastNodeItem = nodeItems.back();
            nodeItems.pop_back();
            scene->removeItem(lastNodeItem);
            delete lastNodeItem;
        }

        // Remove last line if existing
        if (!lineItems.empty()) {
            QGraphicsLineItem* lastLineItem = lineItems.back();
            lineItems.pop_back();
            scene->removeItem(lastLineItem);
            delete lastLineItem;
        }
    }
}

/**
 * Function to instantiate a force on a node
 */
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
	
    if (betrag <= 0) {
	    const QString err = "Please make a force with positive amount";
	    showBox(err);	
	    return;
    }

    double winkel = winkelStr.toDouble(&okWinkel);
    winkel = winkel*M_PI/180;
    
    //Check that force points to a node
    bool isNode = false;
    for (size_t i = 0; i < nodes.size(); i++) {
	    if (x == nodes[i].x() && y == nodes[i].y()) {
		    isNode = true;
		    break;
	    }
    }
    
    if(!isNode) {
	    const QString err = "Force must be on a node. Please draw a force on an already created node";
	    showBox(err);
	    return;
    }

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
}


 

/**
 * Function to make a support on a node
 */
void MainWindow::makeSupport()
{
    QString xStr = ui->lineEdit_x_pos->text();
    QString yStr = ui->lineEditX_y_pos->text();
    QString xDisplacement = ui->lineEdit_x_displacement->text();
    QString yDisplacement = ui->lineEdit_y_displacement->text();


    if (xStr.isEmpty() || yStr.isEmpty() || xDisplacement.isEmpty() || yDisplacement.isEmpty()) {
        return;
    }


    bool okXPos, okYPos, okXDisp, okYDisp; 
    double x = xStr.toDouble(&okXPos);
    double y = yStr.toDouble(&okYPos);
    double xDisp = xDisplacement.toDouble(&okXDisp);
    double yDisp = yDisplacement.toDouble(&okYDisp);

    

    bool isNode = false;
    for (size_t i = 0; i < nodes.size(); i++) {
            if (x == nodes[i].x() && y == nodes[i].y()) {
                    isNode = true;
                    break;
            }
    }

    if(!isNode) {
            const QString err =  "Bearing must be on a node. Please draw a bearing on an already created node";
	    showBox(err);
            return;
    }

	

    if (okXPos && okYPos && okXDisp && okYDisp) {
          QPointF newNode(x, y); 
          support newSupport(newNode, xFixed, yFixed, xDisp, yDisp);
          supports.push_back(newSupport);

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
  }
}
   




/**
 * Clear the grid
 */
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


  //Results
  if (resultGraphicsItem.nodeItems.size() == 0) {return;}
  

  //New nodes
  result.nodes.clear();	 
  for (auto resultNodeItem : resultGraphicsItem.nodeItems) {
   scene->removeItem(resultNodeItem);
   delete resultNodeItem;
  }
  resultGraphicsItem.nodeItems.clear();
  

  //New lines
  result.rods.clear();
  for (auto resultLineItem : resultGraphicsItem.lineItems) {
   scene->removeItem(resultLineItem);
   delete resultLineItem;
  }
  resultGraphicsItem.lineItems.clear();


  //New forces
  result.forces.clear();
  for (auto resultForceItem : resultGraphicsItem.forceGraphicsItems) {
    scene->removeItem(resultForceItem.forceLineItem);
    scene->removeItem(resultForceItem.forcePolygonItem);
    delete resultForceItem.forceLineItem;
    delete resultForceItem.forcePolygonItem;
  }
  resultGraphicsItem.forceGraphicsItems.clear();

  //New bearings
  result.bearings.clear();
  for (auto resultSupportItem : resultGraphicsItem.supportItems) {
   scene->removeItem(resultSupportItem);
   delete resultSupportItem;
  }
  resultGraphicsItem.supportItems.clear();

  for(int i=0; i<displacementVectors.size(); i++) {
    scene->removeItem(displacementVectors[i].forceLineItem); 
    scene->removeItem(displacementVectors[i].forcePolygonItem);
  }
  displacementVectors.clear();
}


/**
 * Save the grid elements
 */
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
    outputFile << support.p.x()  << " " << support.p.y() << " " << support.xFixed << " " << support.yFixed << " " << support.xDisp << " " << support.yDisp;
  }
  outputFile << std::endl;
}




/**
 * Load a truss from a txt file
 */
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

    nodeGraphicsItem* newNodeItem = new nodeGraphicsItem(newNode, this); scene->addItem(newNodeItem);
    newNodeItem->setFlag(QGraphicsItem::ItemIsSelectable, true);  // Enable selection
    nodeItems.push_back(newNodeItem);
  }

  
 for(int i=0; i<numLines; i++) {
    double x1, y1, x2, y2; stream >> x1; stream >> y1; stream >> x2; stream >> y2;
    lines.push_back(std::pair(QPointF(x1, y1), QPointF(x2, y2)));

    QGraphicsLineItem* newLineItem = scene->addLine(x1, y1, x2, y2, QPen(Qt::black));
    newLineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);  // Enable selection
    lineItems.push_back(newLineItem);
 }


 for(int i=0; i<numForces; i++) {
    double x, y, betrag, winkel; stream >> x; stream >> y; stream >> betrag; stream >> winkel;
    winkel = winkel*M_PI/180;	
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
    double x, y, xDisp, yDisp; bool xFixed, yFixed;
    stream >> x; stream >> y; stream >> xFixed; stream >> yFixed; stream >> xDisp; stream >> yDisp;
    QPointF newNode(x, y); support newSupport(newNode, xFixed, yFixed, xDisp, yDisp);
    supports.push_back(newSupport);

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


/**
 * Check if linear
 */
void MainWindow::linearStateChange()
{
  isLinear = !(isLinear);
}


/**
 * Check if bearing x coordinate is fixed
 */
void MainWindow::xFixedChange()
{
  xFixed = !(xFixed);
  std::cout << "xFixed: " << xFixed << "\n";
}

/**
 * Check if bearing y coordinate is fixed
 */
void MainWindow::yFixedChange()
{
  yFixed = !(yFixed);
  std::cout << "yFixed: " << yFixed << "\n";
}

/**
 * Update A
 */
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


/** 
 * Update E
 */
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




/**
 * Solve the linear system and compute new variables
 */
void MainWindow::solve() 
{
  //Make Variables compatible with Backend
  std::vector<Backend::Bearing> backendBearings(supports.size());
  for(int i=0; i<backendBearings.size(); i++) {
	  std::pair<bool,double> xInfo(supports[i].xFixed, supports[i].xDisp);
	  std::pair<bool,double> yInfo(supports[i].yFixed, supports[i].yDisp);
	  backendBearings[i] = Backend::Bearing(supports[i].p.x(), supports[i].p.y(),xInfo, yInfo);
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

  
  //create and run simulator
  bool isVisible = true;
  Backend::Exception err(isVisible);
  Backend::Simulator simulator(isLinear);
  result = simulator.run(backendRods, backendForces, backendBearings, backendNodes, E, A, err);
  

  //Enable displacement and result visibility
  if (err.isVisible) {
  	ui->checkBox_2->setEnabled(true);
  	ui->checkBox_4->setEnabled(true);
  }

  else {
	result.nodes.clear();
	result.rods.clear();
	result.bearings.clear();
	result.forces.clear();
	ui->checkBox_2->setEnabled(false);
	ui->checkBox_4->setEnabled(false);
	ui->checkBox_2->setChecked(false);
	ui->checkBox_4->setChecked(false);
	const QString error =QString::fromStdString(err.message);
	showBox(error);
  }
}

/**
 * Display the results on the grid (GUI)
 */
void MainWindow::showResult() 
{
  resultVisible  = !resultVisible;
  QPen pen;
  if(resultVisible) {
    for(int i=0; i<result.nodes.size(); i++) {
	    result.nodes[i].print();
       QPointF  newNode(result.nodes[i].p.x, result.nodes[i].p.y);
       nodeGraphicsItem* newNodeItem = new nodeGraphicsItem(newNode, this); scene->addItem(newNodeItem);
       newNodeItem->setFlag(QGraphicsItem::ItemIsSelectable, true);  // Enable selection
       resultGraphicsItem.nodeItems.push_back(newNodeItem);
    }


     for(int i=0; i<result.rods.size(); i++) {
        QGraphicsLineItem* newLineItem = scene->addLine(result.rods[i].p1.x, result.rods[i].p1.y, result.rods[i].p2.x, result.rods[i].p2.y, QPen(Qt::red));
        newLineItem->setFlag(QGraphicsItem::ItemIsSelectable, false);  // Enable selection
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
        newLineItem->setFlag(QGraphicsItem::ItemIsSelectable, false);  // Enable selection
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
        newPolygonItem->setFlag(QGraphicsItem::ItemIsSelectable, false);  // Enable selection
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

      for(int i = 0; i < resultGraphicsItem.forceGraphicsItems.size(); i++) {
        scene->removeItem(resultGraphicsItem.forceGraphicsItems[i].forceLineItem); 
        scene->removeItem(resultGraphicsItem.forceGraphicsItems[i].forcePolygonItem);
        delete resultGraphicsItem.forceGraphicsItems[i].forceLineItem;
        delete resultGraphicsItem.forceGraphicsItems[i].forcePolygonItem;
      }
      resultGraphicsItem.forceGraphicsItems.clear();

      //Supports

      for(auto supportItem : resultGraphicsItem.supportItems) {
        scene->removeItem(supportItem);
        delete supportItem;
      }
      resultGraphicsItem.supportItems.clear();
  }
}




/**
 * Display the displacement vectors for each node
 */
void MainWindow::showDisplacement() 
{
  displacementVisible = !(displacementVisible);

  if(displacementVisible) {
    forceGraphicsItems.clear();

    for(int i=0; i<nodes.size(); i++) {
      QPointF start(result.nodes[i].p.x, result.nodes[i].p.y);
      QPointF end = nodes[i];

      double distance = sqrt( pow(start.x() - end.x(), 2) + pow(start.y() - end.y(), 2));
      double winkel = std::atan((end.y() - start.y()) / (end.x() - start.x()));

      QLineF line(start, end);
      //Line Item
      QPen pen(Qt::blue); pen.setWidth(CONSTANTS::displacementVectorLineSize);
      QGraphicsLineItem* newLineItem = scene->addLine(end.x(), end.y(), start.x(), start.y(), pen);
      newLineItem->setFlag(QGraphicsItem::ItemIsSelectable, false);  // Enable selection
      //forceLineItems.push_back(newLineItem);
      
      //Polygon
      QPointF arrowP1 = line.p1() + QPointF(sin(-(winkel + 4*M_PI / 3)) * CONSTANTS::displacementVectorArrowSize,
                                            cos(-(winkel + 4*M_PI / 3)) * CONSTANTS::displacementVectorArrowSize);
      QPointF arrowP2 = line.p1() + QPointF(sin(-(winkel + 2*M_PI - M_PI / 3)) * CONSTANTS::displacementVectorArrowSize,
                                            cos(-(winkel + 2*M_PI - M_PI / 3)) * CONSTANTS::displacementVectorArrowSize);
      QPolygonF arrowHead;
      arrowHead.clear();
      arrowHead << line.p1() << arrowP1 << arrowP2;
      //PolygonItem
      QGraphicsPolygonItem* newPolygonItem = scene->addPolygon(arrowHead , QPen(), QBrush(Qt::SolidPattern));
      newPolygonItem->setFlag(QGraphicsItem::ItemIsSelectable, false);  // Disable selection
            
      //forceGraphicItem
      forceGraphicsItem newforceGraphicsItem(newLineItem, newPolygonItem);
      displacementVectors.push_back(newforceGraphicsItem);
    }
  }

  else {
    for(int i = 0; i < displacementVectors.size(); i++) {
      scene->removeItem(displacementVectors[i].forceLineItem); 
      scene->removeItem(displacementVectors[i].forcePolygonItem);
    }
  }
}




/**
 * Allow to show the original truss, before the simulation
 */
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
      for(int i = 0; i < forceGraphicsItems.size(); i++) {
        scene->removeItem(forceGraphicsItems[i].forceLineItem); 
        scene->removeItem(forceGraphicsItems[i].forcePolygonItem);
        delete forceGraphicsItems[i].forceLineItem;
        delete forceGraphicsItems[i].forcePolygonItem;
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
        QPointF newNode(nodes[i].x(), nodes[i].y());
        nodeGraphicsItem* newNodeItem = new nodeGraphicsItem(newNode, this); scene->addItem(newNodeItem);
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
        double x = supports[i].p.x();
        double y = supports[i].p.y();

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



/**
 * Export the graphical image of truss
 */
void MainWindow::graphicalExport() {
    QString fileName = ui->exportName->text();


    if (fileName.isEmpty()) {
        return;  // if the file doesn't have a name, we break
    }

    //if there is no suffix .pdf we add it
    if (QFileInfo(fileName).suffix().isEmpty()) {
        fileName.append(".pdf");
    }

    // QPrinter für PDF-Ausgabe konfigurieren
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    //Qpainter initialisation
    QPainter painter(&printer);

    
    ui->graphicsView->render(&painter);
    
    //pdf will be created
    painter.end();
}

///To zoom in 
void MainWindow::onButtonZoomIn()
{
  double scale = ui->zoom_scale_spin_box->value();
  ui->graphicsView->scale(scale, scale);
}

///To zoom out
void MainWindow::onButtonZoomOut()
{
  double scale = ui->zoom_scale_spin_box->value();
  ui->graphicsView->scale(1.0/scale, 1.0/scale);
}


