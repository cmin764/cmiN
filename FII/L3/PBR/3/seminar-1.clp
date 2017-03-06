(deffacts studenti
    (STUDENT Ionel IA 10 PBR 9)
    (STUDENT Gigel IA 4)
)

(defrule show-names
    (STUDENT ?x IA ? PBR ?)
    =>
    (printout t "Nume student: " ?x crlf)
)
