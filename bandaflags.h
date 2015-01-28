#ifndef BANDAFLAGS_H
#define BANDAFLAGS_H

#include "bandaprofile.h"
#include "bandaprofilestatus.h"

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QList>
#include <QTimer>
#include <QKeyEvent>
#include <QSettings>
#include <QStringListModel>

namespace Ui {
class Dialog;
}

//class bandaPractice;

/*!
 * \brief The bandaFlags class
 */
class bandaFlags : public QDialog
{
    Q_OBJECT
public:
    explicit bandaFlags(QWidget *parent = 0);
    ~bandaFlags();

    struct ctry{
        QString        fileName;
        QList<QString> countryNameAlt;
        QList<int> modes; //entries follow enum Categorie (so 0 -> all, 5 -> Africa)

        bool operator==(const ctry& other) const;
    };

    bandaProfile* bProf;

private:
    //bandaPractice* practiceGame;
    //bandaTest* testGame;
    //bandaQuiz* quizGame;

private slots:
    void on_lineEdit_returnPressed();
    void on_NextButton_clicked();
    void on_startButton_clicked();
    void on_mainMenuButton_clicked();
    void on_changeProfileButton_clicked();

    void on_profileAddBut_clicked();
    void on_profileDeleteBut_clicked();

    void on_hintButton_clicked();
    void on_radioTest_clicked();
    void on_radioPractice_clicked();
    void on_radioQuiz_clicked();
    void on_filterCombo_currentIndexChanged(int index);
    void on_profileStatusBut_clicked();
    void on_correctFlagsCB_toggled(bool checked);


    void on_testLineEdit_returnPressed();
    void showNextButton(int);

    void updateTestTimer();
    void updateTestProgressbar();
    void updatePauseProgressbar();

    void on_correctAnswerButton_clicked();

    void on_quizOkButton_clicked();

    void on_profileView_doubleClicked(const QModelIndex);

    void on_testPauseBut_clicked();

    void on_profileResetBut_clicked();

    void on_statusButton_clicked();

    void on_radioQuiz2P_clicked();

protected:
    Ui::Dialog* ui;

    //option variables
    //enum Style{rounds=0,wiki} style;
    enum Pages{startP=0, practiceP, testP, quizP, profileP, newGameP, quiz2PP} page;
    enum Mode{practice=0, test, quiz, quiz2P} mode;
    enum Categorie{all=0, UN, Easy, Medium, Hard, Africa, Asia, Europe, NorthAm, Oceania, SouthAm} cat;

    QFont bandaFont;
    QSettings* settings;

    //content variables
    QList<QString> answers;             // typed answers
    QString picPath;                    // path to res data
    QList<int> perm;                    // subset indices

    //implemented with categories
    QList<ctry> countryListAlt;
    QList<ctry> subset;
    QList<ctry> subsetCopy;
    QList<int>  indexUsed;
    QString curCountry;
    static int curItem;


    //for all testModes
    QLabel* curLabel;
    QLabel* curStatusLabel;
    QLineEdit* curLineEdit;
    QString profileName;
    QStringListModel* profileModel;
    QStringList storedProfiles;

    //start up vars
    double ratio;
    bool startupBool;
    bool initFlagsBool;

    //practice mode vars
    QList<bool> hintsUsed;              // used hints -> yes: yellow

    // test mode vars
    QTimer* testTimer;
    QTimer* progressTimer;
    QTimer* pauseTimer;
    int msTimeout;
    int sTimeout;
    struct{
        int timeRemaining;
        int progRemaining;
        bool paused;
    }pauseMode;

    //quiz mode vars
    QList<ctry> falseSubset;
    QList<int> quizRightIdx;
    int noOfQuizButtons;
    QList<Qt::Key> curQuizButtons;


private:
    //methods
    void updateUI();
    void saveProfile();
    void resetProfile();
    void loadProfile();
    void loadProfiles();
    void loadSettings();
    void saveSettings();
    void startup();
    void parseOptions();
    void initFiles();
    void createProfile();
    void generateSubset();

    void startPractise();
    void showProfileStatus();
    void practiceProcedure();
    void startTest();
    void initTestMode();
    void testProcedure();
    void startQuiz();
    void resetQuizButtons();
    void generateQuizSubset();
    void quizProcedure();
    void evaluateQuizSelection();
    void quizResults();
    void testResuts();
    void showFlags();
    void newGame();
    void checkRememberCB(bool checked);

    //reimplement enter event
    void keyPressEvent(QKeyEvent* e);
    void closeEvent(QCloseEvent *);

    //aux
    QString getCatPic(int index);
};

Q_DECLARE_METATYPE( QList<int> )

//Beta stadium
///*!
// * \brief The bandaPractice class
// */
//class bandaPractice : public bandaFlags{
//    Q_OBJECT

//public:
//    explicit bandaPractice(QWidget* parent=0);
//    ~bandaPractice();

//    void startPractise();
//};

///*!
// * \brief The bandaTest class
// */
//class bandaTest : public bandaFlags{
//    Q_OBJECT
//public:

//    explicit bandaTest(QWidget* parent=0);
//    ~bandaTest();
//};


///*!
// * \brief The bandaQuiz class
// */
//class bandaQuiz : public bandaFlags{
//    Q_OBJECT

//public:
//    explicit bandaQuiz(QWidget* parent=0);
//    ~bandaQuiz();
//};


#endif // BANDAFLAGS_H
