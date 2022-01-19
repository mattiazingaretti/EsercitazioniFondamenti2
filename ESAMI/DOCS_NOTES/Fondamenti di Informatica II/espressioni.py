#a^n b^n c^n d^n

def abcd_n(n):
    espressione = 'aBCSd'
    base = 'abcd'
    inizio = 'aBCSd'
    if n == 1:
        print(base)
        return
    for i in range(n-2):
        espressione = espressione.replace('S', inizio)
    espressione = espressione.replace('S', base)

    while not espressione.islower():
        espressione = espressione.replace('Ca', 'aC')
        espressione = espressione.replace('Cb', 'bC')
        espressione = espressione.replace('Cc', 'cc')
        espressione = espressione.replace('Ba', 'aB')
        espressione = espressione.replace('Bb', 'bb')

    print(espressione, int(len(espressione)/4))

abcd_n(10)

def abc_n(n):
    espressione = 'aSBc'
    base = ''
    inizio = espressione
    if n == 0:
        print(base)
        return
    for i in range(n-1):
        espressione = espressione.replace('S', inizio)
    espressione = espressione.replace('S', base)
    i = 0
    while not espressione.islower() and i<20:
        espressione = espressione.replace('Bc', 'bc')
        i+=1
    print(espressione)
#abc_n(5)