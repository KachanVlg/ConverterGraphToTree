#ifndef COMPUTINGFUNCITONS_H
#define COMPUTINGFUNCITONS_H
#include <dataStructeres.h>




/*!
 * \brief Выполняет поиск в глубину (DFS) по ориентированному графу с целью нахождения варианта
 * \brief остовного дерева посредством удаления дуг, начиная с заданной вершины.
 * \param startVertex Указатель на вершину, с которой необходимо начать обход.
 * \param passedVertexes Ссылка на вектор, содержащий пройденные вершины.
 * \param deletedEdges Ссылка на вектор, содержащий удалённые рёбра.
 * \param graph Ссылка на карту графа, где ключ - идентификатор вершины, а значение - указатель на вершину.
 */
void searchTreeDFS(Vertex* startVertex, QVector<Vertex*>& passedVertexes, QVector<Edge>& deletedEdges, const QMap<int, Vertex*>& graph);








#endif // COMPUTINGFUNCITONS_H
