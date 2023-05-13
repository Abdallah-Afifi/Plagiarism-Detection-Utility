#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <sstream>
#include "PlagiarismDetector.h"

using namespace std;
using namespace std::chrono;

PlagiarismDetector::PlagiarismDetector(const vector<Document>& corpus, const Document& potentialDocument)
    : corpus(corpus), potentialDocument(potentialDocument) {}

int PlagiarismDetector::hammingDistance(const string& str1, const string& str2) const {
    int len1 = str1.length();
    int len2 = str2.length();
    int distance = 0;

    if (len1 != len2) {
        cerr << "Error: Hamming distance can only be computed for strings of equal length." << endl;
        return -1;
    }

    for (int i = 0; i < len1; ++i) {
        if (str1[i] != str2[i]) {
            distance++;
        }
    }

    return distance;
}

void PlagiarismDetector::approximateStringMatchingBruteForce() const {
 cout << "Approximate String Matching using Brute Force and Hamming Distance:\n";

        string potentialContent = potentialDocument.getContent();
        int potentialLength = potentialContent.length();

        auto start = high_resolution_clock::now(); // Start measuring execution time

        for (const auto& doc : corpus) {
            string docContent = doc.getContent();
            int docLength = docContent.length();

            for (int i = 0; i <= docLength - potentialLength; i++) {
                string substring = docContent.substr(i, potentialLength);
                int distance = hammingDistance(substring, potentialContent);

                if (distance != -1) {
                    double similarity = 1.0 - static_cast<double>(distance) / potentialLength;
                    if (similarity >= 0.75) {
                        cout << "Potential plagiarism found in document: " << doc.getTitle() << endl;
                        break; // Move to the next document
                    }
                }
            }
        }

        auto end = high_resolution_clock::now(); // Stop measuring execution time
        auto durationmic = duration_cast<microseconds>(end - start);

        cout << "Execution time: " << durationmic.count() << " microseconds" << endl;

        auto durationmil = duration_cast<milliseconds>(end - start);

        cout << "Execution time: " << durationmil.count() << " milliseconds" << endl;
        cout << endl;
}

void PlagiarismDetector::rabinKarp() const {
cout << "String Matching using Rabin-Karp Algorithm:\n";

        string potentialContent = potentialDocument.getContent();
        int potentialLength = potentialContent.length();
        const int prime = 101; // A prime number for hash function

        long long potentialHash = 0;
        long long docHash = 0;
        long long primePower = 1;

        auto start = high_resolution_clock::now(); // Start measuring execution time

        for (int i = 0; i < potentialLength; i++) {
            potentialHash = (potentialHash + potentialContent[i]) % prime;
            docHash = (docHash + corpus[0].getContent()[i]) % prime;
            if (i > 0)
                primePower = (primePower * 256) % prime;
        }

        for (const auto& doc : corpus) {
            string docContent = doc.getContent();
            int docLength = docContent.length();

            for (int i = 0; i <= docLength - potentialLength; i++) {
                if (potentialHash == docHash) {
                    if (docContent.substr(i, potentialLength) == potentialContent) {
                        cout << "Potential plagiarism found in document: " << doc.getTitle() << endl;
                        break; // Move to the next document
                    }
                }

                if (i < docLength - potentialLength) {
                    docHash = (256 * (docHash - docContent[i] * primePower) + docContent[i + potentialLength]) % prime;
                    if (docHash < 0)
                        docHash += prime;
                }
            }
        }

        auto end = high_resolution_clock::now(); // Stop measuring execution time
        auto durationmic = duration_cast<microseconds>(end - start);

        cout << "Execution time: " << durationmic.count() << " microseconds" << endl;

        auto durationmil = duration_cast<milliseconds>(end - start);

        cout << "Execution time: " << durationmil.count() << " milliseconds" << endl;
        cout << endl;
}

void PlagiarismDetector::knuthMorrisPratt() const {
    cout << "String Matching using Knuth-Morris-Pratt (KMP) Algorithm:\n";

        string potentialContent = potentialDocument.getContent();
        int potentialLength = potentialContent.length();

        auto start = high_resolution_clock::now(); // Start measuring execution time

        for (const auto& doc : corpus) {
            string docContent = doc.getContent();
            int docLength = docContent.length();

            // Preprocess the potential pattern to calculate the longest proper prefix that is also a suffix
            vector<int> lps(potentialLength);
            int len = 0; // Length of the previous longest prefix suffix
            int i = 1;

            while (i < potentialLength) {
                if (potentialContent[i] == potentialContent[len]) {
                    len++;
                    lps[i] = len;
                    i++;
                }
                else {
                    if (len != 0) {
                        len = lps[len - 1];
                    }
                    else {
                        lps[i] = 0;
                        i++;
                    }
                }
            }

            int j = 0; // Index for potentialContent[]
            int count = 0; // Number of occurrences

            while (j < docLength) {
                if (potentialContent[count] == docContent[j]) {
                    count++;
                    j++;
                }

                if (count == potentialLength) {
                    cout << "Potential plagiarism found in document: " << doc.getTitle() << endl;
                    break; // Move to the next document
                }

                // Mismatch after count matches
                else if (j < docLength && potentialContent[count] != docContent[j]) {
                    if (count != 0)
                        count = lps[count - 1];
                    else
                        j++;
                }
            }
        }

        auto end = high_resolution_clock::now(); // Stop measuring execution time
        auto durationmic = duration_cast<microseconds>(end - start);

        cout << "Execution time: " << durationmic.count() << " microseconds" << endl;

        auto durationmil = duration_cast<milliseconds>(end - start);

        cout << "Execution time: " << durationmil.count() << " milliseconds" << endl;
        cout << endl;
}

void PlagiarismDetector::boyerMoore() const {
    cout << "String Matching using Boyer-Moore Algorithm:\n";

        string potentialContent = potentialDocument.getContent();
        int potentialLength = potentialContent.length();

        auto start = high_resolution_clock::now(); // Start measuring execution time

        for (const auto& doc : corpus) {
            string docContent = doc.getContent();
            int docLength = docContent.length();

            // Preprocess the potential pattern to calculate the rightmost occurrence of each character
            vector<int> rightmost(256, -1);
            for (int i = 0; i < potentialLength; i++) {
                rightmost[static_cast<int>(potentialContent[i])] = i;
            }

            int j = 0; // Index for potentialContent[]
            int count = 0; // Number of occurrences

            while (j <= docLength - potentialLength) {
                int k = potentialLength - 1;
                while (k >= 0 && potentialContent[k] == docContent[j + k]) {
                    k--;
                }

                if (k == -1) {
                    cout << "Potential plagiarism found in document: " << doc.getTitle() << endl;
                    break; // Move to the next document
                }
                else {
                    int shift = k - rightmost[static_cast<int>(docContent[j + k])];
                    j += max(1, shift);
                }
            }
        }

        auto end = high_resolution_clock::now(); // Stop measuring execution time
       
        auto durationmic = duration_cast<microseconds>(end - start);

        cout << "Execution time: " << durationmic.count() << " microseconds" << endl;
        
        auto durationmil = duration_cast<milliseconds>(end - start);

        cout << "Execution time: " << durationmil.count() << " milliseconds" << endl;
        cout << endl;
}

void PlagiarismDetector::BasicAlgorithm() const {
    cout << "String Matching using a Basic Algorithm:\n";


        string potentialContent = potentialDocument.getContent();



        auto start = high_resolution_clock::now();	// Start measuring execution time

        for (const auto& document : corpus)
        {

            string documentContent = document.getContent();


            if (documentContent.find(potentialContent) !=
                string::npos)
            {

                cout << "Matches found in document: " << document.
                    getTitle() << endl;

            }
        }


        auto end = high_resolution_clock::now();	// Stop measuring execution time
        auto durationmic = duration_cast <microseconds> (end - start);


        cout << "Execution time: " << durationmic.count() << " microseconds" << endl;	// Corrected the time unit

        auto durationmil = duration_cast <milliseconds> (end - start);


        cout << "Execution time: " << durationmil.
            count() << " milliseconds" << endl;

        cout << endl;
}


void PlagiarismDetector::nGramAnalysis() const {
    cout << "Plagiarism Detection using N-gram Analysis:\n";

    int n = 3; // Number of consecutive characters in each n-gram

    string potentialContent = potentialDocument.getContent();

    auto start = high_resolution_clock::now(); // Start measuring execution time

    for (const auto& doc : corpus) {
        string docContent = doc.getContent();

        // Generate n-grams for the potential document
        vector<string> potentialNGrams;
        for (int i = 0; i <= potentialContent.length() - n; i++) {
            string ngram = potentialContent.substr(i, n);
            potentialNGrams.push_back(ngram);
        }

        // Generate n-grams for the current document
        vector<string> docNGrams;
        for (int i = 0; i <= docContent.length() - n; i++) {
            string ngram = docContent.substr(i, n);
            docNGrams.push_back(ngram);
        }

        // Count the number of common n-grams
        int commonNGrams = 0;
        for (const auto& ngram : potentialNGrams) {
            if (find(docNGrams.begin(), docNGrams.end(), ngram) != docNGrams.end()) {
                commonNGrams++;
            }
        }

        // Calculate similarity based on the Jaccard coefficient
        double similarity = static_cast<double>(commonNGrams) / (potentialNGrams.size() + docNGrams.size() - commonNGrams);

        if (similarity >= 0.75) {
            cout << "Potential plagiarism found in document: " << doc.getTitle() << endl;
        }
    }

    auto end = high_resolution_clock::now(); // Stop measuring execution time
    auto durationmic = duration_cast<microseconds>(end - start);

    cout << "Execution time: " << durationmic.count() << " microseconds" << endl;

    auto durationmil = duration_cast<milliseconds>(end - start);

    cout << "Execution time: " << durationmil.count() << " milliseconds" << endl;
    cout << endl;
}

void PlagiarismDetector::cosineSimilarity() const {
    cout << "Plagiarism Detection using Cosine Similarity:\n";

    string potentialContent = potentialDocument.getContent();

    auto start = high_resolution_clock::now(); // Start measuring execution time

    // Calculate the term frequency (TF) for the potential document
    map<string, int> potentialTF;
    stringstream ss(potentialContent);
    string word;
    while (ss >> word) {
        potentialTF[word]++;
    }

    for (const auto& doc : corpus) {
        string docContent = doc.getContent();

        // Calculate the term frequency (TF) for the current document
        map<string, int> docTF;
        stringstream ss(docContent);
        string word;
        while (ss >> word) {
            docTF[word]++;
        }

        // Calculate the dot product of the potential document and the current document
        double dotProduct = 0;
        for (const auto& pair : potentialTF) {
            const string& word = pair.first;
            int potentialTermFreq = pair.second;
            int docTermFreq = docTF[word];
            dotProduct += (potentialTermFreq * docTermFreq);
        }

        // Calculate the magnitude of the potential document vector
        double potentialMagnitude = 0;
        for (const auto& pair : potentialTF) {
            int termFreq = pair.second;
            potentialMagnitude += (termFreq * termFreq);
        }
        potentialMagnitude = sqrt(potentialMagnitude);

        // Calculate the magnitude of the current document vector
        double docMagnitude = 0;
        for (const auto& pair : docTF) {
            int termFreq = pair.second;
            docMagnitude += (termFreq * termFreq);
        }
        docMagnitude = sqrt(docMagnitude);

        // Calculate the cosine similarity between the potential document and the current document
        double similarity = dotProduct / (potentialMagnitude * docMagnitude);

        if (similarity >= 0.75) {
            cout << "Potential plagiarism found in document: " << doc.getTitle() << endl;
        }
    }

    auto end = high_resolution_clock::now(); // Stop measuring execution time
    auto durationmic = duration_cast<microseconds>(end - start);

    cout << "Execution time: " << durationmic.count() << " microseconds" << endl;

    auto durationmil = duration_cast<milliseconds>(end - start);

    cout << "Execution time: " << durationmil.count() << " milliseconds" << endl;
    cout << endl;
}

void PlagiarismDetector::levenshteinDistance() const {
    cout << "Plagiarism Detection using Levenshtein Distance:\n";

    string potentialContent = potentialDocument.getContent();

    auto start = high_resolution_clock::now(); // Start measuring execution time

    for (const auto& doc : corpus) {
        string docContent = doc.getContent();

        // Calculate the Levenshtein Distance between the potential document and the current document
        int potentialLength = potentialContent.length();
        int docLength = docContent.length();

        // Create a matrix to store the Levenshtein Distance values
        vector<vector<int>> distanceMatrix(potentialLength + 1, vector<int>(docLength + 1, 0));

        // Initialize the first row and column of the matrix
        for (int i = 0; i <= potentialLength; ++i) {
            distanceMatrix[i][0] = i;
        }
        for (int j = 0; j <= docLength; ++j) {
            distanceMatrix[0][j] = j;
        }

        // Calculate the Levenshtein Distance for each cell in the matrix
        for (int i = 1; i <= potentialLength; ++i) {
            for (int j = 1; j <= docLength; ++j) {
                if (potentialContent[i - 1] == docContent[j - 1]) {
                    distanceMatrix[i][j] = distanceMatrix[i - 1][j - 1];
                }
                else {
                    distanceMatrix[i][j] = 1 + min({ distanceMatrix[i - 1][j], distanceMatrix[i][j - 1], distanceMatrix[i - 1][j - 1] });
                }
            }
        }

        // Check if the Levenshtein Distance is below a threshold (e.g., 10)
        int threshold = 10;
        if (distanceMatrix[potentialLength][docLength] <= threshold) {
            cout << "Potential plagiarism found in document: " << doc.getTitle() << endl;
        }
    }

    auto end = high_resolution_clock::now(); // Stop measuring execution time
    auto durationmic = duration_cast<microseconds>(end - start);

    cout << "Execution time: " << durationmic.count() << " microseconds" << endl;

    auto durationmil = duration_cast<milliseconds>(end - start);

    cout << "Execution time: " << durationmil.count() << " milliseconds" << endl;
    cout << endl;
}




void PlagiarismDetector::performPlagiarismDetection() const {
    auto start = high_resolution_clock::now();

    // Perform plagiarism detection using all implemented algorithms
    approximateStringMatchingBruteForce();
    rabinKarp();
    knuthMorrisPratt();
    boyerMoore();
    BasicAlgorithm();
    nGramAnalysis();
    cosineSimilarity();
    levenshteinDistance();

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "The process of Plagiarism Detection using all the algorithms completed in " << duration.count() << " microseconds." << endl;
}
