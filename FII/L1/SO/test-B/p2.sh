#!/bin/bash

#######################################################################################################
# Enunt a doua problema:
#
# Sa se scrie comanda inlantuita care afiseaza numele de grup si GID-urile celor 5 grupuri de utilizatori
# din /etc/group care au cel mai mic GID, sortate in ordine crescatoare (numeric) dupa GID.
#
# NOTA: pastrati enuntul in acest comentariu si scrieti rezolvarea mai jos.
#######################################################################################################


cut /etc/group -d : -f 1,3 --output-delimiter " " | sort -n -k 2 | head -n 5

