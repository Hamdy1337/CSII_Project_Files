
#ifndef PLAGIARISMDETECTOR_H
#define PLAGIARISMDETECTOR_H

#include <QMainWindow>
#include <fstream>
#include <iostream>

using namespace std;



QT_BEGIN_NAMESPACE
namespace Ui { class PlagiarismDetector; }
QT_END_NAMESPACE

class PlagiarismDetector : public QMainWindow

{
    Q_OBJECT

public:
    PlagiarismDetector(QWidget *parent = nullptr);
    ~PlagiarismDetector();
    void search(string pat, string txt, int q, int &counter);
    void hammingDist(string str1, string str2);
    void search(char* pat, char* txt, int &counter, int &counter1);

private slots:
    void on_checker1_clicked();
    void on_checker2_clicked();


private:
    Ui::PlagiarismDetector *ui;
};

#endif // PLAGIARISMDETECTOR_H
