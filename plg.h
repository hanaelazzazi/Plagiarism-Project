#ifndef PLG_H
#define PLG_H

#include <QString>
#include <QStringList>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QtSql>
#include <filesDatabase.h>

struct linePlg {
    int index;
    QString file;
    double percentage;
};

class plg {
protected:
    filesDatabase Db;
    int numOfLines;
    int numOfWords;

    float numOfParagraphs;
    QVector<linePlg> lines;
    QVector<QString> sentences;
    QVector<QString> paragraphs;
    const int p = 31; // prime number for hashing
    const int m = 1e9 + 9; // large prime for modulo



public:
    plg();
    ~plg();
    int numOfchar;
    void detect(QString name1, QString name2);
    bool compare(QString sentence1, QString sentence2, int &index);
    int rabinKarp(QString word, QString sentence);
    int bruteForce(QString word, QString str);
    QVector<QString>getsentences(QString path);
    QVector<QString>getparagraphs(QString path);
    QVector<QString> split_sentence(QString sentence);
    void to_lower(QString& x);
    bool charOcc(QString str, QChar c);
    int percentage();
    void Filelength(QString p, int &characters, int &words, int &sentences);
    void printAIlines(QString &result);
    void printLines(QString &result);
    void sortLines();
    void insert(linePlg s);
    QString getOutput();
    QString pythonAI(QString sent);
    QString output= "";
};

#endif // PLG_H
