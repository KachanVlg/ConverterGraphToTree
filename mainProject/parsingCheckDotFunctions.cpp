#include "parsingCheckDotFunctions.h"
#include <QRegularExpression>
#include <QStringList>



void parsingDotGraph(QStringList & dotGraph, QMap<int, Vertex*> & graph)
{
    static QRegularExpression pattIsolateVertex("^ *(100|[1-9]?[0-9]) *$"); /*!< Регулярное выражение, соответствующее объявлению изолированной вершины */

    int idLastStr = dotGraph.size() - 1; /*!< Индекс последней строки дот графа */
    /// Начиная со второй строки и до предпоследней
    for (int iStr = 1; iStr < idLastStr; iStr++)
    {
        QString curStr(dotGraph.at(iStr)); /*!< текущая строка дот графа */
        /// Если строка соответствует объявлению изолированной вершины
        if(pattIsolateVertex.match(curStr).hasMatch())
        {
            /// Получить названиве вершины
            int iCurVertex = curStr.toInt(); /*!< имя текущей вершины; ее индекс */

            /// Если такая вершина еще не была объявлена
            if(!graph.contains(iCurVertex))
            {
                /// Создать такую вершину, где ее ключ - ее имя (индекс);
                Vertex* newVertex = new Vertex({}, {}, iCurVertex);
                graph.insert(iCurVertex, newVertex);
            }
        }
        else /// Если строка соответствует объявлению связи
        {
            static QRegularExpression tmpPatt("->| "); /*!< регулярное выражение для разбиения строки на слова */
            QStringList edgeVertexes = curStr.split(tmpPatt, Qt::SkipEmptyParts); /*!< список вершин в связи */
            int iCurVertex1 = edgeVertexes[0].toInt(); /*!< левая вершина из связи */
            int iCurVertex2 = edgeVertexes[1].toInt(); /*!< правая вершина из связи */


            /// Если первая вершина в этой свзи еще не была создана в graph - создать ее и обновить информацию о ее входящих/выходящих дугах;
            if(!graph.contains(iCurVertex1))
            {
                Vertex* newVertex = new Vertex({}, {iCurVertex2}, iCurVertex1);
                graph.insert(iCurVertex1, newVertex);
            }
            else /// Иначе если первая вершины была создана в graph - обновить информацию о ее входящих/выходящих дугах;
            {
                graph.value(iCurVertex1)->outputAdjVertexes.append(iCurVertex2);
            }

            /// Если вторая вершина в этой связи еще не была создана в graph - создать ее и обновить информацию о ее входящих/выходящих дугах;
            if(!graph.contains(iCurVertex2))
            {
                Vertex* newVertex = new Vertex({iCurVertex1}, {}, iCurVertex2);
                graph.insert(iCurVertex2, newVertex);
            }
            else /// Иначе если вторая вершины была создана в graph - обновить информацию о ее входящих/выходящих дугах;
            {
                graph.value(iCurVertex2)->approachAdjVertexes.append(iCurVertex1);
            }
        }
    }
}
