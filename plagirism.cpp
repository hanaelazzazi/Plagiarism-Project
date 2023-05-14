#include "plagirism.h"
using namespace std;
plagirism::plagirism() {}

plagirism::~plagirism() {
    percent = -1;
    fileName = "";
    filePath = "";

    numOfLines = -1;
    lines.clear();
    sentences.clear();
}

void plagirism::basic(QString name, QString path) {
    qDebug()<<"Basic Opened";
    fileName = name;
    filePath = path;

    Filelength(path, numOfchar, numOfWords, numOfLines);
    sentences = getsentences(path);
    qDebug()<<"Badic 3";
    int ln = Db.getNumFields();

    for (int i = 0; i < ln; i++) {
        QString n;
        QString p;

        Db.select(i + 1, n, p);
        qDebug()<<"Badic 4"<<" "<<n<<" "<<p;

        detect(p, n);
        qDebug()<<"Badic 5";
    }
    percent = percentage();

    Db.insertfile(name, path);
    qDebug()<<"Badic 6";
    sortLines();
    qDebug()<<"Badic 7";
}
void plagirism::aiDetection(QString path) {
    qDebug() << "Function opened yarab.";
    Filelength(path, numOfchar, numOfWords, numOfLines);
    qDebug() << "line 46"<<numOfchar<< " "<<numOfWords<<" " <<numOfLines;

    QVector<QString> paragraphsVec = getparagraphs(path);
    paragraphs = QList<QString>(paragraphsVec.begin(), paragraphsVec.end());

    numOfParagraphs = paragraphs.size();
    qDebug()<<numOfParagraphs;
    for (int i = 0; i < numOfParagraphs; i++) {

        QString result = pythonAI(paragraphs[i]);
        qDebug()<<"result = "<<result;
        if (result == "True") {

            output += "Paragraph number" + (i+1)+'/n';
            linePlg test;
            test.index = i + 1;
            lines.push_back(test);
        }
    }
    percent = (lines.size() / numOfParagraphs)*100;
}


float plagirism::getPercent()
{
    return percent;
}

void plagirism::prefered(QString name, QString path) {
    fileName = name;
    filePath = path;

    Filelength(path, numOfchar, numOfWords, numOfLines);
    int ln = Db.getNumFields();
    float max = 0;
    QString file = "";
    for (int i = 0; i < ln; i++) {
        QString n;
        QString p;

        Db.select(i + 1, n, p);

        float s = detectML(p, n);
        if (s>max)
        {
            max = s;
            file = n;
        }
    }
    percent = max;
    output = file;
    Db.insertfile(name, path);

}

float plagirism::detectML(QString p, QString name) {

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
    stream<<p;
    stream<<'\n';
    stream<<filePath;

    // Close the file
    file.close();


    QStringList args2;
    args2<<"/Users/hanaelazzazi/Desktop/Spring 2023/CS 2/Project and Paper/Python/sharaf2.py";
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
    qDebug()<<content;
    return content.toFloat();


}
void plagirism::code(QString file1, QString file2) {
    QFile f1(file1), f2(file2);
    f1.open(QIODevice::ReadOnly | QIODevice::Text);
    f2.open(QIODevice::ReadOnly | QIODevice::Text);

    QString str1 = QString::fromUtf8(f1.readAll());
    QString str2 = QString::fromUtf8(f2.readAll());

    // Convert both strings to lowercase for case-insensitive comparison
    str1 = str1.toLower();
    str2 = str2.toLower();

    const size_t len1 = str1.length(), len2 = str2.length();
    const size_t maxLen = std::max(len1, len2);

    // Compute the Levenshtein distance between the two strings
    std::vector<std::vector<size_t>> dist(len1 + 1, std::vector<size_t>(len2 + 1, 0));
    for (size_t i = 1; i <= len1; ++i) dist[i][0] = i;
    for (size_t j = 1; j <= len2; ++j) dist[0][j] = j;
    for (size_t j = 1; j <= len2; ++j) {
        for (size_t i = 1; i <= len1; ++i) {
            const size_t cost = (str1[i - 1] == str2[j - 1]) ? 0 : 1;
            dist[i][j] = std::min(std::min(dist[i - 1][j] + 1, dist[i][j - 1] + 1),
                                  dist[i - 1][j - 1] + cost);
        }
    }

    // Compute the similarity percentage
    const double similarity = 100.0 * (1 - static_cast<double>(dist[len1][len2]) / maxLen);
    percent = similarity;
}


