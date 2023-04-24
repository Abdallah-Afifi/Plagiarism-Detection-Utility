# Plagiarism-Detector

# Architecture Design

Class: Document

Description: Represents a document in the corpus.

Properties:

text: string, the content of the document

id: integer, unique identifier for the document

Methods:

getText(): returns the text of the document

getId(): returns the ID of the document



Class: Corpus

Description: Represents the collection of existing documents.

Properties:

documents: list of Document objects, the collection of documents in the corpus

Methods:

addDocument(document: Document): adds a document to the corpus

getDocument(id: integer): returns the document with the specified ID



Class: PlagiarismDetector

Description: Represents the plagiarism detection utility.

Properties:

corpus: Corpus object, the collection of existing documents

testDoc: Document object, the potentially plagiarized document

Methods:

setCorpus(corpus: Corpus): sets the corpus for the detector

setTestDoc(document: Document): sets the potentially plagiarized document for the detector

detectPlagiarism(algorithm: string): finds the documents from which the potential document was plagiarized using the specified algorithm



Class: BruteForceDetector

Description: Implements the Brute Force algorithm for string matching.

Methods:

detectPlagiarism(testDoc: Document, corpus: Corpus): finds the documents from which the potential document was plagiarized using Brute Force algorithm and returns a list of matching documents



Class: RabinKarpDetector

Description: Implements the Rabin-Karp algorithm for string matching.

Methods:

detectPlagiarism(testDoc: Document, corpus: Corpus): finds the documents from which the potential document was plagiarized using Rabin-Karp algorithm and returns a list of matching documents



Class: PerformanceComparator

Description: Compares the performance of the implemented algorithms.

Methods:

compare(algorithm1: string, algorithm2: string, testDoc: Document, corpus: Corpus): compares the performance of two algorithms on a given test document and corpus and returns the results


# Development Workflow

Define the classes and their properties and methods, as given in the architecture design.

Implement the Document class, including the getText() and getId() methods.

Implement the Corpus class, including the addDocument() and getDocument() methods.

Implement the BruteForceDetector class, including the detectPlagiarism() method using the Brute Force algorithm.

Implement the RabinKarpDetector class, including the detectPlagiarism() method using the Rabin-Karp algorithm.

Implement the PlagiarismDetector class, including the setCorpus(), setTestDoc(), and detectPlagiarism() methods.

Implement the PerformanceComparator class, including the compare() method.

Test the classes individually to ensure they work correctly.

Integrate the classes together to test the plagiarism detection system as a whole.

Optimize the system for better performance, if necessary.

Deploy the system and provide documentation and user instructions.

Continue to maintain and update the system as needed.
