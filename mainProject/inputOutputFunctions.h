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




#endif // INPUTOUTPUTFUNCTIONS_H
