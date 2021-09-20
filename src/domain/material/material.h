#ifndef BSF_LIB_SRC_DOMAIN_MATERIAL_H_
#define BSF_LIB_SRC_DOMAIN_MATERIAL_H_

#include <QString>

class Material {

 public:
  explicit Material(int id);
  Material(int id, float weight, QString name, QString description);
  int getId() const;
  float getWeight() const;
  void setWeight(float weight);
  const QString &getName() const;
  void setName(const QString &name);
  const QString &setDescription() const;
  void setDescription(const QString &description);

 private:
  int id;
  float weight = 0.00;
  QString name;
  QString description;
};

#endif //BSF_LIB_SRC_DOMAIN_MATERIAL_H_
