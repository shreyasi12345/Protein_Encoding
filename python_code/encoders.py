from typing import List, Dict, Tuple
from collections import defaultdict
from array import array
from io import TextIOBase
import math
import numpy as np


# Secondary Structure Elements Binary (SSEB)
def SSEB(seq, seqName, allowed, keys, file, types, type):
    encoded = []
    k=[]
    K = []
    aas = ""
    elements = ""
    # Read PSSM file
    # lines = file.readlines()[1:]  # Skip the first line
    if type == "ss2":
        lines = file.readlines()[2:]  # Skip the second line if .ss2

    for line in lines:
        counter = 0
        for word in line.split()[1:]:
            counter += 1
            if counter == 1:
                exists = False
                for c in allowed:
                    if word == c:
                        exists = True
                        k.append(word)

                        break
                if not exists:
                    break
                aas += word
            elif counter == 2:
                elements += word
                break

    found = aas.find(seq)
    # found = seq.index(''.join(aas))
    if found == -1:
        print("Error: Sequence", seqName, "not found in the file.")
    else:
        l = len(seq)
        for i in range(found, found + l):
            c = elements[i]
            K.append(c)

            if c in types:
                vals = types[c]
                encoded.extend(vals)
            else:
                encoded.extend([0.0, 0.0, 0.0])

    pair_C, pair_H , pair_E = [], [] , []
    for cnt in range(len(K)):
        if K[cnt] == 'C':
            pair_C.append(k[cnt])
        elif K[cnt] == 'H':
            pair_H.append(k[cnt])
        elif K[cnt] == 'E':
            pair_E.append(k[cnt])

    C = set(pair_C)
    H = set(pair_H)
    E = set(pair_E)

    print('for C :' , C)
    print('for E :' , E)
    print('for H :', H)
    print("*"*8)


    '''    
    pair = []
    for cnt in range(len(K)):
        if K[cnt] == 'C':
            pair.append((k[cnt] , K[cnt]))
        
    print("before" , len(pair))
    pairs = set(pair)
    print("after", len(pairs))
    for p in pair:
        print(p)

    import pandas as pd

    df = pd.DataFrame(pairs, columns=['Acid', 'Strutucre'])

    # Specify the filename for the Excel file
    import random

    inte = random.randint(1,100)


    # Constructing the CSV filename
    csv_file = f'pairs{inte}.csv'

    # Exporting DataFrame to CSV
    df.to_csv(csv_file, index=False)
    '''
    return encoded


# Secondary structure Elements Content
def SSEC(seq, seqName, allowed, keys, file, types, type):
    encoded = []

    aas = ""
    elements = ""
    # Read PSSM file
    # file.readline()  # Skip the first line
    if type == "ss2":
        lines = file.readlines()[2:]  # Skip the second line if .ss2

    types_count = defaultdict(int)
    for c in types:
        types_count[c] = 0

    for line in lines:
        counter = 0
        for word in line.split()[1:]:
            counter += 1
            if counter == 1:
                exists = False
                for ch in allowed:
                    if word == ch:
                        exists = True
                        break
                if not exists:
                    break
                aas += word
            elif counter == 2:
                elements += word
                break

    found = aas.find(seq)
    if found == -1:
        print("Error: Sequence", seqName, "not found in the file.")
    else:
        l = len(seq)
        for i in range(found, found + l):
            c = elements[i]
            if c in types_count:
                types_count[c] += 1
        for c in types:
            encoded.append(types_count[c] / l)
    print(types_count)

    return encoded


# Secondary Structure Probabilities Bigram(SSBP)
def SSPB(seq, seqName, allowed, keys, file, types, type, n):
    encoded = []
    # lines=[]
    aas = ""
    probs = defaultdict(list)

    # Read PSSM file
    # file.readline()  # Skip the first line
    if type == "ss2":
        lines = file.readlines()[2:]  # Skip the second line if .ss2

    count = defaultdict(float)
    for key in keys:
        count[key] = 0.0

    for line in lines:
        counter = 0
        for word in line.split()[1:]:
            counter += 1
            if counter == 1:
                exists = False
                for c in allowed:
                    if word == c:
                        exists = True
                        break
                if not exists:
                    break
                aas += word
            elif (counter == 3 and type == "ss2") or (counter == 11 and type == "spd33") or (
                    counter == 7 and type == "spXout"):
                val = float(word)
                probs['H'].append(val)
            elif (counter == 4 and type == "ss2") or (counter == 12 and type == "spd33") or (
                    counter == 5 and type == "spXout"):
                val = float(word)
                probs['E'].append(val)
            elif (counter == 5 and type == "ss2") or (counter == 10 and type == "spd33") or (
                    counter == 6 and type == "spXout"):
                val = float(word)
                probs['C'].append(val)

    found = aas.find(seq)
    if found == -1:
        print("Error: Sequence", seqName, "not found in the file.")
    else:
        l = len(seq)
        for c in types:
            for d in types:
                key = c + d
                for i in range(found, found + l - n):
                    count[key] += probs[c][i] * probs[d][i + n]
                    print(key, probs[c][i], probs[d][i + n])
                print(f'combinations\t {key} with value \t {count[key]}')

        for key in keys:
            encoded.append(count[key])

    return encoded


# Secondary Structure Probabilities Auto-Covariance(SSPAC)
def SSPAC(seq, seqName, allowed, keys, file, types, type, n):
    encoded = []

    aas = ""
    probs = defaultdict(list)

    # Read PSSM file
    # file.readline()  # Skip the first line
    if type == "ss2":
        lines = file.readlines()[2:]  # Skip the second line if .ss2

    count = defaultdict(float)
    for key in keys:
        count[key] = 0.0

    for line in lines:
        counter = 0
        for word in line.split()[1:]:
            counter += 1
            if counter == 1:
                exists = False
                for c in allowed:
                    if word == c:
                        exists = True
                        break
                if not exists:
                    break
                aas += word
            elif (counter == 3 and type == "ss2") or (counter == 11 and type == "spd33") or (
                    counter == 7 and type == "spXout"):
                val = float(word)
                probs['H'].append(val)
            elif (counter == 4 and type == "ss2") or (counter == 12 and type == "spd33") or (
                    counter == 5 and type == "spXout"):
                val = float(word)
                probs['E'].append(val)
            elif (counter == 5 and type == "ss2") or (counter == 10 and type == "spd33") or (
                    counter == 6 and type == "spXout"):
                val = float(word)
                probs['C'].append(val)

    found = aas.find(seq)
    if found == -1:
        print("Error: Sequence", seqName, "not found in the file.")
    else:
        l = len(seq)
        for i in range(1, n + 1):
            for c in types:
                key = str(i) + c
                for j in range(found, found + l - i):
                    count[key] += probs[c][j] * probs[c][j + i]
                    # print(key,probs[c][j], probs[c][j + 1])
                print(f'combinations\t {key} with value \t {count[key] / l}')

        for key in keys:
            encoded.append(count[key] / l)

    return encoded


# Disorder
def Disorder(seq, seqName, allowed, keys, file, types, type):
    encoded = []

    # Read disorder file
    line = file.readline().strip()
    while line[0] != '>':
        line = file.readline().strip()
    for _ in range(3):
        line = file.readline().strip()

    scores = line.split(',')

    for score in scores:
        val = float(score)
        encoded.append(val)

    return encoded


# Disorder Content
def DisorderC(seq, seqName, allowed, keys, file, types, type):
    encoded = []

    # Read disorder file
    line = file.readline().strip()
    while line[0] != '>':
        line = file.readline().strip()
    for _ in range(2):
        line = file.readline().strip()

    types = line.split(',')

    l = len(seq)
    order = 0
    disorder = 0
    for type in types:
        if type == '1':
            disorder += 1
        else:
            order += 1
    encoded.append(disorder / l)
    encoded.append(order / l)

    return encoded


# Disorder Binary
def DisorderB(seq, seqName, allowed, keys, file, types, type):
    encoded = []

    # Read disorder file
    line = file.readline().strip()
    while line[0] != '>':
        line = file.readline().strip()
    for _ in range(2):
        line = file.readline().strip()

    types = line.split(',')

    for type in types:
        if type == '1':
            encoded.extend([0.0, 1.0])
        else:
            encoded.extend([1.0, 0.0])

    return encoded


# Torsional Angles (TA)
def TA(seq, seqName, allowed, keys, file, type):
    encoded = []
    # counter=0
    aas = ""
    phis = []
    psis = []
    for line in file.readlines()[1:]:
        parts = line.strip().split()
        for counter, part in enumerate(parts):
            if counter == 1:
                if part not in allowed:
                    break
                aas += part
            elif (type == "spd33" and counter == 4) or (type == "spXout" and counter == 3):
                val = float(part)
                phis.append(val)
            elif (type == "spd33" and counter == 5) or (type == "spXout" and counter == 4):
                val = float(part)
                psis.append(val)
                break

    found = aas.find(seq)
    if found == -1:
        print(f"Error: Sequence {seqName} not found in the file.")
    else:
        l = len(seq)
        for i in range(found, found + l):
            encoded.append(phis[i])
            encoded.append(psis[i])

    return encoded


# Torsional Angles Composition
def TAC(seq, seqName, allowed, keys, file, type):
    encoded = []
    pi = 3.14159265359

    phiSin = []
    phiCos = []
    psiSin = []
    psiCos = []
    aas = ""
    for line in file:
        parts = line.strip().split()
        if len(parts) > 1:
            counter = 0
            for part in parts:
                counter += 1
                if counter == 2:
                    if part not in allowed:
                        break
                    aas += part
                elif (type == "spd33" and counter == 5) or (type == "spXout" and counter == 4):
                    val = float(part) * (pi / 180)
                    phiSin.append(math.sin(val))
                    phiCos.append(math.cos(val))
                elif (type == "spd33" and counter == 6) or (type == "spXout" and counter == 5):
                    val = float(part) * (pi / 180)
                    psiSin.append(math.sin(val))
                    psiCos.append(math.cos(val))
                    break

    found = aas.find(seq)
    if found == -1:
        print(f"Error: Sequence {seqName} not found in the file.")
    else:
        l = len(seq)
        phiSinVal = np.sum(phiSin[found:found + l])
        phiCosVal = np.sum(phiCos[found:found + l])
        psiSinVal = np.sum(psiSin[found:found + l])
        psiCosVal = np.sum(psiCos[found:found + l])

        encoded.append(phiSinVal / l)
        encoded.append(phiCosVal / l)
        encoded.append(psiSinVal / l)
        encoded.append(psiCosVal / l)

    return encoded


# Torsional Angles Bigram(TAB)
def TAB(seq, seqName, allowed, keys, n, file, type):
    encoded = []
    pi = 3.14159265359

    line = file.readline()
    aas = ""
    phiSin = []
    phiCos = []
    psiSin = []
    psiCos = []
    line = file.readline()
    while line:
        counter = 0
        iss = line.split()
        for line in iss:
            if counter == 1:
                exists = False
                for c in allowed:
                    if line[0] == c:
                        exists = True
                        break
                if not exists:
                    break
                aas += line[0]
            elif (type == "spd33" and counter == 4) or (type == "spXout" and counter == 3):
                val = float(line) * (pi / 180)
                phiSin.append(math.sin(val))
                phiCos.append(math.cos(val))
            elif (type == "spd33" and counter == 5) or (type == "spXout" and counter == 4):
                val = float(line) * (pi / 180)
                psiSin.append(math.sin(val))
                psiCos.append(math.cos(val))
                break
            counter += 1
        line = file.readline()

    found = aas.find(seq)
    if found == -1:
        print("Error: Sequence", seqName, "not found in the file.")
    else:
        values = {}
        l = len(seq)
        for i in range(found, found + l - n):
            values["phiSin-phiSin"] = phiSin[i] * phiSin[i + n]
            values["phiSin-phiCos"] = phiSin[i] * phiCos[i + n]
            values["phiSin-psiSin"] = phiSin[i] * psiSin[i + n]
            values["phiSin-psiCos"] = phiSin[i] * psiCos[i + n]
            values["phiCos-phiCos"] = phiCos[i] * phiCos[i + n]
            values["phiCos-psiSin"] = phiCos[i] * psiSin[i + n]
            values["phiCos-psiCos"] = phiCos[i] * psiCos[i + n]
            values["psiSin-psiSin"] = psiSin[i] * psiSin[i + n]
            values["psiSin-psiCos"] = psiSin[i] * psiCos[i + n]
            values["psiCos-psiCos"] = psiCos[i] * psiCos[i + n]

        for key in keys:
            encoded.append(values[key] / l)

    return encoded


# Torsional Angles Autocovariance(TAAC)

def TAAC(seq, seqName, allowed, keys, n, file, type):
    encoded = []

    pi = 3.14159265359

    # Read torsion angle file
    lines = file.readlines()[1:]  # Skip first line
    aas = []
    phiSin = []
    phiCos = []
    psiSin = []
    psiCos = []
    for line in lines:
        counter = 0
        for word in line.split()[1:]:
            counter += 1
            if counter == 1:
                exists = False
                for c in allowed:
                    if word == c:
                        exists = True
                        break
                if not exists:
                    break
                aas.append(word)
            elif (type == "spd33" and counter == 4) or (type == "spXout" and counter == 3):
                val = float(word) * (pi / 180)
                phiSin.append(math.sin(val))
                phiCos.append(math.cos(val))
            elif (type == "spd33" and counter == 5) or (type == "spXout" and counter == 4):
                val = float(word) * (pi / 180)
                psiSin.append(math.sin(val))
                psiCos.append(math.cos(val))
                break

    found = seq.index(''.join(aas))
    if found == -1:
        print("Error: Sequence", seqName, "not found in the file.")
    else:
        values = {}
        l = len(seq)
        for i in range(1, n + 1):
            iString = str(i)
            for j in range(found, found + l - i):
                values[iString + "-phiSin"] = phiSin[j] * phiSin[j + i]
                values[iString + "-phiCos"] = phiCos[j] * phiCos[j + i]
                values[iString + "-psiSin"] = psiSin[j] * psiSin[j + i]
                values[iString + "-psiCos"] = psiCos[j] * psiCos[j + i]

        for key in keys:
            encoded.append(values[key] / l)

    return encoded


# Accessible Surface Area(ASA)
def ASA(seq, seqName, allowed, keys, file, type):
    encoded = []

    # Read ASA file
    lines = file.readlines()[1:]  # Skip first line
    aas = []
    asas = []
    for line in lines:
        counter = 0
        for word in line.split()[1:]:
            counter += 1
            if counter == 1:
                exists = False
                for c in allowed:
                    if word == c:
                        exists = True
                        break
                if not exists:
                    break
                aas.append(word)
            elif (type == "spd33" and counter == 3) or (type == "spXout" and counter == 10):
                val = float(word)
                asas.append(val)
                break
        line = file.readline()

    found = seq in ''.join(aas)
    if not found:
        print("Error: Sequence", seqName, "not found in the file.")
    else:
        l = len(seq)
        for i, aa in enumerate(aas):
            if aa == seq[0]:
                break
        for j in range(i, i + l):
            encoded.append(asas[j] / l)

    return encoded


# Bigram PSSM(BiPSSM)
def BiPSSM(seq, seqName, keys, orderString, n, file):
    encoded = []
    aas = ""
    elements = []
    count = {}
    l = len(seq)
    for key in keys:
        count[key] = 0

    lines = file.readlines()[3:]
    for line in lines:
        newLine = [0] * 20
        counter = 0
        values = []
        iss = line.strip().split()[1:]
        for word in iss:
            counter += 1
            if counter == 1:
                exists = False
                for c in orderString:
                    if word == c:
                        exists = True
                        break
                if not exists:
                    break
                aas += word
            if counter >= 2:
                val = float(word)
                values.append(val)
            counter += 1
        else:
            elements.append(values)

    found = aas.find(seq)
    if found == -1:
        print("Error: Sequence", seqName, "not found in the file.")
    else:
        lines = 0
        l = len(seq)
        for i in range(found, found + l - n):
            for j in range(len(orderString)):
                c1 = orderString[j]
                for k in range(len(orderString)):
                    c2 = orderString[k]
                    key = c1 + c2
                    count[key] += elements[i][j] * elements[i + n][k]

    for key in keys:
        encoded.append(count[key] / (l - (n * 1.0)))

    return encoded


# PSSM Autocovariance (PSSMAC)
def PSSMAC(seq, seqName, keys, orderString, n, file):
    encoded = []
    aas = ""
    elements = []
    avg = {}
    count = {}
    l = len(seq)
    for c in orderString:
        avg[c] = 0
    for key in keys:
        count[key] = 0

    lines = file.readlines()[3:]
    for line in lines:
        newLine = [0] * 20
        counter = 0
        values = []
        iss = line.split()[1:]
        for word in iss:
            counter += 1
            if counter == 1:
                exists = False
                for c in orderString:
                    if word == c:
                        exists = True
                        break
                if not exists:
                    break
                aas += word
            if counter >= 2:
                val = float(word)
                values.append(val)
            counter += 1
        else:
            elements.append(values)

    found = aas.find(seq)
    if found == -1:
        print("Error: Sequence", seqName, "not found in the file.")
    else:
        for i in range(found, found + l):
            for j in range(len(orderString)):
                avg[orderString[j]] += elements[i][j]
        for c in orderString:
            avg[c] /= l
        for i in range(1, n + 1):
            for j in range(found, found + l - i):
                for k in range(20):
                    c = orderString[k]
                    key = str(i) + c
                    count[key] += ((elements[j][k] - avg[c]) * (elements[j + i][k] - avg[c]))
        for key in keys:
            encoded.append(count[key] / (l - (n * 1.0)))

    return encoded


# Pseudo PSSM(PPSM)
def PPSSM(seq, seqName, keys, orderString, n, file):
    encoded = []
    avg = []
    avgChar = {}
    aas = ""
    elements = []
    count = {}
    l = len(seq)

    for c in seq:
        avg.append(0)

    for c in orderString:
        avgChar[c] = 0

    for key in keys:
        count[key] = 0
    # SKIPPING THE FIRST 3 LINES
    lines = file.readlines()[3:]
    lineCount = 0
    for line in lines:
        newLine = [0] * 20
        counter = 0
        values = []
        iss = line.split()[1:]

        for word in iss:
            counter += 1
            if counter == 1:
                exists = False
                for c in orderString:
                    if word == c:
                        exists = True
                        break
                if not exists:
                    break
                aas += word

            if counter >= 2:
                val = float(word)
                values.append(val)

            counter += 1

        elements.append(values)
        line = file.readline()

    found = aas.find(seq)

    if found == -1:
        print("Error: Sequence", seqName, "not found in the file.")
    else:
        for i in range(found, found + l):
            for j in range(len(orderString)):
                avg[i] += elements[i][j]

        for i in range(found, found + l):
            avg[i] /= 20
            den = 0

            for val in elements[i]:
                den += (val - avg[i]) ** 2

            den = (den / 20) ** 0.5

            for j in range(20):
                elements[i][j] -= avg[i]
                elements[i][j] /= den
                key = orderString[j]
                count["S" + key] += elements[i][j]

                if i >= found + n:
                    count["R" + key] += (elements[i - n][j] - elements[i][j]) ** 2

        counter = 0

        for key in keys:
            if counter < 20:
                encoded.append(count[key] / l)
            else:
                encoded.append(count[key] / (l - n))

            counter += 1

    return encoded


# TVD
def TVD(seq, allowed, keys, tvd):
    print(seq)
    encoded = []
    l = len(seq)
    for c in seq:
        for val in tvd[c]:
            encoded.append(val)
    return encoded


def remove_disallowed(seq, allowed):
    allowed_set = set(allowed)
    seq[:] = [c for c in seq if c in allowed_set]


def check_fasta_same_length(seqs):
    length = len(seqs[0])
    for seq in seqs:
        if len(seq) != length:
            return -1
    return length


def get_min_sequence_length(names, seqs):
    min_len = len(seqs[0])
    min_index = 0
    for i in range(1, len(seqs)):
        curr_len = len(seqs[i])
        if curr_len < min_len:
            min_len = curr_len
            min_index = i
    print(f"The shortest sequence is {names[min_index]} - {seqs[min_index]} and has a length of {min_len}")
    return min_len
