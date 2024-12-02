#pragma once
#include <iostream>
#include "math.h"
#include "cmath"
#include "ownDataTypes.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QPointF>
#include <vector>
#include <fstream>

///Log statements
namespace Log 
{
  void print_nodes(const std::vector<QPointF>&);
  void print_nodeItems(const std::vector<nodeGraphicsItem*>&);
  void print_lines(const std::vector<QGraphicsLineItem*>&);
  void print_forces(const std::vector<force>&);
  void print_forceGraphicsItems(const std::vector<forceGraphicsItem>&);
  void print_supportItems(const std::vector<QPointF>&);
}














