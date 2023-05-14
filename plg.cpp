#include "plg.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <vector>
#include <QDebug>
#include <iostream>
#include <QCoreApplication>
#include <QProcess>
#include <QUrl>
#include <QByteArray>
#include <plagirism.h>

using namespace std;

plg::plg(){}

plg::~plg() {
    numOfLines = -1;
    //fileName = "";
    //filePath = "";
    lines.clear();
    sentences.clear();
    //percent = -1;
}

QString plg::pythonAI(QString sent)
{
    QString fileName = "/Users/hanaelazzazi/Desktop/Spring 2023/CS 2/Project and Paper/Python/dump.txt";

    // Open the file in write-only mode, overwriting any existing content
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        qWarning("Failed to open file for writing.");

    }


    // Create a text stream to write to the file
    QTextStream stream(&file);

    // Write the desired text to the file
    stream <<sent;

    // Close the file
    file.close();




    QStringList args2;
    args2<<"/Users/hanaelazzazi/Desktop/Spring 2023/CS 2/Project and Paper/Python/sharaf.py";
    QProcess process;
    process.start("/Library/Frameworks/Python.framework/Versions/3.10/bin/python3",args2);
    process.waitForFinished();



    QByteArray output = process.readAllStandardOutput();
    QByteArray error = process.readAllStandardError();
    qDebug() << "Output:" << output;
    qDebug() << "Error:" << error;




    QFile y(fileName);
    y.open(QIODevice::ReadOnly | QIODevice::Text);

    // Read the contents of the file
    QTextStream in(&y);
    QString content = in.readAll();
    // Close the file
    y.close();

    return content;
}

void plg::detect(QString p, QString name) {
    qDebug()<<"DETECT SUCESSFULLY";
    QVector<QString> file2 = getsentences(p);
    qDebug()<<file2.size();

    qDebug()<<"detect1";
    //int counter = 0;
    for (int i = 0; i < sentences.size(); i++) {
        int max = 0;
        bool flag = false;
        int n=0;

        for (int j = 0; j < file2.size(); j++) {

            bool z = compare(sentences[i], file2[j], n);
            qDebug()<<"detect1"<<" "<<n;
            if (n > max)max = n;
            if (z == true)flag = true;
        }

        if (flag == true) {
            output += "Line number " + QString::number(i+1) + " is plagiarized from: " + name + " by " + QString::number(max) + "%." + "\n";

            linePlg y;
            y.index = i+1;
            y.file = name;
            y.percentage = max;

            insert(y);
        }
    }

}


void plg::insert(linePlg s) {
    bool flag = false;
    for (int i = 0; i < lines.size()&&flag==false; i++) {
        if (lines[i].index == s.index) {
            flag = true;
            if (s.percentage > lines[i].percentage) {
                lines[i] = s;
            }
        }
    }

    if (flag == false) {
        lines.push_back(s);
    }
}

QVector<QString> plg::getsentences(QString path) {
    QFile file (path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"File did not open.";
    }

    QTextStream in(&file);
    QString test = "?.!";

    int words, chars, lines;

    Filelength(path, chars, words, lines);

    QVector<QString> res;
    //int counter = 0;

    QString line = "";
    QChar c;

    for (int i = 0; i < chars; i++) {
        in>>c;
        if (charOcc(test, c)) {
            line = line + " ";
            res.push_back(line);
            line = "";
            //counter++;
        }
        else line = line + c;

    }
    return res;
}

 QString plg::getOutput()
{
    return output;
 }
 QVector<QString> plg::getparagraphs(QString path) {
    qDebug()<<"getparagraphs function";
    QFile infile(path);
    infile.open(QIODevice::ReadOnly);

    QString line;
    QVector<QString> paragraphs;
    QString currentParagraph;

    QTextStream in(&infile);
    while (!in.atEnd()) {
        int i=0;
        line="";
        while (!in.atEnd() && i<=300)
        {
            QChar c;
            in>>c;
            line+=c;
            if(c==' ')
                i++;
        }
        paragraphs.push_back(line);
    }

    // If the file does not end with an empty line, the last paragraph may not have been added
    if (!currentParagraph.isEmpty()) {
        paragraphs.push_back(currentParagraph);
    }

    infile.close();

    // Convert the std::string elements to QString
    QVector<QString> result;
    for (const auto& paragraph : paragraphs) {
        result.push_back(paragraph);

    }

    return result;
 }

 bool plg::compare(QString sntc1, QString sntc2, int& x) {
    qDebug()<<"COMPARE ENTERED";
    double count = 0;
    QVector<QString> box = split_sentence(sntc1);
    qDebug()<<"COMPARE1"<<" "<<box.size();
    for (int i = 0; i < box.size(); i++) {
        double rk = rabinKarp(box[i], sntc2);
        qDebug()<<"Entering brute force";
        //double bf = bruteForce(box[i], sntc2);
        qDebug()<<"COMPARE2"<<" "<<rk<<" "<<" "<<box[i]<<" "<<i<<box.size();
        double avg = rk;
        count += avg;
        qDebug()<<"compare2.5"<<count;
    }
    qDebug()<<"compare2.75"<<count<<" "<<box[1];
    double prcnt = ((count / box.size()) * 100);
    qDebug()<<"compare3"<<prcnt;
    if (prcnt >= 65) {
        x = prcnt;
        return true;
    } else {
        return false;
    }
 }

 int plg::rabinKarp(QString word, QString sentence) {
    to_lower(word);
    to_lower(sentence);

    QStringList words = sentence.split(" ");
    int n = words.size();
    int m = word.size();
    long long p_pow = 1;
    long long word_hash = 0;

    // compute hash for the word
    for (int i = 0; i < m; i++) {
        word_hash = (word_hash + (word[i].toLatin1() - 'a' + 1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
    }

    // check if there is a match
    for (int i = 0; i < n; i++) {
        long long sentence_hash = 0;
        QString current_word = words[i];
        int current_word_size = current_word.size();

        // compute hash for the current word in the sentence
        if (current_word_size >= m) {
            for (int j = 0; j < m; j++) {
                sentence_hash = (sentence_hash + (current_word[j].toLatin1() - 'a' + 1) * p_pow) % m;
                p_pow = (p_pow * p) % m;
            }
        }

        // check if there is a match
        if (word_hash == sentence_hash && current_word == word) {
            return 1;
        }

        // compute hash for the next substring of length m
        for (int j = m; j < current_word_size; j++) {
            sentence_hash = (p * (sentence_hash - (current_word[j - m].toLatin1() - 'a' + 1) * p_pow) + (current_word[j].toLatin1() - 'a' + 1)) % m;
            if (sentence_hash < 0) sentence_hash += m;
            if (word_hash == sentence_hash && current_word.mid(j - m + 1, m) == word) {
                return 1;
            }
        }
    }
    return 0;
 }

int plg::bruteForce(QString word, QString str) {
    word = word.toLower();
    str = str.toLower();

    QString test = ".,>< !@#$%^&*()}{[];'\\/?~+-=";

    int strLen = str.length();
    int wordLen = word.length();
    int result = false;
    try {
        for (int i = 0; i <= strLen - wordLen; i++) {
            if (str[i] == word[0] && (test.contains(str[i + wordLen]) || i + wordLen == strLen)) {
                bool flag = true;
                int j = 1;
                for (j = 1; j < wordLen; j++) {
                    if (str[i + j] != word[j]) {
                        flag = false;
                    }
                }
                if (flag == true) {
                    result = true;
                }
            }
        }
    } catch (const std::exception& ex) {
        // Log any caught exceptions
        qDebug() << "Error in bruteForce function: " << ex.what();
    }

    // Log the input strings and the result of the search
    qDebug() << "bruteForce called with word:" << word << " and str:" << str;
    qDebug() << "Search result: " << result;

    return result;
 }

 QVector<QString> plg::split_sentence(QString sentence) {
    QVector<QString> words;
    QString result="";

    for (int i=0; i<sentence.length(); i++)
    {
        qDebug()<<"SPLIT 0";
        if(sentence[i]==' ')
        {

            words.push_back(result);
            qDebug()<<"SPLIT 1";
            result="";
        }
        else
        {
            result=result+sentence[i];
            qDebug()<<"SPLIT 2";
        }
    }
    if (!result.isEmpty()) {
        words.push_back(result);
    }

    qDebug()<<"SPLIT 3"<<words.size();
    return words;
 }

 void plg::to_lower(QString& x) {
    x = x.toLower();
 }

 bool plg::charOcc(QString str, QChar c) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == c) {
            return true;
        }
    }
    return false;
 }


 int plg::percentage() {
    int sum = 0;
    for (int i = 0; i < lines.size(); i++) {
        sum += lines[i].percentage;
    }

    return sum / numOfLines;
 }

 void plg::sortLines() {


    for (int i = 0; i < lines.size();i++) {
        int minIndex = i;
        for (int j = i+1; j < lines.size(); j++) {
            if (lines[j].index < lines[minIndex].index) {
                minIndex = j;
            }
        }

        linePlg box = lines[minIndex];
        lines[minIndex] = lines[i];
        lines[i] = box;

    }
 }

 void plg::Filelength(QString p,int & characters,int & words ,int & sentences ) {
    QFile file(p);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Error!";
    }

    else {
        QTextStream in(&file);
        QString test = "!?.";

        characters = 0;
        words = 0;
        sentences = 0;


        QChar c;
        while (!in.atEnd()) {

            in>>c;
            if (charOcc(test, c)) {
                sentences++;
            }
            if (c == ' ') {
                words++;
            }
            characters++;
        }
        file.close();

    }
 }
