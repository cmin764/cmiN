(deftemplate elem
    (slot index)
    (slot value)
)

(deffacts vector
    (elem (index 0) (value 4))
    (elem (index 1) (value 10))
    (elem (index 2) (value 3))
    (elem (index 3) (value 9))
    (elem (index 4) (value 6))
)

(defrule bubble-sort
    ?a <- (elem (index ?i1) (value ?v1))
    ?b <- (elem (index ?i2) (value ?v2))
    (test (= ?i2 (+ ?i1 1)))
    (test (< ?v2 ?v1))
    =>
    (modify ?a (value ?v2))
    (modify ?b (value ?v1))
    (printout t "swap: " ?v1 " - " ?v2 crlf)
)


(defrule 1-show
    (declare (salience -5))
    =>
    (printout t "Eelemente sortate: ")
)

(defrule 2-show
    (declare (salience -10))
    ?a <- (elem (index ?i1) (value ?v))
    (forall (elem (index ?i2)) (test (<= ?i1 ?i2)))
    =>
    (printout t ?v " ")
    (retract ?a)
)


(defrule 3-show
    (declare (salience -15))
    =>
    (printout t crlf)
)
