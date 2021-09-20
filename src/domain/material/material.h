#ifndef BSF_LIB_SRC_DOMAIN_MATERIAL_H_
#define BSF_LIB_SRC_DOMAIN_MATERIAL_H_

#include <QString>

class Material {

 public:
  Material(int id);
  Material(int id, int weight, QString name, QString description);
  int getId() const;
  int getWeight() const;
  void setWeight(int weight);
  const QString &getName() const;
  void setName(const QString &name);
  const QString &setDescription() const;
  void setDescription(const QString &description);

 private:
  int id;
  int weight = 0;
  QString name;
  QString description;
};

#endif //BSF_LIB_SRC_DOMAIN_MATERIAL_H_
