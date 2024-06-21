#include <QtTest/QtTest>
#include "../mainProject/parsingCheckDotFunctions.h"
#include "../mainProject/dataStructeres.h"


// Вспомогательная функция для инициализации графа
QMap<int, Vertex*> createGraph(QVector<Vertex*>& vertices);

class TestParsingDotGraph : public QObject {
    Q_OBJECT

private slots:
    void testParsing();
    void testParsing_data();

private:
    QMap<int, Vertex*> createGraph(QVector<Vertex*>& vertices) {
        QMap<int, Vertex*> graph;
        for (Vertex* v : vertices) {
            graph[v->id] = v;
        }
        return graph;
    }
};

typedef QMap<int, Vertex*> GraphMap;
void TestParsingDotGraph::testParsing_data() {
    QTest::addColumn<QStringList>("dotGraph");
    QTest::addColumn<QMap<int, Vertex*>>("expectedGraph");

    /// 1. Типовой тест
    {
        Vertex* v1 = new Vertex({3}, {2}, 1);
        Vertex* v2 = new Vertex({1}, {3}, 2);
        Vertex* v3 = new Vertex({2}, {1}, 3);
        QVector<Vertex*> vertices1 = {v1, v2, v3};
        QMap<int, Vertex*> graph1 = createGraph(vertices1);

        QTest::newRow("1. Model test") << QStringList{"digraph G {", "1 -> 2", "2 -> 3", "3 -> 1", "}"} << graph1;
    }

    /// 2. Несколько пар вершин с несколькими кратными дугами
    {
        Vertex* v1 = new Vertex({3}, {2, 2}, 1);
        Vertex* v2 = new Vertex({1, 1}, {3, 3}, 2);
        Vertex* v3 = new Vertex({2, 2}, {1}, 3);
        QVector<Vertex*> vertices2 = {v1, v2, v3};
        QMap<int, Vertex*> graph2 = createGraph(vertices2);

        QTest::newRow("2. Several pairs of vertices with several multiple arcs") << QStringList{"digraph G {", "1 -> 2", "2 -> 3", "3 -> 1", "1 -> 2", "2 -> 3", "}"} << graph2;
    }

    /// 3. Несколько вершин с несколькими петлями
    {
        Vertex* v1 = new Vertex({3, 1}, {2, 1}, 1);
        Vertex* v2 = new Vertex({1, 2}, {3, 2}, 2);
        Vertex* v3 = new Vertex({2}, {1}, 3);
        QVector<Vertex*> vertices3 = {v1, v2, v3};
        QMap<int, Vertex*> graph3 = createGraph(vertices3);

        QTest::newRow("3. Multiple vertices with multiple loops") << QStringList{"digraph G {", "1 -> 2", "2 -> 3", "3 -> 1", "1 -> 1", "2 -> 2", "}"} << graph3;
    }

    /// 4. Объявление вершины как изолированной, а после как вершины в связи
    {
        Vertex* v1 = new Vertex({3}, {2}, 1);
        Vertex* v2 = new Vertex({1}, {3}, 2);
        Vertex* v3 = new Vertex({2}, {1}, 3);
        QVector<Vertex*> vertices4 = {v1, v2, v3};
        QMap<int, Vertex*> graph4 = createGraph(vertices4);

        QTest::newRow("4. Declaring a vertex as isolated, and then as a connected vertex") << QStringList{"digraph G {", "1", "1 -> 2", "2 -> 3", "3 -> 1", "}"} << graph4;
    }

    /// 5. Объявление вершины как в свзи, а после как изолированной
    {
        Vertex* v1 = new Vertex({3}, {2}, 1);
        Vertex* v2 = new Vertex({1}, {3}, 2);
        Vertex* v3 = new Vertex({2}, {1}, 3);
        QVector<Vertex*> vertices5 = {v1, v2, v3};
        QMap<int, Vertex*> graph5 = createGraph(vertices5);

        QTest::newRow("5. Declaring a vertex as connected, and then as isolated") << QStringList{"digraph G {", "1 -> 2", "2 -> 3", "3 -> 1", "1", "}"} << graph5;
    }

    /// 6. Несколько вершин объявлены сначала как в связи, а после как изолированные
    {
        Vertex* v1 = new Vertex({3}, {2}, 1);
        Vertex* v2 = new Vertex({1}, {3}, 2);
        Vertex* v3 = new Vertex({2}, {1}, 3);
        QVector<Vertex*> vertices6 = {v1, v2, v3};
        QMap<int, Vertex*> graph6 = createGraph(vertices6);

        QTest::newRow("6. Several vertices are declared first as connected, and then as isolated ") << QStringList{"digraph G {", "1 -> 2", "2 -> 3", "3 -> 1", "1", "2", "}"} << graph6;
    }

    /// 7. Несколько вершин объявлены сначала как изолированные, а после как в связи
    {
        Vertex* v1 = new Vertex({3}, {2}, 1);
        Vertex* v2 = new Vertex({1}, {3}, 2);
        Vertex* v3 = new Vertex({2}, {1}, 3);
        QVector<Vertex*> vertices7 = {v1, v2, v3};
        QMap<int, Vertex*> graph7 = createGraph(vertices7);

        QTest::newRow("7. Several vertices are declared first as isolated, and then as connected") << QStringList{"digraph G {", "1", "2", "1 -> 2", "2 -> 3", "3 -> 1", "}"} << graph7;
    }

    /// 8. Несколько вершин объявлены сначала в связи, потом как изолированные, а после еще раз как связи
    {
        Vertex* v1 = new Vertex({3}, {2, 2}, 1);
        Vertex* v2 = new Vertex({1, 1}, {3, 3}, 2);
        Vertex* v3 = new Vertex({2, 2}, {1}, 3);
        QVector<Vertex*> vertices8 = {v1, v2, v3};
        QMap<int, Vertex*> graph8 = createGraph(vertices8);

        QTest::newRow("8. Several vertices are declared first as connections, then as isolated, and then again as connections") << QStringList{"digraph G {", "1 -> 2", "2 -> 3", "3 -> 1", "1", "2", "1 -> 2", "2 -> 3", "}"} << graph8;
    }
}

void TestParsingDotGraph::testParsing() {
    QFETCH(QStringList, dotGraph);
    QFETCH(GraphMap, expectedGraph);

    QMap<int, Vertex*> actualGraph;
    parsingDotGraph(dotGraph, actualGraph);

    QCOMPARE(actualGraph.size(), expectedGraph.size());

    for (auto key : expectedGraph.keys()) {
        Vertex* actualVertex = actualGraph.value(key);
        Vertex* expectedVertex = expectedGraph.value(key);

        QCOMPARE(actualVertex->id, expectedVertex->id);
        QCOMPARE(actualVertex->approachAdjVertexes, expectedVertex->approachAdjVertexes);
        QCOMPARE(actualVertex->outputAdjVertexes, expectedVertex->outputAdjVertexes);
    }

    // Удаляем созданные вершины, чтобы избежать утечек памяти
    qDeleteAll(actualGraph);
    qDeleteAll(expectedGraph);
}

QTEST_MAIN(TestParsingDotGraph)


#include "test_parsingDotGraph.moc"
