class Pion:

    def __init__(self,linie,coloana,culoare):
        self.linie = int(linie)
        self.coloana = int(coloana)
        self.culoare = culoare
        if culoare =='white':
            self.value = 2
        elif culoare =='black':
            self.value = 1

    def muta_inainte(self):
        if self.culoare=='white':
            self.linie +=1
        elif self.culoare=='black':
            self.linie -=1

    def mananca_piese(self,directie):
        if self.culoare=='white':
            if directie=='left':
                self.linie += 1
                self.coloana -=1
            elif directie == 'right':
                self.linie +=1
                self.coloana +=1
        elif self.culoare == 'black':
            if directie == 'left':
                self.linie -=1
                self.coloana -=1
            elif directie == 'right':
                self.linie -=1
                self.coloana +=1
