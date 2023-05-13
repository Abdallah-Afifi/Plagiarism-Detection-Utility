#ifndef PLAGIARISMDETECTOR_H
#define PLAGIARISMDETECTOR_H

#include <vector>
#include "Document.h"

class PlagiarismDetector {
private:
    std::vector<Document> corpus;
    Document potentialDocument;

public:
    PlagiarismDetector(const std::vector<Document>& corpus, const Document& potentialDocument);

    int hammingDistance(const std::string& str1, const std::string& str2) const;
    void approximateStringMatchingBruteForce() const;
    void rabinKarp() const;
    void knuthMorrisPratt() const;
    void boyerMoore() const;
    void BasicAlgorithm() const;
    void nGramAnalysis() const;
    void cosineSimilarity() const;
    void levenshteinDistance() const;
    void performPlagiarismDetection() const;
};

#endif // PLAGIARISMDETECTOR_H
