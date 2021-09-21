#ifndef BSF_LIB_SRC_DOMAIN_MATERIAL_H_
#define BSF_LIB_SRC_DOMAIN_MATERIAL_H_

#include <QString>

class Material {

 public:
  Material(int id, double weight, QString name, QString description);
  int getId() const;
  double getWeight() const;
  void setWeight(double weight);
  const QString &getName() const;
  void setName(const QString &name);
  const QString &setDescription() const;
  void setDescription(const QString &description);

 private:
  int id;
  double weight = 0.00;
  QString name;
  QString description;
};

#endif //BSF_LIB_SRC_DOMAIN_MATERIAL_H_
