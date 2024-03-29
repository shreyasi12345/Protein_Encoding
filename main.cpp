#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <omp.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <map>
#include <array>
#include <vector>
#include <set>
#include "encoder.cpp"
#include <chrono>
#include <numeric>
#include <math.h>
using namespace std;
using namespace std::chrono;

#if defined(WIN32) || defined(_WIN32) || defined __CYGWIN__
    #define PATH_SEPARATOR "\\" 
#else 
    #define PATH_SEPARATOR "/" 
#endif 

void printHelp()
{
    cout << "Main usage:" << endl;
    cout << "  Required arguments: -i <input file> -o <output file> -e <encoding> [options]" << endl;
    cout << "  Suggested argument: --threads <integer>, default 1. Number of threads. Usually double the number of available cores." << endl;
    cout << "  Other arguments: --crop. Recommended for descriptors that need all sequences to have the same length. Crops all sequences to the length of the shortest sequence in the input FASTA file." << endl;
    cout << "Options per encoding:" << endl;
    cout << "  - AAC" << endl;
    cout << "  - EAAC: All input sequences must be the same length and it must be equal or greater than the window size." << endl;
    cout << "    --window <integer>, default: 5. window > 0." << endl;
    cout << "  - CKSAAP: All input sequences length must be equal or greater than the gap size + 2." << endl;
    cout << "    --gap <integer>, default: 5. gap >= 0." << endl;
    cout << "  - DPC: All sequences length must be equal or greater than 2." << endl;
    cout << "  - TPC: All sequences length must be equal or greater than 3" << endl;
    cout << "  - DDE" << endl;
    cout << "  - AAPAS" << endl;
    cout << "  - CMV" << endl;
    cout << "  - GAAC" << endl;
    cout << "  - EGAAC: All input sequences length must be equal or greater than the window size." << endl;
    cout << "    --window <integer>, default: 5. window > 0." << endl;
    cout << "  - CKSAAGP: All input sequences length must be equal or greater than the gap size + 2." << endl;
    cout << "    --gap <integer>, default: 5. gap >= 0." << endl;
    cout << "  - GDPC" << endl;
    cout << "  - GTPC" << endl;
    cout << "  - EBGW" << endl;
    cout << "    --k <integer>, default: 20.  > 0." << endl;
    cout << "  - Moran: All input sequences length must be equal or greater than lag + 1." << endl;
    cout << "    --lag <integer>, default: 30. lag > 0." << endl;
    cout << "    --indices <string>, default: CIDH920105,BHAR880101,CHAM820101,CHAM820102,CHOC760101,BIGC670101,CHAM810101,DAYM780201. Must be a comma-separated string with no spaces. Valid indices are found in the data/AAIdx.txt file." << endl;
    cout << "  - Geary: All input sequences length must be equal or greater than lag + 1." << endl;
    cout << "    --lag <integer>, default: 30. lag > 0." << endl;
    cout << "    --indices <string>, default: CIDH920105,BHAR880101,CHAM820101,CHAM820102,CHOC760101,BIGC670101,CHAM810101,DAYM780201. Must be a comma-separated string with no spaces. Valid indices are found in the data/AAIdx.txt file." << endl;
    cout << "  - NMB: All input sequences length must be equal or greater than lag + 1." << endl;
    cout << "    --lag <integer>, default: 30. lag > 0." << endl;
    cout << "    --indices <string>, default: CIDH920105,BHAR880101,CHAM820101,CHAM820102,CHOC760101,BIGC670101,CHAM810101,DAYM780201. Must be a comma-separated string with no spaces. Valid indices are found in the data/AAIdx.txt file." << endl;
    cout << "  - CTDC" << endl;
    cout << "  - CTDT" << endl;
    cout << "  - CTDD" << endl;
    cout << "  - CT: All sequences length must be equal or greater than 3." << endl;
    cout << "  - KSCT: All sequences length must be equal or greater than (2 * k) + 3." << endl;
    cout << "    --k <integer>, default: 1. k > 0." << endl;
    cout << "  - QSO: All sequences length must be equal or greater than lag + 1." << endl;
    cout << "    --lag <integer>, default: 30. lag > 0." << endl;
    cout << "    --weight <float>, default: 0.1. 0 < weight < 1." << endl;
    cout << "  - SOCN: All sequences length must be equal or greater than lag + 1." << endl;
    cout << "    --lag <integer>, default: 30. lag > 0." << endl;
    cout << "  - PAAC: All sequences length must be equal or greater than lag + 1." << endl;
    cout << "    --lag <integer>, default: 30. lag > 0." << endl;
    cout << "    --weight <float>, default: 0.05. 0 < weight < 1." << endl;
    cout << "  - APAAC: All sequences length must be equal or greater than lag + 1." << endl;
    cout << "    --lag <integer>, default: 30. lag > 0." << endl;
    cout << "    --weight <float>, default: 0.05. 0 < weight < 1." << endl;
    cout << "  - AAI: All sequences must be the same length." << endl;
    cout << "  - BLOSUM62: All sequences must be the same length." << endl;
    cout << "  - ZS: All sequences must be the same length." << endl;
    cout << "  - Binary: All sequences must be the same length." << endl;
    cout << "  - TVD: All sequences must be the same length" << endl;
    cout << "  - SSEB: All sequences must be the same length." << endl;
    cout << "    --path <dirPath>, REQUIRED. Path where .ss2, .spd33 or .spXout files are located, one per input sequence. .ss2 files are generated by PSIPRED, .spd33 files are generated by SPIDER3-Single, .spXout files are generated by SPINE-X." << endl;
    cout << "  - SSEC" << endl;
    cout << "    --path <dirPath>, REQUIRED. Path where .ss2, .spd33 or .spXout files are located, one per input sequence. .ss2 files are generated by PSIPRED, .spd33 files are generated by SPIDER3-Single, .spXout files are generated by SPINE-X." << endl;
    cout << "  - SSPB" << endl;
    cout << "    --path <dirPath>, REQUIRED. Path where .ss2, .spd33 or .spXout files are located, one per input sequence. .ss2 files are generated by PSIPRED, .spd33 files are generated by SPIDER3-Single, .spXout files are generated by SPINE-X." << endl;
    cout << "    --n <integer>, default: 1. n > 0." << endl;
    cout << "  - SSPAC" << endl;
    cout << "    --path <dirPath>, REQUIRED. Path where .ss2, .spd33 or .spXout files are located, one per input sequence. .ss2 files are generated by PSIPRED, .spd33 files are generated by SPIDER3-Single, .spXout files are generated by SPINE-X." << endl;
    cout << "    --n <integer>, default: 10. n > 0." << endl;
    cout << "  - Disorder: All sequences must be the same length." << endl;
    cout << "    --path <dirPath>, REQUIRED. Path where .csv disorder files are located, one per input sequence. .csv disorder files are generated by SPOT-1D." << endl;
    cout << "  - DisorderB: All sequences must be the same length." << endl;
    cout << "    --path <dirPath>, REQUIRED. Path where .csv disorder files are located, one per input sequence. .csv disorder files are generated by SPOT-1D." << endl;
    cout << "  - DisorderC" << endl;
    cout << "    --path <dirPath>, REQUIRED. Path where .csv disorder files are located, one per input sequence. .csv disorder files are generated by SPOT-1D." << endl;
    cout << "  - TA: All sequences must be the same length." << endl;
    cout << "    --path <dirPath>, REQUIRED. Path where .spd33 or .spXout files are located, one per input sequence. .spd33 files are generated by SPIDER3-Single, .spXout files are generated by SPINE-X." << endl;
    cout << "  - TAC" << endl;
    cout << "    --path <dirPath>, REQUIRED. Path where .spd33 or .spXout files are located, one per input sequence. .spd33 files are generated by SPIDER3-Single, .spXout files are generated by SPINE-X." << endl;
    cout << "  - TAB: All sequences length must be equal or greater than n + 1." << endl;
    cout << "    --path <dirPath>, REQUIRED. Path where .spd33 or .spXout files are located, one per input sequence. .spd33 files are generated by SPIDER3-Single, .spXout files are generated by SPINE-X." << endl;
    cout << "    --n <integer>, default: 1. n > 0." << endl;
    cout << "  - TAAC: All sequences length must be equal or greater than n + 1." << endl;
    cout << "    --path <dirPath>, REQUIRED. Path where .spd33 or .spXout files are located, one per input sequence. .spd33 files are generated by SPIDER3-Single, .spXout files are generated by SPINE-X." << endl;
    cout << "    --n <integer>, default: 10. n > 0." << endl;
    cout << "  - ASA: All sequences must be the same length." << endl;
    cout << "    --path <dirPath>, REQUIRED. Path where .spd33 or .spXout files are located, one per input sequence. .spd33 files are generated by SPIDER3-Single, .spXout files are generated by SPINE-X." << endl;
    cout << "  - PSSM: All sequences must be the same length." << endl;
    cout << "    --path <dirPath>, REQUIRED. Path where .pssm files are located, one per input sequence. .spd33 files are generated by SPIDER3-Single, .spXout files are generated by SPINE-X." << endl;
    cout << "  - PSSMAAC" << endl;
    cout << "    --path <dirPath>, REQUIRED. Path where .pssm files are located, one per input sequence. .spd33 files are generated by SPIDER3-Single, .spXout files are generated by SPINE-X." << endl;
    cout << "  - BiPSSM: All sequences length must be equal or greater than n + 1." << endl;
    cout << "    --path <dirPath>, REQUIRED. Path where .pssm files are located, one per input sequence. .spd33 files are generated by SPIDER3-Single, .spXout files are generated by SPINE-X." << endl;
    cout << "    --n <integer>, default: 1. n > 0." << endl;
    cout << "  - PSSMAC: All sequences length must be equal or greater than n + 1." << endl;
    cout << "    --path <dirPath>, REQUIRED. Path where .pssm files are located, one per input sequence. .spd33 files are generated by SPIDER3-Single, .spXout files are generated by SPINE-X." << endl;
    cout << "    --n <integer>, default: 1. n > 0." << endl;
    cout << "  - PPSSM: All sequences length must be equal or greater than n + 1." << endl;
    cout << "    --path <dirPath>, REQUIRED. Path where .pssm files are located, one per input sequence. .spd33 files are generated by SPIDER3-Single, .spXout files are generated by SPINE-X." << endl;
    cout << "    --n <integer>, default: 1. n > 0." << endl;
    cout << "  - KNNprotein" << endl;
    cout << "    --train <filePath>, REQUIRED. Path where the fasta training file is located." << endl;
    cout << "    --labels <filePath>, REQUIRED. Path where the labels file is located. All sequences in the training file must be in the labels file." << endl;
    cout << "    --k <integer>, default: 30. 1 <= k <= 100." << endl;
    cout << "  - KNNpeptide: All sequences must be the same length." << endl;
    cout << "    --train <filePath>, REQUIRED. Path where the fasta training file is located." << endl;
    cout << "    --labels <filePath>, REQUIRED. Path where the labels file is located. All sequences in the training file must be in the labels file." << endl;
    cout << "    --k <integer>, default: 30. 1 <= k <= 100." << endl;
    cout << "  - PseKRAAC" << endl;
    cout << "    For information on how to use PseKRAAC, please run the program with the arguments --help PseKRAAC." << endl << endl;
}

void printPseKRAACHelp()
{
    cout << "PseKRAAC usage: " << endl;
    cout << "  Required arguments: -i <input file> -o <output file> -e PseKRAAC --type <type> --subtype <subtype> --ktuple <integer> --gapLambda <integer> --raactype <integer>" << endl;
    cout << "Arguments: " << endl;
    cout << "  --type <type>. Allowed types are 1, 2, 3A, 3B, 4, 5, 6A, 6B, 6C, 7, 8, 9, 10, 11, 12, 13, 14, 15 and 16." << endl;
    cout << "  --subtype <subtype>. Allowed subtypes are g-gap and lambda-correlation." << endl;
    cout << "  --ktuple <integer>. Allowed k-tuple values are 1, 2 and 3." << endl;
    cout << "  --gapLambda <integer>. If the subtype is g-gap, the value must be between 0 and 9. If the subtype is lambda-correlation, the value must be between 1 and 9." << endl;
    cout << "  --raactype <integer>. The allowed values depend on the selected type." << endl;
    cout << helpPseKRAAC() << endl;
}

bool argumentExists(char** begin, char** end, const string &option)
{
    return find(begin, end, option) != end;
}

string getArgument(char** begin, char** end, const string &option)
{
    char** ptr = find(begin, end, option);
    if (ptr != end && (ptr + 1) != end)
    {
        return string(*(ptr+1));
    }
    return "";
}

int directoryExists(string path)
{
    struct stat info;
    const char* charPath = path.c_str();

    if (stat(charPath, &info) != 0) // Not accessible
    {
        return 0;
    }
    else if (info.st_mode & S_IFDIR) // Exists
    {
        return 1;
    }
    else // Path found, but it's not a directory
    {
        cout << "Error: " << path << " is not a directory." << endl;
        return -1;
    }
}

bool isNumber(string number)
{
    int i = 0;

    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}

bool isFloat(string number)
{
    int i = 0;

    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        if (!isdigit(number[i]) && number[i] != '.')
            return false;
    }
    return true;
}

void swap(string* a, string* b)
{
    string t = *a;
    *a = *b;
    *b = t;
}

int partition (vector<string>& names, vector<string>& seqs, int low, int high)
{
    string pivot = seqs[high];
    int i = (low - 1);
 
    for (int j = low; j <= high- 1; j++)
    {
        if (seqs[j].length() <= pivot.length())
        {
            i++;   
            swap(&seqs[i], &seqs[j]);
            swap(&names[i], &names[j]);
        }
    }
    swap(&seqs[i + 1], &seqs[high]);
    swap(&names[i + 1], &names[high]);
    return (i + 1);
}

void quickSort(vector<string>& names, vector<string>& seqs, int low, int high)
{
    if (low < high)
    {
        int pi = partition(names, seqs, low, high);
        quickSort(names, seqs, low, pi - 1);
        quickSort(names, seqs, pi + 1, high);
    }
}

void quickSortTasks(int low, int high, vector<string>& names, vector<string>& seqs, int lowLimit) {
    if (low < high) 
    {
        if (high - low < lowLimit) 
        {
            quickSort(names, seqs, low, high);
        }
        else
        {
            int q = partition(names, seqs, low, high);
            #pragma omp task shared(names, seqs)
            quickSortTasks(low, q - 1, names, seqs, lowLimit);
            #pragma omp task shared(names, seqs)
            quickSortTasks(q + 1, high, names, seqs, lowLimit);
        }
    } 
}

void parallelQuickSort(vector<string>& names, vector<string>& seqs, int low, int high){
    #pragma omp parallel
    {
        #pragma omp single
        quickSortTasks(low, high, names, seqs, 1000 - 1);
        #pragma omp taskwait
    }
}

static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void printEncoded(vector<string> headers, vector<string> seqNames, vector<vector<double>> encoded, int numSeqs, string output)
{
    ofstream file;
    file.open(output);
    for(int i = 0; i < headers.size(); i++)
    {
        file << headers[i] << "\t";
    }
    file << endl;
    for (int i = 0; i < encoded.size(); i++)
    {
        file << seqNames[i] << "\t";
        for(int j = 0; j < headers.size() - 1; j++)
        {
            file << setprecision(7) << encoded[i][j] << "\t";
        }
        file << endl;
    }
    file.close();
}

int factorial (int n)
{
    int result = 1;
    while (n > 1)
    {
        result *= n;
        n--;
    }
    return result;
}

void cropSequences (vector<string>& seqs, int length)
{
    for (int i = 0; i < seqs.size(); i++)
    {
        seqs[i] = seqs[i].substr(0, length);
    }
}

bool readFasta(string& file, vector<string>& names, vector<string>& seqs)
{
    ifstream inf(file);
    if (inf.is_open())
    {
        string line;
        getline(inf, line);
        while (true)
        {
            if (line[0] == '>')
            {
                string name = line.erase(0, 1);
                string seq;
                while (true)
                {
                    if (getline(inf, line) && line[0] != '>')
                    {
                        if (line[line.length() - 1] == '\r')
                            line.pop_back();
                        seq.append(line);
                    }
                    else
                    {
                        if (name[name.length() - 1] == '\r')
                            name.pop_back();
                        names.push_back(name);
                        seqs.push_back(seq);
                        break;
                    }
                }
            }
            else
            {
                break;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

int main (int argc, char* argv[])
{
    auto start = high_resolution_clock::now();
    if (argumentExists(argv, argv + argc, "--help"))
    {
        if (getArgument(argv, argv + argc, "--help").compare("PseKRAAC") == 0) 
            printPseKRAACHelp();
        else
            printHelp();

        return 1;
    }
    
    if (argc < 7) 
    {
		fprintf(stderr, "Usage: %s -i <input file> -o <output file> -e <encoding> [options]\n", argv[0]);
		fprintf(stderr, "Execute %s --help argument for details.\n", argv[0]);
		return 1;
	}

    std::string dir(argv[0]);
    int pos = dir.find_last_of(PATH_SEPARATOR);
    string dataDir = dir.substr(0, pos + 1) + "data/";

    string numThreadsS = getArgument(argv, argv + argc, "--threads");
    int numThreads = 1;
    if (numThreadsS.compare("") != 0)
    {
        if (!isNumber(numThreadsS))
        {
            cout << "Error: The --threads parameter must be a number greater than 0.\n";
            return 0;
        }
        numThreads = stoi(numThreadsS);
        if (numThreads < 0)
        {
            cout << "Error: The --threads parameter must be a number greater than 0.\n";
            return 0;
        }
    }

    // Get main arguments
    string input = getArgument(argv, argv + argc, "-i");
    string output = getArgument(argv, argv + argc, "-o");
    string encoding = getArgument(argv, argv + argc, "-e");

    vector<string> names;
    vector<string> seqs;
    
    if (!readFasta(input, names, seqs))
    {
        cout << "Error: Cannot open input file.\n";
        return 0;
    }

    int numSeqs = names.size();
    
    // Terminate if no valid sequences are found
    if (numSeqs == 0)
    {
        cout << "Error: The file has no valid fasta sequences.\n";
        return 0;
    }
    
    auto reads = high_resolution_clock::now();

    const static string allowed = "ACDEFGHIKLMNPQRSTVWY";

    auto remove = high_resolution_clock::now();
    auto removeCt = duration_cast<milliseconds>(remove - reads);

    #pragma omp parallel for num_threads(numThreads) default(none) shared(seqs, allowed) schedule(guided) 
    for (int i = 0; i < seqs.size(); i++)
    {
        removeDisallowed(seqs[i], allowed);
    }
    // Sort list by length
    // quickSort(names, seqs, 0, seqs.size() - 1);
    
    auto sort = high_resolution_clock::now();
    auto sortCt =  duration_cast<milliseconds>(sort - remove);
    
    vector<string> seqNames;
    vector<vector<double>> encoded;
    vector<string> headers;
    vector<string> keys;

    // Encode sequences
    if (encoding.compare("AAC") == 0)
    {
        auto enc1 = high_resolution_clock::now();
        headers.push_back("name");
        for(char c : allowed)
        {
            string aa(1, c);
            headers.push_back(aa);
        }

        if (numThreads == 1)
        {
            for (int i = 0; i < seqs.size(); i++)
            {
                // removeDisallowed(seqs[i], allowed);
                vector<double> encodedProtein = AAC(seqs[i], allowed);
                seqNames.push_back(names[i]);
                encoded.push_back(encodedProtein);
            }
        }
        else 
        {
            #pragma omp parallel for num_threads(numThreads) \
                default(none) shared(seqNames, encoded, seqs, names, allowed) schedule(guided) 
            for (int i = 0; i < seqs.size(); i++)
            {
                // removeDisallowed(seqs[i], allowed);
                vector<double> encodedProtein = AAC(seqs[i], allowed);
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
            }
        }
    }

    else if (encoding.compare("EAAC") == 0)
    {
        int seqLength = checkFastaSameLength(seqs);
        if(seqLength == -1)
        {
            bool crop = argumentExists(argv, argv + argc, "--crop");
            if (crop)
            {
                seqLength = getMinSequenceLength(names, seqs);
                cropSequences(seqs, seqLength);
            }
            else
            {
                cout << "Error: All sequences must have the same length. You can use the --crop argument, so it crops the sequences automatically.\n";
                return 0;
            }
        }

        string windowS = getArgument(argv, argv + argc, "--window");
        int window = 5;
        if (windowS != "")
        {
            if (!isNumber(windowS))
            {
                cout << "Error: The window value must be a number equal or greater than 1.\n";
                return 0;
            }
            window = stoi(windowS);
            if (window < 1)
            {
                cout << "Error: The window value must be a number equal or greater than 1.\n";
                return 0;
            }
        }

        if (seqLength < window)
        {
            cout << "Error: All sequences length must be greater than the window size.\n";
            return 0;
        }

        int windows = seqLength - window + 1;
        headers.push_back("name");
        for (int i = 0; i < windows; i++)
        {
            for(char c : allowed)
            {
                string key = to_string(i + 1);
                key.push_back('-');
                key.push_back(c);
                headers.push_back(key);
                keys.push_back(key);
            }
        }

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, allowed, keys, window, windows) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            vector<double> encodedProtein = EAAC(seqs[i], allowed, keys, window, windows);
            #pragma omp critical
            {
                seqNames.push_back(names[i]);
                encoded.push_back(encodedProtein);
            }
        }
    }

    else if (encoding.compare("CKSAAP") == 0)
    {
        string gapS = getArgument(argv, argv + argc, "--gap");
        int gap = 5;
        if (gapS != "")
        {
            if (!isNumber(gapS))
            {
                cout << "Error: The gap value must be a number equal or greater than 0.\n";
                return 0;
            }
            gap = stoi(gapS);
            if (gap < 0)
            {
                cout << "Error: The gap value must be a number equal or greater than 0.\n";
                return 0;
            }
        }

        int minLength = getMinSequenceLength(names, seqs);
        if (minLength < gap + 2)
        {
            cout << "Error: All sequences length must be greater than the gap size + 2.\n";
            return 0;
        }
        int allowedLength = allowed.length();
        headers.push_back("name");
        for (int i = 0; i < gap + 1; i++)
        {
            for(char c : allowed)
            {
                for(char d : allowed)
                {
                    string key = to_string(i);
                    key.push_back('-');
                    key.push_back(c);
                    key.push_back(d);
                    headers.push_back(key);
                    keys.push_back(key);
                }
            }
        }

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, allowed, keys, gap) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            vector<double> encodedProtein = CKSAAP(seqs[i], allowed, keys, gap);
            #pragma omp critical
            {
                seqNames.push_back(names[i]);
                encoded.push_back(encodedProtein);
            }
        }
    }

    else if (encoding.compare("TPC") == 0)
    {
        headers.push_back("name");
        for(char c : allowed)
        {
            for(char d : allowed)
            {
                for(char e : allowed)
                {
                    string key(1, c);
                    key.push_back(d);
                    key.push_back(e);
                    headers.push_back(key);
                    keys.push_back(key);
                }
            }
        }

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, allowed, keys) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            vector<double> encodedProtein = TPC(seqs[i], allowed, keys);
            #pragma omp critical
            {
                seqNames.push_back(names[i]);
                encoded.push_back(encodedProtein);
            }
        }
    }

    else if (encoding.compare("DPC") == 0)
    {
        headers.push_back("name");
        for(char c : allowed)
        {
            for(char d : allowed)
            {
                string key(1, c);
                key.push_back(d);
                headers.push_back(key);
                keys.push_back(key);
            }
        }

        if (numThreads == 1)
        {
            for (int i = 0; i < seqs.size(); i++)
            {
                vector<double> encodedProtein = DPC(seqs[i], allowed, keys);
                seqNames.push_back(names[i]);
                encoded.push_back(encodedProtein);
            }
        }
        else
        {
            #pragma omp parallel for num_threads(numThreads) \
                default(none) shared(seqNames, encoded, seqs, names, allowed, keys) schedule(guided) 
            for (int i = 0; i < seqs.size(); i++)
            {
                vector<double> encodedProtein = DPC(seqs[i], allowed, keys);
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
            }
        }
    }

    else if (encoding.compare("DDE") == 0)
    {
        headers.push_back("name");
        
        map<char, int> codons;
        map<string, double> tm;
        map<string, double> tv;
        codons['A'] = 4;
        codons['C'] = 2;
        codons['D'] = 2;
        codons['E'] = 2;
        codons['F'] = 2;
        codons['G'] = 4;
        codons['H'] = 2;
        codons['I'] = 3;
        codons['K'] = 2;
        codons['L'] = 6;
        codons['M'] = 1;
        codons['N'] = 2;
        codons['P'] = 4;
        codons['Q'] = 2;
        codons['R'] = 6;
        codons['S'] = 6;
        codons['T'] = 4;
        codons['V'] = 4;
        codons['W'] = 1;
        codons['Y'] = 2;

        for(char c : allowed)
        {
            for(char d : allowed)
            {
                string key(1, c);
                key.push_back(d);
                headers.push_back(key);
                keys.push_back(key);
                tm[key] = (codons[c] / 61.0) * (codons[d] / 61.0);
                tv[key] = tm[key] * (1 - tm[key]); // Will be divided by the sequence length - 1
            }
        }

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, allowed, keys, tm, tv) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            vector<double> encodedProtein = DDE(seqs[i], allowed, keys, tm, tv);
            #pragma omp critical
            {
                seqNames.push_back(names[i]);
                encoded.push_back(encodedProtein);
            }
        }
    }

    // Grouped AAC
    else if (encoding.compare("GAAC") == 0 || encoding.compare("EGAAC") == 0 || encoding.compare("CKSAAGP") == 0 || 
        encoding.compare("GDPC") == 0 || encoding.compare("GTPC") == 0)
    {
        map<char, string> groups;
        groups['A'] = "aliphatic";
        groups['C'] = "uncharged";
        groups['D'] = "negative";
        groups['E'] = "negative";
        groups['F'] = "aromatic";
        groups['G'] = "aliphatic";
        groups['H'] = "positive";
        groups['I'] = "aliphatic";
        groups['K'] = "positive";
        groups['L'] = "aliphatic";
        groups['M'] = "aliphatic";
        groups['N'] = "uncharged";
        groups['P'] = "uncharged";
        groups['Q'] = "uncharged";
        groups['R'] = "positive";
        groups['S'] = "uncharged";
        groups['T'] = "uncharged";
        groups['V'] = "aliphatic";
        groups['W'] = "aromatic";
        groups['Y'] = "aromatic";

        array<string, 5> groupStrings = {"aliphatic", "aromatic", "positive", "negative", "uncharged"};

        if(encoding.compare("GAAC") == 0)
        {
            headers.push_back("name");
            for (int i = 0; i < 5; i++)
            {
                headers.push_back(groupStrings[i]);
                keys.push_back(groupStrings[i]);
            }

            #pragma omp parallel for num_threads(numThreads) \
                default(none) shared(seqNames, encoded, seqs, names, keys, groups) schedule(guided) 
            for (int i = 0; i < seqs.size(); i++)
            {
                vector<double> encodedProtein = GAAC(seqs[i], keys, groups);
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
            }
        }
        else if (encoding.compare("EGAAC") == 0)
        {
            int window = 5;
            string windowS = getArgument(argv, argv + argc, "--window");
            if (windowS != "")
            {
                if (!isNumber(windowS))
                {
                    cout << "Error: The window value must be a number greater than 0.\n";
                    return 0;
                }
                window = stoi(windowS);
                if (window < 1)
                {
                    cout << "Error: The window value must be a number greater than 0.\n";
                    return 0;
                }
            }
            
            int seqLength = checkFastaSameLength(seqs);
            if (seqLength == -1)
            {
                bool crop = argumentExists(argv, argv + argc, "--crop");
                if (crop)
                {
                    seqLength = getMinSequenceLength(names, seqs);
                    cropSequences(seqs, seqLength);
                }
                else
                {
                    cout << "Error: All sequences must have the same length. You can use the --crop argument, so it crops the sequences automatically.\n";
                    return 0;
                }
            }

            if (seqLength < window)
            {
                cout << "Error: All sequences length must be greater than the window size.\n";
                return 0;
            }
            int windows = seqLength - window + 1;
            headers.push_back("name");
            
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j <= windows; j++)
                {
                    string key = to_string(j);
                    key.push_back('-');
                    key += groupStrings[i];
                    headers.push_back(key);
                    keys.push_back(key);
                }
            }
            #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, keys, groups, window, windows) schedule(guided) 
            for (int i = 0; i < seqs.size(); i++)
            {
                vector<double> encodedProtein = EGAAC(seqs[i], keys, groups, window, windows);
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
            }
        }
        else if (encoding.compare("CKSAAGP") == 0)
        {
            string gapS = getArgument(argv, argv + argc, "--gap");
            int gap = 5;
            if (gapS != "")
            {
                if (!isNumber(gapS))
                {
                    cout << "Error: The gap value must be a number equal or greater than 0.\n";
                    return 0;
                }
                gap = stoi(gapS);
                if (gap < 0)
                {
                    cout << "Error: The gap value must be a number equal or greater than 0.\n";
                    return 0;
                }
            }

            int minLength = getMinSequenceLength(names, seqs);
            if (minLength < gap + 2)
            {
                cout << "Error: All sequences length must be equal or greater than the gap size + 2.\n";
                return 0;
            }

            headers.push_back("name");
            for (int i = 0; i < gap + 1; i++)
            {
                for(string g : groupStrings)
                {
                    for(string h : groupStrings)
                    {
                        string key = to_string(i);
                        key.push_back('-');
                        key += g;
                        key.push_back('-');
                        key += h;
                        headers.push_back(key);
                        keys.push_back(key);
                    }
                }
            }

            #pragma omp parallel for num_threads(numThreads) \
                default(none) shared(seqNames, encoded, seqs, names, keys, gap, groups, groupStrings) schedule(guided) 
            for (int i = 0; i < seqs.size(); i++)
            {
                vector<double> encodedProtein = CKSAAGP(seqs[i], keys, gap, groups, groupStrings);
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
            }
        }
        else if (encoding.compare("GDPC") == 0)
        {
            headers.push_back("name");
            int counter = 1;
            for(string g : groupStrings)
            {
                for(string h : groupStrings)
                {
                    string key = g;
                    key.push_back('-');
                    key += h;
                    headers.push_back(key);
                    keys.push_back(key);
                }
            }

            #pragma omp parallel for num_threads(numThreads) \
                default(none) shared(seqNames, encoded, seqs, names, keys, groups, groupStrings) schedule(guided) 
            for (int i = 0; i < seqs.size(); i++)
            {
                vector<double> encodedProtein = GDPC(seqs[i], keys, groups, groupStrings);
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
            }
        }
        else if (encoding.compare("GTPC") == 0)
        {
            headers.push_back("name");
            int counter = 1;
            for(string g : groupStrings)
            {
                for(string h : groupStrings)
                {
                    for(string i : groupStrings)
                    {
                        string key = g;
                        key.push_back('-');
                        key += h;
                        key.push_back('-');
                        key += i;
                        headers.push_back(key);
                        keys.push_back(key);
                    }
                }
            }

            #pragma omp parallel for num_threads(numThreads) \
                default(none) shared(seqNames, encoded, seqs, names, keys, groups, groupStrings) schedule(guided) 
            for (int i = 0; i < seqs.size(); i++)
            {
                vector<double> encodedProtein = GTPC(seqs[i], keys, groups, groupStrings);
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
            }
        }
    }

    else if (encoding.compare("Binary") == 0)
    {
        int seqLength = checkFastaSameLength(seqs);
        if(seqLength == -1)
        {
            bool crop = argumentExists(argv, argv + argc, "--crop");
            if (crop)
            {
                seqLength = getMinSequenceLength(names, seqs);
                cropSequences(seqs, seqLength);
            }
            else
            {
                cout << "Error: All sequences must have the same length. You can use the --crop argument, so it crops the sequences automatically.\n";
                return 0;
            }
        }

        int allowedLength = allowed.length();
        headers.push_back("name");
        for (int i = 0; i < seqLength; i++)
        {
            for (char c : allowed)
            {
                string key(1, c);
                key = to_string(i) + key;
                headers.push_back(key);
                keys.push_back(key);
            }
        }

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, keys) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            vector<double> encodedProtein = binary(seqs[i], keys);
            #pragma omp critical
            {
                seqNames.push_back(names[i]);
                encoded.push_back(encodedProtein);
            }
        }
    }

    // Autocorrelation
    else if (encoding.compare("Moran") == 0 || encoding.compare("Geary") == 0 || encoding.compare("NMB") == 0)
    {
        string lagS = getArgument(argv, argv + argc, "--lag");
        int lag = 30;
        if (lagS != "")
        {
            if (!isNumber(lagS))
            {
                cout << "Error: The lag value must be a number equal or greater than 1.\n";
                return 0;
            }
            lag = stoi(lagS);
            if (lag < 1)
            {
                cout << "Error: The lag value must be a number equal or greater than 1.\n";
                return 0;
            }
        }

        int minLength = getMinSequenceLength(names, seqs);
        if(minLength < lag + 1)
        {
            cout << "Error: All sequences must be equal or greater than lag + 1.\n";
            return 0;
        }

        string indicesS = getArgument(argv, argv + argc, "--indices");
        vector<string> indexList;
        if (indicesS != "")
        {
            indexList = splitString(indicesS, ",");
        }
        else
        {
            indexList.push_back("CIDH920105");
            indexList.push_back("BHAR880101");
            indexList.push_back("CHAM820101");
            indexList.push_back("CHAM820102");
            indexList.push_back("CHOC760101");
            indexList.push_back("BIGC670101");
            indexList.push_back("CHAM810101");
            indexList.push_back("DAYM780201");
        }

        map<string, bool> indices;
        for (int i = 0; i < indexList.size(); i++)
        {
            indices[indexList[i]] = true;
        }

        // Order of amino acids in the indices
        string stringOrder = "ARNDCQEGHILKMFPSTWYV";
        map<char, int> order;
        for (int i = 0; i < 20; i++)
        {
            order[stringOrder[i]] = i;
        }

        // Read indices file
        map<string, array<double, 20>> indexData;
        ifstream file(dataDir + "AAidx.txt");
        string line;
        while (getline(file, line))
        {
            size_t pos = line.find('\t');
            string index = line.substr(0, pos);
            string token;
            if (indices.find(index) != indices.end())
            {
                array<double, 20> values;
                line.erase(0, pos + 1);
                int counter = 0;
                while ((pos = line.find('\t')) != string::npos) 
                {
                    token = line.substr(0, pos);
                    values[counter] = stof(token);
                    counter++;
                    line.erase(0, pos + 1);
                }
                values[19] = stof(line);
                indexData[index] = values;
            }
        }
        
        map<string, double> means;
        headers.push_back("name");
        for (string index : indexList)
        {
            // Centralize and standardize index data
            double mean = 0;
            for (double val : indexData[index])
            {
                mean += val;
            }
            mean /= 20;
            means[index] = mean;
            double sd = 0;
            for (int i = 0; i < 20; i++)
            {
                sd += pow(indexData[index][i] - mean, 2);
            }
            sd = sqrt(sd / 20);
            for (int i = 0; i < 20; i++)
            {
                indexData[index][i] = (indexData[index][i] - mean) / sd;
            }

            for (int i = 1; i <= lag; i++)
            {
                string key = index;
                key.push_back('-');
                key += to_string(i);
                headers.push_back(key);
                keys.push_back(key);
            }
        }

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, keys, indexData, indexList, lag, means, order, encoding) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            vector<double> encodedProtein;
            if (encoding.compare("Moran") == 0)
                encodedProtein = Moran(seqs[i], keys, indexData, indexList, lag, means, order);
            else if (encoding.compare("Geary") == 0)
                encodedProtein = Geary(seqs[i], keys, indexData, indexList, lag, means, order);
            else if (encoding.compare("NMB") == 0)
                encodedProtein = NMB(seqs[i], keys, indexData, indexList, lag, means, order);
            #pragma omp critical
            {
                seqNames.push_back(names[i]);
                encoded.push_back(encodedProtein);
            }
        }
    }

    // Composition/Transition/Distribution - Added surface tension
    else if (encoding.rfind("CTD", 0) == 0)
    {
        #pragma region Setup

        map<string, string> group1;
        group1["hidrophobicity_PRAM900101"] = "RKEDQN";
        group1["hydrophobicity_ARGP820101"] = "QSTNGDE";
        group1["hydrophobicity_ZIMJ680101"] = "QNGSWTDERA";
        group1["hydrophobicity_PONP930101"] = "KPDESNQT";
        group1["hydrophobicity_CASG920101"] = "KDEQPSRNTG";
        group1["hydrophobicity_ENGD860101"] = "RDKENQHYP";
        group1["hydrophobicity_FASG890101"] = "KERSQD";
        group1["normVDWvol"] = "GASTPDC";
        group1["polarity"] = "LIFWCMVY";
        group1["polarizability"] = "GASDT";
        group1["charge"] = "KR";
        group1["surfaceTension"] = "GQDNAHR";
        group1["secStructure"] = "EALMQKRH";
        group1["solventAcc"] = "ALFCGIVW";

        map<string, string> group2;
        group2["hidrophobicity_PRAM900101"] = "GASTPHY";
        group2["hydrophobicity_ARGP820101"] = "RAHCKMV";
        group2["hydrophobicity_ZIMJ680101"] = "HMCKV";
        group2["hydrophobicity_PONP930101"] = "GRHA";
        group2["hydrophobicity_CASG920101"] = "AHYMLV";
        group2["hydrophobicity_ENGD860101"] = "SGTAW";
        group2["hydrophobicity_FASG890101"] = "NTPG";
        group2["normVDWvol"] = "NVEQIL";
        group2["polarity"] = "PATGS";
        group2["polarizability"] = "CPNVEQIL";
        group2["charge"] = "ANCQGHILMFPSTWYV";
        group1["surfaceTension"] = "KTSEC";
        group2["secStructure"] = "VIYCWFT";
        group2["solventAcc"] = "RKQEND";

        map<string, string> group3;
        group3["hidrophobicity_PRAM900101"] = "CLVIMFW";
        group3["hydrophobicity_ARGP820101"] = "LYPFIW";
        group3["hydrophobicity_ZIMJ680101"] = "LPFYI";
        group3["hydrophobicity_PONP930101"] = "YMFWLCVI";
        group3["hydrophobicity_CASG920101"] = "FIWC";
        group3["hydrophobicity_ENGD860101"] = "CVLIMF";
        group3["hydrophobicity_FASG890101"] = "AYHWVMFLIC";
        group3["normVDWvol"] = "MHKFRYW";
        group3["polarity"] = "HQRKNED";
        group3["polarizability"] = "KMHFRYW";
        group3["charge"] = "DE";
        group1["surfaceTension"] = "ILMFPWYV";
        group3["secStructure"] = "GNPSD";
        group3["solventAcc"] = "MSPTHY";

        vector<map<string, string>> groups;
        groups.push_back(group1);
        groups.push_back(group2);
        groups.push_back(group3);

        vector<string> properties;
        properties.push_back("hidrophobicity_PRAM900101");
        properties.push_back("hydrophobicity_ARGP820101");
        properties.push_back("hydrophobicity_ZIMJ680101");
        properties.push_back("hydrophobicity_PONP930101");
        properties.push_back("hydrophobicity_CASG920101");
        properties.push_back("hydrophobicity_ENGD860101");
        properties.push_back("hydrophobicity_FASG890101");
        properties.push_back("normVDWvol");
        properties.push_back("polarity");
        properties.push_back("polarizability");
        properties.push_back("charge");
        properties.push_back("surfaceTension");
        properties.push_back("secStructure");
        properties.push_back("solventAcc");

        #pragma endregion

        if (encoding.compare("CTDC") == 0)
        {
            headers.push_back("name");
            for(string prop : properties)
            {
                for (int i = 1; i <= groups.size(); i++)
                {
                    string key = prop;
                    key.push_back('-');
                    key += to_string(i);
                    headers.push_back(key);
                    keys.push_back(key);
                }
            }

            #pragma omp parallel for num_threads(numThreads) \
                default(none) shared(seqNames, encoded, seqs, names, allowed, keys, groups, properties) schedule(guided) 
            for (int i = 0; i < seqs.size(); i++)
            {
                vector<double> encodedProtein = CTDC(seqs[i], allowed, keys, groups, properties);
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
            }
        }
        else if (encoding.compare("CTDT") == 0)
        {
            headers.push_back("name");
            for(string prop : properties)
            {
                for (int i = 1; i <= groups.size(); i++)
                {
                    for (int j = i + 1; j <= groups.size(); j++)
                    {
                        string key = prop;
                        key.push_back('-');
                        key += to_string(i);
                        key.push_back('-');
                        key += to_string(j);
                        headers.push_back(key);
                        keys.push_back(key);
                    }
                }
            }

            #pragma omp parallel for num_threads(numThreads) \
                default(none) shared(seqNames, encoded, seqs, names, allowed, keys, groups, properties) schedule(guided) 
            for (int i = 0; i < seqs.size(); i++)
            {
                vector<double> encodedProtein = CTDT(seqs[i], allowed, keys, groups, properties);
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
            }
        }
        else if (encoding.compare("CTDD") == 0)
        {
            array<int, 5> pcts = {0, 25, 50, 75, 100};
            headers.push_back("name");
            for(string prop : properties)
            {
                for (int i = 1; i <= groups.size(); i++)
                {
                    for (int pct : pcts)
                    {
                        string key = prop;
                        key.push_back('-');
                        key += to_string(i);
                        key.push_back('-');
                        key += to_string(pct);
                        headers.push_back(key);
                        keys.push_back(key);
                    }
                }
            }

            #pragma omp parallel for num_threads(numThreads) \
                default(none) shared(seqNames, encoded, seqs, names, allowed, keys, groups, properties, pcts) schedule(guided) 
            for (int i = 0; i < seqs.size(); i++)
            {
                vector<double> encodedProtein = CTDD(seqs[i], allowed, keys, groups, properties, pcts);
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
            }
        }
    }

    // Conjoint triad
    else if (encoding.compare("CT") == 0 || encoding.compare("KSCT") == 0)
    {
        array<string, 7> groups = {"AGV", "ILFP", "YMTS", "HNQW", "RK", "DE", "C"};
        int minLength = getMinSequenceLength(names, seqs);
        if (encoding.compare("CT") == 0)
        {
            if(minLength < 3)
            {
                cout << "Error: All sequences must be equal or greater than 3.\n";
                return 0;
            }
            headers.push_back("name");
            for (int i = 1; i <= 7; i++)
            {
                for (int j = 1; j <= 7; j++)
                {
                    for (int k = 1; k <= 7; k++)
                    {
                        string key = to_string(i);
                        key.push_back('-');
                        key += to_string(j);
                        key.push_back('-');
                        key += to_string(k);
                        headers.push_back(key);
                        keys.push_back(key);
                    }
                }
            }

            #pragma omp parallel for num_threads(numThreads) \
                default(none) shared(seqNames, encoded, seqs, names, allowed, keys, groups) schedule(guided) 
            for (int i = 0; i < seqs.size(); i++)
            {
                vector<double> encodedProtein = CT(seqs[i], allowed, keys, groups);
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
            }
        }
        else if (encoding.compare("KSCT") == 0)
        {
            string kS = getArgument(argv, argv + argc, "--k");
            int k = 1;
            if (kS != "")
            {
                if (!isNumber(kS))
                {
                    cout << "Error: The k value must be a number greater or equal than 1.\n";
                    return 0;
                }
                k = stoi(kS);
                if (k < 1)
                {
                    cout << "Error: The k value must be a number greater or equal than 1.\n";
                    return 0;
                }
            }
            if(minLength < 2 * k + 3)
            {
                cout << "Error: All sequences length must be equal or greater than (2 * k) + 3.\n";
                return 0;
            }
            headers.push_back("name");
            for (int currK = 0; currK <= k; currK++)
            {
                for (int i = 1; i <= 7; i++)
                {
                    for (int j = 1; j <= 7; j++)
                    {
                        for (int k = 1; k <= 7; k++)
                        {
                            string key = to_string(i);
                            key.push_back('-');
                            key += to_string(j);
                            key.push_back('-');
                            key += to_string(k);
                            key.push_back('-');
                            key += to_string(currK);
                            headers.push_back(key);
                            keys.push_back(key);
                        }
                    }
                }
            }

            #pragma omp parallel for num_threads(numThreads) \
                default(none) shared(seqNames, encoded, seqs, names, allowed, keys, groups, k) schedule(guided) 
            for (int i = 0; i < seqs.size(); i++)
            {
                vector<double> encodedProtein = KSCT(seqs[i], allowed, keys, groups, k);
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
            }
        }
    }

    // Quasi-sequence-order
    else if (encoding.compare("QSO") == 0 || encoding.compare("SOCN") == 0)
    {
        #pragma region Setup
        
        string lagS = getArgument(argv, argv + argc, "--lag");
        int lag = 30;
        if (lagS != "")
        {
            if (!isNumber(lagS))
            {
                cout << "Error: The lag value must be a number greater or equal than 1.\n";
                return 0;
            }
            lag = stoi(lagS);
            if (lag < 1)
            {
                cout << "Error: The lag value must be a number greater or equal than 1.\n";
                return 0;
            }
        }

        int minLength = getMinSequenceLength(names, seqs);
        if(minLength < lag + 1)
        {
            cout << "Error: All sequences length must be equal or greater than lag + 1.\n";
            return 0;
        }

        string weightS = getArgument(argv, argv + argc, "--weight");
        double weight = 0.1;
        if (encoding.compare("QSOrder") == 0 && weightS != "")
        {
            if (!isFloat(weightS))
            {
                cout << "Error: The weight value must be a number between 0 and 1.\n";
                return 0;
            }
            weight = stof(weightS);
            if (weight < 0 || weight > 1)
            {
                cout << "Error: The weight value must be a number between 0 and 1.\n";
                return 0;
            }
        }

        // Read Schneider-Wrede file
        map<char, array<double, 20>> swData;
        ifstream file(dataDir + "Schneider-Wrede.txt");
        string line;
        getline(file, line); // Skip first line
        while (getline(file, line))
        {
            size_t pos = line.find('\t');
            char index = line.substr(0, pos)[0];
            string token;
            array<double, 20> values;
            line.erase(0, pos + 1);
            int counter = 0;
            while ((pos = line.find('\t')) != string::npos) 
            {
                token = line.substr(0, pos);
                values[counter] = stof(token);
                counter++;
                line.erase(0, pos + 1);
            }
            values[19] = stof(line);
            swData[index] = values;
        }
        // Read Grantham file
        map<char, array<double, 20>> gData;
        ifstream file2(dataDir + "Grantham.txt");
        getline(file2, line); // Skip first line
        while (getline(file2, line))
        {
            size_t pos = line.find('\t');
            char aa = line.substr(0, pos)[0];
            string token;
            array<double, 20> values;
            line.erase(0, pos + 1);
            int counter = 0;
            while ((pos = line.find('\t')) != string::npos) 
            {
                token = line.substr(0, pos);
                values[counter] = stof(token);
                counter++;
                line.erase(0, pos + 1);
            }
            values[19] = stof(line);
            gData[aa] = values;
        }

        map<char, int> order;
        for (int i = 0; i < 20; i++)
        {
            order[allowed[i]] = i;
        }
        
        #pragma endregion

        if (encoding.compare("SOCN") == 0)
        {
            headers.push_back("name");
            for (int i = 1; i <= lag; i++)
            {
                string key = "sw";
                key.push_back('-');
                key += to_string(i);
                headers.push_back(key);
                keys.push_back(key);
            }
            for (int i = 1; i <= lag; i++)
            {
                string key = "g";
                key.push_back('-');
                key += to_string(i);
                headers.push_back(key);
                keys.push_back(key);
            }

            #pragma omp parallel for num_threads(numThreads) \
                default(none) shared(seqNames, encoded, seqs, names, allowed, keys, order, swData, gData, lag) schedule(guided) 
            for (int i = 0; i < seqs.size(); i++)
            {
                vector<double> encodedProtein = SOCNumber(seqs[i], allowed, keys, order, swData, gData, lag);
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
            }
        }
        else if (encoding.compare("QSO") == 0)
        {
            double weight = 0.1;
            headers.push_back("name");
            for (char c : allowed)
            {
                string key = "sw";
                key.push_back('-');
                key.push_back(c);
                headers.push_back(key);
                keys.push_back(key);
            }
            for (char c : allowed)
            {
                string key = "g";
                key.push_back('-');
                key.push_back(c);
                headers.push_back(key);
                keys.push_back(key);
            }
            for (int i = 1; i <= lag; i++)
            {
                string key = "sw";
                key.push_back('-');
                key += to_string(i);
                headers.push_back(key);
                keys.push_back(key);
            }
            for (int i = 1; i <= lag; i++)
            {
                string key = "g";
                key.push_back('-');
                key += to_string(i);
                headers.push_back(key);
                keys.push_back(key);
            }

            #pragma omp parallel for num_threads(numThreads) \
                default(none) shared(seqNames, encoded, seqs, names, allowed, keys, order, swData, gData, lag, weight) schedule(guided) 
            for (int i = 0; i < seqs.size(); i++)
            {
                vector<double> encodedProtein = QSOrder(seqs[i], allowed, keys, order, swData, gData, lag, weight);
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
            }
        }
    }
    
    // Pseudo-amino acid composition
    else if (encoding.compare("PAAC") == 0 || encoding.compare("APAAC") == 0)
    {
        #pragma region Setup
        
        string lagS = getArgument(argv, argv + argc, "--lag");
        int lag = 30;
        if (lagS != "")
        {
            if (!isNumber(lagS))
            {
                cout << "Error: The lag value must be a number greater or equal than 1.\n";
                return 0;
            }
            lag = stoi(lagS);
            if (lag < 1)
            {
                cout << "Error: The lag value must be a number greater or equal than 1.\n";
                return 0;
            }
        }

        int minLength = getMinSequenceLength(names, seqs);
        if(minLength < lag + 1)
        {
            cout << "Error: All sequences length must be equal or greater than lag + 1.\n";
            return 0;
        }

        string weightS = getArgument(argv, argv + argc, "--weight");
        double weight = 0.05;
        if (weightS != "")
        {
            if (!isFloat(weightS))
            {
                cout << "Error: The weight value must be a number between 0 and 1.\n";
                return 0;
            }
            weight = stof(weightS);
            if (weight < 0 || weight > 1)
            {
                cout << "Error: The weight value must be a number between 0 and 1.\n";
                return 0;
            }
        }

        // Read PAAC file
        map<string, array<double, 20>> paac;
        ifstream file(dataDir + "PAAC.txt");
        string line;
        getline(file, line); // Skip first line
        while (getline(file, line))
        {
            size_t pos = line.find('\t');
            string prop = line.substr(0, pos);
            string token;
            array<double, 20> values;
            line.erase(0, pos + 1);
            int counter = 0;
            while ((pos = line.find('\t')) != string::npos) 
            {
                token = line.substr(0, pos);
                values[counter] = stof(token);
                counter++;
                line.erase(0, pos + 1);
            }
            values[19] = stof(line);
            paac[prop] = values;
        }

        map<char, int> order;
        for (int i = 0; i < 20; i++)
        {
            order[allowed[i]] = i;
        }

        for (auto &kvp : paac)
        {
            double mean = 0;
            for (double val : kvp.second)
                mean += val;
            mean /= 20;
            double res = 0;
            for (double val : kvp.second)
                res += pow(val - mean, 2);
            res = sqrt(res/20);
            for (int i = 0; i < 20; i++)
                kvp.second[i] = (kvp.second[i] - mean) / res;
        }

        #pragma endregion

        if(encoding.compare("PAAC") == 0)
        {
            string properties[3] = {"Hydrophobicity", "Hydrophilicity", "SideChainMass"};
            headers.push_back("name");
            for (char c : allowed)
            {
                string key(1, c);
                headers.push_back(key);
                keys.push_back(key);
            }
            for (int i = 1; i <= lag; i++)
            {
                string key = to_string(i);
                headers.push_back(key);
                keys.push_back(key);
            }

            #pragma omp parallel for num_threads(numThreads) \
                default(none) shared(seqNames, encoded, seqs, names, allowed, keys, lag, order, paac, weight) schedule(guided) 
            for (int i = 0; i < seqs.size(); i++)
            {
                vector<double> encodedProtein = PAAC(seqs[i], allowed, keys, lag, order, paac, weight);
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
            }
        }
        else if (encoding.compare("APAAC") == 0)
        {
            string properties[2] = {"Hydrophobicity", "Hydrophilicity"};
            headers.push_back("name");
            for (char c : allowed)
            {
                string key(1, c);
                headers.push_back(key);
                keys.push_back(key);
            }
            for (int i = 1; i <= lag; i++)
            {
                for (string prop : properties)
                {
                    string key = prop;
                    key.push_back('-');
                    key += to_string(i);
                    headers.push_back(key);
                    keys.push_back(key);
                }
            }

            #pragma omp parallel for num_threads(numThreads) \
                default(none) shared(seqNames, encoded, seqs, names, allowed, keys, lag, order, paac, properties, weight) schedule(guided) 
            for (int i = 0; i < seqs.size(); i++)
            {
                vector<double> encodedProtein = APAAC(seqs[i], allowed, keys, lag, order, paac, properties, weight);
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
            }
        }
    }

    else if (encoding.compare("AAI") == 0)
    {
        int seqLength = checkFastaSameLength(seqs);
        if(seqLength == -1)
        {
            bool crop = argumentExists(argv, argv + argc, "--crop");
            if (crop)
            {
                seqLength = getMinSequenceLength(names, seqs);
                cropSequences(seqs, seqLength);
            }
            else
            {
                cout << "Error: All sequences must have the same length. You can use the --crop argument, so it crops the sequences automatically.\n";
                return 0;
            }
        }

        // Order of amino acids in the indices
        string stringOrder = "ARNDCQEGHILKMFPSTWYV";
        map<char, int> order;
        for (int i = 0; i < 20; i++)
        {
            order[stringOrder[i]] = i;
        }

        // Read indices file
        map<string, array<double, 20>> indexData;
        vector<string> indexList;
        string filePath = dataDir + "AAidx.txt";
        ifstream file(filePath);
        string line;
        getline(file, line); // Skip the first line
        while (getline(file, line))
        {
            size_t pos = line.find('\t');
            string index = line.substr(0, pos);
            string token;
            array<double, 20> values;
            line.erase(0, pos + 1);
            int counter = 0;
            while ((pos = line.find('\t')) != string::npos) 
            {
                token = line.substr(0, pos);
                if (token.compare("NA") == 0)
                    goto endLoop;
                values[counter] = stof(token);
                counter++;
                line.erase(0, pos + 1);
            }
            values[19] = stof(line);
            indexData[index] = values;
            indexList.push_back(index);
            endLoop:;
        }

        headers.push_back("name");
        for (int i = 1; i <= seqLength; i++)
        {
            for (string index : indexList)
            {
                string key = to_string(i);
                key.push_back('-');
                key += index;
                headers.push_back(key);
                keys.push_back(key);
            }
        }

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, keys, order, indexData, indexList) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            vector<double> encodedProtein = AAINDEX(seqs[i], keys, order, indexData, indexList);
            #pragma omp critical
            {
                seqNames.push_back(names[i]);
                encoded.push_back(encodedProtein);
            }
        }
    }

    else if (encoding.compare("BLOSUM62") == 0)
    {
        int seqLength = checkFastaSameLength(seqs);
        if(seqLength == -1)
        {
            bool crop = argumentExists(argv, argv + argc, "--crop");
            if (crop)
            {
                seqLength = getMinSequenceLength(names, seqs);
                cropSequences(seqs, seqLength);
            }
            else
            {
                cout << "Error: All sequences must have the same length. You can use the --crop argument, so it crops the sequences automatically.\n";
                return 0;
            }
        }

        map<char, array<double, 20>> blosum = getBlosum();

        headers.push_back("name");
        for (int i = 1; i <= seqLength; i++)
        {
            for (char c : allowed)
            {
                string key = to_string(i);
                key.push_back('-');
                key.push_back(c);
                headers.push_back(key);
                keys.push_back(key);
            }
        }

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, keys, blosum) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            vector<double> encodedProtein = BLOSUM62(seqs[i], keys, blosum);
            #pragma omp critical
            {
                seqNames.push_back(names[i]);
                encoded.push_back(encodedProtein);
            }
        }
    }

    else if (encoding.compare("ZS") == 0)
    {
        int seqLength = checkFastaSameLength(seqs);
        if(seqLength == -1)
        {
            bool crop = argumentExists(argv, argv + argc, "--crop");
            if (crop)
            {
                seqLength = getMinSequenceLength(names, seqs);
                cropSequences(seqs, seqLength);
            }
            else
            {
                cout << "Error: All sequences must have the same length. You can use the --crop argument, so it crops the sequences automatically.\n";
                return 0;
            }
        }

        // Z-SCALE
        map<char, array<double, 5>> zscale;
        zscale['A'] = {0.24,  -2.32,  0.60, -0.14,  1.30};
		zscale['C'] = {0.84,  -1.67,  3.71,  0.18, -2.65};
		zscale['D'] = {3.98,   0.93,  1.93, -2.46,  0.75};
		zscale['E'] = {3.11,   0.26, -0.11, -0.34, -0.25};
		zscale['F'] = {-4.22,  1.94,  1.06,  0.54, -0.62};
		zscale['G'] = {2.05,  -4.06,  0.36, -0.82, -0.38};
		zscale['H'] = {2.47,   1.95,  0.26,  3.90,  0.09};
		zscale['I'] = {-3.89, -1.73, -1.71, -0.84,  0.26};
		zscale['K'] = {2.29,   0.89, -2.49,  1.49,  0.31};
		zscale['L'] = {-4.28, -1.30, -1.49, -0.72,  0.84};
		zscale['M'] = {-2.85, -0.22,  0.47,  1.94, -0.98};
		zscale['N'] = {3.05,   1.62,  1.04, -1.15,  1.61};
		zscale['P'] = {-1.66,  0.27,  1.84,  0.70,  2.00};
		zscale['Q'] = {1.75,   0.50, -1.44, -1.34,  0.66};
		zscale['R'] = {3.52,   2.50, -3.50,  1.99, -0.17};
		zscale['S'] = {2.39,  -1.07,  1.15, -1.39,  0.67};
		zscale['T'] = {0.75,  -2.18, -1.12, -1.46, -0.40};
		zscale['V'] = {-2.59, -2.64, -1.54, -0.85, -0.02};
		zscale['W'] = {-4.36,  3.94,  0.59,  3.44, -1.59};
		zscale['Y'] = {-2.54,  2.44,  0.43,  0.04, -1.47};

        headers.push_back("name");
        for (int i = 1; i <= seqLength; i++)
        {
            for (int j = 1; j <= 5; j++)
            {
                string key = to_string(i);
                key.push_back('-');
                key += to_string(j);
                headers.push_back(key);
                keys.push_back(key);
            }
        }

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, keys, zscale) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            vector<double> encodedProtein = ZSCALE(seqs[i], keys, zscale);
            #pragma omp critical
            {
                seqNames.push_back(names[i]);
                encoded.push_back(encodedProtein);
            }
        }
    }

    // Secondary structure (PSIPRED, SPINE-X, SPIDER3)
    else if (encoding.compare("SSEB") == 0 || encoding.compare("SSEC") == 0 || encoding.compare("SSPB") == 0 || encoding.compare("SSPAC") == 0)
    {
        int n = 10;
        string path = getArgument(argv, argv + argc, "--path");
        if (path == "")
        {
            cout << "Error: A path where .ss2, .spd33 or .spXout files are located is needed. Use the --path <path> argument.\n";
            return 0;
        }
        
        bool generate = argumentExists(argv, argv + argc, "--generate");
        int pathExists = directoryExists(path);
        if (pathExists == -1)
            return 0;
        else if (!generate && pathExists == 0)
        {
            cout << "Error: The path does not exist.\n";
            return 0;
        }
        else if (generate)
        {
            // Generate SSE files
        }

        map<char, array<int, 3>> typesB = {{'H', {1, 0, 0}}, {'E', {0, 1, 0}}, {'C', {0, 0, 1}}};
        array<char, 3> typesC = {'H', 'E', 'C'};
        
        headers.push_back("name");

        if (encoding.compare("SSEB") == 0)
        {
            int seqLength = checkFastaSameLength(seqs);
            if (seqLength == -1)
            {
                bool crop = argumentExists(argv, argv + argc, "--crop");
                if (crop)
                {
                    seqLength = getMinSequenceLength(names, seqs);
                    cropSequences(seqs, seqLength);
                }
                else
                {
                    cout << "Error: All sequences must have the same length. You can use the --crop argument, so it crops the sequences automatically.\n";
                    return 0;
                }
            }
            for (int i = 1; i <= seqLength; i++)
            {
                for (auto &kvp : typesB)
                {
                    string key = to_string(i);
                    key.push_back('-');
                    key.push_back(kvp.first);
                    headers.push_back(key);
                    keys.push_back(key);
                }
            }
        }
        else if (encoding.compare("SSEC") == 0)
        {
            for (char c : typesC)
            {
                string key(1, c);
                headers.push_back(key);
                keys.push_back(key);
            }
        }
        else if (encoding.compare("SSPB") == 0)
        {
            n = 1;
            string nS = getArgument(argv, argv + argc, "--n");
            if (nS != "")
            {
                if (!isNumber(nS))
                {
                    cout << "Error: The n value must be a number greater or equal than 1.\n";
                    return 0;
                }
                n = stoi(nS);
                if (n < 1)
                {
                    cout << "Error: The n value must be a number greater or equal than 1.\n";
                    return 0;
                }
            }
            int minLength = getMinSequenceLength(names, seqs);
            if(minLength < n + 1)
            {
                cout << "Error: All sequences length must be equal or greater than n + 1.\n";
                return 0;
            }
            for (char c : typesC)
            {
                for (char d : typesC)
                {
                    string key(1, c);
                    key.push_back(d);
                    headers.push_back(key);
                    keys.push_back(key);
                }
            }
        }
        else if (encoding.compare("SSPAC") == 0)
        {
            string nS = getArgument(argv, argv + argc, "--n");
            if (nS != "")
            {
                if (!isNumber(nS))
                {
                    cout << "Error: The n value must be a number greater or equal than 1.\n";
                    return 0;
                }
                n = stoi(nS);
                if (n < 1)
                {
                    cout << "Error: The n value must be a number greater or equal than 1.\n";
                    return 0;
                }
            }
            int minLength = getMinSequenceLength(names, seqs);
            if(minLength < n + 1)
            {
                cout << "Error: All sequences length must be equal or greater than n + 1.\n";
                return 0;
            }
            for (int i = 1; i <= n; i++)
            {
                string iString = to_string(i);
                for (char c : typesC)
                {
                    string key = iString;
                    key.push_back(c);
                    headers.push_back(key);
                    keys.push_back(key);
                }
            }    
                
        }

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, allowed, keys, path, typesB, typesC, n, cout, encoding) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            ifstream file1(path + "/" + names[i] + ".ss2");
            ifstream file2(path + "/" + names[i] + ".spd33");
            ifstream file3(path + "/" + names[i] + ".spXout");
            if (!file1 && !file2 && !file3) 
                cout << "No predicted secondary structure files (.ss2, .spd33 or spXout) found for sequence " << names[i] << "." << endl;
            else if (!file2 && !file3 && !file1.is_open()) 
                cout << "File " << names[i] << ".ss2 could not be opened." << endl;
            else if (!file1 && !file3 && !file2.is_open()) 
                cout << "File " << names[i] << ".spd33 could not be opened." << endl;
            else if (!file1 && !file2 && !file3.is_open()) 
                cout << "File " << names[i] << ".spXout could not be opened." << endl;
            else if (!file1.is_open() && !file2.is_open() && !file3.is_open()) 
                cout << "Secondary structure files (.ss2, .spd33 or spXout) for sequence " << names[i] << " could not be opened." << endl;
            else
            {
                vector<double> encodedProtein;
                if (encoding.compare("SSEB") == 0)
                {
                    if (file1.is_open())
                        encodedProtein = SSEB(seqs[i], names[i], allowed, keys, file1, typesB, "ss2");
                    else if (file2.is_open())
                        encodedProtein = SSEB(seqs[i], names[i], allowed, keys, file2, typesB, "spd33");
                    else if (file3.is_open())
                        encodedProtein = SSEB(seqs[i], names[i], allowed, keys, file3, typesB, "spXout");
                }
                else if (encoding.compare("SSEC") == 0)
                {
                    if (file1.is_open())
                        encodedProtein = SSEC(seqs[i], names[i], allowed, keys, file1, typesC, "ss2");
                    else if (file2.is_open())
                        encodedProtein = SSEC(seqs[i], names[i], allowed, keys, file2, typesC, "spd33");
                    else if (file3.is_open())
                        encodedProtein = SSEC(seqs[i], names[i], allowed, keys, file3, typesC, "spXout");
                }
                else if (encoding.compare("SSPB") == 0)
                {
                    if (file1.is_open())
                        encodedProtein = SSPB(seqs[i], names[i], allowed, keys, n, file1, typesC, "ss2");
                    else if (file2.is_open())
                        encodedProtein = SSPB(seqs[i], names[i], allowed, keys, n, file2, typesC, "spd33");
                    else if (file3.is_open())
                        encodedProtein = SSPB(seqs[i], names[i], allowed, keys, n, file3, typesC, "spXout");
                }
                else if (encoding.compare("SSPAC") == 0)
                {
                    if (file1.is_open())
                        encodedProtein = SSPAC(seqs[i], names[i], allowed, keys, n, file1, typesC, "ss2");
                    else if (file2.is_open())
                        encodedProtein = SSPAC(seqs[i], names[i], allowed, keys, n, file2, typesC, "spd33");
                    else if (file3.is_open())
                        encodedProtein = SSPAC(seqs[i], names[i], allowed, keys, n, file3, typesC, "spXout");
                }
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
            }
        }
    }

    // Disorder (fldpnn)
    else if (encoding.compare("Disorder") == 0)
    {
        int seqLength = checkFastaSameLength(seqs);
        if (seqLength == -1)
        {
            bool crop = argumentExists(argv, argv + argc, "--crop");
            if (crop)
            {
                seqLength = getMinSequenceLength(names, seqs);
                cropSequences(seqs, seqLength);
            }
            else
            {
                cout << "Error: All sequences must have the same length. You can use the --crop argument, so it crops the sequences automatically.\n";
                return 0;
            }
        }

        string path = getArgument(argv, argv + argc, "--path");
        if (path == "")
        {
            cout << "Error: A path for loading .csv files is needed. Use the --path <path> argument.\n";
            return 0;
        }
        
        bool generate = argumentExists(argv, argv + argc, "--generate");
        int pathExists = directoryExists(path);
        if (pathExists == -1)
            return 0;
        else if (!generate && pathExists == 0)
        {
            cout << "Error: The path does not exist.\n";
            return 0;
        }
        else if (generate)
        {
            // Generate disorder files
        }

        headers.push_back("name");
        for (int i = 1; i <= seqLength; i++)
        {
            string key = to_string(i);
            headers.push_back(key);
            keys.push_back(key);
        }

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, allowed, keys, path, cout) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            ifstream file;
            file.open(path + "/" + names[i] + ".csv");
            if (!file) 
            {
                cout << "File " << names[i] << ".csv does not exist." << endl;
            }
            else if (file.is_open())
            {
                vector<double> encodedProtein = Disorder(seqs[i], names[i], allowed, keys, file);
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
                file.close();
            }
            else
            {
                cout << "File " << names[i] << ".csv cannot be opened." << endl;
            }
        }
    }

    else if (encoding.compare("DisorderC") == 0)
    {
        string path = getArgument(argv, argv + argc, "--path");
        if (path == "")
        {
            cout << "Error: A path for saving or loading .csv files is needed. Use the --path <path> argument.\n";
            return 0;
        }
        
        bool generate = argumentExists(argv, argv + argc, "--generate");
        int pathExists = directoryExists(path);
        if (pathExists == -1)
            return 0;
        else if (!generate && pathExists == 0)
        {
            cout << "Error: The path does not exist.\n";
            return 0;
        }
        else if (generate)
        {
            // Generate disorder files
        }

        headers.push_back("name");
        headers.push_back("disorder");
        headers.push_back("order");
        

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, allowed, keys, path, cout) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            ifstream file;
            file.open(path + "/" + names[i] + ".csv");
            if (!file) 
            {
                cout << "File " << names[i] << ".csv does not exist." << endl;
            }
            else if (file.is_open())
            {
                vector<double> encodedProtein = DisorderC(seqs[i], names[i], allowed, keys, file);
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
                file.close();
            }
            else
            {
                cout << "File " << names[i] << ".csv cannot be opened." << endl;
            }
        }
    }

    else if (encoding.compare("DisorderB") == 0)
    {
        int seqLength = checkFastaSameLength(seqs);
        if (seqLength == -1)
        {
            bool crop = argumentExists(argv, argv + argc, "--crop");
            if (crop)
            {
                seqLength = getMinSequenceLength(names, seqs);
                cropSequences(seqs, seqLength);
            }
            else
            {
                cout << "Error: All sequences must have the same length. You can use the --crop argument, so it crops the sequences automatically.\n";
                return 0;
            }
        }

        string path = getArgument(argv, argv + argc, "--path");
        if (path == "")
        {
            cout << "Error: A path for saving or loading .csv files is needed. Use the --path <path> argument.\n";
            return 0;
        }
        
        bool generate = argumentExists(argv, argv + argc, "--generate");
        int pathExists = directoryExists(path);
        if (pathExists == -1)
            return 0;
        else if (!generate && pathExists == 0)
        {
            cout << "Error: The path does not exist.\n";
            return 0;
        }
        else if (generate)
        {
            // Generate disorder files
        }

        headers.push_back("name");
        for (int i = 1; i <= seqLength; i++)
        {
            string key = to_string(i);
            headers.push_back(key + "-order");
            keys.push_back(key + "-order");
            headers.push_back(key + "-disorder");
            keys.push_back(key + "-disorder");
        }

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, allowed, keys, path, cout) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            ifstream file;
            file.open(path + "/" + names[i] + ".csv");
            if (!file) 
            {
                cout << "File " << names[i] << ".csv does not exist." << endl;
            }
            else if (file.is_open())
            {
                vector<double> encodedProtein = DisorderB(seqs[i], names[i], allowed, keys, file);
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
                file.close();
            }
            else
            {
                cout << "File " << names[i] << ".csv cannot be opened." << endl;
            }
        }
    }

    // Torsion (Spine-X)
    else if (encoding.compare("TA") == 0 || encoding.compare("TAC") == 0 || encoding.compare("TAB") == 0 || encoding.compare("TAAC") == 0)
    {
        int n = 10;

        string path = getArgument(argv, argv + argc, "--path");
        if (path == "")
        {
            cout << "Error: A path for loading .spd33 or .spXout files is needed. Use the --path <path> argument.\n";
            return 0;
        }
        
        bool generate = argumentExists(argv, argv + argc, "--generate");
        int pathExists = directoryExists(path);
        if (pathExists == -1)
            return 0;
        else if (!generate && pathExists == 0)
        {
            cout << "Error: The path does not exist.\n";
            return 0;
        }
        else if (generate)
        {
            // Generate disorder files
        }

        headers.push_back("name");

        if (encoding.compare("TA") == 0)
        {
            int seqLength = checkFastaSameLength(seqs);
            if (seqLength == -1)
            {
                bool crop = argumentExists(argv, argv + argc, "--crop");
                if (crop)
                {
                    seqLength = getMinSequenceLength(names, seqs);
                    cropSequences(seqs, seqLength);
                }
                else
                {
                    cout << "Error: All sequences must have the same length. You can use the --crop argument, so it crops the sequences automatically.\n";
                    return 0;
                }
            }
            for (int i = 1; i <= seqLength; i++)
            {
                string key = to_string(i);
                headers.push_back(key + "-phi");
                keys.push_back(key + "-phi");
                headers.push_back(key + "-psi");
                keys.push_back(key + "-psi");
            }
        }
        else if (encoding.compare("TAC") == 0)
        {
            headers.push_back("phiSin");
            headers.push_back("phiCos");
            headers.push_back("psiSin");
            headers.push_back("psiCos");
            keys.push_back("phiSin");
            keys.push_back("phiCos");
            keys.push_back("psiSin");
            keys.push_back("psiCos");            
        }
        else if (encoding.compare("TAB") == 0)
        {
            n = 1;
            string nS = getArgument(argv, argv + argc, "--n");
            if (nS != "")
            {
                if (!isNumber(nS))
                {
                    cout << "Error: The n value must be a number greater or equal than 1.\n";
                    return 0;
                }
                n = stoi(nS);
                if (n < 1)
                {
                    cout << "Error: The n value must be a number greater or equal than 1.\n";
                    return 0;
                }
            }
            int minLength = getMinSequenceLength(names, seqs);
            if(minLength < n + 1)
            {
                cout << "Error: All sequences length must be equal or greater than n + 1.\n";
                return 0;
            }
            headers.push_back("phiSin-phiSin");
            headers.push_back("phiSin-phiCos");
            headers.push_back("phiSin-psiSin");
            headers.push_back("phiSin-psiCos");
            headers.push_back("phiCos-phiCos");
            headers.push_back("phiCos-psiSin");
            headers.push_back("phiCos-psiCos");
            headers.push_back("psiSin-psiSin");
            headers.push_back("psiSin-psiCos");
            headers.push_back("psiCos-psiCos");
            keys.push_back("phiSin-phiSin");
            keys.push_back("phiSin-phiCos");
            keys.push_back("phiSin-psiSin");
            keys.push_back("phiSin-psiCos");
            keys.push_back("phiCos-phiCos");
            keys.push_back("phiCos-psiSin");
            keys.push_back("phiCos-psiCos");
            keys.push_back("psiSin-psiSin");
            keys.push_back("psiSin-psiCos");
            keys.push_back("psiCos-psiCos");
        }
        else if (encoding.compare("TAAC") == 0)
        {
            string nS = getArgument(argv, argv + argc, "--n");
            if (nS != "")
            {
                if (!isNumber(nS))
                {
                    cout << "Error: The n value must be a number greater or equal than 1.\n";
                    return 0;
                }
                n = stoi(nS);
                if (n < 1)
                {
                    cout << "Error: The n value must be a number greater or equal than 1.\n";
                    return 0;
                }
            }
            int minLength = getMinSequenceLength(names, seqs);
            if(minLength < n + 1)
            {
                cout << "Error: All sequences length must be equal or greater than n + 1.\n";
                return 0;
            }
            for (int i = 1; i <= n; i++)
            {
                string key = to_string(i);
                headers.push_back(key + "-phiSin");
                headers.push_back(key + "-phiCos");
                headers.push_back(key + "-psiSin");
                headers.push_back(key + "-psiCos");
                keys.push_back(key + "-phiSin");
                keys.push_back(key + "-phiCos");
                keys.push_back(key + "-psiSin");
                keys.push_back(key + "-psiCos");  
            }          
        }

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, allowed, keys, n, path, cout, encoding) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            ifstream file1(path + "/" + names[i] + ".spd33");
            ifstream file2(path + "/" + names[i] + ".spXout");

            if (!file1 && !file2) 
                cout << "No torsion angles files (.spd3 or spXout) found for sequence " << names[i] << "." << endl;
            else if (!file1 && !file2.is_open())
                cout << "File " << names[i] << ".spd33 could not be opened." << endl;
            else if (!file2 && !file1.is_open())
                cout << "File " << names[i] << ".spXout could not be opened." << endl;
            else
            {
                vector<double> encodedProtein;
                if (file1.is_open())
                {
                    if (encoding.compare("TA") == 0)
                        encodedProtein = TA(seqs[i], names[i], allowed, keys, file1, "spd33");
                    if (encoding.compare("TAC") == 0)
                        encodedProtein = TAC(seqs[i], names[i], allowed, keys, file1, "spd33");
                    if (encoding.compare("TAB") == 0)
                        encodedProtein = TAB(seqs[i], names[i], allowed, keys, n, file1, "spd33");
                    if (encoding.compare("TAAC") == 0)
                        encodedProtein = TAAC(seqs[i], names[i], allowed, keys, n, file1, "spd33");
                }
                else
                {
                    if (encoding.compare("TA") == 0)
                        encodedProtein = TA(seqs[i], names[i], allowed, keys, file2, "spXout");
                    if (encoding.compare("TAC") == 0)
                        encodedProtein = TAC(seqs[i], names[i], allowed, keys, file2, "spXout");
                    if (encoding.compare("TAB") == 0)
                        encodedProtein = TAB(seqs[i], names[i], allowed, keys, n, file2, "spXout");
                    if (encoding.compare("TAAC") == 0)
                        encodedProtein = TAAC(seqs[i], names[i], allowed, keys, n, file2, "spXout");
                }
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
            }
        }
    }

    // Accessible Solvent Accessibility (Spine-X or SPIDER3)
    else if (encoding.compare("ASA") == 0)
    {
        int seqLength = checkFastaSameLength(seqs);
        if (seqLength == -1)
        {
            bool crop = argumentExists(argv, argv + argc, "--crop");
            if (crop)
            {
                seqLength = getMinSequenceLength(names, seqs);
                cropSequences(seqs, seqLength);
            }
            else
            {
                cout << "Error: All sequences must have the same length. You can use the --crop argument, so it crops the sequences automatically.\n";
                return 0;
            }
        }

        string path = getArgument(argv, argv + argc, "--path");
        if (path == "")
        {
            cout << "Error: A path for loading .spd33 or .spXout files is needed. Use the --path <path> argument.\n";
            return 0;
        }
        
        bool generate = argumentExists(argv, argv + argc, "--generate");
        int pathExists = directoryExists(path);
        if (pathExists == -1)
            return 0;
        else if (!generate && pathExists == 0)
        {
            cout << "Error: The path does not exist.\n";
            return 0;
        }
        else if (generate)
        {
            // Generate ASA files
        }

        headers.push_back("name");
        for (int i = 1; i <= seqLength; i++)
        {
            string key = to_string(i);
            headers.push_back(key);
            keys.push_back(key);
        }

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, allowed, keys, path, cout) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            ifstream file1(path + "/" + names[i] + ".spd33");
            ifstream file2(path + "/" + names[i] + ".spXout");

            if (!file1 && !file2) 
                cout << "No torsion angles files (.spd3 or spXout) found for sequence " << names[i] << "." << endl;
            else if (!file1 && !file2.is_open())
                cout << "File " << names[i] << ".spd33 could not be opened." << endl;
            else if (!file2 && !file1.is_open())
                cout << "File " << names[i] << ".spXout could not be opened." << endl;
            else
            {
                vector<double> encodedProtein;
                if (file1.is_open())
                {
                    encodedProtein = ASA(seqs[i], names[i], allowed, keys, file1, "spd33");
                }
                else
                {
                    encodedProtein = ASA(seqs[i], names[i], allowed, keys, file2, "spXout");
                }
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
            }
        }
    }

    // K-nearest neighbor, train and test files
    else if (encoding.compare("KNNprotein") == 0 || encoding.compare("KNNpeptide") == 0)
    {
        int k = 30;
        string kS = getArgument(argv, argv + argc, "--k");
        if (kS != "")
        {
            if (!isNumber(kS))
            {
                cout << "Error: The k value must be a number between 1 and 100.\n";
                return 0;
            }
            k = stoi(kS);
            if (k < 1)
            {
                cout << "Error: The k value must be a number between 1 and 100.\n";
                return 0;
            }
        }

        string trainPath = getArgument(argv, argv + argc, "--train");
        if (trainPath == "")
        {
            cout << "Error: A training file is needed. Use the --train <path> argument.\n";
            return 0;
        }

        string labelsPath = getArgument(argv, argv + argc, "--labels");
        if (labelsPath == "")
        {
            cout << "Error: A label file for the training file is needed. Use the --labels <path> argument.\n";
            return 0;
        }

        // Read training file
        vector<string> trainNames;
        vector<string> trainSeqs;
        if (!readFasta(trainPath, trainNames, trainSeqs))
        {
            cout << "Error: Cannot open training file.\n";
            return 0;
        }
        
        int trainLen = trainNames.size();
        // Terminate if no valid sequences are found
        if (trainLen == 0)
        {
            cout << "Error: The training file has no valid fasta sequences.\n";
            return 0;
        }

        // Read labels file
        map<string, string> labelsData;
        set<string> labels;
        int labelsLen = 0;
        ifstream file2(labelsPath);
        if (file2.is_open())
        {
            string line;
            while (getline(file2, line))
            {
                string name;
                string label = "";
                int counter = 0;
                istringstream iss(line);
                for (string line; iss >> line; counter++) 
                {
                    if (counter == 0)
                        name = line;
                    else if (counter == 1)
                        label = line;
                    else
                        break;
                }
                if (label != "")
                {
                    labelsData[name] = label;
                    labels.insert(label);
                    labelsLen++;
                }
            }
            file2.close();
        }
        else
        {
            cout << "Error: Cannot open labels file.\n";
            return 0;
        }

        if (labelsLen != trainLen)
        {
            cout << "Error: The training and labels files have different number of sequences.\n";
            return 0;
        }  
        if (labels.size() > k)
        {
            cout << "Error: The number of classes in the labels file must be greater than k. Found " << labels.size() << " classes." << endl;
        }

        if (encoding.compare("KNNpeptide") == 0)
        {
            int seqLength = checkFastaSameLength(seqs);
            if (seqLength == -1)
            {
                bool crop = argumentExists(argv, argv + argc, "--crop");
                if (crop)
                {
                    seqLength = getMinSequenceLength(names, seqs);
                    int trainLength = getMinSequenceLength(trainNames, trainSeqs);
                    if (trainLength < seqLength)
                    {
                        seqLength = trainLength;
                    }
                    cropSequences(seqs, seqLength);
                }
                else
                {
                    cout << "Error: All sequences must have the same length. You can use the --crop argument, so it crops the sequences automatically.\n";
                    return 0;
                }
            }

            bool crop = argumentExists(argv, argv + argc, "--crop");
            bool sameLength = false;
            for (string seq : trainSeqs)
            {
                if (seq.length() != seqLength)
                {
                    if (crop) 
                    {
                        break;
                    }
                    else
                    {
                        cout << "Error: The sequences in the training and input files do not have the same length. You can use the --crop argument, so it crops the sequences automatically.\n";
                        return 0;
                    }
                }
                else
                {
                    sameLength = true;
                }
            }
            if (crop && !sameLength)
            {
                cropSequences(trainSeqs, seqLength);
            }
        }
        
        vector<int> kNums;
        for (int i = 1; i <= k; i++)
        {
            kNums.push_back(ceil(trainLen * i * 0.01));
        }

        map<char, array<double, 20>> blosum = getBlosum();

        // Order of amino acids in the indices
        string stringOrder = "ARNDCQEGHILKMFPSTWYV";
        map<char, int> order;
        for (int i = 0; i < 20; i++)
        {
            order[stringOrder[i]] = i;
        }
        
        headers.push_back("name");
        for (int i = 1; i <= k; i++)
        {
            for (string label : labels)
            {
                stringstream stream;
                stream << fixed << setprecision(2) << (i * 0.01);
                string key = stream.str();
                key.push_back('-');
                key += label;
                headers.push_back(key);
                keys.push_back(key);
            }
        }

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, keys, blosum, order, trainNames, trainSeqs, labelsData, labels, kNums, encoding) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            vector<double> encodedProtein;
            if (encoding.compare("KNNpeptide") == 0)
                encodedProtein = KNNpeptide(seqs[i], names[i], keys, blosum, order, trainNames, trainSeqs, labelsData, labels, kNums);
            else if (encoding.compare("KNNprotein") == 0)
                encodedProtein = KNNprotein(seqs[i], names[i], keys, blosum, order, trainNames, trainSeqs, labelsData, labels, kNums);
            #pragma omp critical
            {
                seqNames.push_back(names[i]);
                encoded.push_back(encodedProtein);
            }
        }
    }

    // Amino acid pair antigenicity scale
    else if (encoding.compare("AAPAS") == 0)
    {
        #pragma region Populate frequencies

        map<string, double> freqs;
        freqs["AA"] = -0.28257;
        freqs["RA"] = 0.71024;
        freqs["NA"] = -0.13778;
        freqs["DA"] = -0.0198;
        freqs["CA"] = -0.65393;
        freqs["EA"] = -0.4111;
        freqs["QA"] = -0.46702;
        freqs["GA"] = -0.74943;
        freqs["HA"] = -0.17435;
        freqs["IA"] = -1.12601;
        freqs["LA"] = -0.23484;
        freqs["KA"] = 0.04317;
        freqs["MA"] = -0.20067;
        freqs["FA"] = -0.63908;
        freqs["PA"] = -0.36179;
        freqs["SA"] = -0.42744;
        freqs["TA"] = -0.10265;
        freqs["WA"] = 0.24116;
        freqs["YA"] = -0.06062;
        freqs["VA"] = 0.08961;
        freqs["AR"] = 0.12516;
        freqs["RR"] = 1.24522;
        freqs["NR"] = 0.60614;
        freqs["DR"] = 0.18232;
        freqs["CR"] = 0.33647;
        freqs["ER"] = 0.07551;
        freqs["QR"] = -0.05557;
        freqs["GR"] = -0.56581;
        freqs["HR"] = 0.08338;
        freqs["IR"] = -0.20972;
        freqs["LR"] = -0.09716;
        freqs["KR"] = 0.0202;
        freqs["MR"] = -2.33537;
        freqs["FR"] = 0.539;
        freqs["PR"] = 0.80235;
        freqs["SR"] = 0.33314;
        freqs["TR"] = 0.21131;
        freqs["WR"] = -0.25131;
        freqs["YR"] = 0.51083;
        freqs["VR"] = 0.12361;
        freqs["AN"] = 0.12783;
        freqs["RN"] = 0.26469;
        freqs["NN"] = 0.02985;
        freqs["DN"] = -0.34628;
        freqs["CN"] = -1.0116;
        freqs["EN"] = 0.16942;
        freqs["QN"] = 0.93609;
        freqs["GN"] = -0.38193;
        freqs["HN"] = 0.16705;
        freqs["IN"] = -0.35667;
        freqs["LN"] = -0.2737;
        freqs["KN"] = 1.02339;
        freqs["MN"] = -0.40547;
        freqs["FN"] = 0.24362;
        freqs["PN"] = 0.8391;
        freqs["SN"] = 0.01709;
        freqs["TN"] = -0.14108;
        freqs["WN"] = 0.47;
        freqs["YN"] = -0.03279;
        freqs["VN"] = 0.04879;
        freqs["AD"] = -0.48059;
        freqs["RD"] = 0.23052;
        freqs["ND"] = 0.32158;
        freqs["DD"] = 0.11123;
        freqs["CD"] = 0.45199;
        freqs["ED"] = 1.0229;
        freqs["QD"] = 0.61619;
        freqs["GD"] = 0.05311;
        freqs["HD"] = 0.23639;
        freqs["ID"] = 0.13353;
        freqs["LD"] = 0.13762;
        freqs["KD"] = 0.19913;
        freqs["MD"] = 1.13943;
        freqs["FD"] = 0.07411;
        freqs["PD"] = 0.42845;
        freqs["SD"] = 0.38777;
        freqs["TD"] = -0.76214;
        freqs["WD"] = 1.94591;
        freqs["YD"] = -0.2036;
        freqs["VD"] = 0.02151;
        freqs["AC"] = -0.6131;
        freqs["RC"] = -1.38629;
        freqs["NC"] = 0.32542;
        freqs["DC"] = -0.40547;
        freqs["CC"] = 0.09531;
        freqs["EC"] = -0.26826;
        freqs["QC"] = -0.9694;
        freqs["GC"] = 0.37949;
        freqs["HC"] = -0.91629;
        freqs["IC"] = -0.43078;
        freqs["LC"] = -0.38566;
        freqs["KC"] = 0.05129;
        freqs["MC"] = -2.89037;
        freqs["FC"] = -0.54654;
        freqs["PC"] = 0.10008;
        freqs["SC"] = -0.22314;
        freqs["TC"] = -0.05129;
        freqs["WC"] = 0;
        freqs["YC"] = -0.25593;
        freqs["VC"] = -0.89794;
        freqs["AE"] = 0.05196;
        freqs["RE"] = 0.04445;
        freqs["NE"] = -0.53166;
        freqs["DE"] = 0.39939;
        freqs["CE"] = -0.45199;
        freqs["EE"] = 0.35105;
        freqs["QE"] = -0.3234;
        freqs["GE"] = -0.85823;
        freqs["HE"] = 0.12516;
        freqs["IE"] = -0.04763;
        freqs["LE"] = 0.11653;
        freqs["KE"] = -0.04763;
        freqs["ME"] = -0.16034;
        freqs["FE"] = -0.34294;
        freqs["PE"] = 0.11123;
        freqs["SE"] = -0.40547;
        freqs["TE"] = 0.0177;
        freqs["WE"] = -0.31845;
        freqs["YE"] = 1.1421;
        freqs["VE"] = 0.36772;
        freqs["AQ"] = 0.07696;
        freqs["RQ"] = 0;
        freqs["NQ"] = -0.57335;
        freqs["DQ"] = 0.39087;
        freqs["CQ"] = -0.45199;
        freqs["EQ"] = 0.40547;
        freqs["QQ"] = 0.22314;
        freqs["GQ"] = -0.01942;
        freqs["HQ"] = 0.48955;
        freqs["IQ"] = -0.06669;
        freqs["LQ"] = -0.13555;
        freqs["KQ"] = 0.08004;
        freqs["MQ"] = -1.27297;
        freqs["FQ"] = 0.04082;
        freqs["PQ"] = 0.59912;
        freqs["SQ"] = 0.27065;
        freqs["TQ"] = -0.29546;
        freqs["WQ"] = -0.69315;
        freqs["YQ"] = 0;
        freqs["VQ"] = 0.08224;
        freqs["AG"] = -0.86148;
        freqs["RG"] = -0.1752;
        freqs["NG"] = 0.09097;
        freqs["DG"] = -0.30421;
        freqs["CG"] = -1.26369;
        freqs["EG"] = 0.04512;
        freqs["QG"] = -0.49644;
        freqs["GG"] = -0.01626;
        freqs["HG"] = 0.25783;
        freqs["IG"] = -0.31845;
        freqs["LG"] = 0.08004;
        freqs["KG"] = -0.86114;
        freqs["MG"] = -0.55962;
        freqs["FG"] = 0.12063;
        freqs["PG"] = -1.0486;
        freqs["SG"] = -0.19167;
        freqs["TG"] = 0;
        freqs["WG"] = 0.16252;
        freqs["YG"] = 0.36772;
        freqs["VG"] = -0.26933;
        freqs["AH"] = 0.83291;
        freqs["RH"] = 0.6614;
        freqs["NH"] = -0.65393;
        freqs["DH"] = 0.24116;
        freqs["CH"] = 2.19722;
        freqs["EH"] = 0.13353;
        freqs["QH"] = 0.18232;
        freqs["GH"] = 0;
        freqs["HH"] = -0.26236;
        freqs["IH"] = -0.45953;
        freqs["LH"] = -0.44183;
        freqs["KH"] = 0.27193;
        freqs["MH"] = 1.25276;
        freqs["FH"] = 0.51083;
        freqs["PH"] = 0.89382;
        freqs["SH"] = -0.21131;
        freqs["TH"] = 0.56798;
        freqs["WH"] = 1.94591;
        freqs["YH"] = 0.76214;
        freqs["VH"] = -0.69315;
        freqs["AI"] = -0.34175;
        freqs["RI"] = -0.30368;
        freqs["NI"] = 0.33213;
        freqs["DI"] = -0.01942;
        freqs["CI"] = -0.18232;
        freqs["EI"] = 0.15719;
        freqs["QI"] = -0.48551;
        freqs["GI"] = -0.44731;
        freqs["HI"] = -0.5213;
        freqs["II"] = -0.60977;
        freqs["LI"] = -0.46702;
        freqs["KI"] = -0.28257;
        freqs["MI"] = -0.40547;
        freqs["FI"] = -0.83291;
        freqs["PI"] = -0.14842;
        freqs["SI"] = -0.21256;
        freqs["TI"] = -0.24784;
        freqs["WI"] = 0.47;
        freqs["YI"] = -0.37469;
        freqs["VI"] = -1.06635;
        freqs["AL"] = -0.63758;
        freqs["RL"] = -0.16551;
        freqs["NL"] = 0.34229;
        freqs["DL"] = 0.82507;
        freqs["CL"] = -0.8873;
        freqs["EL"] = -0.30295;
        freqs["QL"] = 0.32542;
        freqs["GL"] = -0.14232;
        freqs["HL"] = -0.02299;
        freqs["IL"] = -0.56953;
        freqs["LL"] = 0.1217;
        freqs["KL"] = -0.05919;
        freqs["ML"] = -1.36524;
        freqs["FL"] = -0.38137;
        freqs["PL"] = 0.50509;
        freqs["SL"] = -0.25911;
        freqs["TL"] = 0.53408;
        freqs["WL"] = 0.40547;
        freqs["YL"] = -0.27029;
        freqs["VL"] = -0.38299;
        freqs["AK"] = -0.51083;
        freqs["RK"] = 0.17327;
        freqs["NK"] = 0.79851;
        freqs["DK"] = 0.28768;
        freqs["CK"] = 1.03609;
        freqs["EK"] = -0.22108;
        freqs["QK"] = 0.86148;
        freqs["GK"] = -0.09685;
        freqs["HK"] = -0.12516;
        freqs["IK"] = 0;
        freqs["LK"] = 0;
        freqs["KK"] = 0.60614;
        freqs["MK"] = -0.31508;
        freqs["FK"] = -1.30406;
        freqs["PK"] = -0.06899;
        freqs["SK"] = 0.50456;
        freqs["TK"] = 0.04581;
        freqs["WK"] = 0.81093;
        freqs["YK"] = -0.45953;
        freqs["VK"] = 0.42121;
        freqs["AM"] = -0.59205;
        freqs["RM"] = 0.40547;
        freqs["NM"] = 0.76214;
        freqs["DM"] = -0.83625;
        freqs["CM"] = -1.09861;
        freqs["EM"] = -1.70475;
        freqs["QM"] = -0.87547;
        freqs["GM"] = -0.63372;
        freqs["HM"] = -1.20397;
        freqs["IM"] = -0.57536;
        freqs["LM"] = -1.03799;
        freqs["KM"] = -0.1699;
        freqs["MM"] = -1.57554;
        freqs["FM"] = -0.58779;
        freqs["PM"] = -1.77071;
        freqs["SM"] = -0.73571;
        freqs["TM"] = -1.16315;
        freqs["WM"] = -1.09861;
        freqs["YM"] = 1.32176;
        freqs["VM"] = -0.98083;
        freqs["AF"] = -0.66036;
        freqs["RF"] = -0.13815;
        freqs["NF"] = -0.30748;
        freqs["DF"] = 1.15745;
        freqs["CF"] = -0.28768;
        freqs["EF"] = -0.27958;
        freqs["QF"] = -0.27625;
        freqs["GF"] = -0.99853;
        freqs["HF"] = 1.13498;
        freqs["IF"] = -0.10536;
        freqs["LF"] = -0.60354;
        freqs["KF"] = 0.87547;
        freqs["MF"] = 1.79176;
        freqs["FF"] = 0.63252;
        freqs["PF"] = -0.34484;
        freqs["SF"] = -0.06062;
        freqs["TF"] = -0.25131;
        freqs["WF"] = -0.22314;
        freqs["YF"] = 0;
        freqs["VF"] = -0.55962;
        freqs["AP"] = -0.0482;
        freqs["RP"] = -0.5213;
        freqs["NP"] = 0.60825;
        freqs["DP"] = 0.86148;
        freqs["CP"] = -0.81093;
        freqs["EP"] = 0.07522;
        freqs["QP"] = 0.46357;
        freqs["GP"] = -1.25276;
        freqs["HP"] = 0.05716;
        freqs["IP"] = 0.17063;
        freqs["LP"] = 0.07146;
        freqs["KP"] = 0.15123;
        freqs["MP"] = -0.5328;
        freqs["FP"] = -0.23484;
        freqs["PP"] = 0.07083;
        freqs["SP"] = 0.30421;
        freqs["TP"] = 0.34831;
        freqs["WP"] = -1.60944;
        freqs["YP"] = 1.06471;
        freqs["VP"] = 0.28768;
        freqs["AS"] = -0.20391;
        freqs["RS"] = 0.39531;
        freqs["NS"] = -0.11212;
        freqs["DS"] = 0.1038;
        freqs["CS"] = -0.63127;
        freqs["ES"] = 0;
        freqs["QS"] = -0.16252;
        freqs["GS"] = 0.03922;
        freqs["HS"] = 1.02962;
        freqs["IS"] = -0.57732;
        freqs["LS"] = 0;
        freqs["KS"] = 0.19416;
        freqs["MS"] = -0.31366;
        freqs["FS"] = -0.25131;
        freqs["PS"] = 0.51083;
        freqs["SS"] = -0.26053;
        freqs["TS"] = -0.14842;
        freqs["WS"] = 0.60614;
        freqs["YS"] = 0.22957;
        freqs["VS"] = -0.76969;
        freqs["AT"] = -0.10536;
        freqs["RT"] = 0.28768;
        freqs["NT"] = 0.7817;
        freqs["DT"] = -0.3285;
        freqs["CT"] = 0.06899;
        freqs["ET"] = -0.22739;
        freqs["QT"] = -0.24116;
        freqs["GT"] = -0.43672;
        freqs["HT"] = -0.40547;
        freqs["IT"] = -0.14764;
        freqs["LT"] = -0.03974;
        freqs["KT"] = -0.16333;
        freqs["MT"] = -0.72213;
        freqs["FT"] = -0.32542;
        freqs["PT"] = 0.31121;
        freqs["ST"] = 0.18473;
        freqs["TT"] = 0.2344;
        freqs["WT"] = 0;
        freqs["YT"] = 1.17007;
        freqs["VT"] = -0.09157;
        freqs["AW"] = 0;
        freqs["RW"] = 1.0116;
        freqs["NW"] = 0.98083;
        freqs["DW"] = -0.22314;
        freqs["CW"] = 0.13353;
        freqs["EW"] = -0.539;
        freqs["QW"] = 0.96508;
        freqs["GW"] = 0.73397;
        freqs["HW"] = 0.69315;
        freqs["IW"] = 0.58779;
        freqs["LW"] = -0.48551;
        freqs["KW"] = -0.55962;
        freqs["MW"] = -0.51083;
        freqs["FW"] = 0.33647;
        freqs["PW"] = -0.15415;
        freqs["SW"] = 0.55962;
        freqs["TW"] = 0.28768;
        freqs["WW"] = 0;
        freqs["YW"] = 0;
        freqs["VW"] = -1.50408;
        freqs["AY"] = 0.34294;
        freqs["RY"] = 0.63908;
        freqs["NY"] = 0.58779;
        freqs["DY"] = 0.69315;
        freqs["CY"] = -0.52609;
        freqs["EY"] = 0.04652;
        freqs["QY"] = 0.13353;
        freqs["GY"] = -0.10536;
        freqs["HY"] = 2.94444;
        freqs["IY"] = -0.21357;
        freqs["LY"] = -0.22314;
        freqs["KY"] = 0.31237;
        freqs["MY"] = 0;
        freqs["FY"] = -0.99325;
        freqs["PY"] = 0.61904;
        freqs["SY"] = 0.05884;
        freqs["TY"] = -0.12921;
        freqs["WY"] = 0.13353;
        freqs["YY"] = 1.06471;
        freqs["VY"] = 0;
        freqs["AV"] = -0.55657;
        freqs["RV"] = 0.22957;
        freqs["NV"] = 0.06454;
        freqs["DV"] = -0.22631;
        freqs["CV"] = -0.8473;
        freqs["EV"] = -0.31471;
        freqs["QV"] = 0.23361;
        freqs["GV"] = -0.05335;
        freqs["HV"] = 0.48955;
        freqs["IV"] = 0;
        freqs["LV"] = 0.0656;
        freqs["KV"] = -0.18572;
        freqs["MV"] = -1.34373;
        freqs["FV"] = -0.63599;
        freqs["PV"] = 0.05827;
        freqs["SV"] = -0.32721;
        freqs["TV"] = 0.03922;
        freqs["WV"] = -0.74194;
        freqs["YV"] = -0.03637;
        freqs["VV"] = -0.29171;

        #pragma endregion

        headers.push_back("name");
        for(char c : allowed)
        {
            for(char d : allowed)
            {
                string key(1, c);
                key.push_back(d);
                headers.push_back(key);
                keys.push_back(key);
            }
        }

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, allowed, keys, freqs) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            vector<double> encodedProtein = AAPAS(seqs[i], allowed, keys, freqs);
            #pragma omp critical
            {
                seqNames.push_back(names[i]);
                encoded.push_back(encodedProtein);
            }
        }
    }

    // Taylor's Venn diagram
    else if (encoding.compare("TVD") == 0)
    {
        int seqLength = checkFastaSameLength(seqs);
        if (seqLength == -1)
        {
            bool crop = argumentExists(argv, argv + argc, "--crop");
            if (crop)
            {
                seqLength = getMinSequenceLength(names, seqs);
                cropSequences(seqs, seqLength);
            }
            else
            {
                cout << "Error: All sequences must have the same length. You can use the --crop argument, so it crops the sequences automatically.\n";
                return 0;
            }
        }

        #pragma region Populate binary vectors

        // The vectors are in the following order:
        // Hydrophobic, positive, negative, polar, charged, small, tiny, aliphatic, aromatic, proline
        map<char, array<double, 10>> tvd; 

        tvd['A'] = {1, 0, 0, 0, 0, 1, 1, 0, 0, 0};
        tvd['C'] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0};
        tvd['D'] = {0, 0, 1, 1, 1, 1, 0, 0, 0, 0};
        tvd['E'] = {0, 0, 1, 1, 1, 0, 0, 0, 0, 0};
        tvd['F'] = {1, 0, 0, 0, 0, 0, 0, 0, 1, 0};
        tvd['G'] = {1, 0, 0, 0, 0, 1, 1, 0, 0, 0};
        tvd['H'] = {1, 1, 0, 1, 1, 0, 0, 0, 1, 0};
        tvd['I'] = {1, 0, 0, 0, 0, 0, 0, 1, 0, 0};
        tvd['K'] = {1, 1, 0, 1, 1, 0, 0, 0, 0, 0};
        tvd['L'] = {1, 0, 0, 0, 0, 0, 0, 1, 0, 0};
        tvd['M'] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        tvd['N'] = {0, 0, 0, 1, 0, 1, 0, 0, 0, 0};
        tvd['P'] = {0, 0, 0, 0, 0, 1, 0, 0, 0, 1};
        tvd['Q'] = {0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
        tvd['R'] = {0, 1, 0, 1, 1, 0, 0, 0, 0, 0};
        tvd['S'] = {0, 0, 0, 1, 0, 1, 1, 0, 0, 0};
        tvd['T'] = {1, 0, 0, 1, 0, 1, 0, 0, 0, 0};
        tvd['V'] = {1, 0, 0, 0, 0, 1, 0, 1, 0, 0};
        tvd['W'] = {1, 0, 0, 1, 0, 0, 0, 0, 1, 0};
        tvd['Y'] = {1, 0, 0, 1, 0, 0, 0, 0, 1, 0};

        #pragma endregion

        headers.push_back("name");
        for(int i = 0; i < seqLength; i++)
        {
            string key = to_string(i);
            key.push_back('-');
            headers.push_back(key + "hydrophobic");
            keys.push_back(key + "hydrophobic");
            headers.push_back(key + "positive");
            keys.push_back(key + "positive");
            headers.push_back(key + "negative");
            keys.push_back(key + "negative");
            headers.push_back(key + "polar");
            keys.push_back(key + "polar");
            headers.push_back(key + "charged");
            keys.push_back(key + "charged");
            headers.push_back(key + "small");
            keys.push_back(key + "small");
            headers.push_back(key + "tiny");
            keys.push_back(key + "tiny");
            headers.push_back(key + "aliphatic");
            keys.push_back(key + "aliphatic");
            headers.push_back(key + "aromatic");
            keys.push_back(key + "aromatic");
            headers.push_back(key + "proline");
            keys.push_back(key + "proline");
        }

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, allowed, keys, tvd) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            vector<double> encodedProtein = TVD(seqs[i], allowed, keys, tvd);
            #pragma omp critical
            {
                seqNames.push_back(names[i]);
                encoded.push_back(encodedProtein);
            }
        }
    }

    // Composition moment vector
    else if (encoding.compare("CMV") == 0)
    {
        headers.push_back("name");
        for(char c : allowed)
        {
            string key(1, c);
            headers.push_back(key);
            keys.push_back(key);
        }

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, allowed, keys) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            vector<double> encodedProtein = CMV(seqs[i], allowed, keys);
            #pragma omp critical
            {
                seqNames.push_back(names[i]);
                encoded.push_back(encodedProtein);
            }
        }
    }

    // Encoding based on grouped weight
    else if (encoding.compare("EBGW") == 0)
    {
        int k = 20;
        string kS = getArgument(argv, argv + argc, "--k");
        if (kS != "")
        {
            if (!isNumber(kS))
            {
                cout << "Error: The k value must be a number greater or equal than 1.\n";
                return 0;
            }
            k = stoi(kS);
            if (k < 1)
            {
                cout << "Error: The k value must be a number greater or equal than 1.\n";
                return 0;
            }
        }

        map<char, array<int, 3>> groups;

        groups['A'] = {1, 1, 1};
        groups['C'] = {1, 0, 0};
        groups['D'] = {0, 1, 0};
        groups['E'] = {0, 1, 0};
        groups['F'] = {1, 1, 1};
        groups['G'] = {1, 1, 1};
        groups['H'] = {0, 0, 1};
        groups['I'] = {1, 1, 1};
        groups['K'] = {0, 0, 1};
        groups['L'] = {1, 1, 1};
        groups['M'] = {1, 1, 1};
        groups['N'] = {1, 0, 0};
        groups['P'] = {1, 1, 1};
        groups['Q'] = {1, 0, 0};
        groups['R'] = {0, 0, 1};
        groups['S'] = {1, 0, 0};
        groups['T'] = {1, 0, 0};
        groups['V'] = {1, 1, 1};
        groups['W'] = {1, 1, 1};
        groups['Y'] = {1, 0, 0}; 

        headers.push_back("name");
        for (int i = 1; i <= 3; i++)
        {
            for (int j = 1; j <= k; j++)
            {
                string key = "g";
                key.append(to_string(i));
                key.push_back('-');
                key.append(to_string(j));
                headers.push_back(key);
                keys.push_back(key);
            }
        }

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, allowed, keys, groups, k) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            vector<double> encodedProtein = EBGW(seqs[i], allowed, keys, groups, k);
            #pragma omp critical
            {
                seqNames.push_back(names[i]);
                encoded.push_back(encodedProtein);
            }
        }
    }

    // PSSM (blastpgp)
    else if (encoding.compare("PSSM") == 0 || encoding.compare("PSSMAAC") == 0 || encoding.compare("BiPSSM") == 0 ||
        encoding.compare("PSSMAC") == 0 || encoding.compare("PPSSM") == 0)
    {
        int n = 30;
                
        string path = getArgument(argv, argv + argc, "--path");
        if (path == "")
        {
            cout << "Error: A path for saving or loading PSSM files is needed. Use the --path <path> argument.\n";
            return 0;
        }
        
        bool generate = argumentExists(argv, argv + argc, "--generate");
        int pathExists = directoryExists(path);
        if (pathExists == -1)
            return 0;
        else if (!generate && pathExists == 0)
        {
            cout << "Error: The path does not exist.\n";
            return 0;
        }
        else if (generate)
        {
            // Generate PSSM files
        }

        string orderString = "ARNDCQEGHILKMFPSTWYV";
        headers.push_back("name");
        if (encoding.compare("PSSM") == 0)
        {
            int seqLength = checkFastaSameLength(seqs);
            if(seqLength == -1)
            {
                bool crop = argumentExists(argv, argv + argc, "--crop");
                if (crop)
                {
                    seqLength = getMinSequenceLength(names, seqs);
                    cropSequences(seqs, seqLength);
                }
                else
                {
                    cout << "Error: All sequences must have the same length. You can use the --crop argument, so it crops the sequences automatically.\n";
                    return 0;
                }
            }
            for (int i = 0; i < seqLength; i++)
            {
                for (char c : orderString)
                {
                    string key = to_string(i);
                    key.push_back(c);
                    headers.push_back(key);
                    keys.push_back(key);
                }
            }
        }
        else if (encoding.compare("PSSMAAC") == 0)
        {
            for(char c : orderString)
            {
                string aa(1, c);
                headers.push_back(aa);
                keys.push_back(aa);
            }
        }
        else if (encoding.compare("BiPSSM") == 0)
        {
            string nS = getArgument(argv, argv + argc, "--n");
            if (nS != "")
            {
                if (!isNumber(nS))
                {
                    cout << "Error: The n value must be a number greater or equal than 1.\n";
                    return 0;
                }
                n = stoi(nS);
                if (n < 1)
                {
                    cout << "Error: The n value must be a number greater or equal than 1.\n";
                    return 0;
                }
            }
            for(char c : orderString)
            {
                for(char d : orderString)
                {
                    string key(1, c);
                    key.push_back(d);
                    headers.push_back(key);
                    keys.push_back(key);
                }
            }
        }
        else if (encoding.compare("PSSMAC") == 0)
        {
            string nS = getArgument(argv, argv + argc, "--n");
            if (nS != "")
            {
                if (!isNumber(nS))
                {
                    cout << "Error: The n value must be a number greater or equal than 1.\n";
                    return 0;
                }
                n = stoi(nS);
                if (n < 1)
                {
                    cout << "Error: The n value must be a number greater or equal than 1.\n";
                    return 0;
                }
            }
            int minLength = getMinSequenceLength(names, seqs);
            if (minLength < n + 1)
            {
                cout << "Error: All sequences length must be equal or greater than n + 1.\n";
                return 0;
            }
            for(char c : orderString)
            {
                for (int i = 1; i <= n; i++)
                {
                    string key = to_string(i);
                    key.push_back(c);
                    headers.push_back(key);
                    keys.push_back(key);
                }
            }
        }
        else if (encoding.compare("PPSSM") == 0)
        {
            string nS = getArgument(argv, argv + argc, "--n");
            if (nS != "")
            {
                if (!isNumber(nS))
                {
                    cout << "Error: The n value must be a number greater or equal than 1.\n";
                    return 0;
                }
                n = stoi(nS);
                if (n < 1)
                {
                    cout << "Error: The n value must be a number greater or equal than 1.\n";
                    return 0;
                }
            }
            int minLength = getMinSequenceLength(names, seqs);
            if(minLength < n + 1)
            {
                cout << "Error: All sequences length must be equal or greater than n + 1.\n";
                return 0;
            }
            for(char c : orderString)
            {
                string key(1, c);
                headers.push_back("S" + key);
                keys.push_back("S" + key);
            }
            for(char c : orderString)
            {
                string key(1, c);
                headers.push_back("R" + key);
                keys.push_back("R" + key);
            }
        }

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, allowed, keys, orderString, path, cout, encoding, n) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            ifstream file;
            file.open(path + "/" + names[i] + ".pssm");
            if (!file) 
            {
                cout << "File " << names[i] << ".pssm does not exist." << endl;
            }
            else if (file.is_open())
            {
                vector<double> encodedProtein;
                if (encoding.compare("PSSM") == 0)
                    encodedProtein = PSSM(seqs[i], names[i], orderString, keys, file);
                else if (encoding.compare("PSSMAAC") == 0)
                    encodedProtein = PSSMAAC(seqs[i], names[i], keys, orderString, file);
                else if (encoding.compare("BiPSSM") == 0)
                    encodedProtein = BiPSSM(seqs[i], names[i], keys, orderString, n, file);
                else if (encoding.compare("PSSMAC") == 0)
                    encodedProtein = PSSMAC(seqs[i], names[i], keys, orderString, n, file);
                else if (encoding.compare("PPSSM") == 0)
                    encodedProtein = PPSSM(seqs[i], names[i], keys, orderString, n, file);
                #pragma omp critical
                {
                    seqNames.push_back(names[i]);
                    encoded.push_back(encodedProtein);
                }
                file.close();
            }
            else
            {
                cout << "File " << names[i] << ".pssm cannot be opened." << endl;
            }
        }
    }

    else if (encoding.compare("PseKRAAC") == 0)
    {        
        array<string, 19> types = {"1", "2", "3A", "3B", "4", "5", "6A", "6B", "6C", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"};
        string type = getArgument(argv, argv + argc, "--type");
        if (type.compare("") == 0)
        {
            cout << "Error: A descriptor type is needed. Use the --type <type> argument.\n";
            return 0;
        }
        else
        {
            bool found = false;
            for (string s : types)
            {
                if (s.compare(type) == 0)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "Error: Invalid type. Available choices are 1, 2, 3A, 3B, 4, 5, 6A, 6B, 6C, 7, 8, 9, 10, 11, 12, 13, 14, 15 and 16.\n";
                return 0;
            }
        }

        array<string, 2> subtypes = {"g-gap", "lambda-correlation"};
        string subtype = getArgument(argv, argv + argc, "--subtype");
        if (subtype.compare("") == 0)
        {
            subtype = "g-gap";
        }
        else
        {
            bool found = false;
            for (string s : subtypes)
            {
                if (s.compare(subtype) == 0)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "Error: Invalid type. Available choices are g-gap and lambda-correlation.\n";
                return 0;
            }
        }

        array<string, 3> ktuples = {"1", "2", "3"};
        string ktuple = getArgument(argv, argv + argc, "--ktuple");
        if (ktuple.compare("") == 0)
        {
            ktuple = "2";
        }
        else
        {
            bool found = false;
            for (string s : ktuples)
            {
                if (s.compare(ktuple) == 0)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "Error: Invalid k-tuple value. Available choices are 1, 2, and 3. The default value is 2.\n";
                return 0;
            }
        }

        string gapLambdaParam = getArgument(argv, argv + argc, "--gapLambda");
        string innerType = "lambda";
        int lowerBound = 1;
        int gapLambda = -1;
        if (subtype.compare("g-gap") == 0)
        {
            lowerBound = 0;
            innerType = "gap";
        }
        if (gapLambdaParam.compare("") == 0)
        {
            cout << "Error: A " << innerType << " value must be provided. Use the --gapLambda <value> argument.\n";
            return 0;
        }
        else
        {
            if (!isNumber(gapLambdaParam))
            {
                cout << "Error: The " << innerType << " value must be a number between " << lowerBound << " and 9.\n";
                return 0;
            }
            gapLambda = stoi(gapLambdaParam);
            if (gapLambda < 0 || gapLambda > 9)
            {
                cout << "Error: The " << innerType << " value must be a number between " << lowerBound << " and 9.\n";
                return 0;
            }
            else if (gapLambda == 0 && innerType.compare("lambda") == 0)
            {
                cout << "Error: The lambda value must be between 1 and 9.\n";
                return 0;
            }
        }

        map<string, vector<int>> usage = usagePseKRAAC();

        string raactypeParam = getArgument(argv, argv + argc, "--raactype");
        int raactype = -1;
        if (raactypeParam.compare("") == 0)
        {
            cout << "Error: A reduced amino acid cluster type must be provided. Use the --raactype <value> argument.\n";
            return 0;
        }
        if (raactypeParam.compare("") != 0)
        {
            if (!isNumber(raactypeParam))
            {
                cout << "Error: Invalid reduced amino acid type. Please, check the allowed values for the type you selected: \n";
                cout << helpPseKRAAC() << endl;
                return 0;
            }
            raactype = stoi(raactypeParam);
            bool found = false;
            for (int s : usage[type])
            {
                if (s == raactype)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "Error: Invalid reduced amino acid type. Please, check the allowed values for the type you selected: \n";
                cout << helpPseKRAAC() << endl;
                return 0;
            }
        }
        
        map<int, vector<string>> aaGroups;
        if (type.compare("1") == 0)
            aaGroups = type1();
        else if (type.compare("2") == 0)
            aaGroups = type2();
        else if (type.compare("3A") == 0)
            aaGroups = type3A();
        else if (type.compare("3B") == 0)
            aaGroups = type3B();
        else if (type.compare("4") == 0)
            aaGroups = type4();
        else if (type.compare("5") == 0)
            aaGroups = type5();
        else if (type.compare("6A") == 0)
            aaGroups = type6A();
        else if (type.compare("6B") == 0)
            aaGroups = type6B();
        else if (type.compare("6C") == 0)
            aaGroups = type6C();
        else if (type.compare("7") == 0)
            aaGroups = type7();
        else if (type.compare("8") == 0)
            aaGroups = type8();
        else if (type.compare("9") == 0)
            aaGroups = type9();
        else if (type.compare("10") == 0)
            aaGroups = type10();
        else if (type.compare("11") == 0)
            aaGroups = type11();
        else if (type.compare("12") == 0)
            aaGroups = type12();
        else if (type.compare("13") == 0)
            aaGroups = type13();
        else if (type.compare("14") == 0)
            aaGroups = type14();
        else if (type.compare("15") == 0)
            aaGroups = type15();
        else if (type.compare("16") == 0)
            aaGroups = type16();

        headers.push_back("name");
        if (ktuple == "1")
        {
            for (int i = 1; i <= aaGroups[raactype].size(); i++)
            {
                string key = to_string(i);
                headers.push_back(key);
                keys.push_back(key);
            }
        }
        else if (ktuple == "2")
        {
            for (int i = 1; i <= aaGroups[raactype].size(); i++)
            {
                string iString = to_string(i);
                for (int j = 1; j <= aaGroups[raactype].size(); j++)
                {
                    string key = iString + "_" + to_string(j);
                    headers.push_back(key);
                    keys.push_back(key);
                }
            }
        }
        else if (ktuple == "3")
        {
            for (int i = 1; i <= aaGroups[raactype].size(); i++)
            {
                string iString = to_string(i);
                for (int j = 1; j <= aaGroups[raactype].size(); j++)
                {
                    string jString = to_string(j);
                    for (int k = 1; k <= aaGroups[raactype].size(); k++)
                    {
                        string key = iString + "_" + jString + "_" + to_string(k);
                        headers.push_back(key);
                        keys.push_back(key);
                    }
                }
            }
        }

        map<char, int> aaMap;
        for (int i = 0; i < aaGroups[raactype].size(); i++)
        {
            for (char& c : aaGroups[raactype][i])
            {
                aaMap[c] = i;
            }
        }

        #pragma omp parallel for num_threads(numThreads) \
            default(none) shared(seqNames, encoded, seqs, names, allowed, keys, aaMap, ktuple, subtype, gapLambda) schedule(guided) 
        for (int i = 0; i < seqs.size(); i++)
        {
            vector<double> encodedProtein = PseKRAAC(seqs[i], allowed, keys, aaMap, ktuple, subtype, gapLambda);
            #pragma omp critical
            {
                seqNames.push_back(names[i]);
                encoded.push_back(encodedProtein);
            }
        }
    }
    else
    {
        cout << "Error: Invalid encoding." << endl;
        return 0;
    }

    printEncoded(headers, seqNames, encoded, encoded.size(), output);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Success encoding " << encoding << ". Duration: " << duration.count() << " milliseconds" << endl;

	return 0;
}