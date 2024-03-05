def get_codon_table() -> dict:
    codon_table = {
        "ATA": 'I', "ATC": 'I', "ATT": 'I', "ATG": 'M',
        "ACA": 'T', "ACC": 'T', "ACG": 'T', "ACT": 'T',
        "AAC": 'N', "AAT": 'N', "AAA": 'K', "AAG": 'K',
        "AGC": 'S', "AGT": 'S', "AGA": 'R', "AGG": 'R',
        "CTA": 'L', "CTC": 'L', "CTG": 'L', "CTT": 'L',
        "CCA": 'P', "CCC": 'P', "CCG": 'P', "CCT": 'P',
        "CAC": 'H', "CAT": 'H', "CAA": 'Q', "CAG": 'Q',
        "CGA": 'R', "CGC": 'R', "CGG": 'R', "CGT": 'R',
        "GTA": 'V', "GTC": 'V', "GTG": 'V', "GTT": 'V',
        "GCA": 'A', "GCC": 'A', "GCG": 'A', "GCT": 'A',
        "GAC": 'D', "GAT": 'D', "GAA": 'E', "GAG": 'E',
        "GGA": 'G', "GGC": 'G', "GGG": 'G', "GGT": 'G',
        "TCA": 'S', "TCC": 'S', "TCG": 'S', "TCT": 'S',
        "TTC": 'F', "TTT": 'F', "TTA": 'L', "TTG": 'L',
        "TAC": 'Y', "TAT": 'Y', "TGC": 'C', "TGT": 'C',
        "TGG": 'W',
        # Uncomment the lines below if you want to include stop codons
        # "TAA": '_', "TAG": '_',
        # "TGA": '_'
    }
    return codon_table


def get_blosum():
    blosum = {
        'A': [4, -1, -2, -2, 0, -1, -1, 0, -2, -1, -1, -1, -1, -2, -1, 1, 0, -3, -2, 0],
        'R': [-1, 5, 0, -2, -3, 1, 0, -2, 0, -3, -2, 2, -1, -3, -2, -1, -1, -3, -2, -3],
        'N': [-2, 0, 6, 1, -3, 0, 0, 0, 1, -3, -3, 0, -2, -3, -2, 1, 0, -4, -2, -3],
        'D': [-2, -2, 1, 6, -3, 0, 2, -1, -1, -3, -4, -1, -3, -3, -1, 0, -1, -4, -3, -3],
        'C': [0, -3, -3, -3, 9, -3, -4, -3, -3, -1, -1, -3, -1, -2, -3, -1, -1, -2, -2, -1],
        'Q': [-1, 1, 0, 0, -3, 5, 2, -2, 0, -3, -2, 1, 0, -3, -1, 0, -1, -2, -1, -2],
        'E': [-1, 0, 0, 2, -4, 2, 5, -2, 0, -3, -3, 1, -2, -3, -1, 0, -1, -3, -2, -2],
        'G': [0, -2, 0, -1, -3, -2, -2, 6, -2, -4, -4, -2, -3, -3, -2, 0, -2, -2, -3, -3],
        'H': [-2, 0, 1, -1, -3, 0, 0, -2, 8, -3, -3, -1, -2, -1, -2, -1, -2, -2, 2, -3],
        'I': [-1, -3, -3, -3, -1, -3, -3, -4, -3, 4, 2, -3, 1, 0, -3, -2, -1, -3, -1, 3],
        'L': [-1, -2, -3, -4, -1, -2, -3, -4, -3, 2, 4, -2, 2, 0, -3, -2, -1, -2, -1, 1],
        'K': [-1, 2, 0, -1, -3, 1, 1, -2, -1, -3, -2, 5, -1, -3, -1, 0, -1, -3, -2, -2],
        'M': [-1, -1, -2, -3, -1, 0, -2, -3, -2, 1, 2, -1, 5, 0, -2, -1, -1, -1, -1, 1],
        'F': [-2, -3, -3, -3, -2, -3, -3, -3, -1, 0, 0, -3, 0, 6, -4, -2, -2, 1, 3, -1],
        'P': [-1, -2, -2, -1, -3, -1, -1, -2, -2, -3, -3, -1, -2, -4, 7, -1, -1, -4, -3, -2],
        'S': [1, -1, 1, 0, -1, 0, 0, 0, -1, -2, -2, 0, -1, -2, -1, 4, 1, -3, -2, -2],
        'T': [0, -1, 0, -1, -1, -1, -1, -2, -2, -1, -1, -1, -1, -2, -1, 1, 5, -2, -2, 0],
        'W': [-3, -3, -4, -4, -2, -2, -3, -2, -2, -3, -2, -3, -1, 1, -4, -3, -2, 11, 2, -3],
        'Y': [-2, -2, -2, -3, -2, -1, -2, -3, 2, -1, -1, -2, -1, 3, -3, -2, -2, 2, 7, -1],
        'V': [0, -3, -3, -3, -1, -2, -2, -3, -3, 3, 1, -2, 1, -1, -2, -2, 0, -3, -1, 4]
    }
    return blosum


def help_pse_kraac():
    help_str = "The 'raactype' value for each subtype descriptor could be chosen from:\n" \
               "type 1    [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]\n" \
               "type 2    [2, 3, 4, 5, 6,    8,                        15,                 20]\n" \
               "type 3A   [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]\n" \
               "type 3B   [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]\n" \
               "type 4    [         5,       8, 9,     11,     13,                         20]\n" \
               "type 5    [   3, 4,          8,    10,                 15,                 20]\n" \
               "type 6A   [      4, 5,                                                     20]\n" \
               "type 6B   [         5,                                                       ]\n" \
               "type 6C   [         5,                                                       ]\n" \
               "type 7    [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]\n" \
               "type 8    [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]\n" \
               "type 9    [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]\n" \
               "type 10   [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]\n" \
               "type 11   [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]\n" \
               "type 12   [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,     20]\n" \
               "type 13   [      4,                        12,                 17,         20]\n" \
               "type 14   [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]\n" \
               "type 15   [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,             20]\n" \
               "type 16   [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,             20]"
    return help_str


def usage_pse_kraac():
    usage = {
        "1": [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],
        "2": [2, 3, 4, 5, 6, 8, 15, 20],
        "3A": [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],
        "3B": [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],
        "4": [5, 8, 9, 11, 13, 20],
        "5": [3, 4, 8, 10, 15, 20],
        "6A": [4, 5, 20],
        "6B": [5, ],
        "6C": [5, ],
        "7": [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],
        "8": [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],
        "9": [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],
        "10": [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],
        "11": [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],
        "12": [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 20],
        "13": [4, 12, 17, 20],
        "14": [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],
        "15": [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 20],
        "16": [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 20]
    }
    return usage


def type_1():
    aa_groups = {
        2: ["CMFILVWY", "AGTSNQDEHRKP"],
        3: ["CMFILVWY", "AGTSP", "NQDEHRK"],
        4: ["CMFWY", "ILV", "AGTS", "NQDEHRKP"],
        5: ["WFYH", "MILV", "CATSP", "G", "NQDERK"],
        6: ["WFYH", "MILV", "CATS", "P", "G", "NQDERK"],
        7: ["WFYH", "MILV", "CATS", "P", "G", "NQDE", "RK"],
        8: ["WFYH", "MILV", "CA", "NTS", "P", "G", "DE", "QRK"],
        9: ["WFYH", "MI", "LV", "CA", "NTS", "P", "G", "DE", "QRK"],
        10: ["WFY", "ML", "IV", "CA", "TS", "NH", "P", "G", "DE", "QRK"],
        11: ["WFY", "ML", "IV", "CA", "TS", "NH", "P", "G", "D", "QE", "RK"],
        12: ["WFY", "ML", "IV", "C", "A", "TS", "NH", "P", "G", "D", "QE", "RK"],
        13: ["WFY", "ML", "IV", "C", "A", "T", "S", "NH", "P", "G", "D", "QE", "RK"],
        14: ["WFY", "ML", "IV", "C", "A", "T", "S", "NH", "P", "G", "D", "QE", "R", "K"],
        15: ["WFY", "ML", "IV", "C", "A", "T", "S", "N", "H", "P", "G", "D", "QE", "R", "K"],
        16: ["W", "FY", "ML", "IV", "C", "A", "T", "S", "N", "H", "P", "G", "D", "QE", "R", "K"],
        17: ["W", "FY", "ML", "IV", "C", "A", "T", "S", "N", "H", "P", "G", "D", "Q", "E", "R", "K"],
        18: ["W", "FY", "M", "L", "IV", "C", "A", "T", "S", "N", "H", "P", "G", "D", "Q", "E", "R", "K"],
        19: ["W", "F", "Y", "M", "L", "IV", "C", "A", "T", "S", "N", "H", "P", "G", "D", "Q", "E", "R", "K"],
        20: ["W", "F", "Y", "M", "L", "I", "V", "C", "A", "T", "S", "N", "H", "P", "G", "D", "Q", "E", "R", "K"]
    }
    return aa_groups


def type_2():
    aa_groups = {
        2: ["LVIMCAGSTPFYW", "EDNQKRH"],
        3: ["LVIMCAGSTP", "FYW", "EDNQKRH"],
        4: ["LVIMC", "AGSTP", "FYW", "EDNQKRH"],
        5: ["LVIMC", "AGSTP", "FYW", "EDNQ", "KRH"],
        6: ["LVIM", "AGST", "PHC", "FYW", "EDNQ", "KR"],
        8: ["LVIMC", "AG", "ST", "P", "FYW", "EDNQ", "KR", "H"],
        15: ["LVIM", "C", "A", "G", "S", "T", "P", "FY", "W", "E", "D", "N", "Q", "KR", "H"],
        20: ["L", "V", "I", "M", "C", "A", "G", "S", "T", "P", "F", "Y", "W", "E", "D", "N", "Q", "K", "R", "H"]
    }
    return aa_groups


def type_3A():
    aa_groups = {
        2: ["AGSPDEQNHTKRMILFYVC", "W"],
        3: ["AGSPDEQNHTKRMILFYV", "W", "C"],
        4: ["AGSPDEQNHTKRMIV", "W", "YFL", "C"],
        5: ["AGSPDEQNHTKR", "W", "YF", "MIVL", "C"],
        6: ["AGSP", "DEQNHTKR", "W", "YF", "MIL", "VC"],
        7: ["AGP", "DEQNH", "TKRMIV", "W", "YF", "L", "CS"],
        8: ["AG", "DEQN", "TKRMIV", "HY", "W", "L", "FP", "CS"],
        9: ["AG", "P", "DEQN", "TKRMI", "HY", "W", "F", "L", "VCS"],
        10: ["AG", "P", "DEQN", "TKRM", "HY", "W", "F", "I", "L", "VCS"],
        11: ["AG", "P", "DEQN", "TK", "RI", "H", "Y", "W", "F", "ML", "VCS"],
        12: ["FAS", "P", "G", "DEQ", "NL", "TK", "R", "H", "W", "Y", "IM", "VC"],
        13: ["FAS", "P", "G", "DEQ", "NL", "T", "K", "R", "H", "W", "Y", "IM", "VC"],
        14: ["FA", "P", "G", "T", "DE", "QM", "NL", "K", "R", "H", "W", "Y", "IV", "CS"],
        15: ["FAS", "P", "G", "T", "DE", "Q", "NL", "K", "R", "H", "W", "Y", "M", "I", "VC"],
        16: ["FA", "P", "G", "ST", "DE", "Q", "N", "K", "R", "H", "W", "Y", "M", "L", "I", "VC"],
        17: ["FA", "P", "G", "S", "T", "DE", "Q", "N", "K", "R", "H", "W", "Y", "M", "L", "I", "VC"],
        18: ["FA", "P", "G", "S", "T", "DE", "Q", "N", "K", "R", "H", "W", "Y", "M", "L", "I", "V", "C"],
        19: ["FA", "P", "G", "S", "T", "D", "E", "Q", "N", "K", "R", "H", "W", "Y", "M", "L", "I", "V", "C"],
        20: ["F", "A", "P", "G", "S", "T", "D", "E", "Q", "N", "K", "R", "H", "W", "Y", "M", "L", "I", "V", "C"]
    }
    return aa_groups


def type_3B():
    aa_groups = {
        2: ["HRKQNEDSTGPACVIM", "LFYW"],
        3: ["HRKQNEDSTGPACVIM", "LFY", "W"],
        4: ["HRKQNEDSTGPA", "CIV", "MLFY", "W"],
        5: ["HRKQNEDSTGPA", "CV", "IML", "FY", "W"],
        6: ["HRKQNEDSTPA", "G", "CV", "IML", "FY", "W"],
        7: ["HRKQNEDSTA", "G", "P", "CV", "IML", "FY", "W"],
        8: ["HRKQSTA", "NED", "G", "P", "CV", "IML", "FY", "W"],
        9: ["HRKQ", "NED", "ASTG", "P", "C", "IV", "MLF", "Y", "W"],
        10: ["RKHSA", "Q", "NED", "G", "P", "C", "TIV", "MLF", "Y", "W"],
        11: ["RKQ", "NG", "ED", "AST", "P", "C", "IV", "HML", "F", "Y", "W"],
        12: ["RKQ", "ED", "NAST", "G", "P", "C", "IV", "H", "ML", "F", "Y", "W"],
        13: ["RK", "QE", "D", "NG", "HA", "ST", "P", "C", "IV", "ML", "F", "Y", "W"],
        14: ["R", "K", "QE", "D", "NG", "HA", "ST", "P", "C", "IV", "ML", "F", "Y", "W"],
        15: ["R", "K", "QE", "D", "NG", "HA", "ST", "P", "C", "IV", "M", "L", "F", "Y", "W"],
        16: ["R", "K", "Q", "E", "D", "NG", "HA", "ST", "P", "C", "IV", "M", "L", "F", "Y", "W"],
        17: ["R", "K", "Q", "E", "D", "NG", "HA", "S", "T", "P", "C", "IV", "M", "L", "F", "Y", "W"],
        18: ["R", "K", "Q", "E", "D", "NG", "HA", "S", "T", "P", "C", "I", "V", "M", "L", "F", "Y", "W"],
        19: ["R", "K", "Q", "E", "D", "NG", "H", "A", "S", "T", "P", "C", "I", "V", "M", "L", "F", "Y", "W"],
        20: ["R", "K", "Q", "E", "D", "N", "G", "H", "A", "S", "T", "P", "C", "I", "V", "M", "L", "F", "Y", "W"]
    }
    return aa_groups


def type_4():
    aa_groups = {
        5: ["G", "IVFYW", "ALMEQRK", "P", "NDHSTC"],
        8: ["G", "IV", "FYW", "ALM", "EQRK", "P", "ND", "HSTC"],
        9: ["G", "IV", "FYW", "ALM", "EQRK", "P", "ND", "HS", "TC"],
        11: ["G", "IV", "FYW", "A", "LM", "EQRK", "P", "ND", "HS", "T", "C"],
        13: ["G", "IV", "FYW", "A", "L", "M", "E", "QRK", "P", "ND", "HS", "T", "C"],
        20: ["G", "I", "V", "F", "Y", "W", "A", "L", "M", "E", "Q", "R", "K", "P", "N", "D", "H", "S", "T", "C"]
    }
    return aa_groups


def type_5():
    aa_groups = {
        3: ["FWYCILMVAGSTPHNQ", "DE", "KR"],
        4: ["FWY", "CILMV", "AGSTP", "EQNDHKR"],
        8: ["FWY", "CILMV", "GA", "ST", "P", "EQND", "H", "KR"],
        10: ["G", "FYW", "A", "ILMV", "RK", "P", "EQND", "H", "ST", "C"],
        15: ["G", "FY", "W", "A", "ILMV", "E", "Q", "RK", "P", "N", "D", "H", "S", "T", "C"],
        20: ["G", "I", "V", "F", "Y", "W", "A", "L", "M", "E", "Q", "R", "K", "P", "N", "D", "H", "S", "T", "C"]
    }
    return aa_groups


def type_6A():
    aa_groups = {
        4: ["AGPST", "CILMV", "DEHKNQR", "FYW"],
        5: ["AHT", "CFILMVWY", "DE", "GP", "KNQRS"],
        20: ["A", "C", "D", "E", "F", "G", "H", "I", "K", "L", "M", "N", "P", "Q", "R", "S", "T", "V", "W", "Y"]
    }
    return aa_groups


def type_6B():
    aa_groups = {
        5: ["AEHKQRST", "CFILMVWY", "DN", "G", "P"]
    }
    return aa_groups


def type_6C():
    aa_groups = {
        5: ["AG", "C", "DEKNPQRST", "FILMVWY", "H"]
    }
    return aa_groups


def type_7():
    aa_groups = {
        2: ["C", "MFILVWYAGTSNQDEHRKP"],
        3: ["C", "MFILVWYAKR", "GTSNQDEHP"],
        4: ["C", "KR", "MFILVWYA", "GTSNQDEHP"],
        5: ["C", "KR", "MFILVWYA", "DE", "GTSNQHP"],
        6: ["C", "KR", "WYA", "MFILV", "DE", "GTSNQHP"],
        7: ["C", "KR", "WYA", "MFILV", "DE", "QH", "GTSNP"],
        8: ["C", "KR", "WYA", "MFILV", "D", "E", "QH", "GTSNP"],
        9: ["C", "KR", "WYA", "MFILV", "D", "E", "QH", "TP", "GSN"],
        10: ["C", "KR", "WY", "A", "MFILV", "D", "E", "QH", "TP", "GSN"],
        11: ["C", "K", "R", "WY", "A", "MFILV", "D", "E", "QH", "TP", "GSN"],
        12: ["C", "K", "R", "WY", "A", "MFILV", "D", "E", "QH", "TP", "GS", "N"],
        13: ["C", "K", "R", "W", "Y", "A", "MFILV", "D", "E", "QH", "TP", "GS", "N"],
        14: ["C", "K", "R", "W", "Y", "A", "FILV", "M", "D", "E", "QH", "TP", "GS", "N"],
        15: ["C", "K", "R", "W", "Y", "A", "FILV", "M", "D", "E", "Q", "H", "TP", "GS", "N"],
        16: ["C", "K", "R", "W", "Y", "A", "FILV", "M", "D", "E", "Q", "H", "TP", "G", "S", "N"],
        17: ["C", "K", "R", "W", "Y", "A", "FI", "LV", "M", "D", "E", "Q", "H", "TP", "G", "S", "N"],
        18: ["C", "K", "R", "W", "Y", "A", "FI", "LV", "M", "D", "E", "Q", "H", "T", "P", "G", "S", "N"],
        19: ["C", "K", "R", "W", "Y", "A", "F", "I", "LV", "M", "D", "E", "Q", "H", "T", "P", "G", "S", "N"],
        20: ["C", "K", "R", "W", "Y", "A", "F", "I", "L", "V", "M", "D", "E", "Q", "H", "T", "P", "G", "S", "N"]
    }
    return aa_groups


def type_8():
    aa_groups = {
        2: ["ADEGKNPQRST", "CFHILMVWY"],
        3: ["ADEGNPST", "CHKQRW", "FILMVY"],
        4: ["AGNPST", "CHWY", "DEKQR", "FILMV"],
        5: ["AGPST", "CFWY", "DEN", "HKQR", "ILMV"],
        6: ["APST", "CW", "DEGN", "FHY", "ILMV", "KQR"],
        7: ["AGST", "CW", "DEN", "FY", "HP", "ILMV", "KQR"],
        8: ["AST", "CG", "DEN", "FY", "HP", "ILV", "KQR", "MW"],
        9: ["AST", "CW", "DE", "FY", "GN", "HQ", "ILV", "KR", "MP"],
        10: ["AST", "CW", "DE", "FY", "GN", "HQ", "IV", "KR", "LM", "P"],
        11: ["AST", "C", "DE", "FY", "GN", "HQ", "IV", "KR", "LM", "P", "W"],
        12: ["AST", "C", "DE", "FY", "G", "HQ", "IV", "KR", "LM", "N", "P", "W"],
        13: ["AST", "C", "DE", "FY", "G", "H", "IV", "KR", "LM", "N", "P", "Q", "W"],
        14: ["AST", "C", "DE", "FL", "G", "H", "IV", "KR", "M", "N", "P", "Q", "W", "Y"],
        15: ["AST", "C", "DE", "F", "G", "H", "IV", "KR", "L", "M", "N", "P", "Q", "W", "Y"],
        16: ["AT", "C", "DE", "F", "G", "H", "IV", "KR", "L", "M", "N", "P", "Q", "S", "W", "Y"],
        17: ["AT", "C", "DE", "F", "G", "H", "IV", "K", "L", "M", "N", "P", "Q", "R", "S", "W", "Y"],
        18: ["A", "C", "DE", "F", "G", "H", "IV", "K", "L", "M", "N", "P", "Q", "R", "S", "T", "W", "Y"],
        19: ["A", "C", "D", "E", "F", "G", "H", "IV", "K", "L", "M", "N", "P", "Q", "R", "S", "T", "W", "Y"],
        20: ["A", "C", "D", "E", "F", "G", "H", "I", "V", "K", "L", "M", "N", "P", "Q", "R", "S", "T", "W", "Y"]
    }
    return aa_groups


def type_9():
    aa_groups = {
        2: ["ACDEFGHILMNPQRSTVWY", "K"],
        3: ["ACDFGMPQRSTW", "EHILNVY", "K"],
        4: ["AGPT", "CDFMQRSW", "EHILNVY", "K"],
        5: ["AGPT", "CDQ", "EHILNVY", "FMRSW", "K"],
        6: ["AG", "CDQ", "EHILNVY", "FMRSW", "K", "PT"],
        7: ["AG", "CDQ", "EHNY", "FMRSW", "ILV", "K", "PT"],
        8: ["AG", "C", "DQ", "EHNY", "FMRSW", "ILV", "K", "PT"],
        9: ["AG", "C", "DQ", "EHNY", "FMW", "ILV", "K", "PT", "RS"],
        10: ["A", "C", "DQ", "EHNY", "FMW", "G", "ILV", "K", "PT", "RS"],
        11: ["A", "C", "DQ", "EHNY", "FM", "G", "ILV", "K", "PT", "RS", "W"],
        12: ["A", "C", "DQ", "EHNY", "FM", "G", "IL", "K", "PT", "RS", "V", "W"],
        13: ["A", "C", "DQ", "E", "FM", "G", "HNY", "IL", "K", "PT", "RS", "V", "W"],
        14: ["A", "C", "D", "E", "FM", "G", "HNY", "IL", "K", "PT", "Q", "RS", "V", "W"],
        15: ["A", "C", "D", "E", "FM", "G", "HNY", "IL", "K", "PT", "Q", "R", "S", "V", "W"],
        16: ["A", "C", "D", "E", "F", "G", "HNY", "IL", "K", "M", "PT", "Q", "R", "S", "V", "W"],
        17: ["A", "C", "D", "E", "F", "G", "HNY", "IL", "K", "M", "P", "Q", "R", "S", "T", "V", "W"],
        18: ["A", "C", "D", "E", "F", "G", "HNY", "I", "K", "L", "M", "P", "Q", "R", "S", "T", "V", "W"],
        19: ["A", "C", "D", "E", "F", "G", "HN", "I", "K", "L", "M", "P", "Q", "R", "S", "T", "V", "W", "Y"],
        20: ["A", "C", "D", "E", "F", "G", "H", "N", "I", "K", "L", "M", "P", "Q", "R", "S", "T", "V", "W", "Y"]
    }
    return aa_groups


def type_10():
    aa_groups = {
        2: ["CMFILVWY", "AGTSNQDEHRKP"],
        3: ["CMFILVWY", "AGTSP", "NQDEHRK"],
        4: ["CMFWY", "ILV", "AGTS", "NQDEHRKP"],
        5: ["FWYH", "MILV", "CATSP", "G", "NQDERK"],
        6: ["FWYH", "MILV", "CATS", "P", "G", "NQDERK"],
        7: ["FWYH", "MILV", "CATS", "P", "G", "NQDE", "RK"],
        8: ["FWYH", "MILV", "CA", "NTS", "P", "G", "DE", "QRK"],
        9: ["FWYH", "ML", "IV", "CA", "NTS", "P", "G", "DE", "QRK"],
        10: ["FWY", "ML", "IV", "CA", "TS", "NH", "P", "G", "DE", "QRK"],
        11: ["FWY", "ML", "IV", "CA", "TS", "NH", "P", "G", "D", "QE", "RK"],
        12: ["FWY", "ML", "IV", "C", "A", "TS", "NH", "P", "G", "D", "QE", "RK"],
        13: ["FWY", "ML", "IV", "C", "A", "T", "S", "NH", "P", "G", "D", "QE", "RK"],
        14: ["FWY", "ML", "IV", "C", "A", "T", "S", "NH", "P", "G", "D", "QE", "R", "K"],
        15: ["FWY", "ML", "IV", "C", "A", "T", "S", "N", "H", "P", "G", "D", "QE", "R", "K"],
        16: ["W", "FY", "ML", "IV", "C", "A", "T", "S", "N", "H", "P", "G", "D", "QE", "R", "K"],
        17: ["W", "FY", "ML", "IV", "C", "A", "T", "S", "N", "H", "P", "G", "D", "Q", "E", "R", "K"],
        18: ["W", "FY", "M", "L", "IV", "C", "A", "T", "S", "N", "H", "P", "G", "D", "Q", "E", "R", "K"],
        19: ["W", "F", "Y", "M", "L", "IV", "C", "A", "T", "S", "N", "H", "P", "G", "D", "Q", "E", "R", "K"],
        20: ["W", "F", "Y", "M", "L", "I", "V", "C", "A", "T", "S", "N", "H", "P", "G", "D", "Q", "E", "R", "K"]
    }
    return aa_groups


def type_11():
    aa_groups = {
        2: ["CFYWMLIV", "GPATSNHQEDRK"],
        3: ["CFYWMLIV", "GPATS", "NHQEDRK"],
        4: ["CFYW", "MLIV", "GPATS", "NHQEDRK"],
        5: ["CFYW", "MLIV", "G", "PATS", "NHQEDRK"],
        6: ["CFYW", "MLIV", "G", "P", "ATS", "NHQEDRK"],
        7: ["CFYW", "MLIV", "G", "P", "ATS", "NHQED", "RK"],
        8: ["CFYW", "MLIV", "G", "P", "ATS", "NH", "QED", "RK"],
        9: ["CFYW", "ML", "IV", "G", "P", "ATS", "NH", "QED", "RK"],
        10: ["C", "FYW", "ML", "IV", "G", "P", "ATS", "NH", "QED", "RK"],
        11: ["C", "FYW", "ML", "IV", "G", "P", "A", "TS", "NH", "QED", "RK"],
        12: ["C", "FYW", "ML", "IV", "G", "P", "A", "TS", "NH", "QE", "D", "RK"],
        13: ["C", "FYW", "ML", "IV", "G", "P", "A", "T", "S", "NH", "QE", "D", "RK"],
        14: ["C", "FYW", "ML", "IV", "G", "P", "A", "T", "S", "N", "H", "QE", "D", "RK"],
        15: ["C", "FYW", "ML", "IV", "G", "P", "A", "T", "S", "N", "H", "QE", "D", "R", "K"],
        16: ["C", "FY", "W", "ML", "IV", "G", "P", "A", "T", "S", "N", "H", "QE", "D", "R", "K"],
        17: ["C", "FY", "W", "ML", "IV", "G", "P", "A", "T", "S", "N", "H", "Q", "E", "D", "R", "K"],
        18: ["C", "FY", "W", "M", "L", "IV", "G", "P", "A", "T", "S", "N", "H", "Q", "E", "D", "R", "K"],
        19: ["C", "F", "Y", "W", "M", "L", "IV", "G", "P", "A", "T", "S", "N", "H", "Q", "E", "D", "R", "K"],
        20: ["C", "F", "Y", "W", "M", "L", "I", "V", "G", "P", "A", "T", "S", "N", "H", "Q", "E", "D", "R", "K"]
    }
    return aa_groups


def type_12():
    aa_groups = {
        2: ["IVMLFWYC", "ARNDQEGHKPST"],
        3: ["IVLMFWC", "YA", "RNDQEGHKPST"],
        4: ["IVLMFW", "C", "YA", "RNDQEGHKPST"],
        5: ["IVLMFW", "C", "YA", "G", "RNDQEHKPST"],
        6: ["IVLMF", "WY", "C", "AH", "G", "RNDQEKPST"],
        7: ["IVLMF", "WY", "C", "AH", "GP", "R", "NDQEKST"],
        8: ["IVLMF", "WY", "C", "A", "G", "R", "Q", "NDEHKPST"],
        9: ["IVLMF", "WY", "C", "A", "G", "P", "H", "K", "RNDQEST"],
        10: ["IVLM", "F", "W", "Y", "C", "A", "H", "G", "RN", "DQEKPST"],
        11: ["IVLMF", "W", "Y", "C", "A", "H", "G", "R", "N", "Q", "DEKPST"],
        12: ["IVLM", "F", "W", "Y", "C", "A", "H", "G", "N", "Q", "T", "RDEKPS"],
        13: ["IVLM", "F", "W", "Y", "C", "A", "H", "G", "N", "Q", "P", "R", "DEKST"],
        14: ["IVLM", "F", "W", "Y", "C", "A", "H", "G", "N", "Q", "P", "R", "K", "DEST"],
        15: ["IVLM", "F", "W", "Y", "C", "A", "H", "G", "N", "Q", "P", "R", "K", "D", "EST"],
        16: ["IVLM", "F", "W", "Y", "C", "A", "H", "G", "N", "Q", "P", "R", "K", "S", "T", "DE"],
        17: ["IVL", "M", "F", "W", "Y", "C", "A", "H", "G", "N", "Q", "P", "R", "K", "S", "T", "DE"],
        18: ["IVL", "M", "F", "W", "Y", "C", "A", "H", "G", "N", "Q", "P", "R", "K", "S", "T", "D", "E"],
        20: ["I", "V", "L", "M", "F", "W", "Y", "C", "A", "H", "G", "N", "Q", "P", "R", "K", "S", "T", "D", "E"]
    }
    return aa_groups


def type_13():
    aa_groups = {
        4: ["ADKERNTSQ", "YFLIVMCWH", "G", "P"],
        12: ["A", "D", "KER", "N", "TSQ", "YF", "LIVM", "C", "W", "H", "G", "P"],
        17: ["A", "D", "KE", "R", "N", "T", "S", "Q", "Y", "F", "LIV", "M", "C", "W", "H", "G", "P"],
        20: ["A", "D", "K", "E", "R", "N", "T", "S", "Q", "Y", "F", "L", "I", "V", "M", "C", "W", "H", "G", "P"]
    }
    return aa_groups


def type_14():
    aa_groups = {
        2: ["ARNDCQEGHKPST", "ILMFWYV"],
        3: ["ARNDQEGHKPST", "C", "ILMFWYV"],
        4: ["ARNDQEGHKPST", "C", "ILMFYV", "W"],
        5: ["AGPST", "RNDQEHK", "C", "ILMFYV", "W"],
        6: ["AGPST", "RNDQEK", "C", "H", "ILMFYV", "W"],
        7: ["ANDGST", "RQEK", "C", "H", "ILMFYV", "P", "W"],
        8: ["ANDGST", "RQEK", "C", "H", "ILMV", "FY", "P", "W"],
        9: ["AGST", "RQEK", "ND", "C", "H", "ILMV", "FY", "P", "W"],
        10: ["AGST", "RK", "ND", "C", "QE", "H", "ILMV", "FY", "P", "W"],
        11: ["AST", "RK", "ND", "C", "QE", "G", "H", "ILMV", "FY", "P", "W"],
        12: ["AST", "RK", "ND", "C", "QE", "G", "H", "IV", "LM", "FY", "P", "W"],
        13: ["AST", "RK", "N", "D", "C", "QE", "G", "H", "IV", "LM", "FY", "P", "W"],
        14: ["AST", "RK", "N", "D", "C", "Q", "E", "G", "H", "IV", "LM", "FY", "P", "W"],
        15: ["A", "RK", "N", "D", "C", "Q", "E", "G", "H", "IV", "LM", "FY", "P", "ST", "W"],
        16: ["A", "RK", "N", "D", "C", "Q", "E", "G", "H", "IV", "LM", "F", "P", "ST", "W", "Y"],
        17: ["A", "R", "N", "D", "C", "Q", "E", "G", "H", "IV", "LM", "K", "F", "P", "ST", "W", "Y"],
        18: ["A", "R", "N", "D", "C", "Q", "E", "G", "H", "IV", "LM", "K", "F", "P", "S", "T", "W", "Y"],
        19: ["A", "R", "N", "D", "C", "Q", "E", "G", "H", "IV", "L", "K", "M", "F", "P", "S", "T", "W", "Y"],
        20: ["A", "R", "N", "D", "C", "Q", "E", "G", "H", "I", "V", "L", "K", "M", "F", "P", "S", "T", "W", "Y"]
    }
    return aa_groups


def type_15():
    aa_groups = {
        2: ["MFILVAW", "CYQHPGTSNRKDE"],
        3: ["MFILVAW", "CYQHPGTSNRK", "DE"],
        4: ["MFILV", "ACW", "YQHPGTSNRK", "DE"],
        5: ["MFILV", "ACW", "YQHPGTSN", "RK", "DE"],
        6: ["MFILV", "A", "C", "WYQHPGTSN", "RK", "DE"],
        7: ["MFILV", "A", "C", "WYQHP", "GTSN", "RK", "DE"],
        8: ["MFILV", "A", "C", "WYQHP", "G", "TSN", "RK", "DE"],
        9: ["MF", "ILV", "A", "C", "WYQHP", "G", "TSN", "RK", "DE"],
        10: ["MF", "ILV", "A", "C", "WYQHP", "G", "TSN", "RK", "D", "E"],
        11: ["MF", "IL", "V", "A", "C", "WYQHP", "G", "TSN", "RK", "D", "E"],
        12: ["MF", "IL", "V", "A", "C", "WYQHP", "G", "TS", "N", "RK", "D", "E"],
        13: ["MF", "IL", "V", "A", "C", "WYQHP", "G", "T", "S", "N", "RK", "D", "E"],
        14: ["MF", "I", "L", "V", "A", "C", "WYQHP", "G", "T", "S", "N", "RK", "D", "E"],
        15: ["MF", "IL", "V", "A", "C", "WYQ", "H", "P", "G", "T", "S", "N", "RK", "D", "E"],
        16: ["MF", "I", "L", "V", "A", "C", "WYQ", "H", "P", "G", "T", "S", "N", "RK", "D", "E"],
        20: ["M", "F", "I", "L", "V", "A", "C", "W", "Y", "Q", "H", "P", "G", "T", "S", "N", "R", "K", "D", "E"]
    }
    return aa_groups


def type_16():
    aa_groups = {
        2: ["IMVLFWY", "GPCASTNHQEDRK"],
        3: ["IMVLFWY", "GPCAST", "NHQEDRK"],
        4: ["IMVLFWY", "G", "PCAST", "NHQEDRK"],
        5: ["IMVL", "FWY", "G", "PCAST", "NHQEDRK"],
        6: ["IMVL", "FWY", "G", "P", "CAST", "NHQEDRK"],
        7: ["IMVL", "FWY", "G", "P", "CAST", "NHQED", "RK"],
        8: ["IMV", "L", "FWY", "G", "P", "CAST", "NHQED", "RK"],
        9: ["IMV", "L", "FWY", "G", "P", "C", "AST", "NHQED", "RK"],
        10: ["IMV", "L", "FWY", "G", "P", "C", "A", "STNH", "RKQE", "D"],
        11: ["IMV", "L", "FWY", "G", "P", "C", "A", "STNH", "RKQ", "E", "D"],
        12: ["IMV", "L", "FWY", "G", "P", "C", "A", "ST", "N", "HRKQ", "E", "D"],
        13: ["IMV", "L", "F", "WY", "G", "P", "C", "A", "ST", "N", "HRKQ", "E", "D"],
        14: ["IMV", "L", "F", "WY", "G", "P", "C", "A", "S", "T", "N", "HRKQ", "E", "D"],
        15: ["IMV", "L", "F", "WY", "G", "P", "C", "A", "S", "T", "N", "H", "RKQ", "E", "D"],
        16: ["IMV", "L", "F", "W", "Y", "G", "P", "C", "A", "S", "T", "N", "H", "RKQ", "E", "D"],
        20: ["I", "M", "V", "L", "F", "W", "Y", "G", "P", "C", "A", "S", "T", "N", "H", "R", "K", "Q", "E", "D"]
    }
    return aa_groups
