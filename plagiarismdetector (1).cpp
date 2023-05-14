
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


    // The value of h would be "pow(d, M-1)%q" you set it to this value to guarntee that
    //every combination of alphabet is included, and use modulus to ensure that it doesnot overflow
    //here m is the lenght of the pattern, q is the largets prime integer in c++ as it is Mersenne prime number
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of pattern and first
    // window of text
    for (i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;// this is the same as (p+=pat[i]*pow(d,i))%q
        t = (d * t + txt[i]) % q;// this is the same as (t+=txt[i]*pow(d,i))%q
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



            if (j == M)

            ui->ResultWin->setText("Pattern found at index "+QString::number(i)+"\n");
            counter+=pat.length();
        }

        // Calculate hash value for array of charcter os size m in the text:
        // Remove leading digit, add trailing digit,
        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;// we remove the last digit, and add a new digit for example
            // if we had 12345 with m=3 we will calcuate 123 as above, then we will 234 by removing the 1 and adding 4 without the need to recompute the 23

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
int PlagiarismDetector::hammingDist(string str1, string str2)
{
    int i = 0, count = 0;
    while (str1[i] != '\0')
    {
        if (str1[i] != str2[i])
            count++;
        i++;
    }
    return count;
}
//hamming distance function
//The Hamming distance between two codewords is defined as the number of elements in which they differ,
// so here we  count the number of charcters that differ for the same index in both strings.

void PlagiarismDetector::search(char* pat, char* txt)
{
    int M = strlen(pat);// we calcuate the length of the pattern
    int N = strlen(txt);// we calcuate the length of the txt
    cout<<N<<" "<<M<<endl;
    cout<<pat<<"\n"<<txt<<endl;

    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++) {
        int j;

        /* For current index i, check for pattern match */
        for (j = 0; j < M; j++)
            if (txt[i + j] != pat[j])
                break;
            else if (j == M) // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
                cout << "Pattern found at index " << i<< endl;
    }
}
//naive pattern search algorithm(brute force search)

void PlagiarismDetector::on_checker1_clicked(){

    char inp;
    ifstream input_file;
    input_file.open("C:\\Users\AUC\Documents\PlagiarismDetector\txte.txt");

    string txt;
    while(true)
    {
        if( input_file.eof() ) break;
        input_file>>inp;
        txt.push_back(inp);
    }
    int f=0; int j=f;
    QString user_inpu;
    user_inpu=ui->InputWin->toPlainText();
    std::string user_input = user_inpu.toStdString();
    string x[99]; // depends on the number of sentences of the user , we call 2 size for now
    qDebug()<<"reached this line 1"; int count=0;
    for (int i = 0; i < 99; i++)
    {
        for (int j=f ;  j<user_input.length(); j++)
        {
            if(user_input[j]!='.'){x[i].push_back(user_input[j]); }
            else{ f=j+1; j=user_input.length(); count++;}


        }

    }

    int q = INT_MAX;
    qDebug()<<"reached this line 2"; int counter=0;
    for (int i = 0; i < count; i++)
    {

        search(x[i],txt,q,counter);
    }
    ui->ResultWin->setText(ui->ResultWin->toPlainText()+"/n"+QString::number(user_input.length()/counter*100));

}
void PlagiarismDetector::on_checker2_clicked(){

    ifstream in("/Users/hamdy47/Downloads/C++ Projects/CSII project/CSII project/text.txt");
    string tex((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());

    ifstream inn("/Users/hamdy47/Downloads/C++ Projects/CSII project/CSII project/pattern.txt");
    string patt((istreambuf_iterator<char>(inn)), istreambuf_iterator<char>());

    const int l = tex.length();
    const int length = patt.length();

    string text = tex.c_str();
    string pattern = patt.c_str();
    string word;
    string words[length + 1];
    string delim = "."; // delimiter
    static int c = 0;

    char* txt = new char[l + 1];
    char* pat = new char[length + 1];
    char* pattern0 = new char[length + 1];

    strcpy(pat, pattern.c_str());
    strcpy(txt, text.c_str());

    //Function call
    size_t pos = 0;
    string token1; // define a string variable

    // use find() function to get the position of the delimiters
    while (( pos = pattern.find (delim)) != std::string::npos)
    {
        token1 = pattern.substr(0, pos); // store the substring
        cout << token1 << endl;
        pattern.erase(0, pos + delim.length());  /* erase() function store the current positon and move to next token. */
        words[c] = token1;
        c++;
    }
    words[c] = pattern;
    cout<< pattern << endl; // it print last token of the string.
    c++;

    for(int i = 0; i < c; i++)
    {
        string patt1= words[i];
        strcpy(pattern0, patt1.c_str());
        search(pattern0, txt);
        cout<<"the hamming distance is " << hammingDist(pattern0, text)<<endl;
    }
}



