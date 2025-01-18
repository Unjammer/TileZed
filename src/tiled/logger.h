#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <memory>

class Logger
{
public:
    Logger(); // Constructeur
    ~Logger(); // Destructeur pour fermer proprement le fichier
    void log(const QString& message, const QString& severity); // Méthode d'instance

    static Logger& instance(); // Singleton pour un accès global

private:
    QFile m_file; // Fichier de log
};

#endif // LOGGER_H
