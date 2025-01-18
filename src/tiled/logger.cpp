#include "logger.h"
#include <QDir>
// Singleton pour garantir une instance unique
Logger& Logger::instance()
{
    static Logger loggerInstance;
    return loggerInstance;
}

// Constructeur
Logger::Logger()
{
    //QString fileName = QString("log_%1.txt").arg(QDate::currentDate().toString("ddMMyy"));
     QString fileName = QDir::currentPath() + QString(QLatin1String("/log_%1.txt")).arg(QDate::currentDate().toString(QLatin1String("ddMMyy")));
    m_file.setFileName(fileName);

    if (!m_file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        qWarning("Failed to open log file: %s", qUtf8Printable(m_file.errorString()));
    }
}

// Destructeur pour fermer le fichier
Logger::~Logger()
{
    if (m_file.isOpen())
    {
        m_file.close();
    }
}

// Méthode pour écrire un message dans le fichier
void Logger::log(const QString& message, const QString& severity = QLatin1String("INFO"))
{
    if (!m_file.isOpen())
    {
        qWarning("Log file is not open. Message not logged.");
        return;
    }

    QTextStream stream(&m_file);
    stream << QDateTime::currentDateTime().toString(QLatin1String("yyyy-MM-dd hh:mm:ss.zzz"))
           << " [" << severity << "] " << message << "\n";
}

