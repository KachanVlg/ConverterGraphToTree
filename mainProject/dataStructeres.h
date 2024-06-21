#ifndef DATASTRUCTERES_H
#define DATASTRUCTERES_H
#include <QVector>
#include <QtCore/QCoreApplication>






/*!
 * \class Vertex
 * \brief Класс, представляющий вершину в графе.
 *
 * Класс Vertex содержит информацию о вершине, такую как её идентификатор,
 * а также смежные родительские вершины (approachAdjVertexes)
 * и смежные дочерние вершины (outputAdjVertexes).
 */
class Vertex {
public:
    int id; /*!< Имя и идентефикатор вершины */
    QVector<int> approachAdjVertexes; /*!< Список смежных родительских вершин для данной */
    QVector<int> outputAdjVertexes; /*!< Список смежных дочерних вершин для данной */

    Vertex(QVector<int>approachAdjVertexes, QVector<int> outputAdjVertexes,  int id); /*!< Конструктор класса Vertex */
};




/*!
 * \brief Конструктор для класса Vertex.
 *
 * Инициализирует вершину с заданными смежными вершинами и идентификатором.
 *
 * \param approachAdjVertexes Список смежных родительских вершин
 * \param outputAdjVertexes Список смежных дочерних вершин
 * \param id Идентификатор вершины и ее имя.
 */
Vertex::Vertex(QVector<int>approachAdjVertexes, QVector<int> outputAdjVertexes,  int id)
{
    this->id = id;
    this->approachAdjVertexes = approachAdjVertexes;
    this->outputAdjVertexes = outputAdjVertexes;
}







/*!
 * \class Edge
 * \brief Класс, представляющий дугу в графе
 *
 * Класс Edge содержит информацию о дуге графа, а именно о вершине-начале (outcomeVertex)
 * и вершине-конце дуги (approachVertex)
 *
 */
class Edge
{
public:
    Vertex* outcomeVertex; /*!< Вершина-начало дуги */
    Vertex* approachVertex; /*!< Вершина-конец дуги */
    Edge(Vertex* outcomeVertex, Vertex* approachVertex); /*!< Конструктор Edge */
};


/*!
 * \brief Конструктор для класса Edge.
 *
 * Инициализирует дугу с заданными вершиной-началом и вершиной-концом
 *
 * \param outcomeVertex - вершина-начало дуги
 * \param approachVertex - вершина конец дуги
 */
Edge::Edge(Vertex* outcomeVertex, Vertex* approachVertex)
{
    this->outcomeVertex = outcomeVertex;
    this->approachVertex = approachVertex;
}








#endif // DATASTRUCTERES_H
