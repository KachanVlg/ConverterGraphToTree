#ifndef COMPUTINGFUNCITONS_H
#define COMPUTINGFUNCITONS_H
#include "dataStructeres.h"




/*!
 * \brief Выполняет поиск в глубину (DFS) по ориентированному графу с целью нахождения варианта
 * \brief остовного дерева посредством удаления дуг, начиная с заданной вершины.
 * \param startVertex Указатель на вершину, с которой необходимо начать обход.
 * \param passedVertexes Ссылка на вектор, содержащий пройденные вершины.
 * \param deletedEdges Ссылка на вектор, содержащий удалённые рёбра.
 * \param graph Ссылка на карту графа, где ключ - идентификатор вершины, а значение - указатель на вершину.
 */
void searchTreeDFS(Vertex* startVertex, QVector<Vertex*>& passedVertexes, QVector<Edge>& deletedEdges, const QMap<int, Vertex*>& graph);




/*!
 * \brief Выполняет поиск изолированных вершин в графе
 * \param graph - граф
 * \return список изолированных вершин
 */
QVector<Vertex*> searchIsolatedVertexes(const QMap<int, Vertex*> &graph);



/*!
 * \brief Выполняет поиск вершин с нулевой степенью захода
 * \param graph - граф
 * \return список вершин с нулевой степенью захода
 */
QVector<Vertex*> searchVertexesWithZeroDegreeOfApproach(const QMap <int, Vertex*> &graph);

/*!
 * \brief Преобразовывает граф в дерево, если это возможно, посредством нахождения дуг, которые нужно удалить
 * \brief и возвращает список этих дуг, а так же корень этого дерева
 * \param deletedEdges - заполняемый список дуг, которые нужно удалить, чтобы граф стал деревом
 * \param graph - карта графа, который обходим
 * \return корень найденного дерева или nullptr, если дерево невозможно построить посредством удаления дуг
 */
Vertex* convertGraphToTree(QVector<Edge>& deletedEdges, const QMap<int, Vertex*> &graph);




#endif // COMPUTINGFUNCITONS_H
