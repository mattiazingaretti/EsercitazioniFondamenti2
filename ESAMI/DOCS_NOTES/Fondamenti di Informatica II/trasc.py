f = open('trascr.txt').readlines()
f1 = open('t.txt', 'w')
stringa = ''
for riga in f:
    if ':' in riga:
        continue
    riga = riga.replace('\n', ' ')
    stringa += riga
f1.write(stringa)
