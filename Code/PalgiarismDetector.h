#ifndef _PALGIARISMDETECTOR_H
#define _PALGIARISMDETECTOR_H

class PalgiarismDetector {
public: 
void setCorpus(Corpus corpus);
void setTestDoc(Document document);
void detectPalgiarism(string algorithm);

private: 
    Corpus corpus;
    Document testDoc;
};

#endif //_PALGIARISMDETECTOR_H
