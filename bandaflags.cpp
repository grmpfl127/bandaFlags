#include "bandaflags.h"
#include "ui_bandaFlags.h"
#include "bandaConst.h"
#include "result.h"

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QDateTime>
#include <QtGlobal>
#include <QDir>
#include <QMessageBox>
#include <QInputDialog>


int bandaFlags::curItem = 0;

bandaFlags::bandaFlags(QWidget *parent)
    : QDialog(parent), ui(new Ui::Dialog), startupBool(true), initFlagsBool(false)
{
    ui->setupUi(this);
    settings = new QSettings("Vanbg","bandaFlags");
    loadSettings();

    ui->backgroundLabel->setPixmap(QPixmap(":/cfg/res/EarthFlagCut.png").scaled(QSize(ui->backgroundLabel->size()),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    //ui->languageCombo-
    profileModel = new QStringListModel();
    ui->startButton->setEnabled(false);
    ui->profileView->setModel(profileModel);
    ui->profileView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    profileModel->setStringList(storedProfiles);

    pauseMode.paused = false;

    if(storedProfiles.size()){
        QString lastProfile = settings->value("lastProfile").toString();
        QModelIndex lastProfileIDX = profileModel->match(profileModel->index(0, 0),Qt::DisplayRole, lastProfile)[0];
        if(lastProfileIDX.isValid()){
            ui->profileView->selectionModel()->select(lastProfileIDX,QItemSelectionModel::Select);
            profileName = lastProfile;
        }else{
            ui->profileView->selectionModel()->select(profileModel->index(0,0),QItemSelectionModel::Select);
            profileName = profileModel->index(0,0).data(Qt::DisplayRole).toString();
        }
        loadProfile();
    }else{
        createProfile();
    }
    qsrand(QDateTime::currentMSecsSinceEpoch());
    bandaFont = QFont("Georgia",-1,QFont::Bold,false);

    //set Style ***test***
    qApp->setStyleSheet("QLineEdit { background-color: yellow }");
    qApp->setStyle("QLabel { font-family: Georgia }");

    //qApp->setFont(bandaFont);
    ui->stackedWidget->setFont(bandaFont);
    ui->difficultyTestLabel->setStyleSheet("color: #346733");
    ui->filterCombo->setCurrentIndex(0);
    ratio = ui->spinBox->value() / static_cast<double>(ui->spinBox->maximum());
    startup();
}

bandaFlags::~bandaFlags()
{
    delete ui;
}

/******************************
 * PROFILE / SETTINGS FCTS
 ******************************/

void bandaFlags::createProfile()
{
    bool ok;

    QString getAns;
    getAns = QInputDialog::getText(this, tr("Specify your user name"),
                                   tr("Profile name:"), QLineEdit::Normal,
                                   "", &ok);

    if (ok && !storedProfiles.contains(getAns) && !getAns.isEmpty()){
        delete bProf;
        bProf = new bandaProfile(getAns);
        storedProfiles.append(getAns);
        profileModel->setStringList(storedProfiles);
        profileName = getAns;
    }
}

void bandaFlags::on_profileAddBut_clicked()
{
    profileName = ui->profileView->selectionModel()->selectedIndexes().at(0).data().toString();
    createProfile();
    saveProfile();
    ui->profileView->selectionModel()->setCurrentIndex(profileModel->match(profileModel->index(0, 0),Qt::DisplayRole, profileName)[0], QItemSelectionModel::Select);
}


void bandaFlags::loadProfile()
{
    bProf = new bandaProfile(profileName);

    for(int countryID=0; countryID<countryListAlt.size(); countryID++){
        foreach(int catID, countryListAlt.at(countryID).modes){
            bProf->notGuessedIdx[catID].append(countryID);
        }
    }
    QString fileName = QString("%1/cfg/%2.cfg").arg(QDir::currentPath(),profileName);
    QFile proFile(fileName);
    if(proFile.open(QIODevice::ReadOnly)){
        QDataStream read(&proFile);
        read >> bProf->correctGuessedIdx;
    }
    qDebug() << bProf->correctGuessedIdx.at(0).size() << bProf->correctGuessedIdx.at(1).size() << bProf->correctGuessedIdx.at(2).size() << bProf->correctGuessedIdx.at(3).size() << bProf->correctGuessedIdx.at(4).size() << bProf->correctGuessedIdx.at(5).size() << bProf->correctGuessedIdx.at(6).size() << bProf->correctGuessedIdx.at(7).size() << bProf->correctGuessedIdx.at(8).size() << bProf->correctGuessedIdx.at(9).size() << bProf->correctGuessedIdx.at(10).size();
    proFile.close();
}

void bandaFlags::loadProfiles()
{
    QDir dir(QString("%1/cfg").arg(QDir::currentPath()));
    QStringList cfgFiles(dir.entryList(QStringList() << "*.cfg"));

    storedProfiles.clear();
    QListIterator<QString> iter(cfgFiles);
    while(iter.hasNext()){
        QString curProfile = iter.next();
        curProfile.chop(4);
        storedProfiles += curProfile;
    }
}

void bandaFlags::loadSettings()
{
    //resize(settings->value("size",QSize(550,450)).toSize());
    move(settings->value("pos", QPoint(200, 200)).toPoint());
    //storedProfiles += settings->value("profiles").toStringList();

    loadProfiles();
}

void bandaFlags::saveSettings()
{
    //settings->setValue("size", size());
    settings->setValue("pos", pos());
    //settings->setValue("profiles", storedProfiles);
    //settings->beginGroup("stats");
    settings->setValue("lastProfile",profileName);

    //settings->endGroup("stats");
    //settings->setValue(QString("%1").arg(profileName),bProf->correctGuessedIdx.at(0));
    //settings->setValue("stats1", bProf->correctGuessedIdx.at(0));
}

/*!
 * \brief bandaFlags::saveProfile
 */
void bandaFlags::saveProfile()
{
    if(!profileName.isEmpty()){
        QDir cfgDir = QDir(QDir::currentPath()+"/cfg/");
        if(!cfgDir.exists()){
            cfgDir.mkdir(QDir::currentPath()+"/cfg/");
        }
        QFile profileStat(QString("%1/cfg/%2.cfg").arg(QDir::currentPath(),profileName));
        profileStat.open(QIODevice::WriteOnly);
        QDataStream write(&profileStat);
        qDebug() << bProf-> correctGuessedIdx.at(0).size() << bProf->correctGuessedIdx.at(1).size() << bProf->correctGuessedIdx.at(2).size() << bProf->correctGuessedIdx.at(3).size() << bProf->correctGuessedIdx.at(4).size() << bProf->correctGuessedIdx.at(5).size() << bProf->correctGuessedIdx.at(6).size() << bProf->correctGuessedIdx.at(7).size() << bProf->correctGuessedIdx.at(8).size() << bProf->correctGuessedIdx.at(9).size() << bProf->correctGuessedIdx.at(10).size();
        write << bProf->correctGuessedIdx;
        profileStat.close();
    }
}

void bandaFlags::showProfileStatus()
{
    loadProfile();
    bandaProfileStatusDialog profileState(profileName, bProf, this);
    profileState.setModal(false);
    profileState.move(this->x() + 2*ui->profileView->width(), this->y() + ui->profileView->width());

    profileState.exec();
}

void bandaFlags::on_profileStatusBut_clicked()
{
    profileName = ui->profileView->selectionModel()->selectedIndexes().at(0).data().toString();
    showProfileStatus();
    ui->profileView->setFocus();
}

void bandaFlags::on_statusButton_clicked()
{
    on_profileStatusBut_clicked();
}

void bandaFlags::on_profileDeleteBut_clicked()
{
    QModelIndex idx = ui->profileView->selectionModel()->selectedIndexes()[0];
    profileName = profileModel->data(idx, Qt::DisplayRole).toString();
    if(idx.isValid()){
        QString delProf = idx.data().toString();
        int row = idx.row();
        if(row == 0)
            row++;
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Delete profile", QString("Do you really want to delete the profile '%1'?").arg(delProf),QMessageBox::Yes|QMessageBox::No);
        if(reply == QMessageBox::Yes){
            storedProfiles.removeOne(delProf);
            profileModel->setStringList(storedProfiles);
            resetProfile();
            if(storedProfiles.size() == 0){
                profileName = "";
                createProfile();
            }else{
                ui->profileView->selectionModel()->select(profileModel->index(row-1,0),QItemSelectionModel::Select);
                loadProfiles();
            }
        }
    }
    loadProfiles();
}

void bandaFlags::on_profileResetBut_clicked()
{
    QString name = bProf->name;
    QModelIndex idx = ui->profileView->selectionModel()->selectedIndexes()[0];
    profileName = profileModel->data(idx, Qt::DisplayRole).toString();
    if(idx.isValid()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Reset profile?", QString("Do you really want to reset the scores of the profile '%1'?").arg(name),QMessageBox::Yes|QMessageBox::No);
        if(reply == QMessageBox::Yes){
            resetProfile();
            delete bProf;
            bProf = new bandaProfile(name);
            saveProfile();
            ui->profileView->selectionModel()->select(profileModel->match(profileModel->index(0,0),Qt::DisplayRole, name)[0], QItemSelectionModel::Select);
            QMessageBox::information(this, "Profile reset", QString("Profile '%1' was successfully reset.").arg(name),QMessageBox::Ok);
        }
    }
}

void bandaFlags::resetProfile()
{
    QDir dir(QString("%1/cfg").arg(QDir::currentPath()));
    QFile proFile(QString(dir.absolutePath() + "/%1.cfg").arg(profileName));
    if(proFile.exists()){
        dir.remove(proFile.fileName());
    }
}

//??? do nothing on double click
void bandaFlags::on_profileView_doubleClicked(const QModelIndex)
{
    qDebug() << "double clicked";
}

/******************************
 * UI/ STARTUP FCTS
 ******************************/

void bandaFlags::startup()
{
    //page = startP;
    if(startupBool){
        page = profileP;
    }else{
        page = newGameP;
    }
    updateUI();
    newGame();
}

void bandaFlags::updateUI()
{
    switch(page){

    case profileP:
        ui->stackedWidget->setCurrentIndex(profileP);
        ui->mainMenuButton->hide();
        ui->changeProfileButton->hide();
        ui->hintButton->hide();
        ui->NextButton->setEnabled(false);
        ui->profileView->setFocus();
        break;

    case startP:
        ui->stackedWidget->setCurrentIndex(startP);
        ui->startIcon->setPixmap(QPixmap(QString(getCatPic(ui->filterCombo->currentIndex()))).scaled(QSize(ui->startIcon->size()),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        ui->startButton->setEnabled(true);
        ui->NextButton->setEnabled(false);
        ui->hintButton->hide();
        ui->correctAnswerButton->hide();
        ui->helpButton->show();
        ui->mainMenuButton->hide();
        ui->changeProfileButton->show();
        if(startupBool){
            ui->correctFlagsCB->setChecked(false);
            ui->radioPractice->setChecked(true);
            ui->radioEasy->setChecked(true);
            ui->difficultyFrame->hide();
            startupBool = false;
        }
        if(!ui->radioQuiz->isChecked())
            ui->correctFlagsCB->setEnabled(true);
        ui->filterCombo->setFocus();
        break;

    case practiceP:
        ui->stackedWidget->setCurrentIndex(practiceP);
        ui->NextButton->setEnabled(true);
        ui->lineEdit->setText("");
        ui->hintButton->show();
        ui->startButton->setEnabled(false);
        ui->mainMenuButton->show();
        ui->correctAns->setText("");
        ui->progressBar->setValue(0);
        ui->lineEdit->setFocus();
        break;

    case testP:
        ui->stackedWidget->setCurrentIndex(testP);
        ui->NextButton->setEnabled(true);
        ui->testLineEdit->setText("");
        ui->startButton->setEnabled(false);
        ui->mainMenuButton->show();
        ui->testProgressBar->setValue(0);
        ui->testProgressBar->show();
        ui->testLineEdit->show();
        ui->testLineEdit->setFocus();
        break;

    case quizP:
        ui->stackedWidget->setCurrentIndex(quizP);
        ui->quizAnswerLabel->setText("");
        ui->NextButton->setEnabled(false);
        ui->startButton->setEnabled(false);
        ui->mainMenuButton->show();
        ui->groupBox->setEnabled(true);
        ui->quizOkButton->hide();
        break;

    case quiz2PP:
        ui->stackedWidget->setCurrentIndex(quiz2PP);
        ui->quizAnswer2PLabel->setText("");
        ui->NextButton->setEnabled(false);
        ui->startButton->setEnabled(false);
        ui->mainMenuButton->show();
        ui->group2PBox->setEnabled(true);
        ui->quizOk2PButton->hide();
        break;

    case newGameP:
        ui->stackedWidget->setCurrentIndex(startP);
        ui->mainMenuButton->hide();
        ui->NextButton->setEnabled(false);
        break;

    }
}

QString bandaFlags::getCatPic(int index){
    QString pic = bandaConst::filterWords.at(index);
    if(index == 0 || (index > 1 && index <= 4)){pic = "worldFlag";}
    return QString(":/cfg/res/" + pic + ".png");
}

/*********************
 * OPTION FCTS
 ********************/
void bandaFlags::on_filterCombo_currentIndexChanged(int index)
{
    ui->spinBox->setMaximum(bandaConst::catSpinMax.at(index));
    ui->spinBox->setValue(ratio * bandaConst::catSpinMax.at(index));
    if(ui->correctFlagsCB->isChecked()){
        on_correctFlagsCB_toggled(true);
    }
    ui->startIcon->setPixmap(QPixmap(getCatPic(index)));
    //ui->spinBox->setFocus();
}

void bandaFlags::on_startButton_clicked()
{
    if(page == profileP){
        profileName = ui->profileView->selectionModel()->selectedIndexes().at(0).data().toString();
        loadProfile();
        checkRememberCB(ui->correctFlagsCB->isChecked());
        page = startP;
        updateUI();
        setWindowTitle(QString("bandaFlags %1").arg(profileName));
    }else{
        parseOptions();
        if(!initFlagsBool)
            initFiles();
        updateUI();
        switch(mode){
        case practice:
            //            practiceGame = new bandaPractice();
            //            practiceGame->startPractise();
            checkRememberCB(ui->correctFlagsCB->isChecked());
            startPractise();

            //uncomment so Timer will be fired to clear bg-color of lineEdit plus correct Answer label
            //colorTimer = new QTimer(this);
            //colorTimer->setSingleShot(true);
            //connect(colorTimer,SIGNAL(timeout()),this,SLOT(updateLineEditColor()));
            showFlags();
            break;

        case test:
            checkRememberCB(ui->correctFlagsCB->isChecked());
            startTest();
            initTestMode();
            showFlags();
            break;

        case quiz:
            startQuiz();
            quizProcedure();
            showFlags();
            break;

        case quiz2P:
            qDebug() << "2 Player Quiz!!!";
        }
    }
}

void bandaFlags::on_correctFlagsCB_toggled(bool checked)
{
    checkRememberCB(checked);
}

void bandaFlags::parseOptions()
{
    if(ui->radioPractice->isChecked()){
        mode = practice;
        page = practiceP;
    }
    else if(ui->radioTest->isChecked()){
        mode = test;
        page = testP;
    }
    else if(ui->radioQuiz->isChecked()){
        mode = quiz;
        page = quizP;
    }else if(ui->radioQuiz2P->isChecked()){
        mode = quiz2P;
        page = quiz2PP;
    }

    if(mode == test){
        if(ui->radioEasy->isChecked()){
            msTimeout = bandaConst::TIMEOUT_EASY;
        }else if(ui->radioMedium->isChecked()){
            msTimeout = bandaConst::TIMEOUT_MEDIUM;
        }else if(ui->radioHard->isChecked()){
            msTimeout = bandaConst::TIMEOUT_HARD;
        }
    }

    if(mode == quiz){
        if(ui->radioEasy->isChecked()){
            ui->quizOption4->hide();
            ui->quizOption5->hide();
            noOfQuizButtons = 3;
        }else if(ui->radioMedium->isChecked()){
            ui->quizOption4->show();
            ui->quizOption5->hide();
            noOfQuizButtons = 4;
        }else if(ui->radioHard->isChecked()){
            ui->quizOption4->show();
            ui->quizOption5->show();
            noOfQuizButtons = 5;
        }
        curQuizButtons.clear();
        curQuizButtons = bandaConst::quizOptionKeys.mid(0,noOfQuizButtons);
    }

    cat = static_cast<Categorie>(ui->filterCombo->currentIndex());
}

void bandaFlags::on_radioTest_clicked()
{
    //    ui->correctFlagsCB->setChecked(false);
    //    ui->correctFlagsCB->setEnabled(false);
    ui->correctFlagsCB->setEnabled(true);
    ui->difficultyFrame->show();
}

void bandaFlags::on_radioPractice_clicked()
{
    ui->correctFlagsCB->setEnabled(true);
    ui->difficultyFrame->hide();
}

void bandaFlags::on_radioQuiz_clicked()
{
    ui->correctFlagsCB->setChecked(false);
    ui->correctFlagsCB->setEnabled(false);
    ui->difficultyFrame->show();
}

void bandaFlags::on_radioQuiz2P_clicked()
{
    ui->correctFlagsCB->setChecked(false);
    ui->correctFlagsCB->setEnabled(false);
    ui->difficultyFrame->show();
}

//Option C: run only once and store fileName, countryAlternatives, and modes for each country
//          in countryListAlt
void bandaFlags::initFiles()
{
    picPath = ":/wiki/res/wiki/";
    QFile file(":/cfg/res/countries.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream read(&file);
    QList<QString> cList = read.readAll().split("\n");
    file.close();

    QRegExp rxCtr("^(\\w+)\\s|\\s(\\w+)\\s|\\s(\\w+)$");
    foreach(const QString& entry, cList){
        if(entry.contains(rxCtr)){
            //fill countryListAlt
            ctry ctryItem;
            QStringList prts = entry.split('|');
            QList<QString> curAlts = prts.at(1).trimmed().split('&');
            QList<QString> cpyAlts;
            foreach(QString alt, curAlts){
                alt.replace('_',' ');
                cpyAlts.append(alt.trimmed());
            }
            ctryItem.countryNameAlt.append(cpyAlts);
            ctryItem.fileName = prts.at(0).trimmed();

            //categorize countries
            int countryID = 0, modeCnt = 0;
            QListIterator<QString> iter(bandaConst::filterWords);
            QList<int> t;
            while(iter.hasNext()){
                QString curCat = iter.next();
                if(entry.contains(curCat)){
                    t.append(modeCnt);
                }
                modeCnt++;
            }
            ctryItem.modes.append(t);
            countryListAlt.append(ctryItem);
            countryID++;
        }
    }
    initFlagsBool = true;
}

/*********************
 * PRACTISE MODE
 ********************/

//bandaPractice::bandaPractice(QWidget *parent)
//{
//}

//bandaPractice::~bandaPractice()
//{
//}

void bandaFlags::startPractise()
{
    curLabel = ui->label;
    curStatusLabel = ui->iterLabel;
    ui->catPracticeLabel->setText(QString("%1").arg(ui->filterCombo->currentText()));
    ui->practiceCatIcon->setPixmap(QPixmap(getCatPic(ui->filterCombo->currentIndex())).scaled(QSize(ui->practiceCatIcon->size()),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    ui->startButton->setEnabled(false);
    generateSubset();
}

void bandaFlags::on_correctAnswerButton_clicked(){

    ui->correctAnswerButton->hide();
    ui->buttonFrame->show();
    ui->lineEdit->setEnabled(true);
    ui->lineEdit->setFocus();
    ui->lineEdit->show();
    ui->correctAns->hide();
    showFlags();

}

void bandaFlags::on_lineEdit_returnPressed()
{
    on_NextButton_clicked();
}

void bandaFlags::practiceProcedure()
{
    //update progressBar
    int Val = static_cast<int>(((curItem+1)/static_cast<double>(ui->spinBox->value()))*100);
    ui->progressBar->setValue(Val);

    QString answer = ui->lineEdit->text();
    QStringList shouldAnswer = countryListAlt.at(perm.at(curItem)).countryNameAlt;
    bool match = false;
    foreach(QString shAns, shouldAnswer){
        if(QString::compare(answer, shAns, Qt::CaseInsensitive) == 0){
            match = true;
            break;
        }
    }

    //save to alreadyAsked for memory logic
    int countryID = countryListAlt.indexOf(subset.at(curItem));
    //qDebug() << countryID;
    bProf->alreadyAskedIdx[cat].append(countryID);
    //qDebug() << bProf->notGuessedIdx.at(cat).size();
    bProf->notGuessedIdx[cat].removeOne(countryID);
    //qDebug() << bProf->notGuessedIdx.at(cat).size();

    if(match){

        if(hintsUsed[curItem]){
            ui->correctAns->setStyleSheet("color: #FFBF00");
        }else{
            ui->correctAns->setStyleSheet("color: green");
            if(!bProf->correctGuessedIdx[cat].contains(countryID)){
                bProf->correctGuessedIdx[cat].append(countryID);
            }
        }
        ui->correctAns->setText(bandaConst::motivation.at(qrand() % bandaConst::motivation.size()));
        //ui->lineEdit->setStyleSheet("QLineEdit{background: green;}");

    }else{
        //ui->lineEdit->setStyleSheet("QLineEdit{background: red;}");
        ui->correctAns->setStyleSheet("color: red");
        ui->correctAns->setText("Correct Answer:\n" + shouldAnswer.at(0));
    }

    ui->correctAns->show();
    ui->correctAnswerButton->show();
    ui->correctAnswerButton->setFocus();
    ui->buttonFrame->hide();

    //colorTimer->start(1000);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit->setText(QString(""));
    curItem++;

    qDebug() << bProf->alreadyAskedIdx.at(cat).size()
             << bProf->notGuessedIdx.at(cat).size()
             << bProf->correctGuessedIdx.at(cat).size();

}

void bandaFlags::on_hintButton_clicked()
{
    int correctLetters = 0;
    QString curText = ui->lineEdit->text();

    if(QString::compare(curText, curCountry,  Qt::CaseInsensitive)){
        for(int i=0; i < qMin(curText.size(),curCountry.size()); i++){
            if(!QString::compare(curText.at(i),curCountry.at(i), Qt::CaseInsensitive)) correctLetters++;
            else break;
        }
        ui->lineEdit->setText(QString("%1").arg(curCountry.left(correctLetters+1)));
        hintsUsed[curItem] = true;
    }
    ui->lineEdit->setFocus();
}



/*********************************************************
 * TEST MODE
 * *******************************************************/
void bandaFlags::startTest(){

    curLabel = ui->label_2;
    curStatusLabel = ui->testStatusLabel;
    ui->catTestLabel->setText(QString("Test: %1").arg(ui->filterCombo->currentText()));
    ui->difficultyTestLabel->setText(ui->difficultyButtonGroup->checkedButton()->text());
    ui->testCatIcon->setPixmap(QPixmap(getCatPic(ui->filterCombo->currentIndex())).scaled(QSize(ui->practiceCatIcon->size()),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    ui->startButton->setEnabled(false);
    generateSubset();

    testTimer = new QTimer(this);
    connect(testTimer,SIGNAL(timeout()),this,SLOT(updateTestTimer()));
    testTimer->start(msTimeout);

    progressTimer = new QTimer(this);
    connect(progressTimer, SIGNAL(timeout()),this,SLOT(updateTestProgressbar()));

}

void bandaFlags::initTestMode()
{
    sTimeout = msTimeout/1000;
    ui->testProgressBar->setMaximum(sTimeout);
    ui->testProgressBar->setFormat("%v sec");
    ui->testProgressBar->setValue(sTimeout);
    progressTimer->start(1000);
}

void bandaFlags::updateTestTimer()
{
    on_lineEdit_returnPressed();
}

void bandaFlags::updateTestProgressbar()
{
    if(sTimeout >= 1){
        sTimeout--;
        ui->testProgressBar->setValue(sTimeout);
    }else{
        progressTimer->stop();
    }
}

void bandaFlags::updatePauseProgressbar()
{
    if(sTimeout >= 1){
        sTimeout--;
        ui->testProgressBar->setValue(sTimeout);
        progressTimer->start();
    }else{
        progressTimer->stop();
    }
}

//??? Disable enter in test mode - make sure enter is not pressed by accident after next flag shown
// maybe block for the first second?!?
void bandaFlags::on_testLineEdit_returnPressed()
{
    on_NextButton_clicked();
}

void bandaFlags::testProcedure()
{
    testTimer->start(msTimeout);
    initTestMode();

    if(!ui->testLineEdit->text().isEmpty()){
        answers.append(ui->testLineEdit->text());
    }
    else{
        answers.append("");
    }

    ui->testLineEdit->setText(QString(""));
    ui->testLineEdit->setFocus();
    curItem++;
    if(answers.size() == ui->spinBox->value() || subsetCopy.isEmpty()){
        testTimer->stop();
        ui->testProgressBar->hide();
        testResuts();
    }
    else{
        showFlags();
    }
}

void bandaFlags::testResuts()
{
    int right = 0;
    QStringList shouldAnswers;
    for(int i=0; i<answers.size(); i++){
        shouldAnswers.append(countryListAlt.at(perm.at(i)).countryNameAlt.at(0));
        foreach(const QString& ctr, countryListAlt.at(perm.at(i)).countryNameAlt){
            if(ctr == answers.at(i)){
                right++;
                break;
            }
        }
    }

    myResult scores(countryListAlt, perm, picPath, shouldAnswers, answers, hintsUsed, right, ui->spinBox->value(), this);

    //??? how to get scores nicely sized
    scores.setModal(true);
    scores.exec();

    startup();
}

void bandaFlags::on_testPauseBut_clicked()
{
    if(!pauseMode.paused){
        pauseMode.timeRemaining = testTimer->remainingTime();
        pauseMode.progRemaining = progressTimer->remainingTime();
        pauseTimer = new QTimer(this);
        pauseTimer->setInterval(pauseMode.progRemaining);
        pauseTimer->setSingleShot(true);
        connect(pauseTimer,SIGNAL(timeout()),this,SLOT(updatePauseProgressbar()));
        progressTimer->stop();
        testTimer->stop();
        pauseMode.paused = true;
        ui->testLineEdit->setEnabled(false);
        ui->testPauseBut->setText("Continue");
    }else{
        testTimer->start(pauseMode.timeRemaining);
        //progressTimer->start(pauseMode.progRemaining);
        pauseTimer->start();
        ui->testLineEdit->setEnabled(true);
        ui->testPauseBut->setText("&Pause");
        pauseMode.paused = false;
    }
}



/*****************
 * QUIZ MODE
 * **************/
void bandaFlags::startQuiz()
{
    curLabel = ui->quizLabel;
    curStatusLabel = ui->quizStatusLabel;
    ui->catQuizLabel->setText(QString("Quiz: %1").arg(ui->filterCombo->currentText()));
    //ui->startButton->setEnabled(false);
    connect(ui->quizButtonGroup,SIGNAL(buttonClicked(int)),this,SLOT(showNextButton(int)));
    generateQuizSubset();

    resetQuizButtons();
}

void bandaFlags::generateQuizSubset()
{
    for(int i=0; i<ui->spinBox->value() * noOfQuizButtons; i++){
        int randInt = (qrand() % countryListAlt.size());
        if(i % noOfQuizButtons == 0){
            if(!indexUsed.contains(randInt) && countryListAlt.at(randInt).modes.contains(cat)){
                subset.append(countryListAlt.at(randInt));
                perm.append(randInt);
                indexUsed.append(randInt);

            }else{
                i--;
            }
        }
        else{
            if(countryListAlt.at(randInt).modes.contains(cat)){
                falseSubset.append(countryListAlt.at(randInt));
                perm.append(randInt);
            }else{
                i--;
            }
        }
    }

    //make wrong answer situation *** currently Albania Europe ***
//    int wrongCountry = 2;
//    for(int i=0; i<noOfQuizButtons; i++){
//        if(i==0){
//            subset.takeFirst();
//            subset.prepend(countryListAlt.at(wrongCountry));
//        }
//        else{
//            falseSubset.takeAt(i-1);
//            falseSubset.insert(i-1,countryListAlt.at(wrongCountry));
//        }
//        perm.takeAt(i);
//        perm.insert(i,wrongCountry);
//    }

    //make sure all answers are different
    for(int i=0; i<ui->spinBox->value(); i++){
        QList<int> questionInts = perm.mid(i*noOfQuizButtons,noOfQuizButtons);
        for(int j=0; j < noOfQuizButtons; j++){
            if(questionInts.count(questionInts.at(j)) > 1){
                //correct answer first in perm
                if(j != 0){
                    while(true){
                        int randInt = qrand() % countryListAlt.size();
                        if(questionInts.at(0) != randInt && countryListAlt.at(randInt).modes.contains(cat)){
                            falseSubset[i*(noOfQuizButtons-1)+j-1] = countryListAlt.at(randInt);
                            break;
                        }
                    }
                }
            }
        }
    }
    subsetCopy = subset;
}

void bandaFlags::resetQuizButtons(){
    QAbstractButton* checked = ui->quizButtonGroup->checkedButton();
    if (checked)
    {
        ui->quizButtonGroup->setExclusive(false);
        checked->setChecked(false);
        ui->quizButtonGroup->setExclusive(true);
    }
    ui->NextButton->setEnabled(false);
    ui->quizOption1->setText("");
    ui->quizOption2->setText("");
    ui->quizOption3->setText("");
    ui->quizOption4->setText("");
    ui->quizOption5->setText("");
}

void bandaFlags::quizProcedure()
{
    int randInt = (qrand() % noOfQuizButtons);
    QRadioButton* rightBut = static_cast<QRadioButton*>(ui->quizButtonGroup->buttons().at(randInt));
    //qDebug() << rightBut->objectName();
    rightBut->setText(subsetCopy.first().countryNameAlt.at(0));
    quizRightIdx.append(randInt);

    for(int options=0; options < noOfQuizButtons; options++){
        if(ui->quizButtonGroup->buttons().at(options)->text().isEmpty()){
            ui->quizButtonGroup->buttons().at(options)->setText(falseSubset.takeFirst().countryNameAlt.at(0));
        }
    }
}

void bandaFlags::evaluateQuizSelection()
{
    ui->groupBox->setEnabled(false);
    int correctIdx = quizRightIdx.takeFirst();
    int selectedIdx = ui->quizButtonGroup->buttons().indexOf(ui->quizButtonGroup->checkedButton());

    if(correctIdx == selectedIdx){
        ui->quizAnswerLabel->setText(bandaConst::motivation.at(qrand()%bandaConst::motivation.size()));
        ui->quizAnswerLabel->setStyleSheet("color: green");
    }else{
        ui->quizAnswerLabel->setText("Correct solution:\n" + ui->quizButtonGroup->buttons().at(correctIdx)->text());
        ui->quizAnswerLabel->setStyleSheet("color: red");
    }

    curItem++;
    ui->buttonFrame->hide();
    ui->quizOkButton->show();
    ui->quizOkButton->setFocus();
}

void bandaFlags::quizResults()
{

}

void bandaFlags::showNextButton(int)
{
    ui->NextButton->setEnabled(true);
    ui->NextButton->setFocus();
}

void bandaFlags::on_quizOkButton_clicked()
{
    ui->buttonFrame->show();

    if(subsetCopy.isEmpty()){
        quizResults();
        ui->groupBox->setEnabled(false);
        startup();
        //checkRememberCB(ui->correctFlagsCB->isChecked());
    }
    else{
        ui->groupBox->setEnabled(true);
        ui->quizAnswerLabel->setText("");
        ui->quizOkButton->hide();
        resetQuizButtons();
        quizProcedure();
        showFlags();
    }
}

/****************************
 * FUNCTIONS FOR ALL MODES
 * *************************/

void bandaFlags::on_NextButton_clicked()
{
    if(mode == test){
        testProcedure();
    }
    else if(mode == practice){
        practiceProcedure();
    }
    else if(mode == quiz){
        evaluateQuizSelection();
    }
}

void bandaFlags::newGame()
{
    if(mode == test){
        testTimer->stop();
    }

    answers.clear();
    subset.clear();
    subsetCopy.clear();
    hintsUsed.clear();
    perm.clear();
    indexUsed.clear();
    curItem = 0;
    if(ui->radioTest->isChecked()){
        progressTimer->deleteLater();
    }
    falseSubset.clear();
    quizRightIdx.clear();
    ui->startButton->setEnabled(true);
}

void bandaFlags::checkRememberCB(bool checked)
{
    int val = ui->spinBox->value();
    int max = bandaConst::catSpinMax.at(ui->filterCombo->currentIndex());

    if(checked){
        bProf->toggleMemorySize[ui->filterCombo->currentIndex()] = ui->spinBox->value();
        int maxMax = max - bProf->correctGuessedIdx.at(ui->filterCombo->currentIndex()).size();

        if(maxMax > 0){
            if(val>maxMax){
                ui->spinBox->setValue(maxMax);
            }
            ui->spinBox->setMaximum(maxMax);
            ui->startButton->setEnabled(true);
        }else{
            ui->spinBox->setMaximum(0);
            ui->spinBox->setValue(0);
            ui->startButton->setEnabled(false);
        }
    }else{
        ui->spinBox->setMaximum(max);
        //??? how to store previous value
        //ui->spinBox->setValue(bProf->toggleMemorySize[ui->filterCombo->currentIndex()]);
        ui->spinBox->setValue(max);
        bProf->toggleMemorySize[ui->filterCombo->currentIndex()] = 0;
        ui->startButton->setEnabled(true);
    }
}

//generate random testset of size obtained by spinbox
void bandaFlags::generateSubset()
{
    bool filterCB = ui->correctFlagsCB->isChecked();
    for(int i=0; i<ui->spinBox->value(); i++){
        int randInt = (qrand() % countryListAlt.size());
        if(!indexUsed.contains(randInt) && countryListAlt.at(randInt).modes.contains(cat)){
            if(filterCB && bProf->correctGuessedIdx.at(cat).contains(randInt)){
                i--;
            }else{
                perm.append(randInt);
                subset.append(countryListAlt.at(randInt));
                indexUsed.append(randInt);
                hintsUsed.append(false);
                //qDebug() << perm;
            }
        }else{
            i--;
        }
    }
    subsetCopy = subset;
}

void bandaFlags::showFlags()
{
    if(subsetCopy.isEmpty()){
        //ui->stackedWidget->setCurrentIndex(startP);
        startup();
        checkRememberCB(ui->correctFlagsCB->isChecked());
    }
    else{
        ctry akt = subsetCopy.takeFirst();
        curCountry =  akt.countryNameAlt.at(0);
        QString curFlag = picPath + QString("%1").arg(akt.fileName);
        QPixmap px(curFlag);
        curLabel->setPixmap(px);
        curLabel->setFixedSize(px.size());

        curStatusLabel->setText(QString("%1 out of %2").arg(curItem+1).arg(ui->spinBox->value()));
    }
}

/****************************
 * REIMPLEMENT
 * *************************/

void bandaFlags::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Return)
    {
        e->accept();
    }
    else{
        if(mode == quiz && ui->groupBox->isEnabled()){
            if(curQuizButtons.contains(static_cast<Qt::Key>(e->key()))){
                ui->quizButtonGroup->buttons().at(e->key() % Qt::Key_1)->setChecked(true);
                showNextButton(e->key());
            }
        }
        //now pass the keyEvent up to the parent widget,
        QDialog::keyPressEvent(e);
    }
}

void bandaFlags::closeEvent(QCloseEvent*)
{
    saveProfile();
    saveSettings();
    delete bProf;
}


bool bandaFlags::ctry::operator==(const bandaFlags::ctry &other) const
{
    return(other.fileName == this->fileName);
}

/********************
 * BUTTON MAINGROUP
 ********************/

void bandaFlags::on_mainMenuButton_clicked()
{
    saveProfile();
    newGame();
    checkRememberCB(ui->correctFlagsCB->isChecked());
    page = startP;
    updateUI();
}

void bandaFlags::on_changeProfileButton_clicked()
{
    saveProfile();
    startupBool = true;
    newGame();
    page = profileP;
    updateUI();
    bProf->toggleMemorySize.clear();
}

