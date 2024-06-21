#ifndef INPUTOUTPUTFUNCTIONS_H
#define INPUTOUTPUTFUNCTIONS_H
#include <QStringList>
#include <QString>




/*!
 * \brief Получает текст из файла и записывает в QStringList
 * \param filePath путь к файлу
 * \param lines список для записи результата текста
 * \return успешность получения текста
 */
bool getTextFromFile(const QString& filePath, QStringList& lines);


/*!
 * \brief Записывает необходимый текст в файл по данному пути
 * \param text - текст, который необходимо записать
 * \param filepath путь к файлу записи
 * \return успешность записи текста
 */
bool outputResultToFile(const QStringList &text, const QString &filepath);


#endif // INPUTOUTPUTFUNCTIONS_H
