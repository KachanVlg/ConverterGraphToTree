#include <dataStructeres.h>
#include <computingFuncitons.h>


void searchTreeDFS(Vertex* startVertex, QVector<Vertex*>& passedVertexes, QVector<Edge>& deletedEdges, const QMap<int, Vertex*>& graph)
{

    /// Добавляем текущую (стартовую вершину) в список пройденных
    passedVertexes.append(startVertex);


    int countAdjVertexes = startVertex->outputAdjVertexes.size(); /*!< Количетсво смежных вершин у текущей проходящей */

    /// Для каждой смежной для текущей вершины:
    for (int iV = 0; iV < countAdjVertexes; iV++)
    {
        Vertex* curAdjVertex = graph.value(startVertex->outputAdjVertexes[iV]); /*!< текущая смежная вершина (проверяемая на то, была ли пройдена) */
        bool isPassed = passedVertexes.contains(curAdjVertex); /*!< флаг, содержится ли смежная вершина под номером iV в списке тех, что были пройдены */

        /// Если вершина не была пройдена - вызвать алгоритм из данной вершины
        if (!isPassed)
        {
            searchTreeDFS(curAdjVertex, passedVertexes, deletedEdges, graph);
        }
        /// Если вершина была пройдена:
        else
        {   ///добавляем дугу (текущая вершина -> текущая смежная вершина) в список удаляемых
            Edge deletedEdge(startVertex, curAdjVertex); /*!< дуга для удаления */
            deletedEdges.append(deletedEdge);
        }
    }
}
