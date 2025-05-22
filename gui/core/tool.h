#pragma once


#include <QLayout>
#include <QWidget>
#include <QDebug>
#include <QUuid>
#include <QDesktopServices>
#include <QUrl>
#include <QFileInfo>
#include "PinyinLookup.h"
#include <cctype>

bool insertAfterElement(QLayout* layout, QObject* currentElement, QObject* newElement);
std::string getFirstUTF8Char(const std::string& str);
std::string getFirstLetter(PinyinLookup *pinyin, const std::string& str);
bool openFileWithDefaultProgram(const QString &filePath);

QString generateUuid();