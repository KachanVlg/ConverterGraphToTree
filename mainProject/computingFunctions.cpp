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


Vertex* convertGraphToTree(QVector<Edge>& deletedEdges, const QMap<int, Vertex*> &graph)
{
    /// Найти все изолированные вершины графа
    QVector<Vertex*> isolatedVertexes = searchIsolatedVertexes(graph);/*!< список изолированных вершин графа */

    /// Если была найдена хотя-бы одна изолированная вершина, вернуть, что данный граф нельзя преобразовать в дерево.
    if(isolatedVertexes.size() > 0)
    {
        return nullptr;
    }


    QVector<Vertex*> zeroDegreeOfApproachVertexes = searchVertexesWithZeroDegreeOfApproach(graph);/*!< список вершин с нулевой степенью захода */

    int numZeroDegreeOfApproachVertexes = zeroDegreeOfApproachVertexes.size(); /*!< количество вершин с нулевой степенью захода в графе */


    QVector <Vertex*> passedVertexes;/*!< пустой список пройденных вершин */
    int numVertexes = graph.size();/*!< количество вершин в графе */
    bool rootFound = false; /*!< флаг - корень найден */
    Vertex* root = nullptr; /*!< указатель на корень дерева (пока пустой) */

    ///Если была найдена 1 вершина с нулевой степенью захода
    if(numZeroDegreeOfApproachVertexes == 1)
    {
        /// Выполняем обход в глубину, начиная с этой вершины;
        Vertex* startVertex = zeroDegreeOfApproachVertexes.takeFirst();
        searchTreeDFS(startVertex, passedVertexes, deletedEdges, graph);
        /// Если во время обхода были пройдены все вершины, считать корнем дерева вершину, с которой начинали обход;
        if(numVertexes == passedVertexes.size())
        {
            root = startVertex;
        }
    }
    /// Иначе Если было найдено более 1 вершины с нулевой степенью захода, вернуть, что данный граф нельзя преобразовать в дерево;
    else if(numZeroDegreeOfApproachVertexes > 1) return nullptr;

    ///Иначе Если не было найдено ни одной вершины с нулевой степенью захода
    else if(numZeroDegreeOfApproachVertexes == 0)
    {
        QMap<int, Vertex*>::const_iterator iV;

        /// Для каждой вершины графа И пока корень не найден
        for(iV = graph.constBegin(); iV !=graph.constEnd() && !rootFound; iV++)
        {
            /// Выполняем обход в глубину, начиная с текущей вершины;
            searchTreeDFS(iV.value(), passedVertexes, deletedEdges, graph);

            /// Если во время обхода были пройдены все вершины
            if(numVertexes == passedVertexes.size())
            {
                /// Считать, что корень дерева найден;
                rootFound = true;
                /// Считать корнем дерева вершину, с которой начинали текущий обход в глубину
                root = iV.value();
            }
            /// Иначе очистить список дуг, которые нужно удалить
            else
            {
                deletedEdges.clear();
            }
        }
    }
    ///Вернуть корень дерева
    return root;
}

