#include <QCoreApplication>
#include "computingFuncitons.h"
#include "dataStructeres.h"
#include "inputOutputFunctions.h"
#include "parsingCheckDotFunctions.h"
#include <QMessageBox>





int main(int argc, char *argv[])
{
    ///Получить пути вывода и ввода данных
    QString inputFilePath = QString(argv[1]);
    QString outputFilePath = QString(argv[2]);

    if(inputFilePath.isEmpty() && outputFilePath.isEmpty())
    {
        return 0;
    }

    QStringList dotGraph;

    ///Считать входной граф;
    bool inputOK = getTextFromFile(inputFilePath, dotGraph);

    ///Если считать граф не удалось, вывести ошибку об этом и завершить работу программы
    if(!inputOK)
    {
        QMessageBox inputError;
        inputError.setText("Ошибка чтения файла");
        inputError.exec();
        return 0;
    }

    QVector<QString> errors;

    ///Произвести проверку на корректность dot формата в исходном файле
    bool checkDotOK = checkDotFormat(dotGraph, errors);

    ///Если были найдены ошибки формата
    if(!checkDotOK)
    {
        QStringList wrongs = QStringList::fromVector(errors);
        bool outputOK = outputResultToFile(wrongs, outputFilePath);

        if(!outputOK)
        {
            QMessageBox outputError;
            outputError.setText("Ошибка записи в файла");
            outputError.exec();
            return 0;
        }
        return 0;
    }

    QMap<int, Vertex*> graph;

    ///Преобразуем dot граф в структуру данных
    parsingDotGraph(dotGraph, graph);

    ///Преобразуем граф в дерево
    Vertex* root;
    QVector<Edge> deletedEdges;
    root = convertGraphToTree(deletedEdges, graph);

    ///Если корень не найден, дерево построить нельзя
    if(root == nullptr)
    {
        QMessageBox inputError;
        inputError.setText("Граф невозможно преобразовать в дерево");
        inputError.exec();
        return 0;
    }

    ///Преобразуем граф в дерево в dot'e
    convertTreeToDot(deletedEdges, dotGraph);

    ///Выводим граф в файл:
    bool outputOK = outputResultToFile(dotGraph, outputFilePath);

    if(!outputOK)
    {
        QMessageBox inputError;
        inputError.setText("Ошибка записи в файл");
        inputError.exec();
        return 0;
    }




    //QCoreApplication a(argc, argv);

    return 0;//a.exec();
}
