#ifndef BANDACONST_H
#define BANDACONST_H

#include <QStringList>
#include <QKeyEvent>

namespace bandaConst {

const int MAX_ITEM_ROUND = 196;

const int TIMEOUT_EASY   = 8000;
const int TIMEOUT_MEDIUM = 5000;
const int TIMEOUT_HARD   = 3000;


const QStringList catList = QStringList() << "All" << "UN" << "Easy" << "Medium" << "Hard" << "Africa" << "Asia" << "Europe" << "North America" << "Oceania" << "South America";
const QStringList filterWords = QStringList() << "" << "UN" << "Easy" << "Medium" << "Hard" << "Africa" << "Asia" << "Europe" << "NorthAm" << "Oceania" << "SouthAm";
const QList<int> catSpinMax = QList<int>() << 206 << 193 << 56 << 73 << 77 << 57 << 51 << 48 << 22 << 16 << 12;

const QStringList motivation = QStringList() << "Top notch!" << "Nice!" << "You are right!" << "Yes!" << "Correct!" << "That is correct!" << "You gave the right answer." << "Awesome!" << "Great!" << "You are rocking it!" << "Yes, that is right!" << "Good job" << "Keep up the good work!" << "You're a flag-maniac!" << "Was that right? Was that right? YES!" << "You are so smart!" << "My sources say yes" << "Hell yeah!" << "You showed that flag who's boss!" << "Ding ding ding!" << "Fabulous!" << "Score!" << "Maravilloso!";
const QList<Qt::Key> quizOptionKeys = QList<Qt::Key>() << Qt::Key_1 << Qt::Key_2 << Qt::Key_3 << Qt::Key_4 << Qt::Key_5;


const QString bandaColor = "#346733";
const QString bandaColorMarked = "#698e68";
}

#endif // BANDACONST_H
