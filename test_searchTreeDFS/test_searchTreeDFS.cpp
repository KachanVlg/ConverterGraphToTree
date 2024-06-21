#include <QtTest/QtTest>
#include "../mainProject/computingFuncitons.h"
#include "../mainProject/dataStructeres.h"

// Вспомогательная функция для инициализации графа
QMap<int, Vertex*> createGraph(QVector<Vertex*>& vertices) {
    QMap<int, Vertex*> graph;
    for (Vertex* v : vertices) {
        graph[v->id] = v;
    }
    return graph;
}

// Тестовый класс для функции searchTreeDFS
class TestSearchTreeDFS : public QObject
{
    Q_OBJECT

private slots:
    void testSearchTreeDFS_data();
    void testSearchTreeDFS();
};

void TestSearchTreeDFS::testSearchTreeDFS_data()
{
    QTest::addColumn<QVector<Vertex*>>("vertices");
    QTest::addColumn<QVector<Edge>>("expectedDeletedEdges");

    // Тестовый случай 1
    {
        Vertex* v1 = new Vertex({}, {2, 4}, 1);
        Vertex* v2 = new Vertex({1}, {3}, 2);
        Vertex* v3 = new Vertex({2}, {4}, 3);
        Vertex* v4 = new Vertex({1, 3}, {}, 4);

        QVector<Vertex*> vertices = {v1, v2, v3, v4};
        QVector<Edge> expectedDeletedEdges;
        expectedDeletedEdges.append(Edge(v1, v4));

        QTest::newRow("test case 1") << vertices << expectedDeletedEdges;
    }

    // Тестовый случай 2
    {
        Vertex* v1 = new Vertex({}, {}, 1);

        QVector<Vertex*> vertices = {v1};
        QVector<Edge> expectedDeletedEdges;

        QTest::newRow("test case 2") << vertices << expectedDeletedEdges;
    }

    // Тестовый случай 3
    {
        Vertex* v1 = new Vertex({}, {}, 1);
        Vertex* v2 = new Vertex({}, {}, 2);
        Vertex* v3 = new Vertex({}, {}, 3);
        Vertex* v4 = new Vertex({}, {}, 4);

        QVector<Vertex*> vertices = {v1, v2, v3, v4};
        QVector<Edge> expectedDeletedEdges;

        QTest::newRow("test case 3") << vertices << expectedDeletedEdges;
    }

    // Тестовый случай 4
    {
        Vertex* v1 = new Vertex({1}, {2, 4, 1}, 1);
        Vertex* v2 = new Vertex({1}, {3}, 2);
        Vertex* v3 = new Vertex({2}, {4}, 3);
        Vertex* v4 = new Vertex({1, 3}, {}, 4);

        QVector<Vertex*> vertices = {v1, v2, v3, v4};
        QVector<Edge> expectedDeletedEdges;
        expectedDeletedEdges.append(Edge(v1, v4));
        expectedDeletedEdges.append(Edge(v1, v1));

        QTest::newRow("test case 4") << vertices << expectedDeletedEdges;
    }

    // Тестовый случай 5
    {
        Vertex* v1 = new Vertex({1}, {2, 4, 1}, 1);
        Vertex* v2 = new Vertex({1,2}, {3, 2}, 2);
        Vertex* v3 = new Vertex({2,3}, {4, 3}, 3);
        Vertex* v4 = new Vertex({1, 3}, {}, 4);

        QVector<Vertex*> vertices = {v1, v2, v3, v4};
        QVector<Edge> expectedDeletedEdges;
        expectedDeletedEdges.append(Edge(v3, v3));
        expectedDeletedEdges.append(Edge(v2, v2));
        expectedDeletedEdges.append(Edge(v1, v4));
        expectedDeletedEdges.append(Edge(v1, v1));

        QTest::newRow("test case 5") << vertices << expectedDeletedEdges;
    }

    // Тестовый случай 6
    {
        Vertex* v1 = new Vertex({1,1}, {2, 4, 1, 1}, 1);
        Vertex* v2 = new Vertex({1,2,2}, {3, 2, 2}, 2);
        Vertex* v3 = new Vertex({2,3,3}, {4, 3, 3}, 3);
        Vertex* v4 = new Vertex({1, 3}, {}, 4);

        QVector<Vertex*> vertices = {v1, v2, v3, v4};
        QVector<Edge> expectedDeletedEdges;
        expectedDeletedEdges.append(Edge(v3, v3));
        expectedDeletedEdges.append(Edge(v3, v3));
        expectedDeletedEdges.append(Edge(v2, v2));
        expectedDeletedEdges.append(Edge(v2, v2));
        expectedDeletedEdges.append(Edge(v1, v4));
        expectedDeletedEdges.append(Edge(v1, v1));
        expectedDeletedEdges.append(Edge(v1, v1));

        QTest::newRow("test case 6") << vertices << expectedDeletedEdges;
    }

    // Тестовый случай 7
    {
        Vertex* v1 = new Vertex({}, {2, 4, 4}, 1);
        Vertex* v2 = new Vertex({1}, {3}, 2);
        Vertex* v3 = new Vertex({2}, {4, 4}, 3);
        Vertex* v4 = new Vertex({1, 3,3,1}, {}, 4);

        QVector<Vertex*> vertices = {v1, v2, v3, v4};
        QVector<Edge> expectedDeletedEdges;
        expectedDeletedEdges.append(Edge(v3, v4));
        expectedDeletedEdges.append(Edge(v1, v4));
        expectedDeletedEdges.append(Edge(v1, v4));

        QTest::newRow("test case 7") << vertices << expectedDeletedEdges;
    }

    // Тестовый случай 8
    {
        Vertex* v1 = new Vertex({}, {2, 4, 4, 4}, 1);
        Vertex* v2 = new Vertex({1}, {3}, 2);
        Vertex* v3 = new Vertex({2}, {4, 4, 4}, 3);
        Vertex* v4 = new Vertex({ 1,3,3,1,1,3}, {}, 4);

        QVector<Vertex*> vertices = {v1, v2, v3, v4};
        QVector<Edge> expectedDeletedEdges;
        expectedDeletedEdges.append(Edge(v3, v4));
        expectedDeletedEdges.append(Edge(v3, v4));
        expectedDeletedEdges.append(Edge(v1, v4));
        expectedDeletedEdges.append(Edge(v1, v4));
        expectedDeletedEdges.append(Edge(v1, v4));

        QTest::newRow("test case 8") << vertices << expectedDeletedEdges;
    }

    // Тестовый случай 9
    {
        Vertex* v1 = new Vertex({}, {2, 4}, 1);
        Vertex* v2 = new Vertex({}, {}, 2);
        Vertex* v3 = new Vertex({}, {}, 3);
        Vertex* v4 = new Vertex({}, {}, 4);
        Vertex* v5 = new Vertex({}, {}, 5);
        Vertex* v6 = new Vertex({}, {}, 6);

        QVector<Vertex*> vertices = {v1, v2, v3, v4, v5, v6};
        QVector<Edge> expectedDeletedEdges;

        QTest::newRow("test case 9") << vertices << expectedDeletedEdges;
    }

    // Тестовый случай 10
    {
        Vertex* v1 = new Vertex({}, {2, 4}, 1);
        Vertex* v2 = new Vertex({5,1}, {3}, 2);
        Vertex* v3 = new Vertex({2}, {4}, 3);
        Vertex* v4 = new Vertex({5,1, 3}, {}, 4);
        Vertex* v5 = new Vertex({}, {2, 4}, 5);

        QVector<Vertex*> vertices = {v5, v2, v4, v1, v3};
        QVector<Edge> expectedDeletedEdges;
        expectedDeletedEdges.append(Edge(v5, v4));

        QTest::newRow("test case 10") << vertices << expectedDeletedEdges;
    }

    // Тестовый случай 11
    {
        Vertex* v1 = new Vertex({3,5}, {2, 4}, 1);
        Vertex* v2 = new Vertex({1}, {3}, 2);
        Vertex* v3 = new Vertex({2}, {1}, 3);
        Vertex* v4 = new Vertex({1}, {5}, 4);
        Vertex* v5 = new Vertex({4}, {1}, 5);

        QVector<Vertex*> vertices = {v1, v2, v3, v4, v5};
        QVector<Edge> expectedDeletedEdges;
        expectedDeletedEdges.append(Edge(v3, v1));
        expectedDeletedEdges.append(Edge(v5, v1));

        QTest::newRow("test case 11") << vertices << expectedDeletedEdges;
    }
}

void TestSearchTreeDFS::testSearchTreeDFS()
{
    QFETCH(QVector<Vertex*>, vertices);
    QFETCH(QVector<Edge>, expectedDeletedEdges);

    QMap<int, Vertex*> graph = createGraph(vertices);

    QVector<Vertex*> passedVertexes;
    QVector<Edge> deletedEdges;
    searchTreeDFS(vertices[0], passedVertexes, deletedEdges, graph);

    QCOMPARE(deletedEdges.size(), expectedDeletedEdges.size());
    for (int i = 0; i < deletedEdges.size(); ++i) {
        QCOMPARE(deletedEdges[i].outcomeVertex->id, expectedDeletedEdges[i].outcomeVertex->id);
        QCOMPARE(deletedEdges[i].approachVertex->id, expectedDeletedEdges[i].approachVertex->id);
    }

    // Освобождаем память
    qDeleteAll(vertices);
}


// Главная функция запуска тестов
QTEST_MAIN(TestSearchTreeDFS)
#include "test_searchTreeDFS.moc"
