#ifndef AUTOTEST_H
#define AUTOTEST_H

#include <QTest>
#include <QList>
#include <QString>
#include <QObject>
#include <QSharedPointer>


namespace AutoTest
{
typedef QList<QObject*> TestList;

inline TestList& testList()
{
    static TestList list;
    return list;
}

inline bool findObject(QObject* object)
{
    TestList& list = testList();
    if (list.contains(object))
    {
        return true;
    }
        foreach (QObject* test, list)
        {
            if (test->objectName() == object->objectName())
            {
                return true;
            }
        }
    return false;
}

inline void addTest(QObject* object)
{
    TestList& list = testList();
    if (!findObject(object))
    {
        list.append(object);
    }
}

inline int run(int argc, char *argv[])
{
    int ret = 0;

        foreach (QObject* test, testList())
        {
            ret += QTest::qExec(test, argc, argv);
        }

    return ret;
}
}

template <class T>
class Test
{
public:
    QSharedPointer<T> child;

    Test(const QString& name) : child(new T)
    {
        child->setObjectName(name);
        AutoTest::addTest(child.data());
    }
};

// DOMAIN
#define DECLARE_TEST_RECIPE(className) static Test<className> t("RecipeTest");

// PARSER
#define DECLARE_TEST_TRANSFORMPAYLOAD(className) static Test<className> t("TransformPayloadTest");

// REPOSITORIES
#define DECLARE_TEST_ACTION_ARDUINO_REPO(className) static Test<className> t("ActionArduinoRepoTest");
#define DECLARE_TEST_ARDUINO_REPO(className) static Test<className> t("ArduinoRepoTest");
#define DECLARE_TEST_IODEVICE_REPO(className) static Test<className> t("IODeviceRepoTest");
#define DECLARE_TEST_LOG_REPO(className) static Test<className> t("LogRepoTest");
#define DECLARE_TEST_RECIPE_REPO(className) static Test<className> t("RecipeRepoTest");
#define DECLARE_TEST_STATECODE_REPO(className) static Test<className> t("StateCodeRepoTest");

#define TEST_MAIN \
 int main(int argc, char *argv[]) \
 {                \
    QApplication app(argc, argv); \
    return AutoTest::run(argc, argv); \
 }


#endif //AUTOTEST_H
