from element import Pion
from random import randint
import copy
def make_configuration_from_file(file):
    lista_piese = []
    with open(file) as fisier:
        tabla = fisier.readlines()
    linie_e= 8
    for linie in tabla:
        coloana = 1
        for index in range(0,len(linie),2):
                if linie[index] =='1':
                    piesa = Pion(int(linie_e),int(coloana),'black')
                    lista_piese.append(piesa)
                if linie[index] =='2':
                    piesa = Pion(int(linie_e),int(coloana),'white')
                    lista_piese.append(piesa)
                coloana += 1
        linie_e -=1
    return lista_piese

def make_configuration_from_list(lista_pioni):
    tabla_noua = [[0]*8 for x in range(8)]
    for pion in lista_pioni:
        # print("linia {} coloana {}".format(pion.linie,pion.coloana))
        tabla_noua[pion.linie-1][pion.coloana-1]=pion.value
    return tabla_noua

def print_table(configuratie):
    for i in range(1,9):
        print(configuratie[8-i])


def minmax(current_depth,max_depth,current_player,new_lista_pioni,scor):
    if current_depth==max_depth:
        return scor,new_lista_pioni

    best_choice =(scor,new_lista_pioni)

    if current_player==1:
        culoare = "white"
    else:
        culoare ="black"

    generated_moves = generate_mutari(best_choice[1],culoare)
    for listuta in generated_moves:
        if current_player == 1:
            result = minmax(current_depth+1,max_depth,-current_player,listuta[1],listuta[0])
            if best_choice[0] > result[0]:
                best_choice = result
    # print("scor nou ", best_choice[0])
    return best_choice

def validate_move(pion,new_config,mutare):
    #index is out of range
    if (pion.linie and pion.coloana) not in range(0,8):
        return False
    #cannot move on top of another piece
    if mutare=="muta":
        if new_config[pion.linie-1][pion.coloana-1] != 0:
            return False
    #cannot eat another piece with the same value
    if mutare=="mananca":
        if new_config[pion.linie-1][pion.coloana -1] ==0:
            return False
        if new_config[pion.linie-1][pion.coloana-1] !=0 and new_config[pion.linie-1][pion.coloana-1]==pion.value:
            return False
    return True

def generate_mutari(lista_pioni,culoare):
    conf_list = []
    current_conf = make_configuration_from_list(lista_pioni)
    # print_table(current_conf)
    possible_moves_list = []
    for pion in lista_pioni:
        if pion.culoare == culoare:
            #incearca o mutare inainte
            pion2 = copy.copy(pion)
            new_list = copy.copy(lista_pioni)
            new_list.remove(pion)
            pion2.muta_inainte()

            if validate_move(pion2, current_conf, "muta") == True:
                new_list.append(pion2)
                # new_config = make_configuration_from_list(new_list)
                # print("putem muta de la linia {} col {} culoare {} ----> la linia {} coloana {} cul {} ".format(
                #     pion.linie - 1, pion.coloana - 1, pion.culoare, pion2.linie - 1, pion2.coloana - 1, pion2.culoare)
                # )
                # new_config = make_configuration_from_list(new_list)
                scor = 8-pion2.linie
                possible_moves_list.append((scor,new_list))

            #incearca o mancare la stanga
            pion2 = copy.copy(pion)
            new_list = copy.copy(lista_pioni)
            new_list.remove(pion)
            pion2.mananca_piese("left")

            if validate_move(pion2,current_conf,"mananca") == True:
                new_list.append(pion2)
                new_config = make_configuration_from_list(new_list)
                # print("putem muta de la linia {} col {} culoare {} ----> la linia {} coloana {} cul {} ".format(
                #     pion.linie-1,pion.coloana-1,pion.culoare,pion2.linie-1,pion2.coloana-1,pion2.culoare)
                # )
                # new_config = make_configuration_from_list(new_list)
                scor = (8-pion.linie)+5
                possible_moves_list.append((scor,new_list))

            #incearca o mancare la dreapta
            pion2 = copy.copy(pion)
            new_list = copy.copy(lista_pioni)
            new_list.remove(pion)
            pion2.mananca_piese("right")

            if validate_move(pion2, current_conf, "mananca") == True:
                new_list.append(pion2)
                new_config = make_configuration_from_list(new_list)
                # print("putem muta de la linia {} col {} culoare {} ----> la linia {} coloana {} cul {} ".format(
                #     pion.linie - 1, pion.coloana - 1, pion.culoare, pion2.linie - 1, pion2.coloana - 1,
                #     pion2.culoare)
                # )
                # new_config = make_configuration_from_list(new_list)
                scor = (8-pion.linie)+5
                possible_moves_list.append((scor,new_list))


    return possible_moves_list

def mutare(lista_pioni_1,mutare_initiala,culoare,current_player):
    lista_pioni = lista_pioni_1[:]
    if mutare_initiala is True:
        print("initial, albele muta primele")
        pion_1= randint(1,9)
        pion_2 = randint(1,9)
        while pion_2 == pion_1:
            pion_2 = randint(0,8)
        print("am ales piesele {} si {} pentru mutare".format(pion_1,pion_2))
        tabla_1 = make_configuration_from_list(lista_pioni)
        print("tabla initiala ")
        print_table(tabla_1)
        lista_pioni[pion_1].muta_inainte()
        lista_pioni[pion_2].muta_inainte()
        tabla_1 = make_configuration_from_list(lista_pioni)
        print("tabla dupa prima mutare ")
        print_table(tabla_1)
    else:
        current_depth = 0
        max_depth = 3
        new_lista_pioni = copy.copy(lista_pioni_1)
        if culoare == "white":
            lista_after_move = minmax(current_depth,max_depth,current_player,new_lista_pioni,0)
            new_cf = make_configuration_from_list(lista_after_move[1])
            print_table(new_cf)
    # return posibile

f = "configuratie_initiala.txt"
lista_p = make_configuration_from_file(f)

lista_n = make_configuration_from_list(lista_p)
w = mutare(lista_p,False,'white',1)
