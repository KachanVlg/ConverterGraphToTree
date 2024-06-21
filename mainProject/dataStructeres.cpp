#include "dataStructeres.h"

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
