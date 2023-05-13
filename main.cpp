
#include "plagiarismdetector.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlagiarismDetector w;
    w.show();
    return a.exec();

}
