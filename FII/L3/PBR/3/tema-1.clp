(deffacts menu
    (menu 1 Adauga un student)
    (menu 2 Adauga un examen)
    (menu 3 Adauga note student)
    (menu 4 Adauga note examen)
    (menu 5 Afisare informatii student)
    (menu 6 Afisare informatii examen)
    (menu 0 Iesire din sistem)

    (options -1 0 1 2 3 4 5 6)
    (inp -1)
)

(defrule show-menu
    (menu $?x)
    (inp -1)
    =>
    (printout t ?x crlf)
)

(defrule input
    ?a <- (inp -1)
    =>
    (printout t "Optiune: ")
    (retract ?a)
    (assert (inp (read)))
)

(defrule show-option
    (inp ?x)
    (not (inp -1))
    (menu ?x $?y)
    =>
    (printout t "Ai ales: " $?y crlf)
)

(defrule check-option
    ?a <- (inp ?x)
    (not (options $? ?x $?))
    =>
    (printout t "Optiune invalida: " ?x crlf)
    (retract ?a)
    (assert (inp -1))
)

(defrule exit
    ?a <- (inp 0)
    =>
    (retract ?a)
)

(defrule add-stud
    ?a <- (inp 1)
    =>
    (retract ?a)
    (assert (inp -1))

    (printout t "Nume student: ")
    (bind ?x (read))
    (printout t "Note student: ")
    (bind $?y (explode$ (readline)))
    (printout t "Student: " ?x " note: " $?y)
)
