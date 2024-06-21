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



void convertTreeToDot(const QVector<Edge>& deletedEdges, QStringList & recipient)
{
    int numEdges = deletedEdges.size(); /*!< количество дуг, которые нужно удалить */
    QString indicateRed(" [color=red]");

    ///Для каждой связи, которую нужно удалить
    for(int iEdge = 0; iEdge < numEdges; iEdge++)
    {
        /// Создаем строку, которая соответствует связи, что нужно удалить;
        int v1 = deletedEdges.at(iEdge).outcomeVertex->id;
        int v2 = deletedEdges.at(iEdge).approachVertex->id;
        QString input = QString("%1 -> %2").arg(v1).arg(v2);/*!< регулярное выражение, соответствующее связи */
        /// Ищем эту строку в исходном графе
        int idCurEdge = recipient.indexOf(input);

        /// Отмечаем через пробел в этой строке необходимость удалить данную связь
        QString indicateEdge = recipient.at(idCurEdge) + indicateRed;
        recipient.replace(idCurEdge, indicateEdge);
    }

}


bool checkDotFormat(QStringList &graph, QVector<QString> &errors)
{
    ///Если текст пустой, записать это в ошибки и вернуть несоответствие формату dot;
    if(graph.isEmpty())
    {
        errors.append("Ошибка соблюдения формата! Файл не содержит описания графа");
        return false;
    }

    QRegularExpression pattDeclar("^digraph *([a-zA-Z]*) *{$"); /*!< регулярное выражение, соответствующее объявлению графа */

    ///Если нулевая строка не соответствует объявлению графа, записать это в список ошибок
    bool declarOk = pattDeclar.match(graph.at(0)).hasMatch();
    if(!declarOk)
    {
        errors.append("Ошибка! Объявление графа не соответствует формату. Ожидается: digraph <имя графа латиницей или пустота> {");
    }

    /// Если в тексте всего одна строка, записать ошибку о том, что у графа отсутствует тело и конец объявления и вернуть несоответствие формату dot;
    if(graph.size() == 1)
    {
        errors.append("Ошибка! У графа отсутствует тело");
        errors.append("Ошибка! Отсутствует окончание объявления графа");
        return false;
    }

    QRegularExpression pattEndDeclar("^ *} *$"); /*!< регулярное выражение, соответствующее окончанию объявления графа */
    QRegularExpression pattIsolateVertex("^ *(100|[1-9]?[0-9]) *$"); /*!< регулярное выражение, соответствующее объявлению изолированной вершины */
    QRegularExpression pattEdge("^ *(100|[1-9]?[0-9]) *-> *(100|[1-9]?[0-9]) *$"); /*!< регулярное выражение, соответствующее объявлению связи */

    ///Если в тексте две строки
    if(graph.size() == 2)
    {
        ///Если последняя соответствует концу объявления, записать ошибку о том, что у графа отсутствует тело и вернуть несоответствие формату dot;
        if(pattEndDeclar.match(graph.last()).hasMatch())
        {
            errors.append("Ошибка! У графа отсутствует тело");
            return false;
        }

        ///Если вторая сторка соответствует объявлению вершины, записать ошибку о том, что невалидное число дуг И отсутствует конец объявления И вернуть несоответствие формату dot;
        if(pattEndDeclar.match(graph.at(1)).hasMatch())
        {
            errors.append("Ошибка! Отсутствует окончание объявления графа");
            errors.append("Ошибка! Некорректное число дуг. Ожидается количество дуг в промежутке [1;4851]");
            return false;
        }

        ///Если вторая строка соответствует объявлению связи, записать ошибку о том, что отсутствует конец объявления графа И вернуть несоответствие формату dot;
        if(pattEdge.match(graph.at(1)).hasMatch())
        {
            errors.append("Ошибка! Отсутствует окончание объявления графа");
            return false;
        }
    }

    ///Если остутствует конец объявления графа в последней строке текста, записать ошибку об этом;
    if(!pattEndDeclar.match(graph.last()).hasMatch())
    {
        errors.append("Ошибка! Отсутствует окончание объявления графа");
    }

    int countEdge = 0; /*!< счетчик связей */
    QVector<int> declaredV; /*!< массив с индексами вершин для их подсчета */

    ///Пока не последняя строка текста начиная со второй строки текста
    for(int iStr = 1; iStr < graph.size() -1; iStr++)
    {
        QString curStr = graph.at(iStr);

        ///Если строка соответствует объявлению связи
        if(pattEdge.match(curStr).hasMatch())
        {
            ++countEdge;
            static QRegularExpression tmpPatt("->| "); /*!< регулярное выражение для разбиения строки на слова */
            QStringList edgeVertexes = curStr.split(tmpPatt, Qt::SkipEmptyParts); /*!< список вершин в связи */
            int iCurVertex1 = edgeVertexes[0].toInt(); /*!< левая вершина из связи */
            int iCurVertex2 = edgeVertexes[1].toInt(); /*!< правая вершина из связи */
            ///если левая вершина не была объявлена - запоминаем ее
            if(!declaredV.contains(iCurVertex1))
            {
                declaredV.append(iCurVertex1);
            }
            ///если правая вершина не была объявлена - запоминаем ее
            if(!declaredV.contains(iCurVertex2))
            {
                declaredV.append(iCurVertex2);
            }
        }
        /// Иначе если строка соответствует объявлению изолированной вершины
        else if(pattIsolateVertex.match(curStr).hasMatch())
        {
            /// Запомнить ее
            int curV = curStr.toInt();
            if(!declaredV.contains(curV))
            {
                declaredV.append(curV);
            }
        }
        ///Иначе Если строка не соответствует ни объявлению связи, ни объявлению вершины
        else
        {
            ///Записать ошибку об этом, а в ней указать индекс строки, в которой допущена данная ошибка;
            QString wrong = "Ошибка! Строка № " + QString::number(iStr+1);
            wrong = wrong + " не соответствует объявлению связи или изолированной вершины. Ожидается: <имя вершины [0;100]> -> <имя вершины [0;100]> или <имя вершины [0;100]>";
            errors.append(wrong);
        }
    }

    ///Если количество вершин не входит в диапазон допустимых, записать ошибку об этом;
    if(countEdge < 1 || countEdge > 4851)
    {
        errors.append("Ошибка! Некорректное число дуг. Ожидается количество дуг в промежутке [1;4851]");
    }
    ///Если количество дуг не входит в диапазон допустимых, записать ошибку об этом;
    if(declaredV.size() > 99 && declaredV.size() < 1)
    {
        errors.append("Ошибка! Некорректное число вершин. Ожидается количество вершин в промежутке [1;99]");
    }


    ///Если количество ошибок = 0, вернуть true Иначе false;

    if(errors.size() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
