(deftemplate fz-brakes
2 10 (
    (quick (2 1) (6 0))
    (normal (2 0) (6 1) (10 0))
    (slow (6 0) (10 1))
))

(deftemplate fz-cooling
50 150 (
    (under (50 1) (90 0))
    (normal (50 0) (90 1) (120 0))
    (over (90 0) (120 1) (150 1))
))

(deftemplate fz-gauge
0 5 (
    (damaged (0 1) (1 1) (3 0))
    (ok (2 0) (4 1) (5 1))
))

(deftemplate fz-temp
50 150 (
    (low (50 1) (90 0))
    (normal (50 0) (90 1) (120 0))
    (high (90 0) (120 1) (150 1))
))


(deftemplate auto
    (slot name)
    (slot brakes (type FUZZY-VALUE fz-brakes))
    (slot cooling (type FUZZY-VALUE fz-cooling))
    (slot gauge (type FUZZY-VALUE fz-gauge))
    (slot temp (type FUZZY-VALUE fz-temp))
)

(deffacts autos
    (auto 
        (name Mazda)
        (brakes (8 0) (9 1) (10 0))
        (cooling (79 0) (80 1) (81 0))
        (gauge (3 0) (4 1) (5 0))
        (temp (79 0) (80 1) (81 0))
    )
)


(defrule slow-brakes
    (declare (CF 0.8))
    (auto (name ?n) (brakes slow))
    =>
    (printout t ?n ": Stop the car! (slow brakes)" crlf)
)

(defrule overheat
    (declare (CF 0.8))
    (auto (name ?n) (cooling over))
    =>
    (printout t ?n ": Stop the car! (overheat)" crlf)
)

(defrule detect-overheat
    (declare (CF 0.8))
    ?a <- (auto (name ?n) (gauge ok) (temp high))
    =>
    (printout t ?n ": Stop the car! (detected overheat)" crlf)
    ; (modify ?a (cooling (129 0) (130 1) (131 0)))
)
