#ifndef PARSINGCHECKDOTFUNCTIONS_H
#define PARSINGCHECKDOTFUNCTIONS_H
#include "dataStructeres.h"





/*!
 * \brief Выполняет парсинг графа в виде dot формата в структуру QMap graph
 * \param dotGraph - многострочный текст, граф в dot формате
 * \param graph - структура данных графа, которую необходимо заполнить
 */
void parsingDotGraph(QStringList & dotGraph, QMap<int, Vertex*> & graph);







#endif // PARSINGCHECKDOTFUNCTIONS_H
