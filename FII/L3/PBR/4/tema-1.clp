; Menu.


(deffacts menu
    (menu 1 Adauga un student)
    (menu 2 Adauga un examen)
    (menu 3 Adauga note student)
    (menu 4 Adauga note examen)
    (menu 5 Afisare informatii student)
    (menu 6 Afisare informatii examen)
    (menu 7 Cautare student dupa note)
    (menu 0 Iesire din sistem)

    (options -1 0 1 2 3 4 5 6)
    (inp -1)
)

(defrule 1-show-menu
    (menu $?x)
    (inp -1)
    =>
    (printout t ?x crlf)
)

(defrule 2-input
    ?a <- (inp -1)
    =>
    (printout t "Optiune: ")
    (retract ?a)
    (assert (inp (read)))
)


(defrule 3-check-option
    ?a <- (inp ?x)
    (not (options $? ?x $?))
    =>
    (printout t "Optiune invalida: " ?x crlf)
    (retract ?a)
    (assert (inp -1))
)


(defrule 4-show-option
    (disabled)
    (inp ?x)
    (not (inp -1))
    (menu ?x $?y)
    =>
    (printout t "Ai ales: " $?y crlf)
)


(defrule 5-exit
    ?a <- (inp 0)
    =>
    (retract ?a)
)


; Student.


(defrule 5-add-stud-name
    ?a <- (inp 1)
    =>
    (retract ?a)
    (assert (inp -1))

    (printout t "Nume student: ")
    (bind ?x (read))
    (assert (student name ?x))
)


(defrule 5-add-stud-marks
    ?a <- (inp 3)
    =>
    (retract ?a)
    (assert (inp -1))

    (printout t "Nume student: ")
    (bind ?x (read))
    (assert (update student ?x))
)


(defrule 6-add-stud-marks2
    ?a <- (update student ?x)
    (student name ?x)
    =>
    (retract ?a)

    (printout t "Note student " ?x ": ")
    (bind $?y (explode$ (readline)))
    (printout t "Student: " ?x " note: " $?y crlf)
    (assert (student marks ?x $?y))
)


(defrule 7-add-stud-marks2-bad
    ?a <- (update student ?x)
    (not (student name ?x))
    =>
    (retract ?a)

    (printout t "Nu exista studentul: " ?x crlf)
)


(defrule 5-show-stud
    ?a <- (inp 5)
    =>
    (retract ?a)
    (assert (inp -1))

    (printout t "Nume student: ")
    (bind ?x (read))
    (assert (show student ?x))
)


(defrule 6-show-stud2
    ?a <- (show student ?x)
    (student marks ?x $?y)
    =>
    (retract ?a)

    (printout t "Student: " ?x " note: " $?y crlf)
)


(defrule 7-show-stud2-bad
    ?a <- (show student ?x)
    (not (student marks ?x $?y))
    =>
    (retract ?a)

    (printout t "Student fara note: " ?x crlf)
)


; Exam.


(defrule 5-add-exam-name
    ?a <- (inp 2)
    =>
    (retract ?a)
    (assert (inp -1))

    (printout t "Nume examen: ")
    (bind ?x (read))
    (assert (exam name ?x))
)


(defrule 5-add-exam-marks
    ?a <- (inp 4)
    =>
    (retract ?a)
    (assert (inp -1))

    (printout t "Nume examen: ")
    (bind ?x (read))
    (assert (update exam ?x))
)


(defrule 6-add-exam-marks2
    ?a <- (update exam ?x)
    (exam name ?x)
    =>
    (retract ?a)

    (printout t "Note examen " ?x ": ")
    (bind $?y (explode$ (readline)))
    (printout t "Examen " ?x " note: " $?y crlf)
    (assert (exam marks ?x $?y))
)


(defrule 7-add-exam-marks2-bad
    ?a <- (update exam ?x)
    (not (exam name ?x))
    =>
    (retract ?a)

    (printout t "Nu exista examenul: " ?x crlf)
)


(defrule 5-show-exam
    ?a <- (inp 6)
    =>
    (retract ?a)
    (assert (inp -1))

    (printout t "Nume examen: ")
    (bind ?x (read))
    (assert (show exam ?x))
)


(defrule 6-show-exam2
    ?a <- (show exam ?x)
    (exam marks ?x $?y)
    =>
    (retract ?a)

    (printout t "Examen: " ?x " note: " $?y crlf)
)


(defrule 7-show-exam2-bad
    ?a <- (show exam ?x)
    (not (exam marks ?x $?y))
    =>
    (retract ?a)

    (printout t "Examen fara note: " ?x crlf)
)

; Cautare dupa nota.

(defrule 5-search-student
    ?a <- (inp 7)
    =>
    (retract ?a)
    (assert (inp -1))

    (printout t "Nota student: ")
    (bind ?x (read))
    (assert (search marks ?x))
)

(defrule 6-search-student2
    ?a <- (search marks ?x)
    (student marks ?y $? ?x $?)
    (search student ?)
    =>
    (retract ?a)

    (assert (search student ?x))
)
