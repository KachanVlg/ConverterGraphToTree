#ifndef PARSINGCHECKDOTFUNCTIONS_H
#define PARSINGCHECKDOTFUNCTIONS_H
#include "dataStructeres.h"






/*!
 * \brief Выполняет парсинг графа в виде dot формата в структуру QMap graph
 * \param dotGraph - многострочный текст, граф в dot формате
 * \param graph - структура данных графа, которую необходимо заполнить
 */
void parsingDotGraph(QStringList & dotGraph, QMap<int, Vertex*> & graph);


/*!
 * \brief Преобразует исходный граф в дерево dot формата, добавляя к связям индикаторы,
 * \brief говорящие о том, что их нужно удалить
 * \param deletedEdges список дуг, которые необходимо удалить
 * \param recipient текст исходного dot графа (он будет изменен)
 */
void convertTreeToDot(const QVector<Edge>& deletedEdges, QStringList & recipient);




/*!
 * \brief Проверяет соответствие объявления и описания графа формату dot
 * \param graph - dot граф в виде текста
 * \param список найденных ошибок
 */
bool checkDotFormat(QStringList &graph, QVector<QString> &errors);



#endif // PARSINGCHECKDOTFUNCTIONS_H
