#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <chrono>
#include "Document.h"
#include "PlagiarismDetector.h"

using namespace std;
using namespace std::chrono;

int main() {
    // Create an input file stream for corpus documents
    ifstream corpusFile("corpus.txt");
    if (!corpusFile) {
        cerr << "Error opening corpus file." << endl;
        return 1;
    }

    // Read corpus documents from the file
    vector<Document> corpus;
    string title, content;
    while (getline(corpusFile, title) && getline(corpusFile, content)) {
        corpus.emplace_back(title, content);
    }
    corpusFile.close();

    // Create an input file stream for the potential plagiarized document
    ifstream potentialFile("potential.txt");
    if (!potentialFile) {
        cerr << "Error opening potential document file." << endl;
        return 1;
    }

    // Read the potential plagiarized document from the file
    getline(potentialFile, title);
    getline(potentialFile, content);
    potentialFile.close();

    // Create an instance of PlagiarismDetector
    PlagiarismDetector detector(corpus, Document(title, content));

    // Perform plagiarism detection using all implemented algorithms
    detector.performPlagiarismDetection();

    return 0;
}
