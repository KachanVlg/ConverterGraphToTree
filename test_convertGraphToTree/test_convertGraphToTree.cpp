#include <QtTest/QtTest>
#include "../mainProject/computingFuncitons.h"
#include "../mainProject/dataStructeres.h"


// Определение функции createGraph
QMap<int, Vertex*> createGraph(const QVector<Vertex*>& vertices) {
    QMap<int, Vertex*> graph;
    for (Vertex* v : vertices) {
        graph[v->id] = v;
    }
    return graph;
}

class TestConvertGraphToTree : public QObject {
    Q_OBJECT

private slots:
    void testConvert();
    void testConvert_data();

private:
    void compareGraphs(const QMap<int, Vertex*>& actual, const QMap<int, Vertex*>& expected);
    void cleanupGraph(QMap<int, Vertex*>& graph);
};
typedef QMap<int, Vertex*> GraphMap;
void TestConvertGraphToTree::testConvert_data() {
    QTest::addColumn<QMap<int, Vertex*>>("graph");
    QTest::addColumn<int>("expectedRootId");
    QTest::addColumn<QVector<Edge>>("expectedDeletedEdges");

    /// 1. Типовой тест
    {
        Vertex* v1 = new Vertex({}, {2}, 1);
        Vertex* v2 = new Vertex({1}, {3}, 2);
        Vertex* v3 = new Vertex({2}, {1}, 3);
        QVector<Vertex*> vertices1 = {v1, v2, v3};
        QMap<int, Vertex*> graph1 = createGraph(vertices1);
        QVector<Edge> deletedEdges1 = { Edge(v3, v1) };

        QTest::newRow("1. Model test") << graph1 << 1 << deletedEdges1;
    }

    /// 2. Одна вершина
    {
        Vertex* v1 = new Vertex({1}, {1}, 1);
        QVector<Vertex*> vertices2 = {v1};
        QMap<int, Vertex*> graph2 = createGraph(vertices2);
        QVector<Edge> deletedEdges2 = {Edge(v1, v1)};

        QTest::newRow("2. One top") << graph2 << 1 << deletedEdges2;
    }

    /// 3. Несколько изолированных вершин до потенциальных корней
    {
        Vertex* v4 = new Vertex({}, {}, 4);
        Vertex* v5 = new Vertex({}, {}, 5);
        Vertex* v1 = new Vertex({}, {2}, 1);
        Vertex* v2 = new Vertex({1}, {3}, 2);
        Vertex* v3 = new Vertex({2}, {1}, 3);
        QVector<Vertex*> vertices3 = {v4, v5, v1, v2, v3};
        QMap<int, Vertex*> graph3 = createGraph(vertices3);
        QVector<Edge> deletedEdges3 = {};

        QTest::newRow("3. Several isolated vertices to potential roots") << graph3 << -1 << deletedEdges3;
    }

    /// 4. Несколько изолированных вершин после потенциальных корней
    {
        Vertex* v1 = new Vertex({}, {2}, 1);
        Vertex* v2 = new Vertex({1}, {3}, 2);
        Vertex* v3 = new Vertex({2}, {1}, 3);
        Vertex* v4 = new Vertex({}, {}, 4);
        Vertex* v5 = new Vertex({}, {}, 5);
        QVector<Vertex*> vertices4 = {v1, v2, v3, v4, v5};
        QMap<int, Vertex*> graph4 = createGraph(vertices4);
        QVector<Edge> deletedEdges4 = {};

        QTest::newRow("4. Several isolated vertices after potential roots") << graph4 << -1 << deletedEdges4;
    }

    /// 5. Несколько вершин с несколькими кратными дугами
    {
        Vertex* v1 = new Vertex({3}, {2, 2, 2}, 1);
        Vertex* v2 = new Vertex({1, 1, 1}, {3, 3,3}, 2);
        Vertex* v3 = new Vertex({2, 2,2}, {1}, 3);
        QVector<Vertex*> vertices5 = {v1, v2, v3};
        QMap<int, Vertex*> graph5 = createGraph(vertices5);
        QVector<Edge> deletedEdges5 = {Edge(v3, v1), Edge(v2, v3), Edge(v2, v3), Edge(v1, v2), Edge(v1, v2)};

        QTest::newRow("5. Multiple vertices with multiple multiple arcs") << graph5 << 1 << deletedEdges5;
    }

    /// 6. Несколько вершин с петлями
    {
        Vertex* v1 = new Vertex({3,1,1}, {2,1,1}, 1);
        Vertex* v2 = new Vertex({1,2,2}, {3,2,2}, 2);
        Vertex* v3 = new Vertex({2}, {1}, 3);
        QVector<Vertex*> vertices6 = {v1, v2, v3};
        QMap<int, Vertex*> graph6 = createGraph(vertices6);
        QVector<Edge> deletedEdges6 = { Edge(v3, v1), Edge(v2, v2), Edge(v2, v2), Edge(v1, v1), Edge(v1, v1)};

        QTest::newRow("6. Several vertices with loops") << graph6 << 1 << deletedEdges6;
    }

    /// 7. Несколько компонент связности
    {
        Vertex* v4 = new Vertex({}, {1, 3}, 4);
        Vertex* v5 = new Vertex({}, {1, 3}, 5);
        Vertex* v1 = new Vertex({4, 5}, {2}, 1);
        Vertex* v2 = new Vertex({1}, {3}, 2);
        Vertex* v3 = new Vertex({2}, {1}, 3);
        QVector<Vertex*> vertices7 = {v4, v5, v1, v2, v3};
        QMap<int, Vertex*> graph7 = createGraph(vertices7);
        QVector<Edge> deletedEdges7 = {};

        QTest::newRow("7. Multiple connected components") << graph7 << -1 << deletedEdges7;
    }

    /// 8. Уже является деревом, но первая объявленная вершина не является корнем
    {
        Vertex* v1 = new Vertex({4}, {2}, 1);
        Vertex* v2 = new Vertex({1}, {3}, 2);
        Vertex* v3 = new Vertex({2}, {}, 3);
        Vertex* v4 = new Vertex({}, {1}, 4);
        QVector<Vertex*> vertices8 = {v1, v2, v3, v4};
        QMap<int, Vertex*> graph8 = createGraph(vertices8);
        QVector<Edge> deletedEdges8 = {};

        QTest::newRow("8. Already a tree, but the first declared vertex is not the root") << graph8 << 4 << deletedEdges8;
    }

    /// 9. Два потенциальных корня соеденены кратными дугами
    {
        Vertex* v1 = new Vertex({4,4}, {2, 4}, 1);
        Vertex* v2 = new Vertex({1,4,4}, {3}, 2);
        Vertex* v3 = new Vertex({2}, {}, 3);
        Vertex* v4 = new Vertex({1}, {1,1}, 4);
        QVector<Vertex*> vertices9 = {v1, v2, v3, v4};
        QMap<int, Vertex*> graph9 = createGraph(vertices9);
        QVector<Edge> deletedEdges9 = { Edge(v4, v1), Edge(v4, v1) };

        QTest::newRow("9. Two potential roots are connected by multiple arcs") << graph9 << 1 << deletedEdges9;
    }

    /// 10. Корень участвует в двух циклах
    {
        Vertex* v6 = new Vertex({5}, {7}, 6);
        Vertex* v7 = new Vertex({6}, {1}, 7);
        Vertex* v1 = new Vertex({7, 4}, {5, 2}, 1);
        Vertex* v5 = new Vertex({1}, {6}, 5);
        Vertex* v2 = new Vertex({1}, {3}, 2);
        Vertex* v4 = new Vertex({3}, {1}, 4);
        Vertex* v3 = new Vertex({2}, {4}, 3);
        QVector<Vertex*> vertices10 = {v6, v7, v1, v5, v2, v4, v3};
        QMap<int, Vertex*> graph10 = createGraph(vertices10);
        QVector<Edge> deletedEdges10 = { Edge(v7, v1), Edge(v4, v1) };

        QTest::newRow("10. The root participates in two cycles") << graph10 << 1 << deletedEdges10;
    }
}

void TestConvertGraphToTree::testConvert() {
    QFETCH(GraphMap, graph);
    QFETCH(int, expectedRootId);
    QFETCH(QVector<Edge>, expectedDeletedEdges);

    QVector<Edge> actualDeletedEdges;
    Vertex* actualRoot = convertGraphToTree(actualDeletedEdges, graph);

    if (expectedRootId == -1) {
        QCOMPARE(actualRoot, nullptr);
    } else {
        QVERIFY(actualRoot != nullptr);
        QCOMPARE(actualRoot->id, expectedRootId);
    }

    QCOMPARE(actualDeletedEdges.size(), expectedDeletedEdges.size());
    for (int i = 0; i < actualDeletedEdges.size(); ++i) {
        QCOMPARE(actualDeletedEdges[i].outcomeVertex->id, expectedDeletedEdges[i].outcomeVertex->id);
        QCOMPARE(actualDeletedEdges[i].approachVertex->id, expectedDeletedEdges[i].approachVertex->id);
    }

    cleanupGraph(graph);
}

void TestConvertGraphToTree::cleanupGraph(QMap<int, Vertex*>& graph) {
    qDeleteAll(graph);
    graph.clear();
}

QTEST_MAIN(TestConvertGraphToTree)
#include "test_convertGraphToTree.moc"
