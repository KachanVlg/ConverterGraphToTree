#include "inputOutputFunctions.h"
#include <QFile>
#include <QDebug>



bool getTextFromFile(const QString& filePath, QStringList& lines)
{
    /// Открываем файл
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл" << filePath;
        return false;
    }

    /// Создаём текстовый поток для чтения из файла
    QTextStream in(&file);

    /// Читаем содержимое файла построчно и добавляем строки в QStringList
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed(); /// Читаем строку и удаляем пробельные символы по краям
        if (!line.isEmpty())
        {
            lines.append(line);
        }
    }

    /// Закрываем файл
    file.close();

    return true;
}


bool outputResultToFile(const QStringList &text, const QString &filepath)
{
    /// Открываем файл
    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    /// Создаём текстовый поток для чтения из файла
    QTextStream out(&file);
    for (const QString &line : text) {
        out << line << "\n";
    }

    file.close();
    return true;
}
