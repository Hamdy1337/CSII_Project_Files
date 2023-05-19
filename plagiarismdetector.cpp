#include "plagiarismdetector.h"
#include "ui_plagiarismdetector.h"
#include "QDebug"
#define d 256

PlagiarismDetector::PlagiarismDetector(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlagiarismDetector)
{
    ui->setupUi(this);
}

void PlagiarismDetector::search(string pat, string txt, int q, int &counter)
{

    int M = pat.length();
    int N = txt.length();
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of pattern and first
    // window of text
    for (i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++) {

        // Check the hash values of current window of text
        // and pattern. If the hash values match then only
        // check for characters one by one
        if (p == t) {
            /* Check for characters one by one */
            for (j = 0; j < M; j++) {
                if (txt[i + j] != pat[j]) {
                    j=M;
                }
            }

            // if p == t and pat[0...M-1] = txt[i, i+1,
            // ...i+M-1]

            if (j == M)

            ui->ResultWin->setText(ui->ResultWin->toPlainText()+"pattern found at index "+QString::number(i)+"\n");
            counter+= M;        }

        // Calculate hash value for next window of text:
        // Remove leading digit, add trailing digit
        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;

            // We might get negative value of t, converting
            // it to positive
            if (t < 0)
                t = (t + q);
        }
    }
}

PlagiarismDetector::~PlagiarismDetector()
{
    delete ui;
}
void PlagiarismDetector::hammingDist(string str1, string str2)
{
    float i = 0, count = 0;
    int percentage = 0;
    while (str1[i] != '\0')
    {
        if (str1[i] != str2[i])
            count++;
        i++;
    }
    cout<< count << " "<<i<<endl;
    percentage = 100-(count/i)*100 ;
    cout<<"percentage plagiarized by hamming distance = " << percentage<< "%" << endl;
}
//hamming distance function
//The Hamming distance between two codewords is defined as the number of elements in which they differ,
// so here we  count the number of charcters that differ for the same index in both strings.

void PlagiarismDetector::search(char* pat, char* txt, int &counter, int &counter1)
{
    int M = strlen(pat);
    int N = strlen(txt);
    counter1 += M;
    int perecentage = 0;

    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++) {
        int j;

        /* For current index i, check for pattern match */
        for (j = 0; j < M; j++)
            if (txt[i + j] != pat[j])
                break;

        if (j == M)
        {// if pat[0...M-1] = txt[i, i+1, ...i+M-1]
            ui->ResultWin->setText(ui->ResultWin->toPlainText()+"pattern found at index "+QString::number(i)+"\n");
            counter+= M;

        }

    }
   // ui->ResultWin->setText(ui->ResultWin->toPlainText()+QString::number(counter)+"\n");



}
//naive pattern search algorithm(brute force search)

void PlagiarismDetector::on_checker1_clicked(){

    char inp;
    ifstream input_file;
    input_file.open("/Users/hamdy47/Downloads/Qt/txte.txt");

    string txt;
    while(true)
    {
        if( input_file.eof() ) break;
        input_file>>inp;
        txt.push_back(inp);
    }
    int j=0, f = 0;
    QString user_inpu;
    user_inpu=ui->InputWin->toPlainText();
    std::string user_input = user_inpu.toStdString();
    string x[2]; // depends on the number of sentences of the user , we call 2 size for now
     int count=0;
    for (int i = 0; i < 2; i++)
    {
        for (j=f;  j< user_input.length(); j++)
        {
            if(user_input[j]!='.'){x[i].push_back(user_input[j]); }
            else{  f=j+1; j=user_input.length(); count++;}


        }

    }

    int q = INT_MAX;
    int counter=0;cout<<count;
    for (int i = 0; i < count; i++)
    {

        search(x[i],txt,q,counter);
    }
    ui->ResultWin->setText(ui->ResultWin->toPlainText()+"\n"+"The plagiarism percentage is "+QString::number(100.0*(counter+1)/user_input.length())+"\n");

}
void PlagiarismDetector::on_checker2_clicked(){


//    if(ui->comboBox->currentIndex() == 0)
//    {


//        ifstream in("/Users/hamdy47/Downloads/Qt/text.txt");
//        string text((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());


//        ifstream inn("/Users/hamdy47/Downloads/Qt/pattern.txt");
//            string pattern((istreambuf_iterator<char>(inn)), istreambuf_iterator<char>());
//    }
//    else
//    {
//        ifstream in("/Users/hamdy47/Downloads/Qt/text.txt");
//            string text((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());

//        ifstream inn("/Users/hamdy47/Downloads/Qt/pattern.txt");
//            string pattern((istreambuf_iterator<char>(inn)), istreambuf_iterator<char>());
//    }

ifstream in("/Users/hamdy47/Downloads/Qt/text.txt");
string text((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
ifstream inn("/Users/hamdy47/Downloads/Qt/pattern.txt");
string pattern((istreambuf_iterator<char>(inn)), istreambuf_iterator<char>());

    const int l = text.length();
    const int length = pattern.length();

    string word;
    string sentences[length + 1];
    string delim = "."; // delimiter
    static int c = 0;
    int count = 0;
    int counter1 = 0;

    char* txt = new char[l + 1];
    char* patt = new char[length + 1];
    char* pattern0 = new char[length + 1];

    //    strcpy(patt, pattern.c_str());
    strcpy(txt, text.c_str());
    strcpy(patt, pattern.c_str());


    string token1;
    size_t pos = 0;
    //Function call
    // define a string variable

    // use find() function to get the position of the delimiters
    while (( pos = pattern.find (delim)) != std::string::npos)
    {


        token1 = pattern.substr(0, pos); // store the substring
        cout << token1 << endl;

        pattern.erase(0, pos + delim.length());  /* erase() function store the current positon and move to next token. */
        sentences[c] = token1;
        c++;
    }
    sentences[c] = pattern;
    cout<< pattern << endl; // it print last token of the string.
    c++;

    for(int i = 0; i < c - 1; i++)
    {
        string patt1 = sentences[i];
        strcpy(pattern0, patt1.c_str());
        search(pattern0, txt, count, counter1);
        hammingDist(text, pattern);
        cout<<c<<endl;
    }
    int percentage = (100.0*count/counter1) ;
    ui->ResultWin->setText(ui->ResultWin->toPlainText()+"percentage plagiarized = "+QString::number(percentage)+"%"+"\n");

}
