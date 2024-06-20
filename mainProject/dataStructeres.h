#ifndef DATASTRUCTERES_H
#define DATASTRUCTERES_H
#include <QVector>
#include <QtCore/QCoreApplication>


class Vertex {
public:
    int id;
    QVector<int> approachAdjVertexes;
    QVector<int> outputAdjVertexes;

    Vertex(QVector<int>approachAdjVertexes, QVector<int> outputAdjVertexes,  int id);
};

Vertex::Vertex(QVector<int>approachAdjVertexes, QVector<int> outputAdjVertexes,  int id)
{
    this->id = id;
    this->approachAdjVertexes = approachAdjVertexes;
    this->outputAdjVertexes = outputAdjVertexes;
}

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------

class Edge
{
public:
    Vertex* outcomeVertex;
    Vertex* approachVertex;
    Edge(Vertex* outcomeVertex, Vertex* approachVertex);
};



Edge::Edge(Vertex* outcomeVertex, Vertex* approachVertex)
{
    this->outcomeVertex = outcomeVertex;
    this->approachVertex = approachVertex;
}




#endif // DATASTRUCTERES_H
