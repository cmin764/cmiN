(deffacts fapte
    (minge rosie)
    (minge mare)
)

(defrule regula1
    (minge rosie)
    (minge mare)
    =>
    (assert (minge frumoasa))
)

(defrule regula2
    (minge rosie)
    =>
    (assert (suficient))
)
