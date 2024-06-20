#ifndef DATASTRUCTERES_H
#define DATASTRUCTERES_H
#include <QVector>
#include <QtCore/QCoreApplication>

// ------ класс, описывающий вершину графа ------
class Vertex {
public:
    int id; //айди (имя) вершины
    QVector<int> approachAdjVertexes; //массив имен смежных родительских вершин
    QVector<int> outputAdjVertexes; //массив имен смежных дочерних узлов

    Vertex(QVector<int>approachAdjVertexes, QVector<int> outputAdjVertexes,  int id); //конструктор
};


// ------ конструктор вершины ------
Vertex::Vertex(QVector<int>approachAdjVertexes, QVector<int> outputAdjVertexes,  int id)
{
    this->id = id;
    this->approachAdjVertexes = approachAdjVertexes;
    this->outputAdjVertexes = outputAdjVertexes;
}

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------




// ------ класс, описывающий дугу графа ------
class Edge
{
public:
    Vertex* outcomeVertex; //вершина-начало дуги
    Vertex* approachVertex; //вершина-конец дуги
    Edge(Vertex* outcomeVertex, Vertex* approachVertex); //конструктор
};


// ------ конструктор дуги ------
Edge::Edge(Vertex* outcomeVertex, Vertex* approachVertex)
{
    this->outcomeVertex = outcomeVertex;
    this->approachVertex = approachVertex;
}








#endif // DATASTRUCTERES_H
