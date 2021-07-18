#ifndef BSF_DATABASESERVICE_H_
#define BSF_DATABASESERVICE_H_

#include <QObject>
#include <QtSql/QtSql>

namespace service {
class DatabaseService;
}

class service::DatabaseService : public QObject {
 Q_OBJECT

 public:
  explicit DatabaseService(QObject *parent = nullptr);
  virtual ~DatabaseService();

  /// Run a SQL script.
  void runScripts(const QVector<QVector<QString>> &scripts);
  QSqlDatabase openDatabase();

 private:
  QMap<int64_t, QSqlDatabase> connections;

};

#endif //BSF_DATABASESERVICE_H_
