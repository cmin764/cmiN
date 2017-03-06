(deffacts studenti
    (STUDENT Ionel IA 10 PBR 9)
    (STUDENT Gigel IA 4)
    (LISTA 1 5 3 8)
)


(defrule show-name
    (STUDENT Gigel $?x)
    =>
    (printout t $?x crlf)
)

(defrule parcurgere
    (LISTA $? ?x $?)
    =>
    (printout t ?x crlf)
)

(defrule note-pbr
    ?a <- (STUDENT ?x $?y)
    (not (STUDENT ?x $? PBR $?))
    =>
    (printout t "Nota PBR pentru : " ?x crlf)
    (retract ?a)
    (assert (STUDENT ?x $?y PBR (read)))
)
