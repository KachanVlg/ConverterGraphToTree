#include "computingFuncitons.h"


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



QVector<Vertex*> searchIsolatedVertexes(const QMap<int, Vertex*> &graph)
{
    QMap<int, Vertex*>::const_iterator iV; /*!< итератор для обхода graph */
    QVector<Vertex*> isolatedVertexes; /*!< пустой список изолированных вершин */

    ///Для каждой вершины графа
    for(iV = graph.constBegin(); iV !=graph.constEnd(); iV++)
    {
        int numApproachAdjVertexes = iV.value()->approachAdjVertexes.size(); /*!< количество смежных родительских вершин текущей вершины */
        int numOutputAdjVertexes = iV.value()->outputAdjVertexes.size(); /*!< количество смежных дочерних вершин текущей вершины */
        /// Если текущая вершина не имеет смежных родительских и дочерних вершин
        if(numOutputAdjVertexes == 0 && numApproachAdjVertexes == 0)
        {
            /// Добавить текущую вершину в список изолированных вершин
            isolatedVertexes.append(iV.value());
        }
    }
    /// Вернуть список изолированных вершин
    return isolatedVertexes;
}



QVector<Vertex*> searchVertexesWithZeroDegreeOfApproach(const QMap <int, Vertex*> &graph)
{
    QMap<int, Vertex*>::const_iterator iV; /*!< итератор для обхода graph */
    QVector<Vertex*> zeroDegreeOfApproachVertexes; /*!< пустой список вершин с нулевой степенью захода */
    /// Для каждой вершины графа
    for(iV = graph.constBegin(); iV !=graph.constEnd(); iV++)
    {
        int degreeOfApproach = iV.value()->approachAdjVertexes.size(); /*!< степень захода вершины */
        /// Если степень захода текущей вершины нулевая
        if(degreeOfApproach == 0)
        {
            /// Добавить текущую вершину в список вершин с нулевой степенью захода
            zeroDegreeOfApproachVertexes.append(iV.value());
        }
    }
    /// Вернуть список вершин с нулевой степенью захода
    return zeroDegreeOfApproachVertexes;

}
