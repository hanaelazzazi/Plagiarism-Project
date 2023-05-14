#ifndef plagirism_H
#define plagirism_H

#pragma once

#include "plg.h"
#include <algorithm>
using namespace std;

class plagirism :
public plg
{
private:
    float percent=0;
    QString fileName;
    QString filePath;

public:

    plagirism();

    ~plagirism();

    void aiDetection(QString path);

    void basic(QString name, QString path);

    void prefered(QString name, QString path);

    void code(QString file1, QString file2);//paths

    float getPercent();

    float detectML(QString p, QString name);

};

#endif
