#include <QtTest>
#include "../mainProject/dataStructeres.h"
#include "../mainProject/parsingCheckDotFunctions.h"

class TestCheckDotFormat : public QObject {
    Q_OBJECT

private slots:
    void testCheckDotFormat_data();
    void testCheckDotFormat();
};

void TestCheckDotFormat::testCheckDotFormat_data() {
    QTest::addColumn<QStringList>("graph");
    QTest::addColumn<QVector<QString>>("expectedErrors");
    QTest::addColumn<bool>("expectedResult");

    QTest::newRow("Typical case")
        << QStringList({"digraph G {", "1 -> 2", "2 -> 3", "3 -> 1", "}"})
        << QVector<QString>()
        << true;

    QTest::newRow("Missing 'digraph'")
        << QStringList({"G {", "1 -> 2", "2 -> 3", "3 -> 1", "}"})
        << QVector<QString>({"Ошибка! Объявление графа не соответствует формату. Ожидается: digraph <имя графа латиницей или пустота> {"})
        << false;

    QTest::newRow("Missing '{'")
        << QStringList({"digraph G", "1 -> 2", "2 -> 3", "3 -> 1", "}"})
        << QVector<QString>({"Ошибка! Объявление графа не соответствует формату. Ожидается: digraph <имя графа латиницей или пустота> {"})
        << false;

    QTest::newRow("Invalid graph name")
        << QStringList({"digraph 1-. {", "1 -> 2", "2 -> 3", "3 -> 1", "}"})
        << QVector<QString>({"Ошибка! Объявление графа не соответствует формату. Ожидается: digraph <имя графа латиницей или пустота> {"})
        << false;

    QTest::newRow("Invalid characters outside declaration")
        << QStringList({"ww digraph G {", "1 -> 2", "2 -> 3", "3 -> 1", "}"})
        << QVector<QString>({"Ошибка! Объявление графа не соответствует формату. Ожидается: digraph <имя графа латиницей или пустота> {"})
        << false;

    QTest::newRow("Invalid characters within declaration")
        << QStringList({"digraph ww G {", "1 -> 2", "2 -> 3", "3 -> 1", "}"})
        << QVector<QString>({"Ошибка! Объявление графа не соответствует формату. Ожидается: digraph <имя графа латиницей или пустота> {"})
        << false;

    QTest::newRow("Invalid characters at end of declaration")
        << QStringList({"digraph G { ww", "1 -> 2", "2 -> 3", "3 -> 1", "}"})
        << QVector<QString>({"Ошибка! Объявление графа не соответствует формату. Ожидается: digraph <имя графа латиницей или пустота> {"})
        << false;

    QTest::newRow("Invalid vertex declaration")
        << QStringList({"digraph G {", "1 -> 2", "2 ww", "3 -> 1", "}"})
        << QVector<QString>({"Ошибка! Строка № 3 не соответствует объявлению связи или изолированной вершины. Ожидается: <имя вершины [0;100]> -> <имя вершины [0;100]> или <имя вершины [0;100]>"})
        << false;

    QTest::newRow("Invalid first vertex in edge")
        << QStringList({"digraph G {", "1 -> 2", "2 -> 3", "m -> 1", "}"})
        << QVector<QString>({"Ошибка! Строка № 4 не соответствует объявлению связи или изолированной вершины. Ожидается: <имя вершины [0;100]> -> <имя вершины [0;100]> или <имя вершины [0;100]>"})
        << false;

    QTest::newRow("Invalid second vertex in edge")
        << QStringList({"digraph G {", "1 -> 2", "2 -> 3", "3 -> 101", "}"})
        << QVector<QString>({"Ошибка! Строка № 4 не соответствует объявлению связи или изолированной вершины. Ожидается: <имя вершины [0;100]> -> <имя вершины [0;100]> или <имя вершины [0;100]>"})
        << false;

    QTest::newRow("Invalid characters in edge declaration")
        << QStringList({"digraph G {", "1 -> 2", "2 -> 3", "b 3 -> bb 1", "}"})
        << QVector<QString>({"Ошибка! Строка № 4 не соответствует объявлению связи или изолированной вершины. Ожидается: <имя вершины [0;100]> -> <имя вершины [0;100]> или <имя вершины [0;100]>"})
        << false;

    QTest::newRow("Missing '->' operator")
        << QStringList({"digraph G {", "1 -> 2", "2  3", "3 -> 1", "}"})
        << QVector<QString>({"Ошибка! Строка № 3 не соответствует объявлению связи или изолированной вершины. Ожидается: <имя вершины [0;100]> -> <имя вершины [0;100]> или <имя вершины [0;100]>"})
        << false;

    QTest::newRow("Empty line in graph body")
        << QStringList({"digraph G {", "1 -> 2", "", "3 -> 1", "}"})
        << QVector<QString>({"Ошибка! Строка № 3 не соответствует объявлению связи или изолированной вершины. Ожидается: <имя вершины [0;100]> -> <имя вершины [0;100]> или <имя вершины [0;100]>"})
        << false;

    QTest::newRow("Empty graph body")
        << QStringList({"digraph G {", "}"})
        << QVector<QString>({"Ошибка! У графа отсутствует тело"})
        << false;

    QTest::newRow("No edges in graph")
        << QStringList({"digraph G {", "2", "3", "}"})
        << QVector<QString>({"Ошибка! Некорректное число дуг. Ожидается количество дуг в промежутке [1;4851]"})
        << false;


    QTest::newRow("Missing end declaration")
        << QStringList({"digraph G {", "1 -> 2", "2 -> 3", "3 -> 1"})
        << QVector<QString>({"Ошибка! Отсутствует окончание объявления графа"})
        << false;
}

void TestCheckDotFormat::testCheckDotFormat() {
    QFETCH(QStringList, graph);
    QFETCH(QVector<QString>, expectedErrors);
    QFETCH(bool, expectedResult);

    QVector<QString> errors;
    bool result = checkDotFormat(graph, errors);

    QCOMPARE(result, expectedResult);
    QCOMPARE(errors, expectedErrors);
}

QTEST_APPLESS_MAIN(TestCheckDotFormat)

#include "test_checkDotFormat.moc"
